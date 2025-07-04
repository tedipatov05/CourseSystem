// Teodor Patov 2MI0600491

#include "../../headers/command/MessageStudentsCommand.h"
#include <iostream>

MessageStudentsCommand::MessageStudentsCommand(const MyString& buffer, Context& context) : Command(buffer, context){
	
}

void MessageStudentsCommand::execute() {
	MyString courseName = getCourseName();
	MyString content = getContent();

	if (courseName.isEmpty() || content.isEmpty()) {
		std::cout << "Invalid command format." << std::endl;
		return;
	}

	Course* course = context.findCourseByName(courseName);
	if (!course) {
		std::cout << "Course not found!" << std::endl;
		return;
	}

	Vector<MyString> receivers = getReceivers(*course);
	if (receivers.is_empty()) {
		std::cout << "No valid receivers specified." << std::endl;
		return;
	}

	Message* message = new Message(content, receivers, context.user_repo.getUser(context.user_id)->username());

	for (size_t i = 0; i < context.user_repo.getSize(); i++){
		int userId = context.user_repo[i].getId();
		if (course->isUserInCourse(userId) && context.user_repo[i].role() == UserType::Student) {
			context.user_repo.getUser(userId)->receiveMessage(*message);
		}
	}

	this->saveMessage(MESSAGES_FILE, *message);
}

void MessageStudentsCommand::saveMessage(const MyString& filename, const Message& message) const {
	std::ofstream file(filename.data(), std::ios::binary | std::ios::app);
	if (!file.is_open()) {
		std::cout << "Failed to open file: " << filename << std::endl;
		return;
	}

	message.writeToFile(file);
	file.close();
}



MyString MessageStudentsCommand::getCourseName() const {
	Vector<MyString> tokens = split(buffer, " ");
	if (tokens.size() < 2) {
		return "";
	}
	return tokens[1];
}

Vector<MyString> MessageStudentsCommand::getReceivers(const Course& course) const {
	Vector<MyString> receivers;
	
	for (size_t i = 0; i < course.getUsers().size(); i++) {
		User* user = context.user_repo.getUser(course.getUsers()[i]);
		if (!user || user->role() != UserType::Student) {
			continue; 
		}
		receivers.push_back(user->username());
	}

	return receivers;
}

MyString MessageStudentsCommand::getContent() const {
	Vector<MyString> tokens = split(buffer, " ");
	if (tokens.size() < 3) {
		return "";
	}

	MyString content;
	for (size_t i = 2; i < tokens.size(); i++) {
		content += tokens[i] + " ";
	}
	return content;
}
