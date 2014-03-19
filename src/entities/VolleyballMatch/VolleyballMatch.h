#ifndef VOLLEYBALLMATCH_H
#define VOLLEYBALLMATCH_H

#include <iostream>
#include <string>

#include "SharedDefines.h"
#include "Date.h"
#include "Match.h"

class VolleyballMatch : public Match
{
private:	
	std::string m_homeTeam;
	std::string m_guestTeam;
	std::string m_league;
	VolleyAttack* m_scorersHome;
	uint16 m_scorersHomeLength;
	VolleyAttack* m_scorersGuest;
	uint16 m_scorersGuestLength;
	Result m_partialScores[5];
	int16 m_timeoutsHome;
	int16 m_timeoutsGuest;
	uint16 m_length;
	
	VolleyAttack _getAttackForTeam(Team team, uint16 set, uint16 index) const;
	void Copy(const VolleyballMatch &vmtc);
	
public:
	VolleyballMatch(std::string ref = "", Date date = 0, std::string location = "", std::string home = "", std::string guest = "", std::string league = "");
	VolleyballMatch(const VolleyballMatch &vmtc);
	~VolleyballMatch();
	
	// <--------- Getters ------------
	std::string GetHomeTeam() const;
	std::string GetGuestTeam() const;
	std::string GetWinner() const;
	std::string GetLoser() const;
	uint16 GetLength() const;
	std::string GetLeague() const;
	Result GetPartialScore(uint16 set) const;
	uint16 GetTimeouts(Team team) const;
	VolleyAttack GetAttackForTeam(Team team, uint16 set, uint16 index) const;
	uint16 GetAttacksLength(Team team = TEAM_ANY) const;
	uint16 GetAttacksForPlayer(std::string player, Team team) const;
	// ------------------------------>
	
	// <--------- Setters -----------
	void AddAttack(Team team, std::string player, uint16 set);
	void AddTimeout(Team team);
	void SetLength(uint16 length);
	void SetPartial(uint16 set, uint16 homeScore, uint16 guestScore);
	void SetPartial(uint16 set, Result res);
	virtual void SetResult();
	// ------------------------------>
	
	// <-------- Operators -----------
	VolleyballMatch& operator=(const VolleyballMatch &fmtc);
	bool operator==(const Match &mtc) const;
	bool operator!=(const Match &mtc) const;
	friend std::ostream& operator<<(std::ostream &os, const VolleyballMatch &vmtc);
	// ------------------------------>
};
	
#endif
