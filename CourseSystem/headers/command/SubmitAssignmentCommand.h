
// Teodor Patov 2MI0600491

#pragma once
#include "Command.h"
#include "../Context.h"

class SubmitAssignmentCommand :public Command{

public:
	SubmitAssignmentCommand(const MyString& buffer, Context& ctx);
	void execute() override;
private:
	

	MyString getCourseName() const;
	MyString getHomeworkName() const;
	MyString getContent() const;
	void saveSubmission(const MyString& filename, const Submission& submission) const;
};

