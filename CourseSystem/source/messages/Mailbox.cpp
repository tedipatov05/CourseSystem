#include "../../headers/messages/Mailbox.h"

#include <iostream>
#include <fstream>

#include "../../headers/Constants.h"
#include "../../headers/Utils.h"

Mailbox::Mailbox() {
	this->messages = new Message[INITIAL_SIZE];
	this->size = 0;
	this->capacity = INITIAL_SIZE;
}

Mailbox::Mailbox(const Mailbox& mailbox) {
	this->copyDynamicMemory(mailbox);
}
Mailbox& Mailbox::operator=(const Mailbox& other) {
	if (this != &other) {
		this->free();
		this->copyDynamicMemory(other);
	}
	return *this;
}

Mailbox::~Mailbox() {
	this->free();
	this->messages = nullptr;
}

void Mailbox::addMessage(const Message& message) {
	if (this->size == this->capacity) {
		this->resize();
	}
	this->messages[this->size] = message;
	this->size++;
}
void Mailbox::print() const {
	if (this->size == 0) {
		std::cout << "     ";
		std::cout << "No messages to show" << std::endl;
		return;
	}

	std::cout << "> mailbox" << std::endl;
	for (int i = 0; i < this->size; i++) {
		this->messages[i].print();
	}
}

void Mailbox::resize() {
	Message* new_messages = new Message[this->capacity * 2];
	for (int i = 0; i < this->size; i++) {
		new_messages[i] = this->messages[i];
	}
	delete[] this->messages;
	this->messages = new_messages;
	this->capacity *= 2;
}

void Mailbox::copyDynamicMemory(const Mailbox& mailbox) {
	this->messages = new Message[mailbox.capacity];
	for (int i = 0; i < mailbox.size; i++) {
		this->messages[i] = mailbox.messages[i];
	}
	this->size = mailbox.size;
	this->capacity = mailbox.capacity;
}

void Mailbox::free() {
	delete[] this->messages;
	this->messages = nullptr;
	this->size = 0;
	this->capacity = 0;
}

void Mailbox::readFromBinaryFile(std::ifstream& ifs) {
	if (!ifs.is_open()) {
		return;
	}

	// Read the size of the mailbox
	unsigned size;
	ifs.read((char*)&size, sizeof(size));

	if (size <= 0) {
		ifs.close();
		return;
	}

	free();
	this->messages = new Message[roundToPowerOfTwo(size)];
	for (size_t i = 0; i < size; i++) {
		this->messages[i].readFromFile(ifs);
	}

	this->size = size;
	ifs.close();
}

void Mailbox::writeToBinaryFile(std::ofstream& ofs) const {
	if (!ofs.is_open()) {
		return;
	}

	size_t size = this->size;
	ofs.write((char*)&size, sizeof(size));

	for (size_t i = 0; i < size; i++) {
		this->messages[i].writeToFile(ofs);
	}

	ofs.close();
}

size_t Mailbox::getSize() const {
	return this->size;
}

const Message& Mailbox::operator[](size_t index) const {
	return this->messages[index];
}

Message& Mailbox::operator[](size_t index) {
	return this->messages[index];
}

void Mailbox::clear() {
	free();
	this->messages = new Message[INITIAL_SIZE];
	this->size = 0;
	this->capacity = INITIAL_SIZE;
}




