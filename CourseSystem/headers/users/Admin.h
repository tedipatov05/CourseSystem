#pragma once
#include <fstream>

#include "UserRepository.h"
#include "../MyString.h"

class Admin : public User
{
public:
	Admin() = default;
	Admin(const MyString& name, const MyString& email, const MyString& password, int id);


	UserType role() const override;
	User* clone() const override;
	void writeToBinaryFile(std::ofstream& ofs) const override;

};

