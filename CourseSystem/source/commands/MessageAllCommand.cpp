// Teodor Patov 2MI0600491

#include "../../headers/command/MessageAllCommand.h"
#include <iostream>

Vector<MyString> MessageAllCommand::usernames;

MessageAllCommand::MessageAllCommand(const MyString& buffer, Context& system) : Command(buffer, system) {
	setUsernames();
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
		int userId = context.user_repo[i].getId();
		if (userId == context.user_id) {
			continue; 
		}

		User* user = context.user_repo.getUser(userId);
		if (!user) {
			std::cout << "User with ID " << userId << " not found." << std::endl;
			continue; 
		}

		user->receiveMessage(msg);
	}
	this->saveMessage(MESSAGES_FILE, msg);

}

MyString MessageAllCommand::getMessageContentFromBuffer() const {
	Vector<MyString> tokens = split(buffer, " ");
	if (tokens.size() < 2) {
		return "";
	}

	MyString content;
	for (size_t i = 1; i < tokens.size(); i++) {
		content += tokens[i];
		if (i < tokens.size() - 1) {
			content += " ";
		}
	}

	return content;
}

void MessageAllCommand::setUsernames() {
	if (this->usernames.size() > 0) {
		return;
	}

	for (size_t i = 0; i < context.user_repo.getSize(); i++) {
		int userId = context.user_repo[i].getId();
		if (userId == this->context.user_id) {
			continue; 
		}

		User* user = context.user_repo.getUser(userId);
		if (!user) {
			std::cout << "User with ID " << userId << " not found." << std::endl;
			continue;
		}

		this->usernames.push_back(user->username());
	}

}

void MessageAllCommand::saveMessage(const MyString& filename, const Message& message) const{
	std::ofstream ofs(filename.data(), std::ios::binary | std::ios::app);
	if (!ofs.is_open()) {
		std::cerr << "Error opening file for writing: " << filename << std::endl;
		return;
	}

	message.writeToFile(ofs);
	ofs.close();
}


