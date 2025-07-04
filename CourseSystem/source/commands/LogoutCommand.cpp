// Teodor Patov 2MI0600491

#include "../../headers/command/LogoutCommand.h"
#include <iostream>

LogoutCommand::LogoutCommand(const MyString& buffer, Context& system) : Command(buffer, system) {
}


void LogoutCommand::execute(){
	if (this->context.user_id != -1){
		this->context.user_id = -1;
		this->context.user_type = UserType::None;

		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		
	} else{
		std::cout << "You are not logged in." << std::endl;
	}
}


