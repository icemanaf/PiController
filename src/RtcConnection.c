#include "RtcConnection.h"


static void RTC_API gatheringStateCallback(int pc, rtcGatheringState state, void *ptr)
 {
	Peer *peer = (Peer *)ptr;
	printf("Gathering state %s: %d\n", "answerer", state);
	if (state==RTC_GATHERING_COMPLETE)
	{
		printf("\ngenerating offer\n");
		char type[100];
		rtcGetLocalDescriptionType(peer->pc, type, sizeof(type));
		printf("type - %s\n",type);
		rtcSendMessage(peer->wsSocket,type,-1);
		char offer[10000];
		rtcGetLocalDescription(peer->pc, offer, sizeof(offer));
		printf("============\n\n%s\n",offer);
		rtcSendMessage(peer->wsSocket,offer,-1);
		peer->state=AWAITING_ANSWER;
	}

}


static void RTC_API stateChangeCallback(int pc, rtcState state, void *ptr) 
{
	Peer *peer = (Peer *)ptr;
	peer->state = state;
	printf("State %s: %d\n", "answerer", state);
	
	if (state==RTC_CONNECTED)
	{
		printf("/n/nConnected!!/n");
	}
}




int RtcOpen(Peer* peer)
{
    rtcInitLogger(RTC_LOG_DEBUG, NULL);
	rtcConfiguration config;
	memset(&config, 0, sizeof(config));
	config.disableAutoNegotiation=TRUE;
	config.bindAddress="127.0.0.1";
	config.portRangeBegin=35001;
	config.portRangeEnd=35099;

	peer->pc = rtcCreatePeerConnection(&config);
    if (peer->pc<0)
        return -1;
    
	rtcSetUserPointer(peer->pc, peer);
	rtcSetGatheringStateChangeCallback(peer->pc, gatheringStateCallback);
	rtcSetStateChangeCallback(peer->pc, stateChangeCallback);

    return 0;
}

int RtcClose(Peer* peer)
{
	//close down everything;
}


int CreateTrackAndSendOffer(Peer* peer)
{
	//create video track
	
	rtcTrackInit trackInit;
	memset(&trackInit, 0, sizeof(trackInit));
	trackInit.direction=RTC_DIRECTION_SENDONLY;
	trackInit.codec=RTC_CODEC_H264;
	trackInit.payloadType=102;
	trackInit.ssrc=111; //This has to match the ssrc in the gstreamer rtph264pay pipeline element
	trackInit.mid="video";
	trackInit.name="bobo-track";
	trackInit.trackId="track1";
	peer->track=rtcAddTrackEx(peer->pc, &trackInit);
	printf("\n\ntrack result %d\n\n",peer->track);

	//create data channel
	 //peer->dc=rtcCreateDataChannel(peer->pc, "datachannel");
	 rtcSetLocalDescription(peer->pc,"offer");
	
	
}


int ProcessAnswer(Peer* peer,const char* answer)
{
	printf("Processing answer\n");
	rtcSetRemoteDescription(peer->pc, answer, "answer");
}