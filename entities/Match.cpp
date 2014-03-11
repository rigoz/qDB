#include "Match.h"

Match::autoIncrementValue = 0;

uint32 Match::GetNextId() const
{
	return ++autoIncrementValue;
}

Match::Match(Referee ref, Date date, std::string location)
{
	m_id = GetNextId();
	m_result = NULL;
	m_referee = ref;
	m_date = date;
	m_location = location;
	m_closed = false;
	
}
Match::Match(const Match &mtc)
{
	m_id = GetNextId();
	m_result = mtc.m_result;
	m_referee = mtc.m_referee;
	m_date = mtc.m_date;
	m_location = mtc.m_location;
	m_closed = mtc.m_closed;
}

	
// <--------- Getters ------------
uint32 Match::GetId() const
{
	return m_id;
}

Result Match::GetResult() const
{
	return m_result;
}

Referee Match::GetReferee() const
{
	return m_referee;
}

Date Match::GetDate() const
{
	return m_date;
}

std::string Match::GetLocation() const
{
	return m_location;
}

bool Match::IsClosed() const
{
	return m_closed;
}
// ------------------------------>
	
// <--------- Setters -----------
void Match::SetResult(uint16 homeScore, uint16 guestScore)
{
	if (IsClosed())
	{
		m_result.home = homeScore;
		m_result.guest = guestScore;
	}
}

void Match::SetReferee(Referee newReferee)
{
	if (IsClosed() == false)
		m_referee = newReferee;
}

void Match::Postpone(Date newDate)
{
	if (IsClosed() == false)
		m_date = newDate;
}

void Match::SetLocation(std::string location)
{
	if (IsClosed() == false)
		m_location = location;
}

void Match::Close()
{
	m_closed = true;
}
