#pragma once
#include "Command.h"

enum class CommandType : MyString {
	Login = "login",
	Logout = "logout",
	AddTeacher = "add_teacher",
	AddStudent = "add_student",
	MessageAll = "message_all",
	ChangePassword = "change_password",
	CreateCourse = "create_course",
	EnrollInCourse = "enroll",
	AddToCourse = "add_to_course",
	Mailbox = "mailbox",
	AssignHomework = "assign_homework",
	MessageStudents = "message_students",
	Message = "message",
	SubmitAssignment = "submit_assignment",
	ViewSubmission = "view_assignment_submissions",
	GradeAssignment = "grade_assignment",
	ClearMailbox = "clear_mailbox",
	Grade = "grade",

};



