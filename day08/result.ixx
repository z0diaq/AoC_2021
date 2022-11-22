module;

#include <iostream>
#include <deque>
#include <array>
#include <algorithm>
#include <numeric>
#include <string>

export module sesese;

export import :data;

//sesese => SEvent SEgments SEarch
export namespace sesese
{

	class Result : public AoC::Result
	{

	public:
		Result( );

		virtual void Init( ) override;
		virtual bool ProcessOne( const AoC::DataPtr& data ) override;
		virtual bool ProcessTwo( const AoC::DataPtr& data ) override;
		virtual uint64_t Finish( ) const override;
		virtual void Teardown( ) override;

	private:

		//stage 1
		uint64_t m_accumulated;

		//stage 2
		std::string m_mappedDigits[ 10 ];

		void FindMapping( std::array<std::string, 10> digits );
		int DecodeDigit( std::string view );
		const std::string& Normalize( std::string& str ) const;
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
	m_accumulated = 0;
	m_haveDedicatedProcessing = true;
}

void
Result::Teardown( )
{
	m_data.reset( );
}

bool
Result::ProcessOne( const AoC::DataPtr& data )
{
	const Data* ourData = dynamic_cast< const Data* >( data.get( ) );

	m_accumulated += static_cast<uint64_t>( std::count_if(
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

	return true;
}

bool
Result::ProcessTwo( const AoC::DataPtr& data )
{
	const Data* ourData = dynamic_cast< const Data* >( data.get( ) );

	FindMapping( ourData->m_digits );

	int result = 0;
	for( const auto& digit : ourData->m_testData )
	{
		result = 10 * result + DecodeDigit( digit );
	}

	m_accumulated += result;

	return true;
}

void
Result::FindMapping( std::array<std::string, 10> digits )
{
	//sort - shortest front
	std::sort( digits.begin( ), digits.end( ), [ ]( const std::string& lhs, const std::string& rhs )
	{
		return lhs.length( ) < rhs.length( );
	} );

	//normalize each word
	for( auto& digit : digits )
		Normalize( digit );

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
		size_t expectedSize,
		bool enforceLength = true ) -> std::string
	{
		std::string result;
		for( auto c : left )
			if( right.find( c, 0 ) == std::string::npos )
				result.push_back( c );
		if( result.size( ) != expectedSize )
		{
			if( enforceLength )
				throw std::logic_error( "Difference not expected" );
			return "";
		}

		return result;
	};

	auto one = digits[ 0 ],
		four = digits[ 2 ],
		seven = digits[ 1 ],
		eight = digits[ 9 ];
	auto a = findSegmentsDifference( seven, one, 1 );
	auto bd = findSegmentsDifference( four, one, 2 );
	auto eg = findSegmentsDifference( eight, one + a + bd, 2 );

	//g is when from group 069 we find single diff against 4 + a
	std::string g;
	for( int no = 6; no < 9 && g.empty( ); ++no )
	{
		g = findSegmentsDifference(
			digits[ no ],
			four + a,
			1,
			false );
	}

	//d is when from group 235 we find single diff against 1 + a + g
	std::string d;
	for( int no = 3; no < 6 && d.empty( ); ++no )
	{
		d = findSegmentsDifference(
			digits[ no ],
			one + a + g,
			1,
			false );
	}

	std::string b = findSegmentsDifference( four, one + d, 1 );
	std::string e = findSegmentsDifference( eg, g, 1 );


	//c is when from group 235 we find single diff against a + d + eg
	std::string c;
	for( int no = 3; no < 6 && c.empty( ); ++no )
	{
		c = findSegmentsDifference(
			digits[ no ],
			a + d + eg,
			1,
			false );
	}
	std::string f = findSegmentsDifference( one, c, 1 );

	m_mappedDigits[ 0 ] = a + b + c + e + f + g;
	m_mappedDigits[ 1 ] = one;
	m_mappedDigits[ 2 ] = a + c + d + e + g;
	m_mappedDigits[ 3 ] = a + c + d + f + g;
	m_mappedDigits[ 4 ] = four;
	m_mappedDigits[ 5 ] = a + b + d + f + g;
	m_mappedDigits[ 6 ] = m_mappedDigits[ 5 ] + e;
	m_mappedDigits[ 7 ] = seven;
	m_mappedDigits[ 8 ] = eight;
	m_mappedDigits[ 9 ] = findSegmentsDifference( eight, e, 6 );

	for( auto& digit : m_mappedDigits )
		Normalize( digit );

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

int
Result::DecodeDigit( std::string digit )
{
	Normalize( digit );

	for( int pos = 0; pos != 10; ++pos )
		if( m_mappedDigits[ pos ] == digit )
			return pos;

	throw std::logic_error( "Could not find mapping" );
}

uint64_t
Result::Finish( ) const
{
	std::cout
		<< "result = "
		<< m_accumulated
		<< std::endl;

	return m_accumulated;
}

const std::string&
Result::Normalize( std::string& str ) const
{
	std::sort( str.begin( ), str.end( ) );

	return str;
}