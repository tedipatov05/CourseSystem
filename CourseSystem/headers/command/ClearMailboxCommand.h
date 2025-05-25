#pragma once
#include "Command.h"
class ClearMailboxCommand : public Command{
public:
	ClearMailboxCommand(const MyString& buffer, Context& system);
	void execute() override;
	MyString getCommand() const override;
private:
	void clearFile(const MyString& filename, int userId) const;
};

