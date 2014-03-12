#ifndef SHAREDDEFINES_H

#	define SHAREDDEFINES_H

#	include <cstdlib>

#	ifndef NULL
#		define NULL 0
#	endif

#	ifndef NDEBUG
#   	define ASSERT_PTR(condition) \
			if (!(condition)) \
			{ \
				std::cout << std::endl << "<-!->" << std::endl; \
				std::cout << "Something went wrong! NULL pointer dereferenced on file \"" \
				<< __FILE__ << "\", line " << __LINE__ << std::endl << "Program execution has been stopped." << std::endl \
				<< "<-!->" << std::endl; \
				std::exit(EXIT_FAILURE); \
			}
#	endif

typedef unsigned int uint32;
typedef unsigned short uint16;
typedef short int16;

enum Team
{
  TEAM_HOME 		= 0x00000001,
  TEAM_GUEST 		= 0x00000002,
  
  TEAM_ANY 		= TEAM_HOME | TEAM_GUEST
};

struct BasketEvent
{
  std::string player;
  uint16 value;
  uint16 time;
  uint16 quarter;
};

enum BasketEventType
{
  BB_EVENT_TYPE_FREESHOT 	= 0x00000001,
  BB_EVENT_TYPE_DOUBLESHOT 	= 0x00000002,
  BB_EVENT_TYPE_TRIPLESHOT 	= 0x00000004,
 
  BB_EVENT_TYPE_ALL 		= BB_EVENT_TYPE_FREESHOT | BB_EVENT_TYPE_DOUBLESHOT | BB_EVENT_TYPE_TRIPLESHOT
};

struct FootballEvent
{
  std::string player;
  int16 time;
};

enum FootballEventType
{
  FB_EVENT_TYPE_GOAL 		= 0x00000001,
  FB_EVENT_TYPE_AUTOGOAL 	= 0x00000002,
  FB_EVENT_TYPE_YELLOW 		= 0x00000004,
  FB_EVENT_TYPE_RED 		= 0x00000008,
  
  FB_EVENT_SCORE 		= FB_EVENT_TYPE_GOAL 	| FB_EVENT_TYPE_AUTOGOAL,
  FB_EVENT_FAULT 		= FB_EVENT_TYPE_YELLOW 	| FB_EVENT_TYPE_RED,
  FB_EVENT_ALL 			= FB_EVENT_TYPE_GOAL 	| FB_EVENT_TYPE_AUTOGOAL | FB_EVENT_TYPE_YELLOW | FB_EVENT_TYPE_RED
};

struct VolleyAttack
{
  std::string player;
  uint16 set;
};

#endif
