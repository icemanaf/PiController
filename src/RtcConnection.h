#ifndef RTC_CONNECTION_H
#define RTC_CONNECTION_H


#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gst/gst.h>
#include <unistd.h>
#include <string.h>
#include <rtc/rtc.h>
#include "Globals.h"



int RtcOpen(Peer* peer);

int RtcClose(Peer* peer);

int CreateTrackAndSendOffer(Peer* peer);

#endif