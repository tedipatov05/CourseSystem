// Teodor Patov 2MI0600491

#include "../../headers/messages/MessageTime.h"
#include <cstring>
#include <ctime>
#pragma warning(disable:4996)

MessageTime::MessageTime() {
    setCurrentTime();
}


void MessageTime::setCurrentTime() {

    time_t now = time(nullptr);
    tm* ltm = localtime(&now);

    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%H:%M %Y-%m-%d", ltm);

    char* temp = new char[strlen(buffer) + 1];
    std::strcpy(temp, buffer);

	this->_time = MyString(temp);
}

const MyString MessageTime::getTime() const {
    return this->_time;
}


void MessageTime::readFromBinaryFile(std::ifstream& ifs) {

	this->_time.readFromBinaryFile(ifs);
}

void MessageTime::writeToBinaryFile(std::ofstream& ofs) const {
    this->_time.writeToBinaryFile(ofs);
}



