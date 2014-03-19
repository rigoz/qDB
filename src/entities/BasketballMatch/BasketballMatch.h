#ifndef BASKETBALLMATCH_H
#define BASKETBALLMATCH_H

#include <iostream>
#include <string>

#include "SharedDefines.h"
#include "Date.h"
#include "Match.h"

class BasketballMatch : public Match
{
private:	
	std::string m_homeTeam;
	std::string m_guestTeam;
	std::string m_league;
	BasketEvent* m_scorersHome;
	uint16 m_scorersHomeLength;
	BasketEvent* m_scorersGuest;
	uint16 m_scorersGuestLength;
	int16 m_timeoutsHome;
	int16 m_timeoutsGuest;
	
	BasketEvent _getScoreEvent(BasketEventType type,  uint16 index, Team team) const;
	static void InitEvent(BasketEvent *ptr, uint16 index, std::string player, BasketEventType type, uint16 time, uint16 quarter);
	static uint16 UpdateScoreForTeam(BasketEvent *ptr, uint16 size);
	void Copy(const BasketballMatch &bmtc);

public:
	BasketballMatch(std::string ref = "", Date date = 0, std::string location = "", std::string home = "", std::string guest = "", std::string league = "");
	BasketballMatch(const BasketballMatch &bmtc);
	~BasketballMatch();
	
	// <--------- Getters ------------
	std::string GetHomeTeam() const;
	std::string GetGuestTeam() const;
	std::string GetWinner() const;
	std::string GetLoser() const;
	std::string GetLeague() const;
	int16 GetTimeouts(Team team = TEAM_ANY) const;
	BasketEvent GetScoreEvent(BasketEventType type, uint16 index, Team team = TEAM_ANY) const;
	uint16 GetScoreEventsLength(Team team = TEAM_ANY) const; // number of elements of all types
	uint16 GetScoreEventLength(BasketEventType type, Team team = TEAM_ANY) const; // number of elements of one type
	// ------------------------------>
	
	// <--------- Setters -----------
	void AddScoreEvent(BasketEventType type, Team team, std::string player, uint16 time, uint16 quarter);
	void AddTimeout(Team team);
	virtual void SetResult();
	// ------------------------------>
	
	// <-------- Operators -----------
	BasketballMatch& operator=(const BasketballMatch &bmtc);
	bool operator==(const Match &mtc) const;
	bool operator!=(const Match &mtc) const;
	friend std::ostream& operator<<(std::ostream &os, const BasketballMatch &bmtc);
	// ------------------------------>
};
	
#endif
