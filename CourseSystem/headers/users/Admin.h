
// Teodor Patov 2MI0600491

#pragma once
#include <fstream>

#include "UserRepository.h"
#include "../MyString.h"

class Admin : public User
{
public:
	Admin() = default;
	Admin(const MyString& first_name, const MyString& last_name, const MyString& password, int id);


	UserType role() const override;
	User* clone() const override;
	void writeToBinaryFile(std::ofstream& ofs) const override;

};

