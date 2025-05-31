
// Teodor Patov 2MI0600491

#pragma once
#include "Command.h"
#include "../Context.h"

class EnrollCommand : public Command{

public:
	EnrollCommand(const MyString& buffer, Context& ctx);
	void execute() override;
	MyString getCommand() const override;

private:

	MyString getCourseName() const;
	MyString getCoursePassword() const;
	void saveAddedUser(const MyString& filename, const MyString& courseName, int userId) const;
};

