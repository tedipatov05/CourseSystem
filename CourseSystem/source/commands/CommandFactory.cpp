#include "../../headers/command/CommandFactory.h"

#include <iostream>



Command* CommandFactory::createCommand(const MyString& buffer, Context& context) {
	Vector<MyString> tokens = Command::split(buffer, " ");

	if (tokens.is_empty()) {
		return nullptr;
	}
	MyString commandName = tokens[0];

	if (commandName == "change_password") {
		return new ChangePasswordCommand(buffer, context);
	}
	else if (commandName == "add_student") {
		return new AddStudentCommand(buffer, context);
	}
	else if (commandName == "add_to_course") {
		return new AddToCourseCommand(buffer, context);
	}
	else if (commandName == "create_course") {
		return new CreateCourseCommand(buffer, context);
	}
	else if (commandName == "add_teacher") {
		return new AddTeacherCommand(buffer, context);
	}
	else if (commandName == "assign_homework") {
		return new AssignHomeworkCommand(buffer, context);
	}
	else if (commandName == "message_all") {
		return new MessageAllCommand(buffer, context);
	}
	else if (commandName == "message_students") {
		return new MessageStudentsCommand(buffer, context);
	}
	else if (commandName == "message") {
		return new MessageUserCommand(buffer, context);
	}
	else if (commandName == "clear_mailbox") {
		return new ClearMailboxCommand(buffer, context);
	}
	else if (commandName == "mailbox") {
		return new MailboxCommand(buffer, context);
	}
	else if (commandName == "logout") {
		return new LogoutCommand(buffer, context);
	}
	else if (commandName == "login") {
		return new LoginCommand(buffer, context);
	}
	else if (commandName == "grade_assignment") {
		return new GradeAssignmentCommand(buffer, context);
	}
	else if (commandName == "view_assignment_submissions") {
		return new ViewSubmissionsCommand(buffer, context);
	}
	else if (commandName == "grade") {
		return new ViewGradesCommand(buffer, context);
	}
	else if (commandName == "submit_assignment") {
		return new SubmitAssignmentCommand(buffer, context);
	}
	else if (commandName == "enroll") {
		return new EnrollCommand(buffer, context);
	}
	else {
		std::cout << "Unknown command: " << commandName << std::endl;
		return nullptr;
	}


}
