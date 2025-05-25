#pragma once
#include "../MyString.h"
#include "Submission.h"
#include "../Vector.hpp"

class Assignment {

public:

	Assignment() = default;
	Assignment(const MyString& taskName, const MyString& courseName);

	void print() const;
	void printSubmissions() const;


	const MyString& getTaskName() const;
	const MyString& getCourseName() const;

	void addSubmission(const Submission& submission);
	const Vector<Submission>& getSubmissions() const;

	void writeToBinaryFile(std::ofstream& ofs) const;
	void readFromBinaryFile(std::ifstream& ifs);

private:
	MyString _courseName;
	MyString _taskName;
	//MyString _description; 
	Vector<Submission> _submissions;
};


