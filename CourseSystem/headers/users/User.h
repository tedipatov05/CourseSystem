#pragma once
#pragma once

#include "../messages/Message.h"
#include "../MyString.h"
#include "UserFactory.h"
#include "../messages/Mailbox.h"

class User {
public:
	User();
	User(const MyString& first_name, const MyString& last_name, const MyString& password, int id);
	virtual ~User() = default;

	friend class ClearMailboxCommand;

	void printMailbox() const;
	void changePassword(const MyString& newPass);

	const MyString& getFirstName() const;
	const MyString& getLastName() const;
	MyString username() const;
	int getId() const;
	const MyString& getPassword() const;
	const Mailbox& getMailbox() const;

	virtual UserType role() const = 0;
	void receiveMessage(const Message& message);
	virtual User* clone() const = 0;

	virtual void writeToBinaryFile(std::ofstream& ofs) const = 0;
	virtual void readFromBinaryFile(std::ifstream& ifs);


protected:
	MyString first_name;
	MyString last_name;
	MyString password;
	Mailbox mailbox;
	int _id;

};

