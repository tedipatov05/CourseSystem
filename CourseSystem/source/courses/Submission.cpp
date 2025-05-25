#include "../../headers/courses/Submission.h"

#include <iostream>

Submission::Submission(const MyString& user, const MyString& solution, const MyString& courseName, const MyString& assignment, int userId)
: user(user), solution(solution), courseName(courseName),assignment(assignment) ,userId(userId) {
}

void Submission::print() const {
	std::cout << "User: " << user<< ", " << userId  << ": " << solution << std::endl;
}

void Submission::writeToBinaryFile(std::ofstream& ofs) const {
	this->assignment.writeToBinaryFile(ofs);
	this->user.writeToBinaryFile(ofs);
	this->solution.writeToBinaryFile(ofs);
	this->courseName.writeToBinaryFile(ofs);
	ofs.write((const char*)(&userId), sizeof(userId));
}

void Submission::readFromBinaryFile(std::ifstream& ifs) {
	this->assignment.readFromBinaryFile(ifs);
	this->user.readFromBinaryFile(ifs);
	this->solution.readFromBinaryFile(ifs);
	this->courseName.readFromBinaryFile(ifs);
	ifs.read((char*)(&userId), sizeof(userId));
}

const MyString& Submission::getAssignment() const {
	return this->assignment;
}

const MyString& Submission::getCourseName() const {
	return this->courseName;
}

int Submission::getUserId() const {
	return this->userId;
}

void Submission::setGrade(const Grade& grade) {
	this->grade = grade;
}
