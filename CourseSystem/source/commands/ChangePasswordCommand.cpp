#include "../../headers/command/ChangePasswordCommand.h"
#include "../../headers/users/UserFactory.h"

#include <iostream>

ChangePasswordCommand::ChangePasswordCommand(const MyString& buffer, Context& context)
	: Command(buffer, context) {
}

void ChangePasswordCommand::execute() {
	User* user = context.user_repo.getUser(context.user_id);
	if (user) {
		MyString oldPassword = split(buffer, " ")[1];
		MyString newPassword = split(buffer, " ")[2];
		if (user->getPassword() != oldPassword) {
			std::cout << "Old password is incorrect!" << std::endl;
			return;
		}
		user->changePassword(newPassword);

		modifyUserInFile(USERS_FILE, user);
	}
	else {
		std::cout << "User not found!" << std::endl;
	}
}

MyString ChangePasswordCommand::getCommand() const {
	return "change_password";
}


// TODO: check if it works
void ChangePasswordCommand::modifyUserInFile(const MyString& filename, const User* user) const {
	std::ifstream stream(filename.data(), std::ios::binary);
	if (!stream.is_open()) {
		std::cout << "Failed to open file: " << filename << std::endl;
		return;
	}

	int pos;

	while (!stream.eof()){
		int startPos = stream.tellg();

		UserType type;
		stream.read((char*)(&type), sizeof(UserType));

		User* oldUser = Factory::createUser(type);
		if (!oldUser) {
			std::cout << "Failed to create user from file." << std::endl;
			return;
		}
		oldUser->readFromBinaryFile(stream);

		if (oldUser->getId() == user->getId()){
			pos = startPos;
			break;
		}

	}

	stream.close();

	std::ofstream ofs(filename.data(), std::ios::binary | std::ios::app);
	if (!ofs.is_open()) {
		std::cout << "Failed to open file for writing: " << filename << std::endl;
		return;
	}
	ofs.seekp(pos, std::ios::beg);
	user->writeToBinaryFile(ofs);


}