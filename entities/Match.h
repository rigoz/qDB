#ifndef MATCH_H
#define MATCH_H

#include <string>
#include <ctime>
#include "SharedDefines.h"
#include "PhoneNumber.h"
#include "Date.h"

struct Result
{
	uint16 home;
	uint16 guest;
};

struct Referee
{
	std::string surname;
	std::string name;
	PhoneNumber telephone;
};


class Match
{
private:
	uint32 m_id;
	Result m_result;
	Referee m_referee;
	Date m_date;
	std::string m_location;
	bool m_closed;
	
	static uint32 autoIncrementValue;
	uint32 GetNextId() const;
	
public:
	Match(Referee ref, Date date, std::string location);
	Match(const Match &m);
	virtual ~Match();
	
	// <--------- Getters ------------
	uint32 GetId() const;
	Result GetResult() const;
	Referee GetReferee() const;
	Date GetDate() const;
	std::string GetLocation() const;
	bool IsClosed() const;
	// ------------------------------>
	
	// <--------- Setters -----------
	virtual void SetResult(uint16 homeScore, uint16 guestScore);
	void SetReferee(Referee newReferee);
	void Postpone(Date newDate);
	void SetLocation(std::string location);
	virtual void Close();
	// ------------------------------>
	
};

#endif
