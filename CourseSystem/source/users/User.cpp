#include "../../headers/users/User.h"

User::User() : User("", "", "", 0) {}

User::User(const MyString& first_name, const MyString& last_name, const MyString& password, int id)
	: _id(id), first_name(first_name), last_name(last_name), password(password){

}



void User::printMailbox() const {
	this->mailbox.print();
}

void User::receiveMessage(const Message& message) {
	this->mailbox.addMessage(message);
}

void User::readFromBinaryFile(std::ifstream& ifs) {

	this->first_name.readFromBinaryFile(ifs);
	this->last_name.readFromBinaryFile(ifs);
	this->password.readFromBinaryFile(ifs);
	ifs.read((char*)(&this->_id), sizeof(this->_id));
}

const MyString& User::getFirstName() const {
	return this->first_name;
}
const MyString& User::getLastName() const {
	return this->last_name;
}

MyString User::username() const {

	return this->first_name + " " + this->last_name;
}

int User::getId() const {
	return this->_id;
}

const MyString& User::getPassword() const {
	return this->password;
}

const Mailbox& User::getMailbox() const {
	return this->mailbox;
}

void User::changePassword(const MyString& newPass) {
	this->password = newPass;
}




