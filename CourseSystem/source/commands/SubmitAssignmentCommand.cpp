#include "../../headers/command/SubmitAssignmentCommand.h"

#include <iostream>

SubmitAssignmentCommand::SubmitAssignmentCommand(const MyString& buffer, Context& ctx) : Command(buffer, ctx) {

}
MyString SubmitAssignmentCommand::getCommand() const {
	return "submit_assignment";
}

void SubmitAssignmentCommand::execute() {
	if (this->context.user_id == -1) {
		std::cout << "You are not logged in." << std::endl;
		return;
	}

	if (this->context.user_type != UserType::Student) {
		std::cout << "You are not a student." << std::endl;
		return;
	}

	MyString courseName = getCourseName();
	MyString homeworkName = getHomeworkName();
	MyString content = getContent();

	Course* course = context.findCourseByName(courseName);
	Assignment* assignment = context.findAssignmentByName(courseName, homeworkName);
	if (assignment == nullptr) {
		std::cout << "Assignment not found." << std::endl;
		return;
	}

	if (!course->isUserInCourse(context.user_id)) {
		std::cout << "You are not enrolled in this course." << std::endl;
		return;
	}
	User* user = context.user_repo.getUser(context.user_id);

	Submission* submission = new Submission(user->username(), content, courseName, homeworkName, user->getId());
	assignment->addSubmission(*submission);

	this->saveSubmission(SUBMISSIONS_FILE, *submission);

	delete submission;

}

MyString SubmitAssignmentCommand::getCourseName() const {
	Vector<MyString> tokens = split(buffer, " ");
	if (tokens.size() < 2) {
		return "";
	}
	return tokens[1];
}
MyString SubmitAssignmentCommand::getHomeworkName() const {
	Vector<MyString> tokens = split(buffer, " ");
	if (tokens.size() < 3) {
		return "";
	}
	return tokens[2];
}

MyString SubmitAssignmentCommand::getContent() const {
	Vector<MyString> tokens = split(buffer, " ");
	if (tokens.size() < 4) {
		return "";
	}
	MyString content;
	for (size_t i = 3; i < tokens.size(); i++) {
		content += tokens[i] + " ";
	}
	return content;
}

void SubmitAssignmentCommand::saveSubmission(const MyString& filename, const Submission& submission) const {
	std::ofstream ofs(filename.data(), std::ios::binary | std::ios::app);
	if (!ofs.is_open()) {
		std::cerr << "Error opening file for writing." << std::endl;
		return;
	}

	submission.writeToBinaryFile(ofs);
	ofs.close();
}

