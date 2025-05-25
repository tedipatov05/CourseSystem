#include "../../headers/command/LoginCommand.h"

#include <iostream>

MyString LoginCommand::getCommand() const{
	return "login";
}

void LoginCommand::execute() {
	if (this->context.user_id != -1) {
		std::cout << "You are already logged in!" << std::endl;
		return;
	}
	User* user = this->context.user_repo.getUser(getIdFromBuffer());

	if (user != nullptr){
		if (user->getPassword() == getPasswordFromBuffer()) {
			std::cout << "Login successful!" << std::endl;
			std::cout << user->getFirstName() << " " << user->getLastName() << " | " << getRoleName(user->role()) << " | " << user->getId() << std::endl;
			context.user_type = user->role();
			context.user_id = user->getId();
		}
		else {
			std::cout << "Wrong password!" << std::endl;
		}
	}
	else {
		std::cout << "User not found!" << std::endl;
	}

}

LoginCommand::LoginCommand(const MyString& buffer, Context& context): Command(buffer, context)
{
}

int LoginCommand::getIdFromBuffer() const {
	MyString id = buffer.substr(0, buffer.find(" ", 0));

	return toInt(id);
}

MyString LoginCommand::getPasswordFromBuffer() const {
	MyString password = buffer.substr(buffer.find(" ", 0) + 1, buffer.find() - buffer.find(" ", 0));

	return password;
}

