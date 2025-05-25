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
	

	//size_t size = this->_submissions.size();
	//ofs.write((const char*)(&size), sizeof(size));
	//for (size_t i = 0; i < size; ++i) {
	//	this->_submissions[i].writeToBinaryFile(ofs);
	//}
}

void Assignment::readFromBinaryFile(std::ifstream& ifs) {
	this->_courseName.readFromBinaryFile(ifs);
	this->_taskName.readFromBinaryFile(ifs);
	/*size_t size = 0;
	ifs.read((char*)(&size), sizeof(size));

	for (size_t i = 0; i < size; ++i) {
		Submission submission;
		submission.readFromBinaryFile(ifs);
		this->_submissions.push_back(submission);
	}*/
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
