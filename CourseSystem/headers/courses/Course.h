#pragma once
#include "Assignment.h"
#include "../MyString.h"
#include "../users/UserRepository.h"
#include "../Vector.hpp"

class Course {

public:

	Course() = default;
	Course(const MyString& courseName, const MyString& password);

	void addParticipant(const User* user); 
	void addAssignment(const Assignment& assignment); 

	const MyString getCourseName() const;
	const Vector<Assignment>& getAssignments() const;
	const Vector<int>& getUsers() const;

	void writeToBinaryFile(std::ofstream& ofs) const;
	void readFromBinaryFile(std::ifstream& ifs);

	bool isUserInCourse(int userId) const;
	bool isPasswordCorrect(const MyString& password) const;

private:

	Vector<int> users;
	MyString _courseName;
	MyString _password;
	Vector<Assignment> _assignments;


};

