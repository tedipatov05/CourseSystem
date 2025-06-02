// Teodor Patov 2MI0600491

#include <iostream>
#include "../headers/Context.h"
#include "../headers/command/CommandFactory.h"



int main()
{

	Context* context = Context::getInstance();

	while (true){
		std::cout << "> ";
		char buffer[1024];

		std::cin.getline(buffer, 1024);

		MyString command(buffer);

		if (command.isEmpty()) {
			std::cout << "Thank you for using my Course System! " << std::endl;
			break;
		}

		Command* cmd = CommandFactory::createCommand(command, *context);

		if (cmd){
			cmd->execute();
			delete cmd;
		}

		

		
	}


	

}

