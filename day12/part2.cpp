import passage_pathing;

#include <string>
#include <algorithm>

using namespace passage_pathing;

void
Result::ProcessTwo( const std::string& data )
{
	Process( data );
}

std::string
Result::FinishPartTwo( )
{
	//this call will return duplicates
	auto allpaths = GetAllPaths( m_caveMap, "", "start", true );

	//remove duplicates
	std::ranges::sort( allpaths );
	auto last = std::unique( allpaths.begin( ), allpaths.end( ) );
	allpaths.erase( last, allpaths.end( ) );

	return std::to_string( allpaths.size( ) );
}
