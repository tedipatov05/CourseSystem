#pragma once
#include "courses/Course.h"
#include "users/UserRepository.h"
#include "Vector.hpp"
#include "MyString.h"

class Context
{
public:

	UserRepository user_repo;
	Vector<Course> courses;
	UserType user_type;
	int user_id;
	static int next_user_id;


	void readFromBinaryFile(const MyString& usersFilename, const MyString& coursesFilename, const MyString& messagesFile, const MyString& usersCoursesFile, 
		const MyString& assignmentsFile, const MyString& submissionsFile, const MyString& gradesFile);

	User* findUserByUsername(const MyString& username) const;
	Course* findCourseByName(const MyString& courseName) const;
	Assignment* findAssignmentByName(const MyString& course, const MyString& assignmentName) const;
	Submission* findSubmissionByName(const MyString& course, const MyString& assignmentName, int userId) const;


	void readMessages(const MyString& filename);
	void readCourses(const MyString& filename);
	void readUserCourses(const MyString& filename);
	void readAssignments(const MyString& filename);
	void readSubmissions(const MyString& filename);
	void readGrades(const MyString& filename);
	void setNextUserId();

	Context(const Context& other) = delete;
	Context& operator=(const Context& other) = delete;

	static Context* getInstance();

protected:

	static Context* instance;

private:
	Context();
	Context(const UserRepository& user_repo, const Vector<Course>& courses);
	Context(const MyString& usersFilename, const MyString& coursesFilename, const MyString& messagesFile, const MyString& usersCoursesFile,
		const MyString& assignmentsFile, const MyString& submissionsFile, const MyString& gradesFile);
};

