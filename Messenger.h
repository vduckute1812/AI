#ifndef MESSENGER_H
#define MESSENGER_H
#include <QString>
#include <map>
#include <Defines.h>

typedef unsigned int u32;

class Messenger;


namespace msg
{
    struct Forward
    {
        static const u32 WHITE		= u32(1) << 30;         // WHITE PLAYER
        static const u32 BLACK      = u32(1) << 31;         // BLACK PLAYER
        static const u32 BOTH       = WHITE | BLACK;     // BOTH
        static const u32 MASK       = WHITE - 1;         // remove alliance flags and keep message flags only
    };

    //PIECE ACTIONS
    static const u32 MOVE					= (u32(1) << 0);
    static const u32 ATTACK                 = (u32(1) << 1);
    static const u32 DEFEND					= (u32(1) << 2);
    static const u32 PROMOTE                = (u32(1) << 3);
    static const u32 ESCAPE                 = (u32(1) << 4);

    static const u32 BOARD_CHANGED          = (u32(1) << 5);
    static const u32 HISTORY_UPDATE         = (u32(1) << 5);

    // KILL AND SUMMON PIECE
    static const u32 KILL                   = (u32(1) << 7);
    static const u32 REVIVAL                = (u32(1) << 8);

    //HISTORY BOARD
    static const u32 LOAD_GAME              = (u32(1) << 9);
    static const u32 SAVE_GAME              = (u32(1) << 10);

    //OPEN GAME || CLOSE GAME
    static const u32 NEW_GAME               = (u32(1) << 11);
    static const u32 CLOSE_GAME             = (u32(1) << 12);

    // CHANGE TURN
    static const u32 CHANGE_TURN            = (u32(1) << 13);

//    //PAINT EVENTS
//    static const u32 SHOW_THREAT_KING       = (u32(1) << 14);
//    static const u32 SHOW_POSIBLE_MOVES     = (u32(1) << 15);
}

class Message
{
    friend class Messenger;

public:
    Message(u32 type, u32 msg);

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

    Messenger*		GetSender() const;
    void			SetSender(Messenger* messenger);
    void			SetMessageType(u32 msgType);
    bool			HasMessageType() const;

private:
    u32				m_message;
    u32				m_type;

    Messenger*              m_sender;
};


template<class T>
bool Message::IsFrom() const
{
    return GetType() == T::k_msgType;
}


struct MessengerData
{
    u32		typeMask;
    u32		messageMask;
};

typedef std::map<Messenger*, MessengerData> MessengerMap;

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
    virtual void    Forward(Messenger* to, const Message& msg);

    static u32		GetSentCount();
    static u32		GetReceivedCount();
    static u32		GetBlockedCount();
    static u32		GetFilteredCount();

protected:
    void			ListenTo(const Messenger* other, u32 typeMask = ~0U, u32 messageMask = ~0U);        //~0u  0xFFFF
    void			DisconnectFrom(const Messenger* other);
    void			DisconnectFromAll();

    virtual void	OnMessageReceived(const Message& msg);

    bool			AreMessagesBlocked() const;

private:
    Messenger(const Messenger&) {}
    void			AddListener(Messenger* listener, const MessengerData& listenerData) const;
    void			RemoveListener(Messenger* listener) const;

    static MessengerMap*		s_registeredMessengers;
    MessengerMap::iterator		m_registeredMessengersPos;

    AutoPtr<MessengerMap>           m_listeningTo;
    mutable AutoPtr<MessengerMap>	m_listeners;

    int				m_blockMessages;
    static int		s_blockMessages;

    static u32		s_sentCount;
    static u32		s_receivedCount;
    static u32		s_blockedCount;
    static u32		s_filteredCount;
};

#endif // MESSENGER_H
