
// Teodor Patov 2MI0600491

#pragma once

class User;

enum class UserType {
	Teacher,
	Student,
	Admin,
	None	
};

class Factory
{
public:
	static User* createUser(UserType t);
};
