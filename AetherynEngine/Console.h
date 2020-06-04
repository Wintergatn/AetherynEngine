#pragma once
#include <string>
#include <unordered_map>

class Console
{

public:
	Console();
	~Console();

	bool isActive();
	std::string getInput();
	void buildScriptMap();
	void parseCommand(std::string cmd);
	void resetCommand();

	void clearConsole();
	void echoConsole();
	void messageConsole();
	void exitConsole();

private:
	bool cActive;
	std::string command;
	std::string tokens[256];

	typedef void(*scriptFunction)(void);
	std::unordered_map<std::string, scriptFunction> scrMap;

	//typedef void scriptFunction();
	//typedef std::unordered_map<std::string, scriptFunction*> scrMap;
};

