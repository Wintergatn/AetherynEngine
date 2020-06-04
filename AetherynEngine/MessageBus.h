#pragma once
#include <functional>
#include <queue>
#include <vector>
#include <iostream>
#include "Message.h"

class MessageBus
{

public:
	MessageBus();

	~MessageBus();

	void addReceiver(std::function<void(Message)>);

	void sendMessage(Message);

	void notify();

private:
	std::vector<std::function<void(Message)>> receivers;
	std::queue<Message> messages;
};

