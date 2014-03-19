#include "FootballMatch.h"

FootballMatch::FootballMatch(std::string ref, Date date, std::string location, std::string home, std::string guest, std::string league)
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
	
	m_possession = 0;
}

FootballMatch::FootballMatch(const FootballMatch &fmtc)
:
	Match(fmtc.GetReferee(), fmtc.GetDate(), fmtc.GetLocation()),
	m_homeTeam(fmtc.m_homeTeam), 
	m_guestTeam(fmtc.m_guestTeam), 
	m_league(fmtc.m_league)
{
	if (this != &fmtc)
		Copy(fmtc);
}

FootballMatch::~FootballMatch()
{
	delete[] m_scorersHome;
	delete[] m_scorersGuest;
}

std::string FootballMatch::GetHomeTeam() const
{
	return m_homeTeam;
}

std::string FootballMatch::GetGuestTeam() const
{
	return m_guestTeam;
}

std::string FootballMatch::GetWinner() const
{
	Result res = GetResult();
	if (res.home > res.guest)
		return m_homeTeam;
		
	return m_guestTeam;
}

std::string FootballMatch::GetLoser() const
{
	Result res = GetResult();
	if (res.home < res.guest)
		return m_homeTeam;
		
	return m_guestTeam;
}

std::string FootballMatch::GetLeague() const
{
	return m_league;
}

uint16 FootballMatch::GetPossession(Team team) const
{
	if (team == TEAM_HOME)
		return m_possession;
		
	return 100 - m_possession;
}

uint16 FootballMatch::GetScoreEventsLength(Team team) const
{
	uint16 size = 0;
	
	if (team & TEAM_HOME)
		size += m_scorersHomeLength;
	
	if (team & TEAM_GUEST)
		size += m_scorersGuestLength;
		
	return size;
}

GoalEvent FootballMatch::GetScoreEvent(uint16 index, Team team) const
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

	return _getScoreEvent(index+1, team);
}

GoalEvent FootballMatch::_getScoreEvent(uint16 index, Team team) const
{
	GoalEvent *ptr;
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
	
	GoalEvent empty = {"", 0};
	
	if (ptr == NULL || size == 0)
		return empty;
	
	for (int i=0; i<size; ++i)
		if (i+1 == index)
			return ptr[i];
	
	return empty;
}

void FootballMatch::AddScoreEvent(Team team, std::string player, uint16 time)
{
	if (time == 0 || player == "")
		return;
		
	GoalEvent **ptr;
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
		*ptr = new GoalEvent[(*size)];
		(*ptr)[0].player = player;
		(*ptr)[0].time = time;
	}
	else
	{
		GoalEvent *tmp = new GoalEvent[*size];
		CopyEvent<GoalEvent>(tmp, *ptr, *size);
		delete[] *ptr;
		*ptr = new GoalEvent[(*size)+1];
		CopyEvent<GoalEvent>(*ptr, tmp, *size);
		(*ptr)[*size].player = player;
		(*ptr)[*size].time = time;
		*size++;
		
		delete[] tmp;
	}
}

void FootballMatch::SetPossession(uint16 possession, Team team)
{
	if (team == TEAM_HOME)
		m_possession = possession;
	else
		m_possession = 100 - possession;
}

void FootballMatch::SetResult()
{
	Match::SetResult(m_scorersHomeLength, m_scorersGuestLength);
}

FootballMatch& FootballMatch::operator=(const FootballMatch &fmtc)
{
	if (this != &fmtc)
	{
		delete[] m_scorersHome;
		delete[] m_scorersGuest;
		Copy(fmtc);
	}

	return *this;
}

