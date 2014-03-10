#ifndef PHONENUMBER_H
#define PHONENUMBER_H

#include <string>

class PhoneNumber
{
private:
	std::string number;

public:
	PhoneNumber();
	PhoneNumber(char* num);
	PhoneNumber(std::string num);
	PhoneNumber(const PhoneNumber &num);
	
	PhoneNumber& operator=(const char s)
	{
		number = s;
		return *this;
	}
	
	static bool Validate(char* num);
	static bool Validate(std::string num);
};


#endif
