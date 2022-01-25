//https://jsfiddle.net/oj2xnywh/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gst/gst.h>
#include <unistd.h>
#include <string.h>
#include <rtc/rtc.h>
#include "WebSocket.h"
#include "Globals.h"
#include "RtcConnection.h"



Peer *peer;




int main(int argc ,char **argv)
{
	//initialize the peer
	Peer* peer = (Peer *)malloc(sizeof(Peer));
	if (!peer) {
		fprintf(stderr, "Error allocating memory for peer\n");
		return -1;
	}
	memset(peer, 0, sizeof(Peer));
	peer->state=INITIALIZING;
    

	while(true)
	{
			switch(peer->state)
			{
				case  INITIALIZING:
					RtcOpen(peer);
					printf("\n\npeer connection number %d\n\n",peer->pc);
					int ret=StartWebServer(peer);
					printf("Webserver started with return code %d",ret);
					peer->state=AWAITING_CONNECTION;
					break;
				case  AWAITING_CONNECTION:
					
					//todo
				break;
				case  AWAITING_ANSWER:
					//todo
				break;
				case  STREAMING:
					//todo
				break;
				case  EXIT:
					printf("exiting\n");
					return 0;
					break;

			}

		sleep(1);
	}
	
}