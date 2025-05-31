// Teodor Patov 2MI0600491

#include "../../headers/command/EnrollCommand.h"

#include <iostream>

EnrollCommand::EnrollCommand(const MyString& buffer, Context& ctx) : Command(buffer, ctx){
	
}

MyString EnrollCommand::getCommand() const {
	return "enroll";
}

void EnrollCommand::execute() {
	if (context.user_id == -1) {
		std::cout << "You are not logged in!" << std::endl;
		return;
	}

	if (context.user_type != UserType::Student) {
		std::cout << "Only students can enroll in courses!" << std::endl;
		return;
	}

	MyString courseName = getCourseName();
	MyString coursePassword = getCoursePassword();

	Course* course = context.findCourseByName(courseName);
	if (course == nullptr) {
		std::cout << "Course not found!" << std::endl;
		return;
	}

	if (!course->isPasswordCorrect(coursePassword)) {
		std::cout << "Incorrect password!" << std::endl;
		return;
	}

	if (course->isUserInCourse(context.user_id)) {
		std::cout << "You are already enrolled in this course!" << std::endl;
		return;
	}

	User* user = context.user_repo.getUser(context.user_id);
	if (user == nullptr) {
		std::cout << "User not found!" << std::endl;
		return;
	}

	course->addParticipant(user);

	saveAddedUser(USERS_COURSES_FILE, courseName, user->getId());
	std::cout << "Successfully enrolled in the course: " << courseName << std::endl;
}

void EnrollCommand::saveAddedUser(const MyString& filename, const MyString& courseName, int userId) const {
	std::ofstream ofs(filename.data(), std::ios::binary | std::ios::app);
	if (!ofs.is_open()) {
		return;
	}

	ofs.write((char*)(&userId), sizeof(userId));
	courseName.writeToBinaryFile(ofs);

	ofs.close();
}

MyString EnrollCommand::getCourseName() const {
	Vector<MyString> tokens = split(buffer, " ");
	if (tokens.size() < 2) {
		std::cout << "Usage: enroll <course_name> [password]" << std::endl;
		return MyString();
	}

	return tokens[1];
}

MyString EnrollCommand::getCoursePassword() const {
	Vector<MyString> tokens = split(buffer, " ");
	if (tokens.size() < 3) {
		return MyString(); 
	}

	return tokens[2];
}

