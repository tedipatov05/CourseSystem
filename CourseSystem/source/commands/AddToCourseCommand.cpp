// Teodor Patov 2MI0600491

#include "../../headers/command/AddToCourseCommand.h"

#include <iostream>

AddToCourseCommand::AddToCourseCommand(const MyString& buffer, Context& context) :Command(buffer, context){
	
}

MyString AddToCourseCommand::getCommand() const {
	return "add_to_course";
}

int AddToCourseCommand::findCourseToAdd(const MyString& courseName) const {
	for (int i = 0; i < context.courses.size(); i++) {
		if (context.courses[i].getCourseName() == courseName) {
			return i;
		}
	}
	return -1;
}

void AddToCourseCommand::execute() {
	MyString courseName = getCourseNameFromBuffer();
	int userId = toInt(getUserIdFromBuffer());

	if (context.user_type != UserType::Teacher && context.user_type != UserType::Admin){
		std::cout << "You do not have permission to add users to courses!" << std::endl;
		return;
	}

	User* userToAdd = context.user_repo.getUser(userId);
	if (userToAdd == nullptr) {
		std::cout << "User not found!" << std::endl;
		return;
	}

	int courseIndex = findCourseToAdd(courseName);
	if (courseIndex == -1) {
		std::cout << "Course not found!" << std::endl;
		return;
	}

	Course* course = &context.courses[courseIndex];
	if (course->isUserInCourse(userId)) {
		std::cout << "User is already in the course!" << std::endl;
		return;
	}
	course->addParticipant(userToAdd);

	saveAddedUser(USERS_COURSES_FILE, courseName, userId);

}

MyString AddToCourseCommand::getCourseNameFromBuffer() const {
	Vector<MyString> tokens = split(buffer, " ");
	if (tokens.size() < 3) {
		return "";
	}
	return tokens[1];
}

MyString AddToCourseCommand::getUserIdFromBuffer() const {
	Vector<MyString> tokens = split(buffer, " ");
	if (tokens.size() < 3) {
		return "";
	}
	return tokens[2];
}

void AddToCourseCommand::saveAddedUser(const MyString& filename, const MyString& courseName, int userId) const{
	std::ofstream ofs(filename.data(), std::ios::binary | std::ios::app);
	if (!ofs.is_open()){
		return;
	}

	int id = userId;
	ofs.write((const char*)&id, sizeof(id));
	courseName.writeToBinaryFile(ofs);
	ofs.close();


}



