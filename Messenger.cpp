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
    u32 mask = Forward::MASK;
    return ((m_message & msg) & mask) == (msg & mask);
}

bool Message::IsFlag(u32 msg) const
{
    u32 mask = ~Forward::MASK;
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
    m_isReceivingBroadcasts = false;
    m_searchForRemovedListeners = false;
}

Messenger::~Messenger()
{

}

void Messenger::BlockAllMessages(bool yes)
{

}

void Messenger::BlockMessages(bool yes)
{

}

void Messenger::Send(Message &msg)
{

}

void Messenger::SetReceivesBroadcasts(bool yes, u32 typeMask, u32 meIssageMask)
{

}

bool Messenger::IsReceivingBroadcasts() const
{

}

u32 Messenger::GetSentCount()
{

}
