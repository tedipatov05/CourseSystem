#include "../../headers/command/AssignHomeworkCommand.h"

#include <iostream>

AssignHomeworkCommand::AssignHomeworkCommand(const MyString& buffer, Context& ctx) : Command(buffer, ctx){
	
}

MyString AssignHomeworkCommand::getCommand() const {
	return "assign_homework";
}

void AssignHomeworkCommand::execute() {
	if (this->context.user_type != UserType::Teacher) {
		std::cout << "You are not authorized to assign homework." << std::endl;
		return;
	}

	MyString courseName = getCourseName();
	MyString homeworkName = getHomeworkName();

	if (courseName.isEmpty() || homeworkName.isEmpty()) {
		std::cout << "Invalid course name or homework name." << std::endl;
		return;
	}

	Course* course = context.findCourseByName(courseName);
	if (course == nullptr) {
		std::cout << "Course not found!" << std::endl;
		return;
	}
	Assignment* assignment = new Assignment(homeworkName, course->getCourseName());
	course->addAssignment(*assignment);

	this->saveAssignment(ASSIGNMENTS_FILE, *assignment);

	delete assignment; 
	std::cout << "Successfully created a new assignment!" << std::endl;
}

void AssignHomeworkCommand::saveAssignment(const MyString& filename, const Assignment& assignment) const{
	std::ofstream ofs(filename.data(), std::ios::binary | std::ios::app);
	if (!ofs.is_open()) {
		std::cerr << "Error opening file for saving assignment." << std::endl;
		return;
	}

	assignment.writeToBinaryFile(ofs);
	ofs.close();
}

MyString AssignHomeworkCommand::getCourseName() const {
	Vector<MyString> tokens = split(buffer, " ");
	if (tokens.size() < 3) {
		return "";
	}
	return tokens[1];
}

MyString AssignHomeworkCommand::getHomeworkName() const {
	Vector<MyString> tokens = split(buffer, " ");
	if (tokens.size() < 4) {
		return "";
	}
	return tokens[2];
}


