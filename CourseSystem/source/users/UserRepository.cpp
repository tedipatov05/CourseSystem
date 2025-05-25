#include "../../headers/users/UserRepository.h"

#include <iostream>

#include "../../headers/Constants.h"

UserRepository::UserRepository() {
	this->_capacity = INITIAL_SIZE;
	this->_size = 0;
	this->_users = new User * [this->_capacity];
}

UserRepository::UserRepository(const UserRepository& other) {
	this->copyDynamicMemory(other);
}

UserRepository& UserRepository::operator=(const UserRepository& other) {
	if (this != &other) {
		free();
		copyDynamicMemory(other);
	}
	return *this;
}

UserRepository::~UserRepository() {
	free();
}

void UserRepository::addUser(const User* user) {
	if (this->_size == this->_capacity) {
		this->resize();
	}
	this->_users[this->_size] = user->clone();
	this->_size++;
}

User* UserRepository::findUser(const MyString& username) const {
	for (size_t i = 0; i < this->_size; i++) {
		if (this->_users[i]->getFirstName() == username) {
			return this->_users[i];
		}
	}
	return nullptr;
}

void UserRepository::removeUser(const MyString& username) {

	int indexToDelete = this->findIndexToDelete(username);
	if (indexToDelete == -1) {
		return;
	}

	delete this->_users[indexToDelete];
	// TODO: shift the elements to the left


}

int UserRepository::findIndexToDelete(const MyString& username) const {
	for (size_t i = 0; i < this->_size; i++) {
		if (this->_users[i]->username() == username) {
			return i;
		}
	}
	return -1;
}

const User& UserRepository::operator[](int index) const {
	return *this->_users[index];
}


void UserRepository::free() {
	for (size_t i = 0; i < this->_size; i++) {
		delete this->_users[i];
	}
	delete[] this->_users;
	this->_users = nullptr;
	this->_size = 0;
	this->_capacity = 0;

}

void UserRepository::copyDynamicMemory(const UserRepository& other) {
	this->_capacity = other._capacity;
	this->_size = other._size;
	this->_users = new User * [this->_capacity];
	for (size_t i = 0; i < this->_size; i++) {
		this->_users[i] = other._users[i]->clone();
	}
}

void UserRepository::resize() {
	this->_capacity *= 2;
	User** newUsers = new User * [this->_capacity];
	for (size_t i = 0; i < this->_size; i++) {
		newUsers[i] = this->_users[i]->clone();
	}
	delete[] this->_users;
	this->_users = newUsers;
}

void UserRepository::readFromBinaryFile(const MyString& filename) {
	std::ifstream ifs(filename.data(), std::ios::binary);
	if (!ifs) {
		std::cout << "Error opening file: " << filename << std::endl;
		return;
	}

	while (!ifs.eof()) {
		UserType type;
		ifs.read((char*)&type, sizeof(type));

		User* user = Factory::createUser(type);

		if (!user) {
			std::cout << "Error creating a user" << std::endl;
			break;
		}

		user->readFromBinaryFile(ifs);
		this->addUser(user);
	}

	ifs.close();
}

void UserRepository::writeToBinaryFile(const MyString& filename) const {
	std::ofstream ofs(filename.data(), std::ios::binary);
	if (!ofs) {
		std::cout << "Error opening file: " << filename << std::endl;
		return;
	}

	for (size_t i = 0; i < this->_size; i++) {
		this->_users[i]->writeToBinaryFile(ofs);
	}

	ofs.close();
}

User* UserRepository::getUser(int id) const {
	for (size_t i = 0; i < this->_size; i++) {
		if (this->_users[i]->getId() == id) {
			return this->_users[i];
		}
	}

	return nullptr;
}

size_t UserRepository::getSize() const {
	return this->_size;
}
