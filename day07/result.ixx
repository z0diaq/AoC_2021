module;

#include <iostream>
#include <deque>
#include <array>
#include <algorithm>
#include <numeric>

export module whale;

export import :data;

export namespace whale
{

	class Result : public AoC::Result
	{

	public:
		Result( );

		virtual void Init( ) override;
		virtual bool ProcessGeneral( const AoC::DataPtr& data ) override;
		virtual uint64_t Finish( ) const override;
		virtual void Teardown( ) override;

	private:
		std::deque<unsigned long> m_positions;

		unsigned long Distance( unsigned long position ) const;
	};
}

using namespace whale;

Result::Result( )
{
}

void
Result::Init( )
{
	m_data.reset( new whale::Data( ) );
	m_haveDedicatedProcessing = false;
}

void
Result::Teardown( )
{
	m_data.reset( );
}

bool
Result::ProcessGeneral( const AoC::DataPtr& data )
{
	const Data* ourData = dynamic_cast< const Data* >( data.get( ) );

	m_positions = ourData->m_positions;

	std::sort( m_positions.begin( ), m_positions.end( ) );

	return true;
}

uint64_t
Result::Finish( ) const
{
	auto minValue = *std::min_element( m_positions.begin( ), m_positions.end( ) );
	auto maxValue = *std::max_element( m_positions.begin( ), m_positions.end( ) );

	auto distanceToMin = Distance( minValue );
	auto distanceToMax = Distance( maxValue );
	while( minValue != maxValue )
	{
		if( distanceToMin < distanceToMax )
		{
			maxValue = std::min( ( minValue + maxValue ) / 2, maxValue - 1 );
			distanceToMax = Distance( maxValue );
		}
		else
		{

			minValue = std::max( ( minValue + maxValue ) / 2, minValue + 1 );
			distanceToMin = Distance( minValue );
		}
	}

	uint64_t computedValue = std::min( distanceToMin, distanceToMax );

	std::cout
		<< "result = "
		<< computedValue
		<< std::endl;

	return computedValue;
}

static unsigned long
Lookup( unsigned long distance );


unsigned long 
Result::Distance( unsigned long position ) const
{
	unsigned long distance = 0u;

	for( auto value : m_positions )
	{
		auto currentDistance = std::max( value, position ) - std::min( value, position );
		distance += IsPartTwo( ) ? Lookup( currentDistance ) : currentDistance;
	}

	return distance;
}

unsigned long
Lookup( unsigned long distance )
{
	static std::deque<unsigned long> lookup = { 0 };
	while( lookup.size( ) <= distance )
	{
		lookup.push_back( lookup.back( ) + static_cast< unsigned long>( lookup.size( ) ) );
	}

	return lookup[ distance ];
}