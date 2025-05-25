#include "../../headers/command/ClearMailboxCommand.h"

#include <iostream>

#include "../../headers/Context.h"

ClearMailboxCommand::ClearMailboxCommand(const MyString& buffer, Context& system) : Command(buffer, system){
}

void ClearMailboxCommand::execute() {
	User* user = context.user_repo.getUser(context.user_id);
	if (user) {
		user->mailbox.clear();
	}
}

MyString ClearMailboxCommand::getCommand() const {
	return "clear_mailbox";
}

void ClearMailboxCommand::clearFile(const MyString& filename, int userId) const {
	std::ofstream file(filename.data(), std::ios::binary | std::ios::trunc);
	if (!file.is_open()) {
		std::cout << "Failed to open file: " << filename << std::endl;
		return;
	}

	for (size_t i = 0; i < context.user_repo.getSize(); i++){
		User* user = context.user_repo.getUser(i);
		if (user && user->getId() != userId) {
			user->mailbox.writeToBinaryFile(file);
		}
	}

	
}


