#pragma once
#include "User.h"


class UserRepository {
public:
	UserRepository();
	UserRepository(const UserRepository& other);
	UserRepository& operator=(const UserRepository& other);
	~UserRepository();

	void addUser(const User* user);
	User* findUser(const MyString& username) const;
	void removeUser(const MyString& username);
	void readFromBinaryFile(const MyString& filename);
	void writeToBinaryFile(const MyString& filename) const;

	User* getUser(int id) const;
	size_t getSize() const;

	const User& operator[](int index) const;

private:

	User** _users;
	size_t _size;
	size_t _capacity;

	void copyDynamicMemory(const UserRepository& other);
	void free();
	void resize();

	int findIndexToDelete(const MyString& username) const;
};

