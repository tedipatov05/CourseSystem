
// Teodor Patov 2MI0600491

#pragma once
#include "Command.h"

class GradeAssignmentCommand : public Command {
public:

	GradeAssignmentCommand(const MyString& buffer, Context& system);
	void execute() override;

private:

	MyString getComment() const;

	void saveGrade(const MyString& filename, const Grade& grade);
	void saveMessageInFile(const MyString& filename, const Message& message) const;
};

