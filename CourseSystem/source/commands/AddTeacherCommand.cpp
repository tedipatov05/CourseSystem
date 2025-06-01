// Teodor Patov 2MI0600491

#include "../../headers/command/AddTeacherCommand.h"

#include <iostream>

#include "../../headers/users/Teacher.h"
#include "../../headers/Constants.h"

AddTeacherCommand::AddTeacherCommand(const MyString& buffer, Context& system) : Command(buffer, system){
	
}



void AddTeacherCommand::execute(){
	if (context.user_type != UserType::Admin) {
		std::cout << "You are not an admin!" << std::endl;
		return;
	}

	User* user = new Teacher(getFirstNameFromBuffer(), getLastNameFromBuffer(), getPasswordFromBuffer(), Context::next_user_id);
	Context::next_user_id++;
	context.user_repo.addUser(user);

	std::ofstream file(USERS_FILE.data(), std::ios::binary | std::ios::app);
	if (!file.is_open()) {
		return;
	}

	user->writeToBinaryFile(file);

	std::cout << "Added teacher " << user->getFirstName() << " " << user->getLastName() << " with ID " << user->getId() << std::endl;


}


MyString AddTeacherCommand::getPasswordFromBuffer() const {
	Vector<MyString> tokens = split(buffer, " ");
	if (tokens.size() < 3) {
		return "";
	}
	return tokens[3];
}

MyString AddTeacherCommand::getFirstNameFromBuffer() const {
	Vector<MyString> tokens = split(buffer, " ");
	if (tokens.size() < 3) {
		return "";
	}
	return tokens[1];
}
MyString AddTeacherCommand::getLastNameFromBuffer() const {
	Vector<MyString> tokens = split(buffer, " ");
	if (tokens.size() < 3) {
		return "";
	}
	return tokens[2];
}



