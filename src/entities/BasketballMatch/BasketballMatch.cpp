#include "BasketballMatch.h"

BasketballMatch::BasketballMatch(std::string ref, Date date, std::string location, std::string home, std::string guest, std::string league)
: 
	Match(ref, date, location), 
	m_homeTeam(home), 
	m_guestTeam(guest), 
	m_league(league) 
{
	m_scorersHome = NULL;
	m_scorersHomeLength = 0;
	
	m_scorersGuest = NULL;
	m_scorersGuestLength = 0;
	
	m_timeoutsHome = -1;
	m_timeoutsGuest = -1;
}

BasketballMatch::BasketballMatch(const BasketballMatch &bmtc)
:
	Match(bmtc.GetReferee(), bmtc.GetDate(), bmtc.GetLocation()),
	m_homeTeam(bmtc.m_homeTeam), 
	m_guestTeam(bmtc.m_guestTeam), 
	m_league(bmtc.m_league)
{
	if (this != &bmtc)
		Copy(bmtc);
}

BasketballMatch::~BasketballMatch()
{
	delete[] m_scorersHome;
	delete[] m_scorersGuest;
}

std::string BasketballMatch::GetHomeTeam() const
{
	return m_homeTeam;
}

std::string BasketballMatch::GetGuestTeam() const
{
	return m_guestTeam;
}

std::string BasketballMatch::GetWinner() const
{
	Result res = GetResult();
	if (res.home > res.guest)
		return m_homeTeam;
		
	return m_guestTeam;
}

std::string BasketballMatch::GetLoser() const
{
	Result res = GetResult();
	if (res.home < res.guest)
		return m_homeTeam;
		
	return m_guestTeam;
}

std::string BasketballMatch::GetLeague() const
{
	return m_league;
}

int16 BasketballMatch::GetTimeouts(Team team) const
{
	int16 timeouts = 0;
	
	if (team & TEAM_HOME)
		timeouts += m_timeoutsHome;
	
	if (team & TEAM_GUEST)
		timeouts += m_timeoutsGuest;
		
	return timeouts;
}

uint16 BasketballMatch::GetScoreEventsLength(Team team) const
{
	uint16 size = 0;
	
	if (team & TEAM_HOME)
		size += m_scorersHomeLength;
	
	if (team & TEAM_GUEST)
		size += m_scorersGuestLength;
		
	return size;
}

uint16 BasketballMatch::GetScoreEventLength(BasketEventType type, Team team) const
{
	uint16 size = 0;
	
	if (team & TEAM_HOME && m_scorersHome != NULL)
	{
		for (int i=0; i<m_scorersHomeLength; ++i)
			if (m_scorersHome[i].type & type)
				size++;
	}
	
	if (team & TEAM_GUEST && m_scorersGuest != NULL)
	{
		for (int i=0; i<m_scorersGuestLength; ++i)
			if (m_scorersGuest[i].type & type)
				size++;
	}
		
	return size;
}

BasketEvent BasketballMatch::GetScoreEvent(BasketEventType type, uint16 index, Team team) const
{
	if (team == TEAM_ANY)
	{
		if (index > m_scorersHomeLength)
		{
			index = index - m_scorersHomeLength;
			team = TEAM_GUEST;
		}
		else
			team = TEAM_HOME;
	}

	return _getScoreEvent(type, index+1, team);
}

BasketEvent BasketballMatch::_getScoreEvent(BasketEventType type, uint16 index, Team team) const
{
	BasketEvent *ptr;
	uint16 size;
	if (team == TEAM_HOME)
	{
		ptr = m_scorersHome;
		size = m_scorersHomeLength;
	}
	else
	{
		ptr = m_scorersGuest;
		size = m_scorersGuestLength;
	}
	
	BasketEvent empty = {"", BB_EVENT_TYPE_ALL, 0, 0};
	
	if (ptr == NULL || size == 0)
		return empty;
	
	int count = 0;
	for (int i=0; i<size; ++i)
	{
		if (type & ptr[i].type)
			count++;
		
		if (count == index)
			return ptr[i];
	}
	
	return empty;
}

