#pragma once
#include "Command.h"
#include "../Context.h"

class ViewAssignmentsCommand : public Command{
public:
	ViewAssignmentsCommand(const MyString& buffer, Context& context);
	void execute() override;
	MyString getCommand() const override;

private:
	MyString getCourseName() const;
};

