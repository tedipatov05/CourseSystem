#pragma once
#include "Command.h"
#include "../Context.h"

class MessageAllCommand : public Command {

public:
	void execute() override;
	MyString getCommand() const override;
	MessageAllCommand(const MyString& buffer, Context& system);

	static Vector<MyString> usernames;

private:
	/*Context& context;
	MyString buffer;*/

	MyString getMessageContentFromBuffer() const;
	void setUsernames();
	void saveMessage(const MyString& filename, const Message& message) const;
};

