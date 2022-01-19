#ifndef GLOBALS_H
#define GLOBALS_H



enum STATE {INITIALIZING=0,AWAITING_CONNECTION=1,AWAITING_ANSWER=2,STREAMING=3,EXIT=4};


//typedef   void  (*WsSocketOnMessage)(const char* message,void* ptr);


typedef struct {
	volatile enum STATE state;
	int pc;
	int dc;
	int track;
    int wsServer;
    int wsSocket;
    bool connected;
	//WsSocketOnMessage onWsMessage;
} Peer;


#endif