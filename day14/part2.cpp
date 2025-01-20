import extended_polymerization;

//leave what is needed
#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
#include <stdexcept>

//containers
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <array>

//boost
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/replace.hpp>

using namespace extended_polymerization;

void
Result::ProcessTwo(const std::string& data)
{
	if( m_template.empty( ) )
		std::copy( data.begin( ), data.end( ), std::back_inserter( m_template ) );
	else if( data.length( ) == 7 )
		m_pairInsertionRules[ data[ 0 ] ][ data[ 1 ] ] = data[ 6 ];
}

using CharPair = std::array<char, 2>;
using PolymerPairMap = std::map<CharPair, std::uint64_t>;

CharList ApplyRules( CharList _polymer, const PairInsertionRulesMap& _rules );

void PushNewPairOrIncrementExisting( PolymerPairMap& _map, const CharPair& _pair )
{
	auto insertResult = _map.insert( { _pair, 1 } );
	if( false == insertResult.second )
		++insertResult.first->second;
}

std::string
Result::FinishPartTwo()
{
	PolymerPairMap polymer;
	{
		auto prevIt = m_template.begin( );
		auto currentIt = ++prevIt;
		while( currentIt != m_template.end( ) )
		{
			PushNewPairOrIncrementExisting( polymer, { *prevIt, *currentIt } );
			prevIt = currentIt++;
		}
	}

	for( size_t iterations = 0; iterations != 40; ++iterations )
	{
		PolymerPairMap newPolymer;
		for( auto it = polymer.begin( ); it != polymer.end( ); ++it )
		{
			const auto& pair = it->first;
			const std::uint64_t& count = it->second;

			bool foundMatchingRule{ false };
			const auto& itFirstCharResult{ m_pairInsertionRules.find( pair[ 0 ] ) };
			if( itFirstCharResult != m_pairInsertionRules.end( ) )
			{
				const auto& itSecondCharResult{ itFirstCharResult->second.find( pair[ 1 ] ) };
				if( itSecondCharResult != itFirstCharResult->second.end( ) )
				{
					const char charToInsert{ itSecondCharResult->second };
					auto firstInsertResult = newPolymer.insert( { { pair[ 0 ], charToInsert }, count } );
					if( false == firstInsertResult.second )
						firstInsertResult.first->second += count;
					auto secondInsertResult = newPolymer.insert( { { charToInsert, pair[ 1 ]}, count } );
					if( false == secondInsertResult.second )
						secondInsertResult.first->second += count;
					foundMatchingRule = true;
				}
			}
			if( false == foundMatchingRule )
			{
				newPolymer.insert( *it );
			}
		}
		polymer.swap( newPolymer );
	}

	auto Position = [ ]( char _c ) -> size_t
		{ return _c - 'A'; };

	std::array<std::uint64_t, 'Z' - 'A'> occurrances{};
	for( const auto& item : polymer )
	{
		occurrances[ Position(item.first[ 0 ])] += item.second;
		occurrances[ Position(item.first[ 1 ])] += item.second;
	}

	++occurrances[ Position(*m_template.begin( ))];
	++occurrances[ Position(*m_template.rbegin( ))];


	for( std::uint64_t& o : occurrances )
		o /= 2;

	// we might not get all chars used so can't go for std::minmax_element
	auto most_occuring = 0ULL,
		least_occuring = static_cast< std::uint64_t >( -1 );
	for( std::uint64_t value : occurrances )
	{
		if( 0 == value )
			continue;
		most_occuring = std::max( most_occuring, value );
		least_occuring = std::min( least_occuring, value );
	}

	std::cout << "most  occurring: " << most_occuring << std::endl;
	std::cout << "least occurring: " << least_occuring << std::endl;

	// 4105531961858 is too low
	return std::to_string( most_occuring - least_occuring );
}