#include "Messenger.h"


Message::Message(u32 type, u32 msg):
    m_message(msg),
    m_id(0),
    m_type(type),
    m_sender(nullptr),
    m_forwarder(nullptr),
    m_ownsArguments(false)
{

}

Message::Message(u32 msg):
    m_message(msg),
    m_id(0),
    m_type(0),
    m_sender(nullptr),
    m_forwarder(nullptr),
    m_ownsArguments(false)
{

}

Message::Message(const Message &other) :
    m_message(other.m_message),
    m_id(other.m_id),
    m_type(other.m_type),
    m_sender(other.m_sender),
    m_forwarder(other.m_forwarder),
    m_ownsArguments(false)
{

}

Message &Message::operator=(const Message &other)
{
    if (this == &other)
        return *this;

    m_type = other.m_type;
    m_id = other.m_id;
    m_message = other.m_message;

    m_sender = other.m_sender;
    m_forwarder = other.m_forwarder;
    m_ownsArguments = other.m_ownsArguments;

    return *this;
}

bool Message::Is(u32 msg) const
{
    u32 mask = msg::Forward::MASK;
    return ((m_message & msg) & mask) == (msg & mask);
}

bool Message::IsFlag(u32 msg) const
{
    u32 mask = ~msg::Forward::MASK;
    return ((m_message & msg) & mask) == (msg & mask);
}

void Message::SetMessage(u32 msg)
{
    m_message = msg;
}

u32 Message::GetMessage() const
{
    return m_message;
}

u32 Message::GetType() const
{
    return m_type;
}

u32 Message::GetId() const
{
    return m_type;
}

Message &Message::SetId(u32 id)
{
    m_id = id;
    return *this;
}


void Message::SetMessageType(u32 msgType)
{
    m_type = msgType;
}

bool Message::HasMessageType() const
{
    return m_type > 0;
}

Message &Message::Set(const QString &name)
{
    return Set(name, 1);
}

Message &Message::Set(const QString &name, u32 val)
{
    if (!m_arguments || !m_ownsArguments)
    {
        if (m_arguments)
            m_arguments = std::make_shared<ArgumentsMap>(*m_arguments);
        else
            m_arguments = std::make_shared<ArgumentsMap>();

        m_ownsArguments = true;
    }

    m_arguments->insert(std::make_pair(name, val));
    return *this;
}

u32 Message::Get(const QString &name) const
{
    if (!m_arguments)
        return 0;

    ArgumentsMap::const_iterator it = m_arguments->find(name);
    if (it == m_arguments->end())
        return 0;
    return it->second;
}

bool Message::Has(const QString &name) const
{
    if (!m_arguments)
        return false;

    ArgumentsMap::const_iterator it = m_arguments->find(name);
    return it != m_arguments->end();
}


////////////////////////////////////////////////////////////////

ClaraMessengerMap* Messenger::s_registeredMessengers = nullptr;
u32 Messenger::s_blockedCount = 0;
u32 Messenger::s_sentCount = 0;
u32 Messenger::s_receivedCount = 0;
u32 Messenger::s_filteredCount = 0;
int Messenger::s_blockMessages = 0;

Messenger *Message::GetSender() const
{
    return m_sender;
}

void Message::SetSender(Messenger *messenger)
{
    m_sender = messenger;
}

Messenger *Message::GetForwarder() const
{
    return m_forwarder;
}

void Message::SetForwarder(Messenger *messenger)
{
    m_forwarder = messenger;
}

template<class T>
bool Message::IsFrom() const
{
    return GetType() == T::k_msgType;
}

Messenger::Messenger()
{
    m_searchForRemovedListeners = false;
}

Messenger::~Messenger()
{

}

void Messenger::BlockAllMessages(bool yes)
{
    s_blockMessages += yes ? 1 : -1;
}

void Messenger::BlockMessages(bool yes)
{
    m_blockMessages += yes ? 1 : -1;
}

void Messenger::Send(Message &msg)
{

    if (AreMessagesBlocked())
    {
        s_blockedCount++;
        return;
    }

    if (!m_listeners.get() && !s_registeredMessengers)
        return;

    Message m(msg);
    m.SetSender(this);

    s_sentCount++;

    m_searchForRemovedListeners = false;

    //send to listeners
    if (m_listeners.get())
    {
        // a message could modify the listeners list breaking the iterators, use a cloned list to iterate
        ClaraMessengerMap tmp = *m_listeners;
        ClaraMessengerMap::iterator it = tmp.begin();
        while (it != tmp.end())
        {
            ClaraMessengerMap::iterator next = it;
            next++;

            Messenger* msgr = it->first;
            const MessengerData& listenerData = it->second;
            // check if listener is still valid
            if (!m_searchForRemovedListeners || m_listeners->find(msgr) != m_listeners->end())
            {
                if (msg.GetSender() != msgr)
                {
                    if ((msg.GetType() & listenerData.typeMask) && (msg.GetMessage() & listenerData.messageMask))
                    {
                        s_receivedCount++;
                        msgr->OnMessageReceived(m);
                    }
                    else
                    {
                        s_filteredCount++;
                    }
                }
            }
            else
            {
                // listener has been erased
                //...
            }
            it = next;
        }
    }
}

inline u32 Messenger::GetSentCount()
{
    return s_sentCount;
}

void Messenger::ListenTo(const Messenger *other, u32 typeMask, u32 messageMask)
{
    if (!other)
        return;

    if (!m_listeningTo.get())
    {
        m_listeningTo.reset(new ClaraMessengerMap);
    }

    MessengerData data;
    //data.messenger = (Messenger*)other;
    data.typeMask = typeMask;
    data.messageMask = (messageMask & msg::Forward::MASK); //exclude the forward mask

    //ClaraMessengerList::const_iterator it = std::find(m_listeningTo->begin(), m_listeningTo->end(), data);
    ClaraMessengerMap::const_iterator it = m_listeningTo->find((Messenger*)other);
    //already listening ?
    if (it != m_listeningTo->end())
        return;

    //m_listeningTo->push_back(data);
    m_listeningTo->insert(std::make_pair((Messenger*)other, data));

    //data.messenger = this;
    other->AddListener(this, data);

}

void Messenger::DisconnectFrom(const Messenger *other)
{

}

void Messenger::DisconnectFromAll()
{

}

inline void Messenger::OnMessageReceived(const Message&)
{
}


//////////////////////////////////////////////////////////////////////////

inline bool Messenger::AreMessagesBlocked() const
{
    return (s_blockMessages + m_blockMessages) != 0;
}

void Messenger::AddListener(Messenger *listener, const MessengerData &listenerData) const
{
    if (!m_listeners.get())
    {
        m_listeners.reset(new ClaraMessengerMap);
    }


    m_listeners->insert(std::make_pair(listener, listenerData));
}

void Messenger::RemoveListener(Messenger *listener) const
{
    if (m_listeners.get())
    {
        ClaraMessengerMap::const_iterator it = m_listeners->find(listener);
        if (it != m_listeners->end())
        {
            m_listeners->erase(it);
            m_searchForRemovedListeners = true;
        }
    }
}

