#include "../../headers/users/Student.h"

Student::Student() : User() {
	
}

Student::Student(const MyString& first_name, const MyString& last_name, const MyString& password, int id) : User(first_name, last_name, password, id) {
}

UserType Student::role() const {
	return UserType::Student;
}
User* Student::clone() const {
	return new Student(*this);
}

void Student::writeToBinaryFile(std::ofstream& ofs) const {
	UserType type = this->role();
	ofs.write((const char*)(&type), sizeof(type));

	this->first_name.writeToBinaryFile(ofs);
	this->last_name.writeToBinaryFile(ofs);
	this->password.writeToBinaryFile(ofs);
	ofs.write((const char*)(&this->_id), sizeof(this->_id));
}

