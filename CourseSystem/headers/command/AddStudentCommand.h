#pragma once
#include "Command.h"
#include "../Context.h"

class AddStudentCommand : public Command{

public:
	AddStudentCommand(const MyString& buffer, Context& system);
	MyString getCommand() const override;
	void execute() override;

private:
	/*Context& context;
	MyString buffer;*/

	MyString getPasswordFromBuffer() const;
	MyString getFirstNameFromBuffer() const;
	MyString getLastNameFromBuffer() const;

};

