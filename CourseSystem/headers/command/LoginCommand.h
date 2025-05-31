
// Teodor Patov 2MI0600491

#pragma once
#include "Command.h"
#include "../Context.h"
#include "../users/User.h"

class LoginCommand :
    public Command
{

public:
	LoginCommand(const MyString& buffer, Context& system);
	MyString getCommand() const override;
	void execute() override;

private:
	
	int getIdFromBuffer() const;
	MyString getPasswordFromBuffer() const;
};

