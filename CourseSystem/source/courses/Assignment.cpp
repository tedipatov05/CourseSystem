// Teodor Patov 2MI0600491

#include "../../headers/courses/Assignment.h"

#include <iostream>



Assignment::Assignment(const MyString& taskName, const MyString& courseName)
	: _taskName(taskName),_courseName(courseName) {

}

void Assignment::print() const {
	std::cout << " | " << _taskName << std::endl;
}

const MyString& Assignment::getTaskName() const {
	return this->_taskName;
}

void Assignment::addSubmission(const Submission& submission) {
	this->_submissions.push_back(submission);
}

void Assignment::writeToBinaryFile(std::ofstream& ofs) const {
	this->_courseName.writeToBinaryFile(ofs);
	this->_taskName.writeToBinaryFile(ofs);

}

void Assignment::readFromBinaryFile(std::ifstream& ifs) {
	this->_courseName.readFromBinaryFile(ifs);
	this->_taskName.readFromBinaryFile(ifs);

}

const MyString& Assignment::getCourseName() const {
	return this->_courseName;
}

const Vector<Submission>& Assignment::getSubmissions() const {
	return _submissions;
}

void Assignment::printSubmissions() const {
	for (size_t i = 0; i < this->_submissions.size(); ++i) {
		this->_submissions[i].print();
	}
}
