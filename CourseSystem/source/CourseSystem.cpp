// CourseSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "../headers/Context.h"
#include "../headers/command/CommandFactory.h"
#include "../headers/users/Admin.h"
#include "../headers/users/Teacher.h"
#include "../headers/users/Student.h"


int main()
{

	Context* context = Context::getInstance();

	while (true){
		std::cout << "> ";
		char buffer[1024];

		std::cin.getline(buffer, 1024);

		MyString command(buffer);

		if (command.isEmpty()) {
			break;
		}

		Command* cmd = CommandFactory::createCommand(command, *context);

		if (cmd){
			cmd->execute();
			delete cmd;
		}

		
	}

	//UserRepository repo;
	//repo.addUser(new Admin("Admin", "Adminov", "0000", 0));
	//repo.addUser(new Teacher("Peter", "Petrov", "qwerty", 100));
	//repo.addUser(new Student("Ivan", "Ivanov", "1234", 101));
	//repo.writeToBinaryFile(USERS_FILE);

	/*Course course("OOP_SE", "cooked");
	std::ofstream ofs(COURSES_FILE.data(), std::ios::binary);
	course.writeToBinaryFile(ofs);
	ofs.close();*/

	//MyString courseName = "OOP_SE";
	//int id = 100;
	//std::ofstream ofs2(USERS_COURSES_FILE.data(), std::ios::binary);
	//ofs2.write(reinterpret_cast<const char*>(&id), sizeof(int));
	//courseName.writeToBinaryFile(ofs2);
	//ofs2.close();

}

