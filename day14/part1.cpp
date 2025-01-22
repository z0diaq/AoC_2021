import extended_polymerization;

#include <string>
#include <algorithm>
#include <iterator>
#include <numeric>

//containers
#include <vector>
#include <array>

using namespace extended_polymerization;

void
Result::ProcessOne( const std::string& data )
{
	if( m_template.empty( ) )
		std::copy( data.begin( ), data.end( ), std::back_inserter( m_template ) );
	else if( data.length( ) == 7 )
		m_pairInsertionRules[ { data[ 0 ], data[ 1 ] } ] = data[ 6 ];
}

CharList ApplyRules( CharList _polymer, const PairInsertionRulesMap& _rules );

std::string
Result::FinishPartOne( )
{
	auto polymer = m_template;

	for( int iterations = 0; iterations < 10; ++iterations )
		polymer = ApplyRules( polymer, m_pairInsertionRules );

	std::array<size_t, 'Z' - 'A'> occurrences{};

	auto countOccurance = [&occurrences]( const char _value ) { ++occurrences[ _value - 'A' ]; };

	std::for_each( polymer.begin( ), polymer.end( ), countOccurance );

	auto result = std::accumulate(
		occurrences.begin( ),
		occurrences.end( ),
		std::pair<size_t, size_t>{ static_cast< size_t >( -1 ),  0 },
		[ ]( const std::pair<size_t, size_t>& _minAndMax, size_t _value ) {
			if( _value == 0 )
				return _minAndMax;
			return std::pair<size_t, size_t>{std::min( _minAndMax.first, _value ), std::max( _minAndMax.second, _value )};
		} );

	return std::to_string( result.second - result.first );
}

CharList ApplyRules( CharList _polymer, const PairInsertionRulesMap& _rules )
{
	CharList result = _polymer;

	auto itCurrent = result.begin( );
	auto itPrevious = itCurrent++;

	while( itCurrent != result.end( ) )
	{
		auto itRuleFindResult = _rules.find( { *itPrevious, *itCurrent } );
		if(itRuleFindResult != _rules.end())
			result.insert( itCurrent, itRuleFindResult->second );
		itPrevious = itCurrent++;
	}

	return result;
}