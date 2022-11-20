module;

#include <iostream>
#include <deque>
#include <array>
#include <algorithm>
#include <numeric>

export module sesese;

export import :data;

export namespace sesese
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
		unsigned int m_foundCount;
	};
}

using namespace sesese;

Result::Result( )
{
}

void
Result::Init( )
{
	m_data.reset( new sesese::Data( ) );
	m_foundCount = 0;
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

	if( IsPartOne( ) )
	{
		m_foundCount += static_cast<unsigned int>( std::count_if(
			ourData->m_testData.begin( ),
			ourData->m_testData.end( ),
			[ ]( const std::string& segments )
		{
			switch( segments.length( ) )
			{
			case 2://1
			case 3://7
			case 4://4
			case 7://8
				return true;
			default:
				return false;
			}
		} ) );
	}
	else
	{
		auto digits = ourData->m_digits;
		//need to sort data first so std::set_union can be used
		for( auto& digit : digits )
			std::sort( digit.begin( ), digit.end( ) );

		auto findFirstDigitWithNSegments = [ &digits ]( size_t length ) -> std::string
		{
			return *std::find_if( digits.begin( ), digits.end( ), [ length ]( const std::string& digit ) -> bool
				{
					return digit.length( ) == length;
				} );
		};

		auto segmentSum = [ ](
			const std::string& left,
			const std::string& right ) -> std::string
		{
			std::string result;
			std::set_union(
				left.begin( ), left.end( ),
				right.begin( ), right.end( ),
				std::back_inserter( result ) );
			return result;
		};

		auto findSegmentsDifference = [ ](
			const std::string& left,
			const std::string& right,
			size_t expectedSize ) -> std::string
		{
			std::string result;
			for( auto c : left )
				if( right.find( c, 0 ) == std::string::npos )
					result.push_back( c );
			if( result.size( ) != expectedSize )
				throw std::logic_error( "Does not match expected size!" );
			return result;
		};

		auto one = findFirstDigitWithNSegments( 2 ),
			four = findFirstDigitWithNSegments( 4 ),
			seven = findFirstDigitWithNSegments( 3 ),
			eight = findFirstDigitWithNSegments( 7 );
		char topSegment = findSegmentsDifference( seven, one, 1 ).front( );
		//char topRightSegment = findSegmentsDifference(  )
		//auto leftAndBottom = findSegmentsDifference( );
		std::string a;
		/*
		0 -> 6 seg
		1 -> 2 seg
		2 -> 5 seg
		3 -> 5 seg
		4 -> 4 seg
		5 -> 5 seg
		6 -> 6 seg
		7 -> 3 seg
		8 -> 7 seg
		9 -> 6 seg

		2 seg -> 1
		3 seg -> 7
		4 seg -> 4
		5 seg -> 2,3,5
		6 seg -> 0,6,9
		7 seg -> 8
		*/
	}

	return true;
}

uint64_t
Result::Finish( ) const
{
	uint64_t computedValue = m_foundCount;

	std::cout
		<< "result = "
		<< computedValue
		<< std::endl;

	return computedValue;
}
