module;

#include <iostream>
#include <deque>
#include <array>
#include <numeric>

export module lanternfish;

export import :data;

export namespace lanternfish
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
		std::deque<signed char> m_population;

		uint64_t IterateNTimes( unsigned int n ) const;
	};
}

using namespace lanternfish;

Result::Result( )
{
}

void
Result::Init( )
{
	m_data.reset( new lanternfish::Data( ) );
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

	m_population = ourData->m_population;

	return true;
}

uint64_t
Result::Finish( ) const
{
	uint64_t computedValue = IterateNTimes( IsPartTwo( ) ? 256 : 80 );

	std::cout
		<< "result = "
		<< computedValue
		<< std::endl;

	return computedValue;
}

uint64_t
Result::IterateNTimes( unsigned int N ) const
{
	std::array<uint64_t, 9> counts{ 0u };

	for( auto value : m_population )
		++counts[ value ];

	for( ; N > 0; --N )
	{
		auto dead = counts[ 0 ];

		for( size_t age = 1; age <= 8; ++age )
		{
			counts[ age - 1 ] = counts[ age ];
		}

		counts[ 8 ] = dead;
		counts[ 6 ] += dead;
	}

	return std::accumulate( counts.begin( ), counts.end( ), 0ull );
}
