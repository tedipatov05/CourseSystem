#pragma once
#include "Command.h"
#include "../Context.h"

class EnrollCommand : public Command{

public:
	EnrollCommand(const MyString& buffer, Context& ctx);
	void execute() override;
	MyString getCommand() const override;

private:
	//Context& context;
	//MyString buffer;

	MyString getCourseName() const;
	MyString getCoursePassword() const;
	void saveAddedUser(const MyString& filename, const MyString& courseName, int userId) const;
};

