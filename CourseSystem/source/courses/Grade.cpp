#include "../../headers/courses/Grade.h"

#include <iostream>


Grade::Grade(const MyString& assignment, const MyString& course, const MyString& description, double grade, int userId) :
	_assignment(assignment), _courseName(course), _description(description), grade(grade), _userId(userId) {}

void Grade::printGrade() const {

	std::cout << _courseName << " | " << _assignment << " | " << grade << " | " << _description << std::endl;
}

const MyString& Grade::getAssignment() const {
	return this->_assignment;
}

const MyString& Grade::getCourseName() const {
	return this->_courseName;
}

void Grade::writeToBinaryFile(std::ofstream& ofs) const {
	this->_assignment.writeToBinaryFile(ofs);
	this->_courseName.writeToBinaryFile(ofs);
	this->_description.writeToBinaryFile(ofs);
	ofs.write((const char*)(&grade), sizeof(grade));
	ofs.write((const char*)(&_userId), sizeof(_userId));
}
void Grade::readFromBinaryFile(std::ifstream& ifs) {
	this->_assignment.readFromBinaryFile(ifs);
	this->_courseName.readFromBinaryFile(ifs);
	this->_description.readFromBinaryFile(ifs);
	ifs.read((char*)(&grade), sizeof(grade));
	ifs.read((char*)(&_userId), sizeof(_userId));
}

int Grade::getUserId() const {
	return this->_userId;
}




