#pragma once

#include <string>
#include <map>

typedef void(*CommandFunction)(void);

struct CommandDefinition
{
	std::string name = "";
	std::string Definition = "";
	CommandFunction CommandToExecute = nullptr;
};

class CommandManager
{
public:

	bool Initialize();
	void Deinitialize();

	bool AddCommand(const std::string & Command, CommandFunction Callback, const std::string & Description);

	bool ProcessCommand(const std::string & Command) const;
	
	std::pair<std::map<std::string, CommandDefinition>::const_iterator, std::map<std::string, CommandDefinition>::const_iterator> GetCommands()const;
	
private:
	std::map<std::string, CommandDefinition> Commands;

};