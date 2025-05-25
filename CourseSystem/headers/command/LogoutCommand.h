#pragma once
#include "Command.h"
#include "../Context.h"

class LogoutCommand : public Command{
public:
	void execute() override;
	MyString getCommand() const override;
	LogoutCommand(const MyString& buffer, Context& system);

//private:
//	Context& context;
//	MyString buffer;

};

