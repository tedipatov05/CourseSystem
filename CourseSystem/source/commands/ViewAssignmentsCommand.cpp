
// Teodor Patov 2MI0600491

#include "../../headers/command/ViewAssignmentsCommand.h"
#include <iostream>

ViewAssignmentsCommand::ViewAssignmentsCommand(const MyString& buffer, Context& context) :Command(buffer, context) {

}

void ViewAssignmentsCommand::execute() {
	if (context.user_id == -1) {
		std::cout << "You are not logged in!" << std::endl;
		return;
	}

	MyString courseName = getCourseName();
	Course* course = context.findCourseByName(courseName);
	if (course == nullptr) {
		std::cout << "Course not found." << std::endl;
		return;
	}
	if (!course->isUserInCourse(context.user_id)) {
		std::cout << "You are not enrolled in this course." << std::endl;
		return;
	}

	for (size_t i = 0; i < course->getAssignments().size(); i++) {
		course->getAssignments()[i].print();
	}
}


MyString ViewAssignmentsCommand::getCourseName() const {
	Vector<MyString> tokens = split(buffer, " ");
	if (tokens.size() < 2) {
		return "";
	}
	return tokens[1];
}