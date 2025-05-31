
// Teodor Patov 2MI0600491

#pragma once
#include "Command.h"
#include "../Context.h"

class ViewSubmissionsCommand : public Command{
public:
	ViewSubmissionsCommand(const MyString& buffer, Context& context);
	void execute() override;
	MyString getCommand() const override;

private:

	MyString getCourseName() const;
	MyString getHomeworkName() const;
	
};

