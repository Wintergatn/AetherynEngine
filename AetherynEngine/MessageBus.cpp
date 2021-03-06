#include "MessageBus.h"



MessageBus::MessageBus() { }

MessageBus::~MessageBus() { }

void MessageBus::addReceiver(std::function<void(Message)> messageReceiver)
{
	receivers.push_back(messageReceiver);
}

void MessageBus::sendMessage(Message message)
{
	messages.push(message);
}

void MessageBus::notify()
{
	while (!messages.empty()) {
		for (auto iter = receivers.begin(); iter != receivers.end(); iter++) {
			(*iter)(messages.front());
		}
		messages.pop();
	}
}