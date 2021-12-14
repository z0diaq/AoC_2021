module;

#include <iostream>
#include <vector>
#include <algorithm>

export module binary_diagnostic;

export import :data;

export namespace binary_diagnostic
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
		virtual bool Process( const AoC::DataPtr& data ) override;
		virtual uint64_t Finish( ) const override;
		virtual void Teardown( ) override;

	private:

		std::string BuildRate( Rate rate ) const;
		unsigned int ToNumber( const std::string& bits ) const;

		std::vector<unsigned int> m_ones;
		unsigned int m_processedLines{0};
	};
}

binary_diagnostic::Result::Result( )
{
}

void
binary_diagnostic::Result::Init( )
{
	m_data.reset( new binary_diagnostic::Data( ) );
	m_processedLines = 0;
}

void
binary_diagnostic::Result::Teardown( )
{
	m_data.reset( );
}

bool
binary_diagnostic::Result::Process( const AoC::DataPtr& data )
{
	const binary_diagnostic::Data* ourData = static_cast< const binary_diagnostic::Data* >( data.get( ) );
	//one time init
	if( 0 == m_processedLines )
		m_ones = ourData->m_bits;
	else
	{
		for( size_t bit = 0; bit != m_ones.size( ); ++bit )
		{
			m_ones[ bit ] += ourData->m_bits[ bit ];
		}
	}

	++m_processedLines;

	return true;
}

std::string
binary_diagnostic::Result::BuildRate( Rate rate ) const
{
	const auto size = m_ones.size( );
	std::string result( size, '0' );

	const auto half = ( m_processedLines >> 1 );// eq '/ 2'

	for( int bit = 0; bit != size; ++bit )
		result[ bit ] = '0' + ( rate == Rate::Gamma ? m_ones[ bit ] >= half : m_ones[ bit ] < half );

	return result;
}

unsigned int
binary_diagnostic::Result::ToNumber( const std::string& bits ) const
{
	unsigned int result{ 0 };
	unsigned int powerOfTwo = 1;

	std::for_each( bits.rbegin( ), bits.rend( ), [ &result, &powerOfTwo ]( char c ) -> void
	{
		result += static_cast< unsigned int >( c - '0' ) * powerOfTwo;
		powerOfTwo <<= 1;// eq '2 *'
	} );

	return result;
}

uint64_t
binary_diagnostic::Result::Finish( ) const
{
	std::string
		gammaRate = BuildRate( Rate::Gamma ),
		epsilonRate = BuildRate( Rate::Epsilon );

	std::cout
		<< "final values - "
		"gamma rate:[ " << gammaRate << " ], "
		"epsilon rate: [ " << epsilonRate << " ]"
		<< std::endl;

	const uint64_t computedValue = ToNumber( gammaRate ) * ToNumber( epsilonRate );

	std::cout
		<< "result = "
		<< computedValue
		<< std::endl;

	return computedValue;
}
