#include "../../headers/command/MessageUserCommand.h"

#include <iostream>

MessageUserCommand::MessageUserCommand(const MyString& buffer, Context& context) : Command(buffer, context){
	
}

void MessageUserCommand::execute() {
	int userId = getUserId();
	MyString content = getContent();

	User* user = context.user_repo.getUser(userId);
	if (!user) {
		std::cout << "User not found." << std::endl;
		return;
	}
	User* sender = context.user_repo.getUser(context.user_id);

	Vector<MyString> receivers;
	receivers.push_back(user->username());

	Message* message = new Message(content, receivers, sender->username());

	user->receiveMessage(*message);

	this->saveMessageInFile(MESSAGES_FILE, *message);
	
	std::cout << "Message sent to user with ID: " << userId << std::endl;
}

void MessageUserCommand::saveMessageInFile(const MyString& filename, const Message& message) const{
	std::ofstream file(filename.data(), std::ios::binary | std::ios::app);
	if (!file.is_open()) {
		std::cout << "Failed to open file: " << filename << std::endl;
		return;
	}

	message.writeToFile(file);
	file.close();
	
}


MyString MessageUserCommand::getCommand() const {
	return "message";
}

int MessageUserCommand::getUserId() const {
	Vector<MyString> tokens = split(buffer, " ");
	if (tokens.size() < 2) {
		std::cout << "Invalid command format. Usage: message <user_id> <message_content>" << std::endl;
		return -1;
	}
	return toInt(tokens[1]);
}

MyString MessageUserCommand::getContent() const {
	Vector<MyString> tokens = split(buffer, " ");
	if (tokens.size() < 3) {
		std::cout << "Invalid command format. Usage: message <user_id> <message_content>" << std::endl;
		return "";
	}
	MyString content;
	for (size_t i = 2; i < tokens.size(); i++) {
		content += tokens[i] + " ";
	}
	return content;
}




