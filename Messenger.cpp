#include "Messenger.h"


Message::Message(u32 type, u32 msg):
    m_message(msg),
    m_type(type),
    m_sender(nullptr)
{

}

Message::Message(u32 msg):
    m_message(msg),
    m_type(0),
    m_sender(nullptr)
{

}

Message::Message(const Message &other) :
    m_message(other.m_message),
    m_type(other.m_type),
    m_sender(other.m_sender)
{

}

Message &Message::operator=(const Message &other)
{
    if (this == &other)
        return *this;

    m_type = other.m_type;
    m_message = other.m_message;
    m_sender = other.m_sender;

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


void Message::SetMessageType(u32 msgType)
{
    m_type = msgType;
}

bool Message::HasMessageType() const
{
    return m_type > 0;
}

////////////////////////////////////////////////////////////////

MessengerMap* Messenger::s_registeredMessengers = nullptr;
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

Messenger::Messenger()
{

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

//    if (AreMessagesBlocked())
//    {
//        s_blockedCount++;
//        return;
//    }

    if (!m_listeners.get() && !s_registeredMessengers)
        return;

    Message m(msg);
    m.SetSender(this);

    s_sentCount++;

    //send to listeners
    if (m_listeners.get())
    {
        MessengerMap tmp = *m_listeners;
        MessengerMap::iterator it = tmp.begin();
        while (it != tmp.end())
        {
            MessengerMap::iterator next = it;
            next++;

            Messenger* msgr = it->first;
            const MessengerData& listenerData = it->second;

            if (m_listeners->find(msgr) != m_listeners->end())
            {
                if (msg.GetSender() != msgr)    // don't send to it self
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

            it = next;
        }
    }
}

void Messenger::Forward(Messenger *to, const Message &msg)
{
    if (msg.GetSender() == this)
        return;

    //send to listeners
    if (AreMessagesBlocked())
    {
        s_blockedCount++;
        return;
    }

    Message m(msg);

    s_sentCount++;
    s_receivedCount++;

    to->OnMessageReceived(m);
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
        m_listeningTo.reset(new MessengerMap);
    }

    MessengerData data;

    data.typeMask = typeMask;
    data.messageMask = (messageMask & msg::Forward::MASK); //exclude the forward mask

    MessengerMap::const_iterator it = m_listeningTo->find((Messenger*)(other));

    if (it != m_listeningTo->end())
        return;

    m_listeningTo->insert(std::make_pair((Messenger*)other, data));

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
        m_listeners.reset(new MessengerMap);
    }

    m_listeners->insert(std::make_pair(listener, listenerData));
}

void Messenger::RemoveListener(Messenger *listener) const
{
    if (m_listeners.get())
    {
        MessengerMap
                ::const_iterator it = m_listeners->find(listener);
        if (it != m_listeners->end())
        {
            m_listeners->erase(it);
        }
    }
}

