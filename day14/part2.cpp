import extended_polymerization;

#include <string>
#include <algorithm>
#include <iterator>
#include <map>
#include <array>

using namespace extended_polymerization;

void
Result::ProcessTwo(const std::string& data)
{
	if( m_template.empty( ) )
		std::copy( data.begin( ), data.end( ), std::back_inserter( m_template ) );
	else if( data.length( ) == 7 )
		m_pairInsertionRules[ { data[ 0 ], data[ 1 ] } ] = data[ 6 ];
}

using PolymerPairMap = std::map<CharPair, std::uint64_t>;

void PushNewPairOrIncrementExisting( PolymerPairMap& _map, const CharPair& _item, const std::uint64_t _count = 1 )
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
	for( auto it = m_template.begin( ); std::next( it ) != m_template.end( ); ++it )
	{
		++occurrances[ *it ];
		PushNewPairOrIncrementExisting( polymer, { *it, *std::next( it ) } );
	}
	++occurrances[ m_template.back( ) ];

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
				PushNewPairOrIncrementExisting( newPolymer, pair, count );
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