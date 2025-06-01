
// Teodor Patov 2MI0600491

#include "../../headers/command/ViewSubmissionsCommand.h"
#include <iostream>

ViewSubmissionsCommand::ViewSubmissionsCommand(const MyString& buffer, Context& context) :Command(buffer, context) {

}

void ViewSubmissionsCommand::execute() {
	if (context.user_id == -1){
		std::cout << "You are not logged in!" << std::endl;
		return;
	}
	if (context.user_type != UserType::Teacher) {
		std::cout << "You do not have permission to view submissions!" << std::endl;
		return;
	}

	MyString courseName = getCourseName();
	MyString homeworkName = getHomeworkName();
	Assignment* assignment = context.findAssignmentByName(courseName, homeworkName);
	if (assignment == nullptr) {
		std::cout << "Assignment not found." << std::endl;
		return;
	}
	User* user = context.user_repo.getUser(context.user_id);
	if (user == nullptr) {
		std::cout << "User not found." << std::endl;
		return;
	}
	Course* course = context.findCourseByName(courseName);
	if (course == nullptr) {
		std::cout << "Course not found." << std::endl;
		return;
	}
	if (!course->isUserInCourse(user->getId())) {
		std::cout << "You are not enrolled in this course." << std::endl;
		return;
	}

	assignment->printSubmissions();

}



MyString ViewSubmissionsCommand::getCourseName() const {
	Vector<MyString> tokens = split(buffer, " ");
	if (tokens.size() < 2) {
		return "";
	}
	return tokens[1];
}

MyString ViewSubmissionsCommand::getHomeworkName() const {
	Vector<MyString> tokens = split(buffer, " ");
	if (tokens.size() < 3) {
		return "";
	}
	return tokens[2];
}
