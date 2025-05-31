
// Teodor Patov 2MI0600491

#pragma once
#include "../../headers/command/ViewGradesCommand.h"
#include "../../headers/command/AddStudentCommand.h"
#include "../../headers/command/AddStudentCommand.h"
#include "../../headers/command/AddToCourseCommand.h"
#include "../../headers/command/ChangePasswordCommand.h"
#include "../../headers/command/CreateCourseCommand.h"
#include "../../headers/command/AddTeacherCommand.h"
#include "../../headers/command/AssignHomeworkCommand.h"
#include "../../headers/command/ChangePasswordCommand.h"
#include "../../headers/command/MessageAllCommand.h"
#include "../../headers/command/MessageStudentsCommand.h"
#include "../../headers/command/MessageUserCommand.h"
#include "../../headers/command/ClearMailboxCommand.h"
#include "../../headers/command/MailboxCommand.h"
#include "../../headers/command/LogoutCommand.h"
#include "../../headers/command/LoginCommand.h"
#include "../../headers/command/GradeAssignmentCommand.h"
#include "../../headers/command/ViewSubmissionsCommand.h"
#include "../../headers/command/SubmitAssignmentCommand.h"
#include "../../headers/command/EnrollCommand.h"
#include "../../headers/command/ViewAssignmentsCommand.h"


class CommandFactory {

public:
	static Command* createCommand(const MyString& buffer, Context& context);
};



