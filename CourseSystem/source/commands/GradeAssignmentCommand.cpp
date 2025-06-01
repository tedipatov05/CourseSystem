
// Teodor Patov 2MI0600491
#include "../../headers/command/GradeAssignmentCommand.h"
#include <iostream>

GradeAssignmentCommand::GradeAssignmentCommand(const MyString& buffer, Context& system) : Command(buffer, system) {

}

void GradeAssignmentCommand::execute() {
	if (this->context.user_id == -1) {
		std::cout << "You are not logged in." << std::endl;
		return;
	}

	if (this->context.user_type != UserType::Teacher) {
		std::cout << "You are not a teacher." << std::endl;
		return;
	}

	Vector<MyString> tokens = split(this->buffer, " ");

	const MyString& courseName = tokens[1];
	const MyString& assignmentName = tokens[2];
	int studentId = toInt(tokens[3]);
	double grade = toDouble(tokens[4]);
	MyString comment = getComment();

	if (courseName.isEmpty() || assignmentName.isEmpty() || studentId < 0 || grade < 0.0 || comment.isEmpty()) {
		std::cout << "Invalid input. Please check the course name, assignment name, student ID, grade, and comment." << std::endl;
		return;
	}

	Assignment* assignment = context.findAssignmentByName(courseName, assignmentName);
	if (assignment == nullptr) {
		std::cout << "Assignment not found." << std::endl;
		return;
	}

	Grade* newGrade = new Grade(assignmentName, courseName, comment, grade, studentId);

	for (size_t i = 0; i < assignment->getSubmissions().size(); i++){
		if (assignment->getSubmissions()[i].getUserId() == studentId) {
			Submission subm = assignment->getSubmissions()[i];
			subm.setGrade(*newGrade);
			break;
		}
	}

	User* teacher = context.user_repo.getUser(context.user_id);
	User* student = context.user_repo.getUser(studentId);
	MyString content = teacher->username();
	content += " has graded your assignment ";
	content += assignmentName;
	content += " in course ";
	content += courseName;

	Vector<MyString> receivers;
	receivers.push_back(student->username());
	Message msg(content, receivers, teacher->username());
	student->receiveMessage(msg);
	saveMessageInFile(MESSAGES_FILE, msg);

	saveGrade(GRADES_FILE, *newGrade);

	delete newGrade;

	
}

void GradeAssignmentCommand::saveGrade(const MyString& filename, const Grade& grade) {
	std::ofstream ofs(filename.data(), std::ios::binary | std::ios::app);
	if (!ofs.is_open()) {
		std::cout << "Failed to open file: " << filename << std::endl;
		return;
	}

	grade.writeToBinaryFile(ofs);

}

void GradeAssignmentCommand::saveMessageInFile(const MyString& filename, const Message& message) const {
	std::ofstream file(filename.data(), std::ios::binary | std::ios::app);
	if (!file.is_open()) {
		std::cout << "Failed to open file: " << filename << std::endl;
		return;
	}

	message.writeToFile(file);
	file.close();

}

MyString GradeAssignmentCommand::getComment() const {
	Vector<MyString> tokens = split(this->buffer, " ");
	if (tokens.size() < 6) {
		return "";
	}

	MyString comment;
	for (size_t i = 5; i < tokens.size(); ++i) {
		comment += tokens[i] + " ";
	}
	return comment;
}


