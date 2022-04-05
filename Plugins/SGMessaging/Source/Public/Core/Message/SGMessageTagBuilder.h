#pragma once

#define MESSAGE_TAG_PARAM_SIGNATURE

#define MESSAGE_TAG_WITH_TOPIC 1

#if MESSAGE_TAG_WITH_TOPIC
#undef MESSAGE_TAG_PARAM_SIGNATURE
#define TOPIC_ID_TYPE int32
#define MESSAGE_ID_TYPE int32
#define TOPIC_ID InTopicID
#define MESSAGE_ID InMessageID
#define TOPIC_ID_DEFINE TOPIC_ID_TYPE TOPIC_ID
#define MESSAGE_ID_DEFINE MESSAGE_ID_TYPE MESSAGE_ID
#define CONST_TOPIC_ID_DEFINE const TOPIC_ID_TYPE TOPIC_ID
#define CONST_MESSAGE_ID_DEFINE const MESSAGE_ID_TYPE MESSAGE_ID
#define MESSAGE_TAG_PARAM_SIGNATURE CONST_TOPIC_ID_DEFINE, CONST_MESSAGE_ID_DEFINE
#define MESSAGE_TAG_PARAM_VALUE TOPIC_ID, MESSAGE_ID
#include "Kismet/KismetStringLibrary.h"
#endif

class FSGMessageTagBuilder
{
public:
	static FName Builder(MESSAGE_TAG_PARAM_SIGNATURE)
	{
#if MESSAGE_TAG_WITH_TOPIC
		return FName(
			UKismetStringLibrary::Conv_IntToString(TOPIC_ID) + ":" + UKismetStringLibrary::Conv_IntToString(
				MESSAGE_ID));
#endif
	}
};