import passage_pathing;

#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace passage_pathing;

bool
IsSmallCave( const std::string& cave );

void
Append( std::vector<std::string>&& source, std::vector<std::string>& destination );

std::vector<std::string>
Result::GetAllPaths(
	std::map<std::string, Result::ConnectionList> caveMap,
	std::string                                   currentPath,
	const std::string&                            startingPoint,
	bool                                          allowSecondVisit )
{
	std::vector<std::string> result;
	auto connections = caveMap[ startingPoint ];
	const bool startPointIsSmall = IsSmallCave( startingPoint );

	if( false == currentPath.empty( ) )
		currentPath += ",";
	currentPath += startingPoint;

	for( size_t connNo = 0; connNo != connections.size( ); ++connNo )
	{
		auto connection = connections[ connNo ];
		// need to work on copy when processing points
		// or we get changes propagated to next paths removing valid connections
		auto tempMap = caveMap;

		if( startPointIsSmall )
		{
			auto connCopy = tempMap[ startingPoint ];
			for( const auto& conn : connCopy )
				tempMap[ conn ].erase( std::remove( tempMap[ conn ].begin( ), tempMap[ conn ].end( ), startingPoint ) );//remove path-back
			tempMap[ startingPoint ].clear( );
		}

		if( connection == "end" )
			result.push_back( currentPath + ",end" );
		else
			Append( GetAllPaths( tempMap, currentPath, connection, allowSecondVisit ), result );
	}

	if( startPointIsSmall && allowSecondVisit && startingPoint != "start" )
	{
		allowSecondVisit = false;
		for( size_t connNo = 0; connNo != connections.size( ); ++connNo )
		{
			auto connection = connections[ connNo ];
			// need to work on copy when processing points
			// or we get changes propagated to next paths removing valid connections
			auto tempMap = caveMap;

			if( connection == "end" )
			{
				result.push_back( currentPath + ",end" );
			}
			else
				Append( GetAllPaths( tempMap, currentPath, connection, allowSecondVisit ), result );
		}
	}

	return result;
}

void
Result::Process( const std::string& data )
{
	auto splitPos = data.find( '-' );

	m_caveMap[ data.substr( 0, splitPos ) ].push_back( data.substr( splitPos + 1 ) );
	m_caveMap[ data.substr( splitPos + 1 ) ].push_back( data.substr( 0, splitPos ) );
}

void
Result::Teardown( )
{
	m_caveMap.clear( );
}

void
Append( std::vector<std::string>&& source, std::vector<std::string>& destination )
{
	destination.reserve( destination.size( ) + source.size( ) );
	for( auto& element : source )
		destination.push_back( std::move( element ) );
}

bool
IsSmallCave( const std::string& cave )
{
	return cave[ 0 ] >= 'a' && cave[ 0 ] <= 'z';
}
