
// Teodor Patov 2MI0600491

#pragma once
#include "Command.h"

class AddToCourseCommand :
    public Command
{
	
public:
	AddToCourseCommand(const MyString& buffer, Context& context);
	void execute() override;
	MyString getCommand() const override;

private:

	MyString getCourseNameFromBuffer() const;
	MyString getUserIdFromBuffer() const;
	int findCourseToAdd(const MyString& courseName) const;
	void saveAddedUser(const MyString& filename, const MyString& courseName, int userId) const;

};

