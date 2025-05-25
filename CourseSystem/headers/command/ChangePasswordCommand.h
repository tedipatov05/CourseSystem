#pragma once

#include "../../headers/command/Command.h"

class ChangePasswordCommand : public Command {

public:
	ChangePasswordCommand(const MyString& buffer, Context& context);
	void execute() override;
	MyString getCommand() const override;
private:

	void modifyUserInFile(const MyString& filename, const User* user) const;

};