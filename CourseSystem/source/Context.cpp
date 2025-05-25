#include "../headers/Context.h"


int Context::next_user_id = 100;


Context::Context() : Context(USERS_FILE, COURSES_FILE, MESSAGES_FILE, USERS_COURSES_FILE, ASSIGNMENTS_FILE, SUBMISSIONS_FILE, GRADES_FILE){
	
}


Context::Context(const UserRepository& user_repo, const Vector<Course>& courses) : user_repo(user_repo), courses(courses) {
	this->user_type = UserType::None;
	this->user_id = -1;
}
Context::Context(const MyString& usersFilename, const MyString& coursesFilename, const MyString& messagesFile, const MyString& usersCoursesFile,
	const MyString& assignmentsFile, const MyString& submissionsFile, const MyString& gradesFile) {

	this->readFromBinaryFile(usersFilename, coursesFilename, messagesFile, usersCoursesFile, assignmentsFile, submissionsFile, gradesFile);
}

void Context::readFromBinaryFile(const MyString& usersFilename, const MyString& coursesFilename, const MyString& messagesFile, const MyString& usersCoursesFile, 
	const MyString& assignmentsFile, const MyString& submissionsFile, const MyString& gradesFile) {
	this->user_repo.readFromBinaryFile(usersFilename);
	this->readCourses(coursesFilename);
	this->readMessages(messagesFile);
	this->readUserCourses(usersCoursesFile);
	this->readAssignments(assignmentsFile);
	this->readSubmissions(submissionsFile);
	this->readGrades(gradesFile);

}

void Context::readMessages(const MyString& filename){
	std::ifstream ifs(filename.data(), std::ios::binary);
	if (!ifs.is_open()) {
		return;
	}

	while (!ifs.eof()) {
		Message message;
		message.readFromFile(ifs);

		for (size_t i = 0; i < message.receivers().size(); i++){
			User* receiver = this->findUserByUsername(message.receivers()[i]);
			if (receiver == nullptr) {
				continue;
			}
			receiver->receiveMessage(message);
		}

	}

	ifs.close();

}

void Context::readCourses(const MyString& filename) {
	std::ifstream ifs(filename.data(), std::ios::binary);
	if (!ifs.is_open()) {
		return;
	}

	while (!ifs.eof()) {
		Course course;
		course.readFromBinaryFile(ifs);
		this->courses.push_back(course);
	}

	ifs.close();
}

void Context::readUserCourses(const MyString& filename) {
	std::ifstream ifs(filename.data(), std::ios::binary);
	if (!ifs.is_open()) {
		return;
	}

	while (!ifs.eof()) {
		int userId;
		ifs.read((char*)(&userId), sizeof(userId));
		User* user = this->user_repo.getUser(userId);
		if (user == nullptr) {
			continue;
		}
		MyString courseName;
		courseName.readFromBinaryFile(ifs);
		this->findCourseByName(courseName)->addParticipant(user);
	}

	ifs.close();
}

void Context::readAssignments(const MyString& filename){
	std::ifstream ifs(filename.data(), std::ios::binary);
	if (!ifs.is_open()) {
		return;
	}

	while (!ifs.eof()) {
		Assignment assignment;
		assignment.readFromBinaryFile(ifs);
		if (assignment.getCourseName().isEmpty()) {
			continue;
		}
		this->findCourseByName(assignment.getCourseName())->addAssignment(assignment);
	}

	ifs.close();

}

void Context::readSubmissions(const MyString& filename){
	std::ifstream ifs(filename.data(), std::ios::binary);
	if (!ifs.is_open()) {
		return;
	}

	while (!ifs.eof()) {
		Submission submission;
		submission.readFromBinaryFile(ifs);
		if (submission.getCourseName().isEmpty()) {
			continue;
		}

		this->findAssignmentByName(submission.getCourseName(), submission.getAssignment())->addSubmission(submission);
		
	}

	ifs.close();

}

void Context::readGrades(const MyString& filename){
	std::ifstream ifs(filename.data(), std::ios::binary);
	if (!ifs.is_open()) {
		return;
	}

	while (!ifs.eof()) {
		Grade grade;
		grade.readFromBinaryFile(ifs);
		if (grade.getCourseName().isEmpty()) {
			continue;
		}

		this->findSubmissionByName(grade.getCourseName(), grade.getAssignment(), grade.getUserId())->setGrade(grade);

	}

	ifs.close();


}




Course* Context::findCourseByName(const MyString& courseName) const {
	for (int i = 0; i < this->courses.size(); i++) {
		if (this->courses[i].getCourseName() == courseName) {
			return (Course*)&this->courses[i];
		}
	}
	return nullptr;
}


User* Context::findUserByUsername(const MyString& username) const{
	for (int i = 0; i < this->user_repo.getSize(); i++) {
		if (this->user_repo.getUser(i)->username() == username) {
			return this->user_repo.getUser(i);
		}
	}
	return nullptr;
	
}

Assignment* Context::findAssignmentByName(const MyString& course, const MyString& assignmentName) const {
	Course* coursePtr = this->findCourseByName(course);
	if (coursePtr == nullptr) {
		return nullptr;
	}
	for (int i = 0; i < coursePtr->getAssignments().size(); i++) {
		if (coursePtr->getAssignments()[i].getTaskName() == assignmentName) {
			return (Assignment*)&coursePtr->getAssignments()[i];
		}
	}
	return nullptr;
}

Submission* Context::findSubmissionByName(const MyString& course, const MyString& assignmentName, int userId) const {
	Assignment* assignment = this->findAssignmentByName(course, assignmentName);
	if (assignment == nullptr) {
		return nullptr;
	}
	for (int i = 0; i < assignment->getSubmissions().size(); i++) {
		if (assignment->getSubmissions()[i].getUserId() == userId) {
			return (Submission*)&assignment->getSubmissions()[i];
		}
	}
	return nullptr;
}








