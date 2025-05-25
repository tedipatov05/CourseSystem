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
	/*void printSubmissions(const MyString& courseName, const MyString& homeworkName) const;
	void printSubmission(const Submission& submission) const;*/
};

