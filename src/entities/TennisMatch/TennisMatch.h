#ifndef TENNISMATCH_H
#define TENNISMATCH_H

#include <iostream>
#include <string>

#include "SharedDefines.h"
#include "Date.h"
#include "Match.h"

class TennisMatch : public Match
{
private:
	std::string m_player1;
	std::string m_player2;
	std::string m_league;
	Result m_partialScores[5];
	uint16 m_length;
	
public:
	TennisMatch(std::string ref = "", Date date = 0, std::string location = "", std::string home = "", std::string guest = "", std::string league = "");
	
	 // <--------- Getters ------------
	std::string GetPlayer1() const;
	std::string GetPlayer2() const;
	std::string GetWinner() const;
	std::string GetLoser() const;
	uint16 GetLength() const;
	Result GetPartialScore(uint16 set) const;
	std::string GetLeague() const;
	// ------------------------------>
	
	// <--------- Setters -----------
	void SetLength(uint16 length);
	void SetPartial(uint16 set, uint16 p1score, uint16 p2score);
	void SetPartial(uint16 set, Result res);
	virtual void SetResult();
	// ------------------------------>
	
	// <-------- Operators -----------
	bool operator==(const Match &mtc) const;
	bool operator!=(const Match &mtc) const;
	friend std::ostream& operator<<(std::ostream &os, const TennisMatch &tmtc);
	// ------------------------------>
};

#endif
