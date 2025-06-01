
// Teodor Patov 2MI0600491

#pragma once
#include "Command.h"

class MessageUserCommand :public Command{

public:

	MessageUserCommand(const MyString& buffer, Context& context);
	void execute() override;

private:

	MyString getContent() const;
	int getUserId() const;
	void saveMessageInFile(const MyString& filename, const Message& message) const;
};

