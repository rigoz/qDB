#ifndef VOLLEYBALLMATCH_H
#define VOLLEYBALLMATCH_H

#include <iostream>
#include <string>

#include "SharedDefines.h"
#include "Date.h"
#include "Match.h"

struct VolleyAttack
{
  std::string player;
  uint16 set;
};

class VolleyballMatch : public Match
{
private:    
    std::string m_homeTeam;
    std::string m_guestTeam;
    std::string m_league;
    VolleyAttack* m_scorersHome;
    VolleyAttack* m_scorersGuest;
    Result m_partialScores[5];
    uint16 m_timeoutsHome;
    uint16 m_timeoutsGuest;
    uint16 m_length;
    
public:
    VolleyballMatch(std::string ref, Date date, std::string location, std::string home, std::string guest, std::string league);
    VolleyballMatch(const VolleyballMatch &vmtc);
    
    // <--------- Getters ------------
    std::string GetHomeTeam() const;
    std::string GetGuestTeam() const;
    std::string GetWinner() const;
    std::string GetLoser() const;
    uint16 GetLength() const;
    std::string GetLeague() const;
    Result GetPartialScore(uint16 set);
    uint16 GetTimeouts(Team team) const;
    uint16 GetAttacksForPlayer(std::string player, Team team = TEAM_ANY) const;
    // ------------------------------>
    
    // <--------- Setters -----------
    void AddAttack(Team team, std::string player, uint16 set);
    void SetTimeout(Team team);
    void SetLength(uint16 length);
    void SetPartial(uint16 set, uint16 p1score, uint16 p2score);
    void SetPartial(uint16 set, Result res);
    virtual void SetResult();
    // ------------------------------>
    
    // <-------- Operators -----------
    bool operator==(const Match &mtc) const;
    bool operator!=(const Match &mtc) const;
    friend std::ostream& operator<<(std::ostream &os, const VolleyballMatch &mtc);
    // ------------------------------>
};
	
#endif
