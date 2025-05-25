#pragma once
#include "Command.h"
#include "../Context.h"

class CreateCourseCommand :
    public Command
{
public:
	CreateCourseCommand(const MyString& buffer, Context& system);
	MyString getCommand() const override;
	void execute() override;

private:
	//Context& context;
	//MyString buffer;
	MyString getCourseNameFromBuffer() const;
	MyString getCoursePasswordFromBuffer() const;
};

