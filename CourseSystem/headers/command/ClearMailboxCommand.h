
// Teodor Patov 2MI0600491

#pragma once
#include "Command.h"


class ClearMailboxCommand : public Command{
public:

	ClearMailboxCommand(const MyString& buffer, Context& system);
	void execute() override;
	MyString getCommand() const override;

private:

	Mailbox _mailbox;
	void clearFile(const MyString& filename, const MyString& username) const;
	void loadMessages(const MyString& filename);
};