bool FootballMatch::operator==(const Match &mtc) const
{
	const FootballMatch *fmtc = dynamic_cast<const FootballMatch*>(&mtc);

	if (fmtc == NULL) // If they are different sports, check only base class members
		return Match::operator==(mtc);

	// Check equality only on defined members
	if (fmtc->m_homeTeam != "" && m_homeTeam != fmtc->m_homeTeam)
		return false;

	if (fmtc->m_guestTeam != "" && m_guestTeam != fmtc->m_guestTeam)
		return false;

	if (fmtc->m_league != "" && m_league != fmtc->m_league)
		return false;

	if (fmtc->m_possession > 0 && m_possession != fmtc->m_possession)
		return false;

	// Everything defined is equal, check base class
	return this->Match::operator==(mtc);
}

bool FootballMatch::operator!=(const Match &mtc) const
{
	const FootballMatch *fmtc = dynamic_cast<const FootballMatch*>(&mtc);

	if (fmtc == NULL) // If they are different sports, check only base class members
		return Match::operator!=(mtc);

	// Check difference only on defined members
	if (fmtc->m_homeTeam != "" && m_homeTeam == fmtc->m_homeTeam)
		return false;

	if (fmtc->m_guestTeam != "" && m_guestTeam == fmtc->m_guestTeam)
		return false;

	if (fmtc->m_league != "" && m_league == fmtc->m_league)
		return false;

	if (fmtc->m_possession > 0 && m_possession == fmtc->m_possession)
		return false;

	// Everything defined is different, check base class
	return Match::operator!=(mtc);
}

std::ostream& operator<<(std::ostream &os, const FootballMatch &fmtc)
{
	const Match *m = &fmtc;
	os << "\t<match type=\"football\">\n";
	if (m != NULL)
		os << *m << "\n";
		
	os << "\t\t<home>" << fmtc.m_homeTeam << "</home>\n";
	os << "\t\t<guest>" << fmtc.m_guestTeam << "</guest>\n";
	os << "\t\t<league>" << fmtc.m_league << "</league>\n";
	os << "\t\t<timeoutshome>" << fmtc.m_possession << "</timeoutshome>\n";
	if (fmtc.m_scorersHomeLength > 0)
	{
		os << "\t\t<scorershome>\n";
		for (int i=0; i<fmtc.m_scorersHomeLength; ++i)
		{
			os << "\t\t\t<score>\n";
			os << "\t\t\t\t<player>" << fmtc.m_scorersHome[i].player << "</player>\n";
			os << "\t\t\t\t<time>" << fmtc.m_scorersHome[i].time << "</time>\n";
			os << "\t\t\t</score>\n";
		}
		os << "\t\t</scorershome>\n";
	}
	if (fmtc.m_scorersGuestLength > 0)
	{
		os << "\t\t<scorersguest>\n";
		for (int i=0; i<fmtc.m_scorersGuestLength; ++i)
		{
			os << "\t\t\t<score>\n";
			os << "\t\t\t\t<player>" << fmtc.m_scorersGuest[i].player << "</player>\n";
			os << "\t\t\t\t<time>" << fmtc.m_scorersGuest[i].time << "</time>\n";
			os << "\t\t\t</score>\n";
		}
		os << "\t\t</scorersguest>\n";
	}
	
	os << "\t</match>\n";
	
	return os;
}

void FootballMatch::Copy(const FootballMatch &fmtc)
{
	m_scorersHomeLength = fmtc.m_scorersHomeLength;
	m_scorersGuestLength = fmtc.m_scorersGuestLength;

	m_scorersHome = NULL;
	m_scorersGuest = NULL;
	
	if (m_scorersHomeLength > 0)
	{
		m_scorersHome = new GoalEvent[m_scorersHomeLength];
		CopyEvent<GoalEvent>(m_scorersHome, fmtc.m_scorersHome, m_scorersHomeLength);
	}
	
	if (m_scorersGuestLength > 0)
	{
		m_scorersGuest = new GoalEvent[m_scorersGuestLength];
		CopyEvent<GoalEvent>(m_scorersGuest, fmtc.m_scorersGuest, m_scorersGuestLength);
	}
	
	m_possession = fmtc.m_possession;
}