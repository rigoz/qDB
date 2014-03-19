#include "VolleyballMatch.h"

VolleyballMatch::VolleyballMatch(std::string ref, Date date, std::string location, std::string home, std::string guest, std::string league)
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
	
	Result zero = {0, 0};
	for (int i=0; i<5; ++i)
		m_partialScores[i] = zero;
	
	m_timeoutsHome = -1;
	m_timeoutsGuest = -1;
	m_length = 0;
}

VolleyballMatch::VolleyballMatch(const VolleyballMatch &vmtc)
:
	Match(vmtc.GetReferee(), vmtc.GetDate(), vmtc.GetLocation()),
	m_homeTeam(vmtc.m_homeTeam), 
	m_guestTeam(vmtc.m_guestTeam), 
	m_league(vmtc.m_league)
{
	if (this != &vmtc)
		Copy(vmtc);
}

VolleyballMatch::~VolleyballMatch()
{
	delete[] m_scorersHome;
	delete[] m_scorersGuest;
}

std::string VolleyballMatch::GetHomeTeam() const
{
	return m_homeTeam;
}

std::string VolleyballMatch::GetGuestTeam() const
{
	return m_guestTeam;
}

std::string VolleyballMatch::GetWinner() const
{
	Result res = GetResult();
	if (res.home > res.guest)
		return m_homeTeam;
		
	return m_guestTeam;
}

std::string VolleyballMatch::GetLoser() const
{
	Result res = GetResult();
	if (res.home < res.guest)
		return m_homeTeam;
		
	return m_guestTeam;
}

std::string VolleyballMatch::GetLeague() const
{
	return m_league;
}

uint16 VolleyballMatch::GetLength() const
{
	return m_length;
}

uint16 VolleyballMatch::GetTimeouts(Team team) const
{
	uint16 count = 0;
	if (team & TEAM_HOME)
		count += m_timeoutsHome;
		
	if (team & TEAM_GUEST)
		count += m_timeoutsGuest;
		
	return count;
}

uint16 VolleyballMatch::GetAttacksLength(Team team) const
{
	uint16 size = 0;
	
	if (team & TEAM_HOME)
		size += m_scorersHomeLength;
	
	if (team & TEAM_GUEST)
		size += m_scorersGuestLength;
		
	return size;
}

Result VolleyballMatch::GetPartialScore(uint16 set) const
{
	return m_partialScores[set-1];
}

VolleyAttack VolleyballMatch::GetAttackForTeam(Team team, uint16 set, uint16 index) const
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

	return _getAttackForTeam(team, set, index+1);
}

VolleyAttack VolleyballMatch::_getAttackForTeam(Team team, uint16 set, uint16 index) const
{
	VolleyAttack *ptr;
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
	
	VolleyAttack empty = {"", 0};
	
	if (ptr == NULL || size == 0)
		return empty;
	
	uint16 count = 0;
	for (int i=0; i<size; ++i)
	{
		if (ptr[i].set == set)
			count++;
		if (count == index)
			return ptr[i];
	}
	
	return empty;
}

uint16 VolleyballMatch::GetAttacksForPlayer(std::string player, Team team) const
{
	uint16 attacks = 0;
	VolleyAttack *ptr;
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
	
	if (ptr == NULL || size == 0)
		return 0;
	
	for (int i=0; i<size; ++i)
		if (ptr[i].player == player)
			attacks++;
	
	return attacks;
}

void VolleyballMatch::AddAttack(Team team, std::string player, uint16 set)
{
	if (set == 0 || player == "")
		return;
		
	VolleyAttack **ptr;
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
		*ptr = new VolleyAttack[(*size)];
		(*ptr)[0].player = player;
		(*ptr)[0].set = set;
	}
	else
	{
		VolleyAttack *tmp = new VolleyAttack[*size];
		CopyEvent<VolleyAttack>(tmp, *ptr, *size);
		delete[] *ptr;
		*ptr = new VolleyAttack[(*size)+1];
		CopyEvent<VolleyAttack>(*ptr, tmp, *size);
		(*ptr)[*size].player = player;
		(*ptr)[*size].set = set;
		*size++;
		
		delete[] tmp;
	}
}

void VolleyballMatch::AddTimeout(Team team)
{
	if (team == TEAM_HOME)
		m_timeoutsHome++;
	else
		m_timeoutsGuest++;
}

void VolleyballMatch::SetLength(uint16 length)
{
	m_length = length;
}

void VolleyballMatch::SetPartial(uint16 set, uint16 homeScore, uint16 guestScore)
{
	m_partialScores[set-1].home = homeScore;
	m_partialScores[set-1].guest = homeScore;
}

void VolleyballMatch::SetPartial(uint16 set, Result res)
{
	m_partialScores[set-1] = res;
}

void VolleyballMatch::SetResult()
{
	uint16 homeScore = 0;
	uint16 guestScore = 0;
	for (int i=0; i<5; ++i)
		if (m_partialScores[i].home > m_partialScores[i].guest)
			homeScore++;
		else
			guestScore++;
	
	Match::SetResult(homeScore, guestScore);
}

VolleyballMatch& VolleyballMatch::operator=(const VolleyballMatch &vmtc)
{
	if (this != &vmtc)
	{
		delete[] m_scorersHome;
		delete[] m_scorersGuest;
		Copy(vmtc);
	}

	return *this;
}

