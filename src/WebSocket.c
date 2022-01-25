#include "WebSocket.h"
#include <rtc/rtc.h>
#include "RtcConnection.h"

void WebSocketCallback(int id, const char *message, int size, void *ptr)
{
    Peer* peer=(Peer*)ptr;
    printf("current state : %d\n", peer->state);
	printf("%s\n",message);
	

    switch(peer->state)
	{
		case  AWAITING_CONNECTION:
                if (strcmp("stream",message)==0)
	            {
                    CreateTrackAndSendOffer(peer);
	            }
    			//todo
				break;
		case  AWAITING_ANSWER:
                    ProcessAnswer(peer,message);
				break;
		case  STREAMING:
					//todo
				break;
		default:
            //default statements
            break;

	}




}


void webSocketServerCallBack(int wsserver, int ws, void *ptr)
{
    Peer *peer = (Peer *)ptr;
    printf("\nws server %d and old connection is %d and new connection is %d\n",wsserver,peer->wsSocket,ws);
    if (ws!=peer->wsSocket)
    {
         //delete the old connection - we can only have 1 connection
         if (peer->wsSocket>0)
         {
            printf("deleting track %d\n",peer->wsSocket);
            rtcDeleteWebSocket(peer->wsSocket);
         }

         peer->wsSocket=ws;
    }
    
    rtcSetUserPointer(peer->wsSocket, peer);
    rtcSetMessageCallback(peer->wsSocket, WebSocketCallback);
    
}



int StartWebServer(Peer* peer)
{
    //creating a new websocket server
    rtcWsServerConfiguration wsConfig;
    wsConfig.port=35001;
    wsConfig.enableTls=FALSE;
    wsConfig.certificatePemFile=NULL;
    wsConfig.keyPemFile=NULL;
    wsConfig.keyPemPass=NULL;

    peer->wsServer=rtcCreateWebSocketServer(&wsConfig, webSocketServerCallBack);
    rtcSetUserPointer(peer->wsServer, peer);
    printf("websocket server %d created \n",peer->wsServer);

    return 0;
}