// CourseSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "../headers/Context.h"
#include "../headers/command/CommandFactory.h"
#include "../headers/command/AddToCourseCommand.h"
#include "../headers/users/Admin.h"


int main()
{

	User* admin = new Admin("Admin", "Adminov", "0000", 0);
	std::ofstream ofs(USERS_FILE.data(), std::ios::binary);
	admin->writeToBinaryFile(ofs);

}

