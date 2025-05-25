#pragma once

#include "../courses/Course.h"
#include "../Vector.hpp"

class Teacher : public User {

public:
	Teacher();
	Teacher(const MyString& firstname, const MyString& lastname, const MyString& password, int id);

	UserType role() const override;
	User* clone() const override;
	void writeToBinaryFile(std::ofstream& ofs) const override;

	void addCourse(const Course& course);

private:
	Vector<Course> _courses;

};

