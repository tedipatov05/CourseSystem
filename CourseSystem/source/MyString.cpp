#include "../headers/MyString.h"
#include "../headers/Utils.h"
#include <istream>
#pragma warning(disable : 4996) // Disable deprecation warning for strcpy

namespace Utils {

	constexpr size_t INITIAL_CAPACITY = 16;
	constexpr int BUFFER_SIZE = 1024;


}

MyString::MyString() : MyString("") {}

void MyString::copyString(char*& dest, const char* src, size_t capacity) const {
	if (src == nullptr) {
		dest = nullptr;
		return;
	}
	size_t len = strlen(src) + 1;
	dest = new char[capacity];
	std::strcpy(dest, src);
}


MyString::MyString(const char* str) {
	if (str == nullptr) {
		this->_data = nullptr;
		this->_capacity = 0;
		this->_size = 0;
		return;
	}

	this->_capacity = dataToAllocByStringLen(strlen(str));
	this->_size = std::strlen(str);
	copyString(this->_data, str, this->capacity());
}

MyString::MyString(const MyString& str) : _capacity(str.capacity()), _size(str.size()) {
	copyDynamic(str);
}

MyString::~MyString() {
	freeDynamic();
	this->_capacity = 0;
	this->_size = 0;
}

MyString& MyString::operator=(const MyString& str) {
	if (this != &str) {
		freeDynamic();
		copyDynamic(str);
		this->_capacity = str.capacity();
		this->_size = std::strlen(str.data());
	}
	return *this;
}

MyString& MyString::operator+=(const MyString& str) {
	if (str.data() == nullptr) {
		return *this;
	}

	if (this->size() + str.size() + 1 > this->capacity()) {
		this->reserve(this->size() + str.size());
	}

	std::strncat(this->_data, str.data(), str.size());

	return *this;


}


size_t MyString::size() const {
	return this->_size;
}

size_t MyString::capacity() const {
	return _capacity;
}

const char* MyString::data() const {
	return _data;
}

char& MyString::operator[](size_t index) {
	return _data[index];
}

const char& MyString::operator[](size_t index) const {
	return _data[index];
}

char& MyString::front() {
	if (isEmpty()) {
		throw std::out_of_range("The string is empty");
	}

	return this->_data[0];
}

const char& MyString::front() const {
	if (isEmpty()) {
		throw std::out_of_range("Used front() on empty string!");
	}

	return this->_data[0];
}

bool MyString::isEmpty() const {
	return strlen(this->data()) == 0;
}

void MyString::shrink_to_fit() {

	if (this->capacity() > this->size() + 1) {

		this->reserve(this->size() + 1);
	}
}

void MyString::push_back(char ch) {
	if (this->size() + 1 == this->capacity()) {
		this->reserve(this->capacity() * 2);
	}

	this->_data[this->size()] = ch;
	this->_size++;
	this->_data[this->size()] = '\0';
}

void MyString::pop_back() {
	if (!this->isEmpty()) {
		this->_data[this->size()] = '\0';
		this->_size--;
	}
}

MyString& MyString::erase(size_t index, size_t count) {
	if (index > this->size() || (index + count) > this->size()) {
		throw std::out_of_range("Index out of range");
	}

	for (size_t i = index + count; i <= this->size(); i++) {
		this->_data[i - count] = this->_data[i];
	}

	_size -= count;

	return *this;

}

MyString& MyString::append(const char* str, size_t count) {
	if (!str) {
		return *this;
	}

	size_t len = std::strlen(str);

	count = std::min(len, count);

	if (this->size() + count + 1 > this->_capacity) {
		this->reserve(dataToAllocByStringLen(this->size() + count + 1));
	}

	unsigned index = 0;

	while (count != index) {
		this->_data[_size] = str[index];
		index++;
		this->_size++;

	}
	this->_data[_size] = '\0';

	return *this;
}

MyString& MyString::append(const MyString& str) {
	return this->append(str.data(), str.size());
}

MyString& MyString::append(const char* str) {
	return this->append(str, std::strlen(str));
}

MyString& MyString::replace(size_t pos, size_t count, const char* str) {

	if (pos > this->size()) {
		throw std::out_of_range("Index out of range");
	}

	count = std::min(this->size(), count);
	size_t len = std::strlen(str);

	size_t newCapacity = dataToAllocByStringLen(this->size() - count + len + 1);
	char* newData = new char[newCapacity];

	this->copy(newData, pos);

	for (size_t i = 0; i < len; i++) {
		newData[i + pos] = str[i];
	}

	for (size_t i = pos + count; i < this->size(); i++) {
		newData[i - count + len] = this->_data[i];
	}

	newData[this->size() - count + len] = '\0';

	delete[] this->_data;
	this->_data = newData;
	this->_size = this->size() - count + len;
	this->_capacity = newCapacity;

	return *this;


}

