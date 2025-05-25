#pragma once
#include "Command.h"

class AddTeacherCommand : public Command
{
public:
	AddTeacherCommand(const MyString& buffer, Context& system);
	MyString getCommand() const override;
	void execute() override;

private:
	/*Context& context;
	MyString buffer;*/

	MyString getPasswordFromBuffer() const;
	MyString getFirstNameFromBuffer() const;
	MyString getLastNameFromBuffer() const;
};

