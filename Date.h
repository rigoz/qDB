#ifndef DATE_H
#define DATE_H

#include "SharedDefines.h"
#include <iostream>
#include <string>
#include <sstream>

const uint16 monthsLength[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

const uint16 firstLeapyear = 1972;
const uint16 baseYear = 1970;
const uint16 leapRecurrence = 4;

class Date
{
private:
	uint32 m_days;
	
	static uint16 GetDaysUntilMonth(uint16 month)
	{
	    uint16 sum = 0;
	    for (int i=0; i<month-1; i++)
		sum += monthsLength[i];
	    
	    
	    return sum;
	}
	
	static bool IsLeapYear(uint16 year)
	{
	    return ((year-firstLeapyear) % leapRecurrence) == 0;
	    
	}
	
	static uint16 GetLeapYears(uint16 year)
	{
	    return (year < firstLeapyear) ? 0 : ((year-firstLeapyear) / leapRecurrence);
	}

public:
	Date() : m_days(0) {}
    
	Date(int days)
	{
	    m_days = days < 0 ? 0 : days;
	}
	
	Date(uint16 day, uint16 month, uint16 year)
	{
	    uint16 daysForYear = (year > baseYear) ? (year - baseYear) * 365 + GetLeapYears(year) : 0;
	    
	    m_days = day-1 + GetDaysUntilMonth(month) + daysForYear + (IsLeapYear(year) && month > 2 ? 1 : 0);
	}
	
	Date(const Date &date) : m_days(date.m_days) {}
	
	std::string ToString() const
	{
	    uint16 year = m_days / 365 + baseYear;
	    uint16 days = m_days % 365 - GetLeapYears(year) + 1;
	    uint16 month = 1;
	    for (int i=0; i<12; i++)
		if (days > monthsLength[i])
		{
		    month++;
		    days -= monthsLength[i];
		}
	    
	    std::ostringstream oss;
	    oss << days << "/" << month << "/" << year;
	    return oss.str();
	}
	
	friend std::ostream& operator<<(std::ostream &os, const Date &date)
	{
	    return os << date.ToString();
	}
	
	Date operator+(int n)
	{
	    Date t(m_days + n);
	    return t;
	}
	
	Date operator-(int n)
	{
	    Date t(m_days - n);
	    return t;
	}
};


#endif
