#include "../../headers/command/CreateCourseCommand.h"
#include "../../headers/Constants.h"
#include <iostream>

CreateCourseCommand::CreateCourseCommand(const MyString& buffer, Context& system) : Command(buffer, system){
}

MyString CreateCourseCommand::getCommand() const {
	return "create_course";
}

MyString CreateCourseCommand::getCourseNameFromBuffer() const {
	Vector<MyString> tokens = split(buffer, " ");
	if (tokens.size() < 3) {
		return "";
	}
	return tokens[1];
}

MyString CreateCourseCommand::getCoursePasswordFromBuffer() const {
	Vector<MyString> tokens = split(buffer, " ");
	if (tokens.size() < 3) {
		return "";
	}
	return tokens[2];
}
void CreateCourseCommand::execute() {
	if (context.user_type != UserType::Teacher) {
		std::cout << "You are not a teacher!" << std::endl;
		return;
	}

	Course* course = new Course(getCourseNameFromBuffer(), getCoursePasswordFromBuffer());
	context.courses.push_back(*course);

	std::ofstream ofs(COURSES_FILE.data(), std::ios::binary | std::ios::app);
	if (!ofs.is_open()) {
		return;
	}

	course->writeToBinaryFile(ofs);
	ofs.close();
	

	std::cout << "Successfully created course: " << course->getCourseName();
}