MyString MyString::substr(size_t pos, size_t count) const {
	count = std::min(this->size() - pos, count);

	if (pos + count > this->size()) {
		throw std::out_of_range("Index out of range");
	}



	char* temp = new char[count + 1];
	copy(temp, count, pos);
	MyString result(temp);
	delete[] temp;

	return result;
}

MyString& MyString::insert(size_t pos, const char* str, size_t count) {

	if (pos > this->size()) {
		throw std::out_of_range("Index out of range");
	}

	count = std::min(this->size(), count);

	size_t newCapacity = dataToAllocByStringLen(this->size() + count + 1);
	char* newData = new char[newCapacity];

	this->copy(newData, pos);

	for (size_t i = 0; i < count; i++) {
		newData[i + pos] = str[i];
	}

	for (size_t i = pos; i < this->size(); i++) {
		newData[i + count] = this->_data[i];
	}

	newData[this->size() + count] = '\0';

	delete[] this->_data;
	this->_data = newData;
	this->_size += count;
	this->_capacity = newCapacity;

	return *this;
}

MyString& MyString::insert(size_t pos, const MyString& str) {
	return this->insert(pos, str.data(), str.size());
}

MyString& MyString::insert(size_t pos, const char* str) {
	return this->insert(pos, str, std::strlen(str));
}


bool MyString::contains(const MyString& str) const {
	return this->find() != std::string::npos;
}

bool MyString::contains(const char* str) const {
	return this->find(str) != std::string::npos;
}

void MyString::copy(char*& dest, size_t count, size_t pos) const {
	if (pos > this->size()) {
		throw std::out_of_range("Index out of range");
	}

	count = std::min(this->size() - pos, count);


	for (size_t i = 0; i < count; i++) {
		dest[i] = this->_data[pos + i];
	}
	dest[count] = '\0';
}

int MyString::find(size_t pos) const {
	return this->find(this->data(), pos);

}

int MyString::find(const char* str, size_t pos) const {
	if (pos > this->size()) {
		throw std::out_of_range("Index out of range");
	}

	size_t len = std::strlen(str);

	if (len > this->size()) {
		return std::string::npos;
	}

	for (size_t i = pos; i <= this->size() - len; i++) {
		if (stringCmp(this->_data + i, str, len)) {
			return i;
		}
	}

	return std::string::npos;
}




MyString operator+(const MyString& lhs, const MyString& rhs) {
	MyString result(lhs);
	result += rhs;
	return result;
}


void MyString::copyDynamic(const MyString& other) {
	if (other.data() == nullptr) {
		this->_data = nullptr;
		return;
	}
	copyString(this->_data, other.data(), other._capacity);
}

void MyString::freeDynamic() {
	delete[] _data;
	_data = nullptr;
}

bool operator==(const MyString& lhs, const MyString& rhs) {
	return strcmp(lhs.data(), rhs.data()) == 0;
}
bool operator!=(const MyString& lhs, const MyString& rhs) {
	return !(lhs == rhs);
}

bool operator<(const MyString& lhs, const MyString& rhs) {
	return strcmp(lhs.data(), rhs.data()) < 0;
}

bool operator>(const MyString& lhs, const MyString& rhs) {
	return strcmp(lhs.data(), rhs.data()) > 0;
}

bool operator<=(const MyString& lhs, const MyString& rhs) {
	return !(lhs > rhs);
}

bool operator>=(const MyString& lhs, const MyString& rhs) {
	return !(lhs < rhs);
}

void MyString::reserve(size_t newCapacity) {

	char* temp = new char[newCapacity];
	strcpy(temp, _data);
	delete[] _data;
	this->_data = temp;
	this->_capacity = newCapacity;

}



std::ostream& operator<<(std::ostream& os, const MyString& str) {

	os << str.data();
	return os;

}

std::istream& operator>>(std::istream& is, MyString& str) {

	char buffer[Utils::BUFFER_SIZE];
	is >> buffer;
	size_t bufferStringSize = std::strlen(buffer);

	if (bufferStringSize > str.capacity()) {
		str.reserve(roundToPowerOfTwo(bufferStringSize));
	}

	std::strcpy(str._data, buffer);
	return is;

}

void MyString::readFromBinaryFile(std::ifstream& ifs) {

	freeDynamic();

	ifs.read((char*)&this->_size, sizeof(this->_size));
	this->_capacity = dataToAllocByStringLen(this->_size);

	this->_data = new char[this->_capacity];
	ifs.read(this->_data, this->_size);
	this->_data[this->_size] = '\0';
}

void MyString::writeToBinaryFile(std::ofstream& ofs) const {
	ofs.write((const char*)&this->_size, sizeof(this->_size));
	ofs.write(this->data(), this->_size);
}



