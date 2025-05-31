
// Teodor Patov 2MI0600491

#pragma once
#include "MessageTime.h"
#include "../MyString.h"
#include "../Vector.hpp"

class Message {

public:

	Message() = default;
	Message(const MyString& content, const Vector<MyString>& receivers, const MyString& sender);
	
	const char* content() const;

	void print() const;
	
	const Vector<MyString>& receivers() const;

	void readFromFile(std::ifstream& ifs);
	void writeToFile(std::ofstream& ofs) const;
	void removeReceiver(const MyString& receiver);

private:

	MyString _content;
	MyString _sender; 
	Vector<MyString> _receivers; 
	MessageTime time;
};
