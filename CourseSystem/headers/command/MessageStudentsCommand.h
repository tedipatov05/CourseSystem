
// Teodor Patov 2MI0600491

#pragma once
#include "Command.h"

class MessageStudentsCommand : public Command {
public:
	MessageStudentsCommand(const MyString& buffer, Context& context);
	void execute() override;
	MyString getCommand() const override;

private:
	Vector<MyString> getReceivers(const Course& course) const;
	MyString getCourseName() const;
	MyString getContent() const;
	void saveMessage(const MyString& filename, const Message& message) const;

};