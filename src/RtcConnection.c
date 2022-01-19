#include "RtcConnection.h"


static void RTC_API gatheringStateCallback(int pc, rtcGatheringState state, void *ptr) {
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
		
	}

}



int RtcOpen(Peer* peer)
{
    rtcInitLogger(RTC_LOG_DEBUG, NULL);
	rtcConfiguration config;
	memset(&config, 0, sizeof(config));
	config.disableAutoNegotiation=TRUE;

	peer->pc = rtcCreatePeerConnection(&config);
    if (peer->pc<0)
        return -1;
    
	rtcSetUserPointer(peer->pc, peer);

    return 0;
}

int RtcClose(Peer* peer)
{
	//close down everything;
}


int CreateTrackAndSendOffer(Peer* peer)
{
	//create video track
	rtcSetGatheringStateChangeCallback(peer->pc, gatheringStateCallback);
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
	 peer->dc=rtcCreateDataChannel(peer->pc, "datachannel");
	 printf("\ndatachannel %d\n\n",peer->dc);
 	 rtcSetLocalDescription(peer->pc,"offer");
}