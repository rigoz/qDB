#ifndef DATE_H
#define DATE_H

class Date
{
private:
	uint32 seconds;

public:
	Date(uint32 sec);
	Date(const Date &date);
};


#endif
