#ifndef MATCH_H
#define MATCH_H

#include <string>
#include <iostream>
#include "SharedDefines.h"
#include "Date.h"

class Match
{
private:
	uint32 m_id;
	Result m_result;
	std::string m_referee;
	Date m_date;
	std::string m_location;
	bool m_closed;

	static uint32 autoIncrementValue;

public:
	Match(std::string ref, Date date, std::string location);
	Match(const Match &m);
	virtual ~Match() = 0;

	// <--------- Getters ------------
	uint32 GetId() const;
	Result GetResult() const;
	std::string GetReferee() const;
	Date GetDate() const;
	std::string GetLocation() const;
	bool IsClosed() const;
	static uint32 GetNextId();
	// ------------------------------>

	// <--------- Setters -----------
	virtual void SetResult(int16 homeScore, int16 guestScore);
	void SetReferee(std::string newReferee);
	void Postpone(Date newDate);
	void SetLocation(std::string location);
	void Close();
	// ------------------------------>

	// <-------- Operators -----------
	bool operator==(const Match &mtc) const;
	bool operator!=(const Match &mtc) const;
	friend std::ostream& operator<<(std::ostream &os, const Match &mtc);
	// ------------------------------>
};

#endif
