import passage_pathing;

#include <string>

using namespace passage_pathing;

void
Result::ProcessOne( const std::string& data )
{
	Process( data );
}

std::string
Result::FinishPartOne( )
{
	//no duplicates possible here
	return std::to_string( GetAllPaths( m_caveMap, "", "start", false ).size( ) );
}
