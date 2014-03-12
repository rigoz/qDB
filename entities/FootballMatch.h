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
    FootballEvent* m_scorersHome;
    FootballEvent* m_scorersGuest;
    FootballEvent* m_yellowsHome;
    FootballEvent* m_yellowsGuest;
    uint16 m_possession;
    
public:
    FootballMatch(std::string ref, Date date, std::string location, std::string home, std::string guest, std::string league);
    FootballMatch(const FootballMatch &fmtc);
    
    // <--------- Getters ------------
    std::string GetHomeTeam() const;
    std::string GetGuestTeam() const;
    std::string GetWinner() const;
    std::string GetLoser() const;
    std::string GetLeague() const;
    FootballEvent* GetAllEvents(Event event, Team team) const;
    // ------------------------------>
    
    // <--------- Setters -----------
    void SetEvent(Event event, Team team, std::string player, uint16 time);
    void SetPossession(uint16 possession);
    virtual void SetResult();
    // ------------------------------>
    
    // <-------- Operators -----------
    bool operator==(const Match &mtc) const;
    bool operator!=(const Match &mtc) const;
    friend std::ostream& operator<<(std::ostream &os, const FootballMatch &mtc);
    // ------------------------------>
};
	
#endif
