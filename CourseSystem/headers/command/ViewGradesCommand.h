
// Teodor Patov 2MI0600491

#pragma once
#include "Command.h"
class ViewGradesCommand :public Command{
public:
	ViewGradesCommand(const MyString& buffer, Context& system);
	void execute() override;

private:
	Vector<Grade> grades;

	void loadGrades(const MyString& filename);
};

