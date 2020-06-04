#include "Message.h"



Message::Message(const std::string event)
{
	messageEvent = event;
}

std::string Message::getEvent() const
{
	return messageEvent;
}

Message::~Message()
{
}
