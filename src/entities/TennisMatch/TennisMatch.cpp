#include "TennisMatch.h"

TennisMatch::TennisMatch(std::string ref, Date date, std::string location, std::string player1, std::string player2, std::string league)
: 
	Match(ref, date, location), 
	m_player1(player1), 
	m_player2(player2), 
	m_league(league) 
{
	m_length = 0;
	
	Result zero = {0, 0};
	for (int i=0; i<5; ++i)
		m_partialScores[i] = zero;
}

std::string TennisMatch::GetPlayer1() const
{
	return m_player1;
}

std::string TennisMatch::GetPlayer2() const
{
	return m_player2;
}

std::string TennisMatch::GetWinner() const
{
	Result res = GetResult();
	if (res.home > res.guest)
		return m_player1;
	
	return m_player2;
}

std::string TennisMatch::GetLoser() const
{
	Result res = GetResult();
	if (res.home < res.guest)
		return m_player1;
	
	return m_player2;
}

std::string TennisMatch::GetLeague() const
{
	return m_league;
}

uint16 TennisMatch::GetLength() const
{
	return m_length;
}

Result TennisMatch::GetPartialScore(uint16 set) const
{
	return m_partialScores[set-1];
}

void TennisMatch::SetLength(uint16 length)
{
	m_length = length;
}

void TennisMatch::SetPartial(uint16 set, uint16 homeScore, uint16 guestScore)
{
	m_partialScores[set-1].home = homeScore;
	m_partialScores[set-1].guest = homeScore;
}

void TennisMatch::SetPartial(uint16 set, Result res)
{
	m_partialScores[set-1] = res;
}

void TennisMatch::SetResult()
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

bool TennisMatch::operator==(const Match &mtc) const
{
	const TennisMatch *tmtc = dynamic_cast<const TennisMatch*>(&mtc);

	if (tmtc == NULL) // If they are different sports, check only base class members
		return Match::operator==(mtc);

	// Check equality only on defined members
	if (tmtc->m_player1 != "" && m_player1 != tmtc->m_player1)
		return false;

	if (tmtc->m_player2 != "" && m_player2 != tmtc->m_player2)
		return false;

	if (tmtc->m_league != "" && m_league != tmtc->m_league)
		return false;
	
	if (tmtc->m_length > 0 && m_length != tmtc->m_length)
		return false;

	// Everything defined is equal, check base class
	return this->Match::operator==(mtc);
}

bool TennisMatch::operator!=(const Match &mtc) const
{
	const TennisMatch *tmtc = dynamic_cast<const TennisMatch*>(&mtc);

	if (tmtc == NULL) // If they are different sports, check only base class members
		return Match::operator!=(mtc);

	// Check difference only on defined members
	if (tmtc->m_player1 != "" && m_player1 == tmtc->m_player1)
		return false;

	if (tmtc->m_player2 != "" && m_player2 == tmtc->m_player2)
		return false;

	if (tmtc->m_league != "" && m_league == tmtc->m_league)
		return false;
	
	if (tmtc->m_length > 0 && m_length == tmtc->m_length)
		return false;

	// Everything defined is different, check base class
	return Match::operator!=(mtc);
}

std::ostream& operator<<(std::ostream &os, const TennisMatch &tmtc)
{
	const Match *m = &tmtc;
	os << "\t<match type=\"tennis\">\n";
	if (m != NULL)
		os << "\t\t" << *m << "\n";
		
	os << "\t\t<player1>" << tmtc.m_player1 << "</player1>\n";
	os << "\t\t<player2>" << tmtc.m_player2 << "</player2>\n";
	os << "\t\t<league>" << tmtc.m_league << "</league>\n";
	os << "\t\t<length>" << tmtc.m_length << "</length>\n";
	os << "\t\t<partials>\n";
	for (int i=0; i<5; ++i)
		os << "\t\t\t<result>" << tmtc.m_partialScores[i].home << " | " << tmtc.m_partialScores[i].guest << "</result>\n";
	os << "\t\t</partials>\n";
	
	os << "\t</match>\n";
	
	return os;
}
