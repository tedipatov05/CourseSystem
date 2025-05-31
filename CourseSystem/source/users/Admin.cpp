// Teodor Patov 2MI0600491

#include "../../headers/users/Admin.h"
#include <fstream>
#include "../../headers/users/User.h"

Admin::Admin(const MyString& first_name, const MyString& last_name, const MyString& password, int id)
	: User(first_name, last_name , password, id)
{
}

UserType Admin::role() const
{
	return UserType::Admin;
}

User* Admin::clone() const
{
	return new Admin(*this);
}

void Admin::writeToBinaryFile(std::ofstream& ofs) const{
	UserType type = this->role();
	ofs.write((const char*)(&type), sizeof(type));

	this->first_name.writeToBinaryFile(ofs);
	this->last_name.writeToBinaryFile(ofs);
	this->password.writeToBinaryFile(ofs);
	ofs.write((const char*)(&this->_id), sizeof(this->_id));
}
