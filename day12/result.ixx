module;

#include <iostream>
#include <vector>
#include <map>

export module passage_pathing;

import AoC;

export namespace passage_pathing
{
	class Result : public AoC::Result
	{

	public:
		typedef std::vector<std::string> ConnectionList;

		Result( ) = default;

		virtual void Init( ) override { };
		virtual void ProcessOne( const std::string& data ) override;
		virtual void ProcessTwo( const std::string& data ) override;
		virtual uint64_t Finish( ) override;
		virtual void Teardown( ) override;

	private:
		std::map<std::string, ConnectionList > m_caveMap;

		//part one section
		virtual uint64_t FinishPartOne( ) const;

		//part two section
		virtual uint64_t FinishPartTwo( ) const;
	};
}

using namespace passage_pathing;

void
Result::Teardown( )
{
	m_caveMap.clear( );
}

void
Result::ProcessOne( const std::string& data )
{
	auto splitPos = data.find( '-' );

	m_caveMap[ data.substr( 0, splitPos ) ].push_back( data.substr( splitPos + 1 ) );
	m_caveMap[ data.substr( splitPos + 1 ) ].push_back( data.substr( 0, splitPos ) );
}

void
Result::ProcessTwo( const std::string& data )
{
}

bool
IsSmallCave( const std::string& cave );

std::vector<std::string>
GetAllPaths(
	std::map<std::string, Result::ConnectionList> caveMap,
	std::string                                   currentPath,
	const std::string&                            startingPoint );

uint64_t
Result::Finish( )
{
	return IsPartOne( ) ? FinishPartOne( ) : FinishPartTwo( );
}

uint64_t
Result::FinishPartOne( ) const
{
	return static_cast< uint64_t >( GetAllPaths( m_caveMap, "", "start" ).size( ) );
}

uint64_t
Result::FinishPartTwo( ) const
{
	return 0;
}

template<typename T>
void RemoveSingleElement( std::vector<T>& vec, const T& value )
{
	auto it = std::find( vec.begin( ), vec.end( ), value );
	if( it != vec.end( ) )
	{
		std::swap( *it, vec.back( ) );
		vec.resize( vec.size( ) - 1 );
	}
}

std::vector<std::string>
GetAllPaths(
	std::map<std::string, Result::ConnectionList> caveMap,
	std::string                                   currentPath,
	const std::string&                            startingPoint )
{
	std::vector<std::string> result;

	auto connections = caveMap[ startingPoint ];

	auto Append = [ ]( std::vector<std::string>&& source, std::vector<std::string>& destination ) -> void
	{
		destination.reserve( destination.size( ) + source.size( ) );
		for( auto& element : source )
			destination.push_back( std::move( element ) );
	};

	if( false == currentPath.empty( ) )
		currentPath += ",";
	currentPath += startingPoint;

	for( auto connection : connections )
	{
		// need to work on copy when processing points
		// or we get changes propagated to next paths removing valid connections
		auto tempMap = caveMap;

		//can't go back to small cave from any direction
		if( IsSmallCave( startingPoint ) )
		{
			for( auto link : connections )
				RemoveSingleElement( tempMap[ link ], startingPoint );
				//std::erase( tempMap[ link ], startingPoint );
		}

		//can't go again into small cave from any direction
		if( IsSmallCave( connection ) )
		{
			auto links = tempMap[ connection ];
			for( auto link : links )
				RemoveSingleElement( tempMap[ link ], connection );
				//std::erase( tempMap[ link ], connection );
		}

		if( connection == "end" )
		{
			currentPath += ",end";
			result.push_back( currentPath );
		}
		else
			Append( GetAllPaths( tempMap, currentPath, connection ), result );
	}

	return result;
}

bool
IsSmallCave( const std::string& cave )
{
	return cave[ 0 ] >= 'a' && cave[ 0 ] <= 'z';
}
