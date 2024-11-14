#include "CommandInterface.h"

CommandInterfacePtr CommandInterface::Create(GameController *newGameController, GameModel *newGameModel)
{
	return CommandInterfacePtr(new CommandInterface(newGameController, newGameModel));
}

void CommandInterfaceDeleter::operator ()(CommandInterface *ptr) const
{
	delete ptr;
}

void CommandInterface::OnTick()
{
}

void CommandInterface::Init()
{
}

bool CommandInterface::HandleEvent(const GameControllerEvent &event)
{
	return true;
}

bool CommandInterface::HaveSimGraphicsEventHandlers()
{
	return false;
}

int CommandInterface::Command(PTString command)
{
	return PlainCommand(command);
}

PTString CommandInterface::FormatCommand(PTString command)
{
	return PlainFormatCommand(command);
}

void CommandInterface::SetToolIndex(ByteString identifier, std::optional<int> index)
{
}
