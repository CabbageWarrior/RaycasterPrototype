
#include "stdafx.h"
#include "CommandManager.h"
#include <iostream>
bool CommandManager::Initialize()
{
	
	return false;
}

void CommandManager::Deinitialize()
{
}

bool CommandManager::AddCommand(const std::string & Command, CommandFunction Callback, const std::string & Description)
{
	if (!Callback || Command.empty())
	{
		std::cout << "The command you're trying to add is invalid" << std::endl;
		return false;
	}

	CommandDefinition MyCommand{Command, Description, Callback};
	
	std::pair<std::map<std::string, CommandDefinition>::iterator, bool> CommandPair = Commands.insert(std::pair<std::string, CommandDefinition>(MyCommand.name, MyCommand));
	if (!CommandPair.second)
	{
		std::cout << "The command you're trying to add already exists!" << std::endl;
	}
	return CommandPair.second;
}

bool CommandManager::ProcessCommand(const std::string & Command) const
{
	std::map<std::string, CommandDefinition>::const_iterator MyIterator = Commands.find(Command);

	if (MyIterator != Commands.end())
	{
		MyIterator->second.CommandToExecute();
		return true;
	}
	std::cout << "Command doesn't exist" << std::endl;
	return false;
	
}

std::pair<std::map<std::string, CommandDefinition>::const_iterator, std::map<std::string, CommandDefinition>::const_iterator> CommandManager::GetCommands()const
{
	std::pair<std::map<std::string, CommandDefinition>::const_iterator, std::map<std::string, CommandDefinition>::const_iterator> IteratorsPair;
	IteratorsPair.first = Commands.begin();
	IteratorsPair.second = Commands.end();
	return IteratorsPair;
}