void BasketballMatch::AddScoreEvent(BasketEventType type, Team team, std::string player, uint16 time, uint16 quarter)
{
	if (time == 0 || quarter == 0 || player == "")
		return;
		
	BasketEvent **ptr;
	uint16 *size;
	if (team == TEAM_HOME)
	{
		ptr = &m_scorersHome;
		size = &m_scorersHomeLength;
	}
	else
	{
		ptr = &m_scorersGuest;
		size = &m_scorersGuestLength;
	}
	
	if (*ptr == NULL && *size == 0)
	{
		(*size)++;
		*ptr = new BasketEvent[(*size)];
		InitEvent(*ptr, 0, player, type, time, quarter);
	}
	else
	{
		BasketEvent *tmp = new BasketEvent[*size];
		CopyEvent<BasketEvent>(tmp, *ptr, *size);
		delete[] *ptr;
		*ptr = new BasketEvent[(*size)+1];
		CopyEvent<BasketEvent>(*ptr, tmp, *size);
		(*size)++;
		InitEvent(*ptr, (*size)-1, player, type, time, quarter);
		
		delete[] tmp;
		
	}
}

void BasketballMatch::InitEvent(BasketEvent *ptr, uint16 index, std::string player, BasketEventType type, uint16 time, uint16 quarter)
{
	ptr[index].player = player;
	ptr[index].type = type;
	ptr[index].time = time;
	ptr[index].quarter = quarter;
}

void BasketballMatch::AddTimeout(Team team)
{
	if (team == TEAM_HOME)
		m_timeoutsHome++;
	else
		m_timeoutsGuest++;
}

void BasketballMatch::SetResult()
{
	uint16 homeScore = UpdateScoreForTeam(m_scorersHome, m_scorersHomeLength);
	uint16 guestScore = UpdateScoreForTeam(m_scorersGuest, m_scorersGuestLength);
	
	Match::SetResult(homeScore, guestScore);
}

uint16 BasketballMatch::UpdateScoreForTeam(BasketEvent *ptr, uint16 size)
{
	uint16 score = 0;
	for (int i=0; i<size; ++i)
		switch (ptr[i].type)
		{
			case BB_EVENT_TYPE_FREESHOT:
				score++;
			case BB_EVENT_TYPE_DOUBLESHOT:
				score += 2;
			case BB_EVENT_TYPE_TRIPLESHOT:
				score += 3;
		}
	
	return score;
}

BasketballMatch& BasketballMatch::operator=(const BasketballMatch &bmtc)
{
	if (this != &bmtc)
	{
		delete[] m_scorersHome;
		delete[] m_scorersGuest;

		Copy(bmtc);
	}

	return *this;
}

bool BasketballMatch::operator==(const Match &mtc) const
{
	const BasketballMatch *bmtc = dynamic_cast<const BasketballMatch*>(&mtc);

	if (bmtc == NULL) // If they are different sports, check only base class members
		return Match::operator==(mtc);

	// Check equality only on defined members
	if (bmtc->m_homeTeam != "" && m_homeTeam != bmtc->m_homeTeam)
		return false;

	if (bmtc->m_guestTeam != "" && m_guestTeam != bmtc->m_guestTeam)
		return false;

	if (bmtc->m_league != "" && m_league != bmtc->m_league)
		return false;

	if (bmtc->m_timeoutsHome != -1 && m_timeoutsHome != bmtc->m_timeoutsHome)
		return false;

	if (bmtc->m_timeoutsGuest != -1 && m_timeoutsGuest != bmtc->m_timeoutsGuest)
		return false;

	// Everything defined is equal, check base class
	return this->Match::operator==(mtc);
}