bool VolleyballMatch::operator==(const Match &mtc) const
{
	const VolleyballMatch *vmtc = dynamic_cast<const VolleyballMatch*>(&mtc);

	if (vmtc == NULL) // If they are different sports, check only base class members
		return Match::operator==(mtc);

	// Check equality only on defined members
	if (vmtc->m_homeTeam != "" && m_homeTeam != vmtc->m_homeTeam)
		return false;

	if (vmtc->m_guestTeam != "" && m_guestTeam != vmtc->m_guestTeam)
		return false;

	if (vmtc->m_league != "" && m_league != vmtc->m_league)
		return false;

	if (vmtc->m_timeoutsHome != -1 && m_timeoutsHome != vmtc->m_timeoutsHome)
		return false;

	if (vmtc->m_timeoutsGuest != -1 && m_timeoutsGuest != vmtc->m_timeoutsGuest)
		return false;
	
	if (vmtc->m_length > 0 && m_length != vmtc->m_length)
		return false;

	// Everything defined is equal, check base class
	return this->Match::operator==(mtc);
}

bool VolleyballMatch::operator!=(const Match &mtc) const
{
	const VolleyballMatch *vmtc = dynamic_cast<const VolleyballMatch*>(&mtc);

	if (vmtc == NULL) // If they are different sports, check only base class members
		return Match::operator!=(mtc);

	// Check difference only on defined members
	if (vmtc->m_homeTeam != "" && m_homeTeam == vmtc->m_homeTeam)
		return false;

	if (vmtc->m_guestTeam != "" && m_guestTeam == vmtc->m_guestTeam)
		return false;

	if (vmtc->m_league != "" && m_league == vmtc->m_league)
		return false;

	if (vmtc->m_timeoutsHome != -1 && m_timeoutsHome == vmtc->m_timeoutsHome)
		return false;

	if (vmtc->m_timeoutsGuest != -1 && m_timeoutsGuest == vmtc->m_timeoutsGuest)
		return false;
	
	if (vmtc->m_length > 0 && m_length == vmtc->m_length)
		return false;

	// Everything defined is different, check base class
	return Match::operator!=(mtc);
}

std::ostream& operator<<(std::ostream &os, const VolleyballMatch &vmtc)
{
	const Match *m = &vmtc;
	os << "\t<match type=\"volley\">\n";
	if (m != NULL)
		os << *m << "\n";
		
	os << "\t\t<home>" << vmtc.m_homeTeam << "</home>\n";
	os << "\t\t<guest>" << vmtc.m_guestTeam << "</guest>\n";
	os << "\t\t<league>" << vmtc.m_league << "</league>\n";
	os << "\t\t<timeoutshome>" << vmtc.m_timeoutsHome << "</timeoutshome>\n";
	os << "\t\t<timeoutsguest>" << vmtc.m_timeoutsGuest << "</timeoutsguest>\n";
	os << "\t\t<length>" << vmtc.m_length << "</length>\n";
	if (vmtc.m_scorersHomeLength > 0)
	{
		os << "\t\t<scorershome>\n";
		for (int i=0; i<vmtc.m_scorersHomeLength; ++i)
		{
			os << "\t\t\t<score>\n";
			os << "\t\t\t\t<player>" << vmtc.m_scorersHome[i].player << "</player>\n";
			os << "\t\t\t\t<set>" << vmtc.m_scorersHome[i].set << "</set>\n";
			os << "\t\t\t</score>\n";
		}
		os << "\t\t</scorershome>\n";
	}
	if (vmtc.m_scorersGuestLength > 0)
	{
		os << "\t\t<scorersguest>\n";
		for (int i=0; i<vmtc.m_scorersGuestLength; ++i)
		{
			os << "\t\t\t<score>\n";
			os << "\t\t\t\t<player>" << vmtc.m_scorersGuest[i].player << "</player>\n";
			os << "\t\t\t\t<set>" << vmtc.m_scorersGuest[i].set << "</set>\n";
			os << "\t\t\t</score>\n";
		}
		os << "\t\t</scorersguest>\n";
	}
	os << "\t\t<partials>\n";
	for (int i=0; i<5; ++i)
		os << "\t\t\t<result>" << vmtc.m_partialScores[i].home << " | " << vmtc.m_partialScores[i].guest << "</result>\n";
	os << "\t\t</partials>\n";
	
	os << "\t</match>\n";
	
	return os;
}

void VolleyballMatch::Copy(const VolleyballMatch &vmtc)
{
	m_scorersHomeLength = vmtc.m_scorersHomeLength;
	m_scorersGuestLength = vmtc.m_scorersGuestLength;

	m_scorersHome = NULL;
	m_scorersGuest = NULL;
	
	if (m_scorersHomeLength > 0)
	{
		m_scorersHome = new VolleyAttack[m_scorersHomeLength];
		CopyEvent<VolleyAttack>(m_scorersHome, vmtc.m_scorersHome, m_scorersHomeLength);
	}
	
	if (m_scorersGuestLength > 0)
	{
		m_scorersGuest = new VolleyAttack[m_scorersGuestLength];
		CopyEvent<VolleyAttack>(m_scorersGuest, vmtc.m_scorersGuest, m_scorersGuestLength);
	}
	
	for (int i=0; i<5; ++i)
		m_partialScores[i] = vmtc.m_partialScores[i];
	
	m_timeoutsHome = vmtc.m_timeoutsHome;
	m_timeoutsGuest = vmtc.m_timeoutsGuest;
	m_length = vmtc.m_length;
}