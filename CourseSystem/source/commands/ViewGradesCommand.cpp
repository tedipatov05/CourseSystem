#include "../../headers/command/ViewGradesCommand.h"

#include <iostream>

ViewGradesCommand::ViewGradesCommand(const MyString& buffer, Context& system) : Command(buffer, system) {
}

MyString ViewGradesCommand::getCommand() const {
	return "view_grades";
}

void ViewGradesCommand::execute() {
	if (this->context.user_id == -1) {
		std::cout << "You are not logged in." << std::endl;
		return;
	}

	if (this->context.user_type != UserType::Student) {
		std::cout << "You are not a student." << std::endl;
		return;
	}

	User* user = context.user_repo.getUser(context.user_id);
	if (user == nullptr) {
		std::cout << "User not found." << std::endl;
		return;
	}

	this->loadGrades(GRADES_FILE);
	if (grades.is_empty()) {
		std::cout << "No grades found." << std::endl;
		return;
	}

	for (size_t i = 0; i < grades.size(); i++) {
		if (grades[i].getUserId() == user->getId()){
			grades[i].printGrade();
		}
	}

}

void ViewGradesCommand::loadGrades(const MyString& filename){
	std::ifstream ifs(filename.data(), std::ios::binary | std::ios::app);
	if (!ifs.is_open()) {
		std::cout << "Failed to open file: " << filename << std::endl;
		return;
	}
	while (!ifs.eof()) {
		Grade grade;
		grade.readFromBinaryFile(ifs);

		grades.push_back(grade);
	}


	
}

