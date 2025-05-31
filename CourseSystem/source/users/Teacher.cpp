
// Teodor Patov 2MI0600491

#include "../../headers/users/Teacher.h"


Teacher::Teacher(const MyString& firstname, const MyString& lastname, const MyString& password, int id) : User(firstname, lastname, password, id) {
}
Teacher::Teacher() : User() {
}

UserType Teacher::role() const {
	return UserType::Teacher;
}

User* Teacher::clone() const {
	return new Teacher(*this);
}

void Teacher::writeToBinaryFile(std::ofstream& ofs) const {
	UserType type = this->role();
	ofs.write((const char*)(&type), sizeof(type));

	this->first_name.writeToBinaryFile(ofs);
	this->last_name.writeToBinaryFile(ofs);
	this->password.writeToBinaryFile(ofs);
	ofs.write((const char*)(&this->_id), sizeof(this->_id));
}

void Teacher::addCourse(const Course& course) {
	this->_courses.push_back(course);
}