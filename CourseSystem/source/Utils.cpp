#include "../headers/Utils.h"
#include "../headers/Constants.h"
#include <iostream>
#pragma warning(disable:4996)


void setString(char*& dest, const char* src) {
    size_t len = strlen(src);
    dest = new char[len + 1];
    strcpy(dest, src);
}

size_t roundToPowerOfTwo(size_t v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

MyString getRoleName(UserType userType) {
	switch (userType) {
	case UserType::Student:
		return MyString("Student");
	case UserType::Teacher:
		return MyString("Teacher");
	case UserType::Admin:
		return MyString("Admin");
	default:
		return MyString("Unknown");
	}
}


size_t dataToAllocByStringLen(size_t size)
{
	return std::max(roundToPowerOfTwo(size + 1), INITIAL_SIZE);
}

bool stringCmp(const char* str1, const char* str2, size_t size) {
	for (size_t i = 0; i < size; i++) {
		if (str1[i] != str2[i]) {
			return false;
		}
	}
	return true;
}

int toInt(const MyString& str) {
	int result = 0;
	for (size_t i = 0; i < str.size(); i++) {
		result = result * 10 + (str[i] - '0');
	}
	return result;
}

double toDouble(const MyString& str) {
	double result = 0.0;
	double factor = 1.0;
	bool isFractionalPart = false;

	for (size_t i = 0; i < str.size(); i++) {
		if (str[i] == '.') {
			isFractionalPart = true;
			continue;
		}

		if (isFractionalPart) {
			factor /= 10.0;
			result += (str[i] - '0') * factor;
		}
		else {
			result = result * 10.0 + (str[i] - '0');
		}
	}

	return result;
}

//Vector<MyString> split(const MyString& str, const MyString& delimiter) {
//	Vector<MyString> result;
//	size_t start = 0;
//	size_t end = str.find(delimiter.data(), start);
//
//	while (end != std::string::npos) {
//		result.push_back(str.substr(start, end - start));
//		start = end + delimiter.size();
//		end = str.find(delimiter.data(), start);
//	}
//
//	result.push_back(str.substr(start, end));
//	return result;
//}


