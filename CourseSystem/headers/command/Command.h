#pragma once
#include "../Context.h"
#include "../MyString.h"

class Command{
public:

	Command(const MyString& buffer, Context& ctx);
	virtual MyString getCommand() const = 0;
	virtual void execute() = 0;
	virtual ~Command() = default;

	Vector<MyString> split(const MyString& str, const MyString& delimiter) const;

	MyString buffer;
	Context& context;
};

