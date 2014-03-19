#ifndef FOOTBALLMATCH_H
#define FOOTBALLMATCH_H

#include <iostream>
#include <string>

#include "SharedDefines.h"
#include "Date.h"
#include "Match.h"

class FootballMatch : public Match
{
private:	
	std::string m_homeTeam;
	std::string m_guestTeam;
	std::string m_league;
	GoalEvent* m_scorersHome;
	uint16 m_scorersHomeLength;
	GoalEvent* m_scorersGuest;
	uint16 m_scorersGuestLength;
	uint16 m_possession;
	
	GoalEvent _getScoreEvent(uint16 index, Team team) const;
	void Copy(const FootballMatch &fmtc);
	
public:
	FootballMatch(std::string ref = "", Date date = 0, std::string location = "", std::string home = "", std::string guest = "", std::string league = "");
	FootballMatch(const FootballMatch &fmtc);
	~FootballMatch();
	
	// <--------- Getters ------------
	std::string GetHomeTeam() const;
	std::string GetGuestTeam() const;
	std::string GetWinner() const;
	std::string GetLoser() const;
	std::string GetLeague() const;
	uint16 GetPossession(Team team) const;
	GoalEvent GetScoreEvent(uint16 index, Team team = TEAM_ANY) const;
	uint16 GetScoreEventsLength(Team team = TEAM_ANY) const;
	// ------------------------------>
	
	// <--------- Setters -----------
	void AddScoreEvent(Team team, std::string player, uint16 time);
	void SetPossession(uint16 possession, Team team);
	virtual void SetResult();
	// ------------------------------>
	
	// <-------- Operators -----------
	FootballMatch& operator=(const FootballMatch &fmtc);
	bool operator==(const Match &mtc) const;
	bool operator!=(const Match &mtc) const;
	friend std::ostream& operator<<(std::ostream &os, const FootballMatch &mtc);
	// ------------------------------>
};
	
#endif
