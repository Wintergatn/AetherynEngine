#pragma once
#include <iostream>
#include <string>


#ifndef MESSAGE
#define MESSAGE

class Message
{
public:
	Message(const std::string);

	~Message();

	std::string getEvent() const;

private:
	std::string messageEvent;
};

#endif