#ifndef _ioengine_h
#define _ioengine_h

struct Socket;

typedef int (*IOEngineInitFunc)(int);
typedef int (*IOEngineAddSockFunc)(struct Socket *);
typedef void (*IOEngineDelSockFunc)(struct Socket *);

int ioengine_init(int max_connects);

struct IOEngine {
    const char*         eng_name;
    IOEngineInitFunc    eng_init;
    IOEngineAddSockFunc eng_addsock;
    IOEngineDelSockFunc eng_delsock;
};

#define SE_READ   0x00000001
#define SE_WRITE  0x00000002
#define SE_ERROR  0x00000004

typedef void (*SockEventCallback)(struct Socket, int);

struct Socket {
    int fd;                          /* socket file descriptor */
    int events;                      /* IO engine events */
    int ed;                          /* IO Engine Data */
    SockEventCallback sock_callback; /* sock callback function */
};

#endif /* _ioengine_h */
