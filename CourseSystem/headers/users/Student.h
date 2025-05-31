
// Teodor Patov 2MI0600491

#pragma once

#include "User.h"
#include "../Vector.hpp"
#include "../courses/Course.h"

class Student : public User {

public:
	Student();
	Student(const MyString& first_name, const MyString& last_name, const MyString& password, int id);

	UserType role() const override;
	User* clone() const override;

	void writeToBinaryFile(std::ofstream& ofs) const override;

private:

	Vector<Course> _courses;

};

