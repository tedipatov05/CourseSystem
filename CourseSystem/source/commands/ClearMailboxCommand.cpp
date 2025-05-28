#include "../../headers/command/ClearMailboxCommand.h"

#include <iostream>

#include "../../headers/Context.h"

ClearMailboxCommand::ClearMailboxCommand(const MyString& buffer, Context& system) : Command(buffer, system), _mailbox() {
}

void ClearMailboxCommand::execute() {
	User* user = context.user_repo.getUser(context.user_id);
	if (user) {
		user->mailbox.clear();
		this->loadMessages(MESSAGES_FILE);
		clearFile(MESSAGES_FILE, user->username());
	}
}

MyString ClearMailboxCommand::getCommand() const {
	return "clear_mailbox";
}

void ClearMailboxCommand::clearFile(const MyString& filename, const MyString& username) const {
	std::ofstream file(filename.data(), std::ios::binary | std::ios::trunc);
	if (!file.is_open()) {
		std::cout << "Failed to open file: " << filename << std::endl;
		return;
	}

	for (size_t i = 0; i < _mailbox.getSize(); i++) {
		if (_mailbox[i].receivers().contains(username)) {
			Message& msg = (Message&)_mailbox[i];
			msg.removeReceiver(username);
			if (msg.receivers().size() == 0){
				continue;
			}
			msg.writeToFile(file);
		}
	}


}

void ClearMailboxCommand::loadMessages(const MyString& filename) {
	std::ifstream file(filename.data(), std::ios::binary);
	if (!file.is_open()) {
		std::cout << "Failed to open file: " << filename << std::endl;
		return;
	}

	while (!file.eof()) {
		Message msg;
		msg.readFromFile(file);
		if (strlen(msg.content()) > 0) {
			_mailbox.addMessage(msg);
		}
	}
	file.close();

}





