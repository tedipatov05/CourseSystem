#pragma once
#include <fstream>


class MyString {
public:

	MyString();
	MyString(const char* str);
	MyString(const MyString& str);
	MyString& operator=(const MyString& str);
	~MyString();

	size_t size() const;
	size_t capacity() const;
	const char* data() const;

	char& operator[](size_t index);
	const char& operator[](size_t index) const;
	MyString& operator+=(const MyString& str);

	const char& front() const;
	char& front();
	bool isEmpty() const;
	void shrink_to_fit();
	void reserve(size_t newCapacity);
	void push_back(char ch);
	void pop_back();

	MyString& erase(size_t index, size_t count);
	MyString& append(const char* str);
	MyString& append(const char* str, size_t count);
	MyString& append(const MyString& str);

	MyString& replace(size_t pos, size_t count, const char* str);
	void copy(char*& dest, size_t count, size_t pos = 0) const;

	int find(size_t pos = 0) const;
	int find(const char* str, size_t pos = 0) const;
	MyString substr(size_t pos = 0, size_t count = 0) const;
	bool contains(const MyString& str) const;
	bool contains(const char* str) const;
	MyString& insert(size_t pos, const MyString& str);
	MyString& insert(size_t pos, const char* str);
	MyString& insert(size_t pos, const char* str, size_t count);

	void readFromBinaryFile(std::ifstream& ifs);
	void writeToBinaryFile(std::ofstream& ofs) const;

	friend std::ostream& operator<<(std::ostream& os, const MyString& str);
	friend std::istream& operator>>(std::istream& is, MyString& str);
	friend MyString operator+(const MyString& lhs, const MyString& rhs);



private:
	char* _data;
	size_t _size;
	size_t _capacity;


	void copyDynamic(const MyString& other);
	void freeDynamic();
	void copyString(char*& dest, const char* src, size_t capacity) const;


};


bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);
bool operator<(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);



