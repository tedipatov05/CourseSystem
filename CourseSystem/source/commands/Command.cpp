// Teodor Patov 2MI0600491


#include "../../headers/command/Command.h"

Command::Command(const MyString& buffer, Context& ctx)
	: buffer(buffer), context(ctx) {}

Vector<MyString> Command::split(const MyString& str, const MyString& delimiter) {
	Vector<MyString> result;
	size_t start = 0;
	size_t end = str.find(delimiter.data(), start);

	while (end != std::string::npos) {
		result.push_back(str.substr(start, end - start));
		start = end + delimiter.size();
		end = str.find(delimiter.data(), start);
	}

	result.push_back(str.substr(start, end));
	return result;
}
