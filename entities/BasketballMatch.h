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
    BasketEvent* m_scorersGuest;
    uint16 m_timeoutsHome;
    uint16 m_timeoutsGuest;
    
public:
    BasketballMatch(std::string ref, Date date, std::string location, std::string home, std::string guest, std::string league);
    BasketballMatch(const BasketballMatch &bmtc);
    
    // <--------- Getters ------------
    std::string GetHomeTeam() const;
    std::string GetGuestTeam() const;
    std::string GetWinner() const;
    std::string GetLoser() const;
    std::string GetLeague() const;
    uint16 GetTimeouts(Team team) const;
    BasketEvent* GetScoreEvents(BasketEventType type, Team team) const;
    // ------------------------------>
    
    // <--------- Setters -----------
    void SetEvent(BasketEventType type, Team team, std::string player, uint16 time, uint16 quarter);
    void SetTimeout(Team team);
    virtual void SetResult();
    // ------------------------------>
    
    // <-------- Operators -----------
    bool operator==(const Match &mtc) const;
    bool operator!=(const Match &mtc) const;
    friend std::ostream& operator<<(std::ostream &os, const BasketballMatch &mtc);
    // ------------------------------>
};
	
#endif
