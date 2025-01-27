import transparent_origami;

//leave what is needed
#include <string>
#include <algorithm>

using namespace transparent_origami;

void
Result::ProcessOne( const std::string& data )
{
	static bool seenFoldBy = false;

	if( m_sheet.empty( ) )
		seenFoldBy = false;

	if( false == seenFoldBy && Process( data ) )
		seenFoldBy = true;
}

std::string
Result::FinishPartOne( )
{
	int64_t visiblePoints{ 0 };
	for( const auto& line : m_sheet )
		visiblePoints += std::count( line.begin( ), line.end( ), '#' );

	return std::to_string( visiblePoints );
}
