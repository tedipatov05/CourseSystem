
// Teodor Patov 2MI0600491

#pragma once
#include "Command.h"
#include "../Context.h"

class MailboxCommand : public Command{
public:
	MailboxCommand(const MyString& buffer, Context& system);
	MyString getCommand() const override;
	void execute() override;

};

