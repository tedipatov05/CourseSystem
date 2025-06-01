
// Teodor Patov 2MI0600491

#pragma once
#include "Command.h"
#include "../Context.h"

class AddStudentCommand : public Command{

public:
	AddStudentCommand(const MyString& buffer, Context& system);
	void execute() override;

private:
	
	MyString getPasswordFromBuffer() const;
	MyString getFirstNameFromBuffer() const;
	MyString getLastNameFromBuffer() const;

};

