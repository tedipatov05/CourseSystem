
// Teodor Patov 2MI0600491

#pragma once
#include "../MyString.h"

class Grade {
public:

	Grade() = default;
	Grade(const MyString& assignment, const MyString& course, const MyString& description, double grade, int userId);


	void printGrade() const;
	const MyString& getAssignment() const;
	const MyString& getCourseName() const;
	int getUserId() const;

	void writeToBinaryFile(std::ofstream& ofs) const;
	void readFromBinaryFile(std::ifstream& ifs);


private:
	MyString _assignment;
	MyString _courseName;
	MyString _description;
	double grade;
	int _userId;

};

