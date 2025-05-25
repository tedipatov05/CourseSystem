#pragma once
#include "Command.h"
class ViewGradesCommand :public Command{
public:
	ViewGradesCommand(const MyString& buffer, Context& system);
	void execute() override;
	MyString getCommand() const override;

private:
	Vector<Grade> grades;

	void loadGrades(const MyString& filename);
};

