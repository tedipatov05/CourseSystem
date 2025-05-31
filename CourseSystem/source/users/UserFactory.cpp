
// Teodor Patov 2MI0600491

#include "../../headers/users/UserFactory.h"

#include "../../headers/users/Admin.h"
#include "../../headers/users/Student.h"
#include "../../headers/users/Teacher.h"


User* Factory::createUser(UserType t) {
	switch (t) {
	case UserType::Teacher:
		return new Teacher();
	case UserType::Student:
		return new Student();
	case UserType::Admin:
		return new Admin();
	default:
		return nullptr;
	}
}
