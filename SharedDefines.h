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


#endif
