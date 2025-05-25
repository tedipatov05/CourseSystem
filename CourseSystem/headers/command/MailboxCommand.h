#pragma once
#include "Command.h"
#include "../Context.h"

class MailboxCommand : public Command{
public:
	MailboxCommand(const MyString& buffer, Context& system);
	MyString getCommand() const override;
	void execute() override;

//private:
//	Context& context;
//	MyString buffer;

};

