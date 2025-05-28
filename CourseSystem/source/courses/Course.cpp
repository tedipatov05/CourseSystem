#include "../../headers/courses/Course.h"


Course::Course(const MyString& courseName, const MyString& password) {
	this->_courseName = courseName;
	this->_password = password;
}

void Course::addParticipant(const User* user) {
	this->users.push_back(user->getId());
}

void Course::addAssignment(const Assignment& assignment) {
	this->_assignments.push_back(assignment);
}

const MyString Course::getCourseName() const {
	return this->_courseName;
}

void Course::writeToBinaryFile(std::ofstream& ofs) const {
	
	this->_courseName.writeToBinaryFile(ofs);
	this->_password.writeToBinaryFile(ofs);

	/*size_t size = this->_assignments.size();
	ofs.write((const char*)(&size), sizeof(size));
	for (size_t i = 0; i < size; ++i) {
		this->_assignments[i].writeToBinaryFile(ofs);
	}*/
}

void Course::readFromBinaryFile(std::ifstream& ifs){
	
	this->_courseName.readFromBinaryFile(ifs);
	this->_password.readFromBinaryFile(ifs);

	/*size_t size = 0;
	ifs.read((char*)(&size), sizeof(size));

	for (size_t i = 0; i < size; ++i) {
		Assignment assignment;
		assignment.readFromBinaryFile(ifs);
		this->_assignments.push_back(assignment);
	}*/
}

bool Course::isUserInCourse(int userId) const {
	for (size_t i = 0; i < this->users.size(); ++i) {
		if (this->users[i] == userId) {
			return true;
		}
	}
	return false;
}

const Vector<int>& Course::getUsers() const {
	return this->users;
}

const Vector<Assignment>& Course::getAssignments() const {
	return this->_assignments;
}

bool Course::isPasswordCorrect(const MyString& password) const {
	return this->_password == password;
}

