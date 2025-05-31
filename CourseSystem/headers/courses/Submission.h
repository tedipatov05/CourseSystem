
// Teodor Patov 2MI0600491

#pragma once
#include "Grade.h"
#include "../MyString.h"


class Submission
{
public:
	Submission() = default;
	Submission(const MyString& user, const MyString& solution, const MyString& courseName, const MyString& assignment, int userId);

	void print() const;

	void writeToBinaryFile(std::ofstream& ofs) const;
	void readFromBinaryFile(std::ifstream& ifs);
	const MyString& getAssignment() const;
	const MyString& getCourseName() const;
	int getUserId() const;

	void setGrade(const Grade& grade);
	

private:
	MyString user;
	MyString solution;
	MyString courseName;
	MyString assignment;
	int userId;
	Grade grade;

};


