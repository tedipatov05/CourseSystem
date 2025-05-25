#include "../../headers/command/MessageAllCommand.h"
#include <iostream>

Vector<MyString> MessageAllCommand::usernames;

MessageAllCommand::MessageAllCommand(const MyString& buffer, Context& system) : Command(buffer, system) {
	setUsernames();
}

MyString MessageAllCommand::getCommand() const {
	return "message_all";
}

void MessageAllCommand::execute() {
	MyString messageContent = getMessageContentFromBuffer();
	if (messageContent == "") {
		std::cout << "No message content provided." << std::endl;
		return;
	}
	User* admin = context.user_repo.getUser(context.user_id);
	if (!admin) {
		std::cout << "Admin not found" << std::endl;
	}

	if (context.user_type != UserType::Admin) {
		std::cout << "Only admin can send messages to all students." << std::endl;
		return;
	}

	Message msg = Message(messageContent, usernames, admin->username());

	for (size_t i = 0; i < context.user_repo.getSize(); i++) {
		if (i == context.user_id) {
			continue; // Skip the admin
		}

		User* user = context.user_repo.getUser(i);
		user->receiveMessage(msg);
	}


}

MyString MessageAllCommand::getMessageContentFromBuffer() const {
	Vector<MyString> tokens = split(buffer, " ");
	if (tokens.size() < 2) {
		return "";
	}

	return tokens[1];
}

void MessageAllCommand::setUsernames() const {
	if (this->usernames.size() > 0) {
		return;
	}

	for (size_t i = 0; i < context.user_repo.getSize(); i++) {
		if (i == this->context.user_id) {
			continue; // Skip the admin
		}
		User* user = context.user_repo.getUser(i);

		this->usernames.push_back(user->username());
	}

}

