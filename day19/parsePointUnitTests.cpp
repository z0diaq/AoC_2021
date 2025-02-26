#include <gtest/gtest.h>
#include <string>
#include <stdexcept>

import beacon_scanner;

using namespace beacon_scanner;

extern Point ParsePoint( const std::string& line );

TEST( ParserTest, ParseValidPoint )
{
	std::string input = "1,2,3";
	Point expected{ {1, 2, 3} };

	EXPECT_EQ( ParsePoint( input ), expected );
}

TEST( ParserTest, ParseNegativeNumbers )
{
	std::string input = "-5,-10,-15";
	Point expected{ {-5, -10, -15} };

	EXPECT_EQ( ParsePoint( input ), expected );
}

TEST( ParserTest, ParseMixedNumbers )
{
	std::string input = "123,-456,789";
	Point expected{ {123, -456, 789} };

	EXPECT_EQ( ParsePoint( input ), expected );
}

TEST( ParserTest, InvalidFormat )
{
	// Too few components
	std::string input1 = "1,2";
	EXPECT_THROW( ParsePoint( input1 ), std::logic_error );

	// Too many components
	std::string input2 = "1,2,3,4";
	EXPECT_THROW( ParsePoint( input2 ), std::logic_error );

	// Non-numeric data
	std::string input3 = "1,a,3";
	EXPECT_THROW( ParsePoint( input3 ), std::invalid_argument );
}
