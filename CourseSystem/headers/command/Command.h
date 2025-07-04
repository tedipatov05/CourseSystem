
// Teodor Patov 2MI0600491

#pragma once
#include "../Context.h"
#include "../MyString.h"

class Command{
public:

	Command(const MyString& buffer, Context& ctx);
	virtual void execute() = 0;
	virtual ~Command() = default;

	static Vector<MyString> split(const MyString& str, const MyString& delimiter);

	MyString buffer;
	Context& context;
};

