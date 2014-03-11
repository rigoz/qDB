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

public:
	Date() : m_days(0) {}
    
	Date(uint32 days) : m_days(days) {}
	
	Date(uint16 day, uint16 month, uint16 year)
	{
	    uint16 daysForYear = 0;
	    uint16 leapYears = (year < firstLeapyear) ? 0 : ((year-firstLeapyear) / leapRecurrence);
	    if (year > baseYear)
		daysForYear = (year - baseYear) * 365 + leapYears;
	    
	    m_days = day-1 + GetDaysUntilMonth(month) + daysForYear + (IsLeapYear(year) && month > 2 ? 1 : 0);
	}
	
	Date(const Date &date) : m_days(date.m_days) {}
	
	/*uint16 GetDay() const
	{
	    uint16 days = m_days % 365;
	    for (int i=0; i<12; i++)
		if (days > monthsLength[i])
		    days -= monthsLength[i];
	    
	    days -= 
	}
	
	uint16 GetMonth() const
	{
	    uint16 days = m_days % 365;
	    for (int i=0; i<12; i++)
		if (days < monthsLength[i])
		    return i+1;
		else
		    days -= monthsLength[i];
	    
	    return days;
	}
	
	uint16 GetYear() const
	{
	    return m_days / 365 + baseYear;
	}*/
	
	std::string ToString() const
	{
	    uint16 year = m_days / 365 + baseYear;
	    uint16 leapYears = (year < firstLeapyear) ? 0 : ((year-firstLeapyear) / leapRecurrence);
	    uint16 days = m_days % 365 - leapYears + 1;
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
};
