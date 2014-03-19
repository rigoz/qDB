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
	if (this != &mtc)
	{
		m_id = GetNextId();
		m_result = mtc.m_result;
		m_referee = mtc.m_referee;
		m_date = mtc.m_date;
		m_location = mtc.m_location;
		m_closed = mtc.m_closed;
	}
}

Match::~Match() {}


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
	// Check equality only on defined members
	if (mtc.m_result.home > -1 && (m_result.home != mtc.m_result.home || m_result.guest != mtc.m_result.guest))
		return false;
	
	if (mtc.m_referee != "" && m_referee != mtc.m_referee)
		return false;
		
	if (mtc.m_date.GetDays() != 0 && m_date != mtc.m_date)
		return false;
		
	if (mtc.m_location != "" && m_location != mtc.m_location)
		return false;
		
	return true;
}

bool Match::operator!=(const Match &mtc) const
{
	// Check difference only on defined members
	if (mtc.m_result.home > -1 && (m_result.home == mtc.m_result.home || m_result.guest == mtc.m_result.guest))
		return false;
	
	if (mtc.m_referee != "" && m_referee == mtc.m_referee)
		return false;
		
	if (mtc.m_date.GetDays() != 0 && m_date == mtc.m_date)
		return false;
		
	if (mtc.m_location != "" && m_location == mtc.m_location)
		return false;
		
	return true;
}
std::ostream& operator<<(std::ostream &os, const Match &mtc)
{
	os << "<id>" << mtc.m_id << "</id>\n";
	os << "\t\t<date>" << mtc.m_date << "</date>\n";
	os << "\t\t<location>" << mtc.m_location << "</location>\n";
	os << "\t\t<referee>" << mtc.m_referee << "</referee>\n";
	os << "\t\t<result>" << mtc.m_result.home << " | " << mtc.m_result.guest << "</result>\n";
	os << "\t\t<closed>" << mtc.m_closed << "</closed>\n";

	return os;
}
// ------------------------------>
