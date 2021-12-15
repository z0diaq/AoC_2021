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
		virtual bool Process( const AoC::DataPtr& data ) override;
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
}

void
Result::Teardown( )
{
	m_data.reset( );
}

bool
Result::Process( const AoC::DataPtr& data )
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
			maxValue = ( ( minValue + maxValue ) / 2 );
			distanceToMax = Distance( maxValue );
		}
		else
		{

			minValue = ( ( minValue + maxValue ) / 2 );
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

unsigned long 
Result::Distance( unsigned long position ) const
{
	unsigned long distance = 0u;

	for( auto value : m_positions )
	{
		distance += std::max( value, position ) - std::min( value, position );
	}

	return distance;
}