bool BasketballMatch::operator!=(const Match &mtc) const
{
	const BasketballMatch *bmtc = dynamic_cast<const BasketballMatch*>(&mtc);

	if (bmtc == NULL) // If they are different sports, check only base class members
		return Match::operator!=(mtc);

	// Check difference only on defined members
	if (bmtc->m_homeTeam != "" && m_homeTeam == bmtc->m_homeTeam)
		return false;

	if (bmtc->m_guestTeam != "" && m_guestTeam == bmtc->m_guestTeam)
		return false;

	if (bmtc->m_league != "" && m_league == bmtc->m_league)
		return false;

	if (bmtc->m_timeoutsHome != -1 && m_timeoutsHome == bmtc->m_timeoutsHome)
		return false;

	if (bmtc->m_timeoutsGuest != -1 && m_timeoutsGuest == bmtc->m_timeoutsGuest)
		return false;

	// Everything defined is different, check base class
	return Match::operator!=(mtc);
}

std::ostream& operator<<(std::ostream &os, const BasketballMatch &bmtc)
{
	const Match *m = &bmtc;
	os << "\t<match type=\"basket\">\n";
	if (m != NULL)
		os << *m << "\n";
		
	os << "\t\t<home>" << bmtc.m_homeTeam << "</home>\n";
	os << "\t\t<guest>" << bmtc.m_guestTeam << "</guest>\n";
	os << "\t\t<league>" << bmtc.m_league << "</league>\n";
	os << "\t\t<timeoutshome>" << bmtc.m_timeoutsHome << "</timeoutshome>\n";
	os << "\t\t<timeoutsguest>" << bmtc.m_timeoutsGuest << "</timeoutsguest>\n";
	if (bmtc.m_scorersHomeLength > 0)
	{
		os << "\t\t<scorershome>\n";
		for (int i=0; i<bmtc.m_scorersHomeLength; ++i)
		{
			os << "\t\t\t<score>\n";
			os << "\t\t\t\t<player>" << bmtc.m_scorersHome[i].player << "</player>\n";
			os << "\t\t\t\t<type>" << bmtc.m_scorersHome[i].type << "</type>\n";
			os << "\t\t\t\t<time>" << bmtc.m_scorersHome[i].time << "</time>\n";
			os << "\t\t\t\t<quarter>" << bmtc.m_scorersHome[i].quarter << "</quarter>\n";
			os << "\t\t\t</score>\n";
		}
		os << "\t\t</scorershome>\n";
	}
	if (bmtc.m_scorersGuestLength > 0)
	{
		os << "\t\t<scorersguest>\n";
		for (int i=0; i<bmtc.m_scorersGuestLength; ++i)
		{
			os << "\t\t\t<score>\n";
			os << "\t\t\t\t<player>" << bmtc.m_scorersGuest[i].player << "</player>\n";
			os << "\t\t\t\t<type>" << bmtc.m_scorersGuest[i].type << "</type>\n";
			os << "\t\t\t\t<time>" << bmtc.m_scorersGuest[i].time << "</time>\n";
			os << "\t\t\t\t<quarter>" << bmtc.m_scorersGuest[i].quarter << "</quarter>\n";
			os << "\t\t\t</score>\n";
		}
		os << "\t\t</scorersguest>\n";
	}
	
	os << "\t</match>\n";
	
	return os;
}

void BasketballMatch::Copy(const BasketballMatch &bmtc)
{
	m_scorersHomeLength = bmtc.m_scorersHomeLength;
	m_scorersGuestLength = bmtc.m_scorersGuestLength;

	m_scorersHome = NULL;
	m_scorersGuest = NULL;
	
	if (m_scorersHomeLength > 0)
	{
		m_scorersHome = new BasketEvent[m_scorersHomeLength];
		CopyEvent<BasketEvent>(m_scorersHome, bmtc.m_scorersHome, m_scorersHomeLength);
	}
	
	if (m_scorersGuestLength > 0)
	{
		m_scorersGuest = new BasketEvent[m_scorersGuestLength];
		CopyEvent<BasketEvent>(m_scorersGuest, bmtc.m_scorersGuest, m_scorersGuestLength);
	}
	
	m_timeoutsHome = bmtc.m_timeoutsHome;
	m_timeoutsGuest = bmtc.m_timeoutsGuest;
}