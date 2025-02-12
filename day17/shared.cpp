import trick_shot;

#include <string>
#include <regex>

using namespace trick_shot;

void
Result::Teardown()
{
	m_targetAreaDescription.clear( );
}

std::pair<int, int>
Result::Solve( const std::string& targetAreaDescription ) const
{
	// sample format
	// target area: x=20..30, y=-10..-5
	std::regex pattern( "target area: x=(-?\\d+)\\.\\.(-?\\d+), y=(-?\\d+)\\.\\.(-?\\d+)" );

	std::smatch matches;
	if( !std::regex_match( targetAreaDescription, matches, pattern ) ) {
		throw std::invalid_argument( "Invalid format" );
	}

	return { FindMaxHeight( TargetArea(
		std::stoi( matches[ 1 ].str( ) ),   // minX
		std::stoi( matches[ 2 ].str( ) ),   // maxX
		std::stoi( matches[ 3 ].str( ) ),   // minY
		std::stoi( matches[ 4 ].str( ) )    // maxY
	) ) };
}
