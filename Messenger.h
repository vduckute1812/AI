#ifndef MESSENGER_H
#define MESSENGER_H
#include <QString>
#include <map>
#include <Defines.h>

typedef unsigned int u32;

class Messenger;

struct Forward
{
    static const u32 UP		= u32(1) << 30;
    static const u32 DOWN	= u32(1) << 31;
    static const u32 ALL	= UP | DOWN;
    static const u32 MASK	= UP - 1;  //mask used to filter out the forward flags and remain with the message only
};

//CLARANODE
static const u32 DESTROYED					= (1 << 0);// | Forward::UP;
static const u32 NAME_CHANGED				= (1 << 1) | Forward::DOWN;
static const u32 DELETED					= (1 << 4) | Forward::ALL;
static const u32 UNDELETED					= (1 << 5) | Forward::ALL;
static const u32 ERRORS_CHANGED				= (1 << 8) | Forward::UP;

//PROJECT
static const u32 PROJECT_WILL_BE_OPENED		= (u32(1) << 0);
static const u32 PROJECT_OPENED				= (u32(1) << 1);
static const u32 PROJECT_CLOSED				= (u32(1) << 2);
static const u32 PROJECT_SAVED				= (u32(1) << 3);

static const u32 DATABASE_OPENED			= (u32(1) << 4);
static const u32 STRUCTURE_CHANGED			= (u32(1) << 5);

//SELECTOR
static const u32 SELECTION_CHANGED			= (u32(1) << 6);

class Message
{
    friend class Messenger;

public:
    Message(u32 type, u32 msg);

    //the message type will be taken from the messenger sending it
    Message(u32 msg);

    Message(const Message& other);
    inline Message& operator=(const Message& other);

    bool			Is(u32 msg) const;
    bool			IsFlag(u32 msg) const;

    void			SetMessage(u32 msg);
    u32             GetMessage() const;

    u32             GetType() const;

    template<class T>
    bool			IsFrom() const;

    u32             GetId() const;
    Message&		SetId(u32 id);

    Message&		Set(const QString& name);
    Message&		Set(const QString& name, unsigned int val);
    bool			Has(const QString& name) const;
    u32             Get(const QString& name) const;

    Messenger*		GetSender() const;
    void			SetSender(Messenger* messenger);
    Messenger*		GetForwarder() const;
    void			SetForwarder(Messenger* messenger);

    void			SetMessageType(u32 msgType);
    bool			HasMessageType() const;

private:
    u32				m_message;
    u32				m_id; //specialized param, to avoid Set("id", id)
    u32				m_type;


#if defined _MSC_VER >= 1700
    typedef	std::map<QString, u32, StringLT> ArgumentsMap;
#else
    typedef	std::map<QString, u32, StringLT > ArgumentsMap;
#endif
    SharedPtr<ArgumentsMap>	m_arguments; //copy on write
    Messenger*		m_sender;
    Messenger*		m_forwarder;
    bool			m_ownsArguments;
};

struct MessengerData
{
    //sbool operator==(const MessengerData& other) const { return messenger == other.messenger; }
    //Messenger* messenger;
    u32		typeMask;
    u32		messageMask;
};

typedef std::map<Messenger*, MessengerData>	 ClaraMessengerMap;

class Messenger
{
public:
    Messenger();
    virtual ~Messenger();

    //blocks ALL messages for all messengers
    static void		BlockAllMessages(bool yes);

    //blocks messages for this messenger only
    void			BlockMessages(bool yes);

    //sends the message to all listeners of this messenger
    virtual void	Send(Message& msg);


    void			SetReceivesBroadcasts(bool yes, u32 typeMask = ~0U, u32 meIssageMask = ~0U);
    bool			IsReceivingBroadcasts() const;

    static u32		GetSentCount();
    static u32		GetReceivedCount();
    static u32		GetBlockedCount();
    static u32		GetFilteredCount();

protected:
    void			Forward(const Message& msg);
    void			Forward(Messenger* to, const Message& msg);

    void			ListenTo(const Messenger* other, u32 typeMask = ~0U, u32 messageMask = ~0U);
    void			DisconnectFrom(const Messenger* other);
    void			DisconnectFromAll();

    virtual void	OnMessageReceived(const Message& msg);
    virtual void	OnBroadcastReceived(const Message& msg);

    bool			AreMessagesBlocked() const;

private:
    Messenger(const Messenger& other) {}
    void			AddListener(Messenger* listener, const MessengerData& listenerData) const;
    void			RemoveListener(Messenger* listener) const;

    static ClaraMessengerMap*		s_registeredMessengers;
    ClaraMessengerMap::iterator		m_registeredMessengersPos;

    AutoPtr<ClaraMessengerMap>	m_listeningTo;
    mutable AutoPtr<ClaraMessengerMap>	m_listeners;

    bool			m_isReceivingBroadcasts;

    int				m_blockMessages;
    static int		s_blockMessages;

    static u32		s_sentCount;
    static u32		s_receivedCount;
    static u32		s_blockedCount;
    static u32		s_filteredCount;

    // this variable controls whether we have to check listener when processing listeners list
    mutable bool m_searchForRemovedListeners;
};

#endif // MESSENGER_H
