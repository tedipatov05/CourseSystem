#pragma once
#pragma once
#include <fstream>

#include "../MyString.h"

class MessageTime {

public:

	MessageTime();

	const MyString getTime() const;

	void readFromBinaryFile(std::ifstream& ifs);
	void writeToBinaryFile(std::ofstream& ofs) const;

private:

	MyString _time;

	void setCurrentTime();
	
};


