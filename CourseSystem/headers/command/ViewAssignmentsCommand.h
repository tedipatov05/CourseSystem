
// Teodor Patov 2MI0600491

#pragma once
#include "Command.h"
#include "../Context.h"

class ViewAssignmentsCommand : public Command{
public:
	ViewAssignmentsCommand(const MyString& buffer, Context& context);
	void execute() override;

private:
	MyString getCourseName() const;
};

