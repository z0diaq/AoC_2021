module;

#include <iostream>
#include <deque>
#include <vector>
#include <numeric> // std::iota
#include <algorithm> // std::for_each

export module life_support_data;

export import :data;

enum class SearchMode
{
	MostCommon,
	LeastCommon
};

export namespace life_support_data
{
	enum class Rate
	{
		Gamma,
		Epsilon
	};


	class Result : public AoC::Result
	{

	public:
		Result( );

		virtual void Init( ) override;
		virtual void Process( const AoC::Data* data ) override;
		virtual int Finish( ) const override;
		virtual void Teardown( ) override;

	private:

		Item FindRating( SearchMode mode ) const;

		Item FindOxygenGeneratorRating( ) const;
		Item FindCO2ScrubberRating( ) const;

		unsigned int ToNumber( const Item& bits ) const;

		size_t m_usedBits;
		std::deque<Item> m_testData;
	};
}

life_support_data::Result::Result( )
{
}

void
life_support_data::Result::Init( )
{
	m_data = new life_support_data::Data( );
	m_testData.clear( );
	m_usedBits = 0;
}

void
life_support_data::Result::Teardown( )
{
	delete m_data;
	m_data = nullptr;
}

void
life_support_data::Result::Process( const AoC::Data* data )
{
	const life_support_data::Data* ourData = static_cast< const life_support_data::Data* >( data );
	m_usedBits = ourData->m_usedBits;
	m_testData.push_back( ourData->m_bits );
}

life_support_data::Item
life_support_data::Result::FindRating( SearchMode mode ) const
{
	typedef std::vector<unsigned int> Matching_T;
	//rely on bookkeeping instead modify source data or work on a copy
	Matching_T matchingItems( m_testData.size( ) );
	std::iota( matchingItems.begin( ), matchingItems.end( ), 0 );

	auto mostCommonBit = [ &matchingItems, this ]( size_t bitPos, auto end ) -> bool
	{
		size_t ones{ 0 };
		std::for_each(
			matchingItems.begin( ),
			end,
			[ this, &ones, bitPos ]( unsigned int index ) -> void
			{
				if( m_testData[ index ][ bitPos ] )
					++ones;
			} );
		// multiply rather than devide to avoid integers rounding i.e. 7 / 2 = 3
		if( ones * 2 >= ( static_cast<size_t>( std::distance( matchingItems.begin( ), end ) ) ) )
			return true;
		return false;
	};

	auto end = matchingItems.end( );
	for( size_t bitNo = 0; bitNo != m_usedBits; ++bitNo )
	{
		auto bitToKeep = mostCommonBit( bitNo, end );

		//negate for least common mode
		if( mode == SearchMode::LeastCommon )
			bitToKeep = !bitToKeep;

		end = std::remove_if(
			matchingItems.begin( ),
			end,
			[ this, bitToKeep, bitNo ]( unsigned int index ) -> bool
			{
				return m_testData[ index ][ bitNo ] != bitToKeep;
			}
		);

		if( std::distance( matchingItems.begin( ), end ) == 1 )
			return m_testData[ matchingItems.front( ) ];
	}

	return m_testData[ matchingItems.front( ) ];
}

life_support_data::Item
life_support_data::Result::FindOxygenGeneratorRating( ) const
{
	return FindRating( SearchMode::MostCommon );
}

life_support_data::Item
life_support_data::Result::FindCO2ScrubberRating( ) const
{
	return FindRating( SearchMode::LeastCommon );
}

unsigned int
life_support_data::Result::ToNumber( const Item& bits ) const
{
	unsigned int result{ 0 };
	unsigned int powerOfTwo{ 1 };

	for( size_t pos = m_usedBits; pos > 0; --pos )
	{
		result += static_cast< unsigned int >( bits.test( pos - 1 ) ) * powerOfTwo;
		powerOfTwo <<= 1;// eq '2 *'
	}

	return result;
}

int
life_support_data::Result::Finish( ) const
{
	Item
		oxygenGeneratorRating = FindOxygenGeneratorRating( ),
		co2ScrubberRating = FindCO2ScrubberRating( );

	std::cout
		<< "final values - "
		"oxygenGeneratorRating: [ " << oxygenGeneratorRating.to_string( ).substr( oxygenGeneratorRating.size( ) - m_usedBits ) << " ], "
		"co2ScrubberRating: [ " << co2ScrubberRating.to_string( ).substr( co2ScrubberRating.size( ) - m_usedBits ) << " ]"
		<< std::endl;

	const unsigned int computedValue = ToNumber( oxygenGeneratorRating ) * ToNumber( co2ScrubberRating );

	std::cout
		<< "result = "
		<< computedValue
		<< std::endl;

	return computedValue;
}
