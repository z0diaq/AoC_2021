import extended_polymerization;

#include <string>
#include <algorithm>
#include <iterator>
#include <map>
#include <array>

#include <iostream>

using namespace extended_polymerization;

void
Result::ProcessTwo(const std::string& data)
{
	if( m_template.empty( ) )
		std::copy( data.begin( ), data.end( ), std::back_inserter( m_template ) );
	else if( data.length( ) == 7 )
	{
		std::cout << "processed " << data << std::endl;
		m_pairInsertionRules[ { data[ 0 ], data[ 1 ] } ] = data[ 6 ];
	}
}

using PolymerPairMap = std::map<CharPair, std::uint64_t>;

template<typename ItemType>
void PushNewPairOrIncrementExisting( std::map<ItemType, std::uint64_t>& _map, const ItemType& _item, const std::uint64_t _count = 1 )
{
	auto insertResult = _map.insert( { _item, _count } );
	if( false == insertResult.second )
		insertResult.first->second += _count;
}

std::string
Result::FinishPartTwo()
{
	std::map<char, std::uint64_t> occurrances{};

	PolymerPairMap polymer;
	{
		auto prevIt = m_template.begin( );
		++occurrances[ *prevIt ];
		auto currentIt = ++prevIt;
		while( currentIt != m_template.end( ) )
		{
			++occurrances[ *currentIt ];
			PushNewPairOrIncrementExisting( polymer, { *prevIt, *currentIt } );
			prevIt = currentIt++;
		}
	}

	for( size_t iterations = 0; iterations != 40; ++iterations )
	{
		PolymerPairMap newPolymer;
		for( auto it = polymer.begin( ); it != polymer.end( ); ++it )
		{
			const auto& pair{ it->first };
			const std::uint64_t& count{ it->second };

			const auto& itCharResult{ m_pairInsertionRules.find( pair ) };
			if( itCharResult != m_pairInsertionRules.end( ) )
			{
				const char charToInsert{ itCharResult->second };

				PushNewPairOrIncrementExisting( newPolymer, { pair[ 0 ], charToInsert }, count );
				PushNewPairOrIncrementExisting( newPolymer, { charToInsert, pair[ 1 ] }, count );
				occurrances[ charToInsert ] += count;
			}
			else
			{
				PushNewPairOrIncrementExisting( newPolymer, pair, count );
			}
		}
		polymer.swap( newPolymer );
	}

	const auto minmax = std::minmax_element(
		std::begin( occurrances ),
		std::end( occurrances ),
		[ ]( const auto& _lhs, const auto& _rhs ) -> bool
	{
		return _lhs.second < _rhs.second;
	} );

	return std::to_string( minmax.second->second - minmax.first->second );
}