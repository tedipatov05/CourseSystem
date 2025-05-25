#include "../../headers/messages/Message.h"
#include <iostream>

Message::Message(const MyString& content, const Vector<MyString>& receivers, const MyString& sender) {
	this->_content = content;
	this->_receivers = receivers;
	this->_sender = sender;
}



const char* Message::content() const {
	return this->_content.data();
}

void Message::print() const {
	std::cout << "     ";
	std::cout << this->time.getTime() << ", " << "sent by " << this->_sender << ": " << this->_content << std::endl;
}

void Message::readFromFile(std::ifstream& ifs) {

	//this->_content = new MyString();
	this->_content.readFromBinaryFile(ifs);
	this->_sender.readFromBinaryFile(ifs);
	this->time.readFromBinaryFile(ifs);

	size_t size;
	ifs.read((char*)(&size), sizeof(size));
	for (size_t i = 0; i < size; ++i) {
		MyString receiver;
		receiver.readFromBinaryFile(ifs);
		this->_receivers.push_back(receiver);
	}
}

void Message::writeToFile(std::ofstream& ofs) const {

	this->_content.writeToBinaryFile(ofs);
	this->_sender.writeToBinaryFile(ofs);
	this->time.writeToBinaryFile(ofs);

	size_t size = this->_receivers.size();
	ofs.write((const char*)(&size), sizeof(size));
	for (size_t i = 0; i < size; ++i) {
		this->_receivers[i].writeToBinaryFile(ofs);
	}

}

const Vector<MyString>& Message::receivers() const {
	return this->_receivers;
}

