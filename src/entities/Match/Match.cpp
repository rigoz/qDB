#include "Match.h"

uint32 Match::autoIncrementValue = 0;

uint32 Match::GetNextId()
{
	return ++autoIncrementValue;
}

Match::Match(std::string ref, Date date, std::string location)
{
	m_id = GetNextId();
	m_result.home = -1;
	m_result.guest = -1;
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

std::string Match::GetReferee() const
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
void Match::SetResult(int16 homeScore, int16 guestScore)
{
	if (IsClosed())
		return;

	m_result.home = homeScore;
	m_result.guest = guestScore;
	Close();
}

void Match::SetReferee(std::string newReferee)
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
// ------------------------------>


// <-------- Operators -----------
bool Match::operator==(const Match &mtc) const
{
	// we are going to check equality member by member
	// for every member that is 
}

bool Match::operator!=(const Match &mtc) const
{

}
std::ostream& operator<<(std::ostream &os, const Match &mtc)
{
	os << "Match details:\n";
	os << "- id: " << mtc.m_id << "\n";
	os << "- date: " << mtc.m_date << "\n";
	os << "- location: " << mtc.m_location << "\n";
	os << "- referee: " << mtc.m_referee << "\n";
	if (mtc.IsClosed())
	{
		os << "- match is closed ";
		if (mtc.m_result.home < 0 && mtc.m_result.guest < 0)
			os << "but no result has been submitted\n\n";
		else
			os << "with result: Home " << mtc.m_result.home << "-" << mtc.m_result.guest << " Guest\n\n";
	}
	else
		os << "- match is still open\n\n";

	return os;
}
// ------------------------------>
