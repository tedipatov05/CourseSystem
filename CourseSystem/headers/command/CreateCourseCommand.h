
// Teodor Patov 2MI0600491

#pragma once
#include "Command.h"
#include "../Context.h"

class CreateCourseCommand :
    public Command
{
public:
	CreateCourseCommand(const MyString& buffer, Context& system);
	void execute() override;

private:
	
	MyString getCourseNameFromBuffer() const;
	MyString getCoursePasswordFromBuffer() const;
};

