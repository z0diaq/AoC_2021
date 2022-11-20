module;

#include <iostream>
#include <deque>
#include <algorithm>
#include <sstream>

#if 0
// can't use boost now:
//1>C:\<projects>\AoC_2021\d04ep01\result.ixx(129,1): fatal  error C1001: Internal compiler error.
//1 > ( compiler file 'D:\a\_work\1\s\src\vctools\Compiler\CxxFE\sl\p1\c\module\writer.cpp', line 1277 )..
#include <boost/algorithm/string.hpp>
#endif

export module giant_squid;

export import :data;

export namespace giant_squid
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

		void ReadDrawnNumbers( );
		std::deque<std::string> GetTokens( const std::string numbersLine ) const;

		std::deque<unsigned int> m_drawnNumbers;
		mutable std::deque<Board> m_boards;
	};
}

giant_squid::Result::Result( )
{
}

void
giant_squid::Result::Init( )
{
	m_data.reset( new giant_squid::Data( ) );

	this->ReadDrawnNumbers( );
}

void
giant_squid::Result::ReadDrawnNumbers( )
{
	m_drawnNumbers.clear( );
	std::string numbersLine;
	if( false == m_input.Next( numbersLine ) )
	{
		std::cerr << "ERROR: errno = " << errno << std::endl;
		throw std::exception( "Could not read drawn numbers line!" );
	}

	std::deque<std::string> tokens = GetTokens( numbersLine );

#if 0
	boost::split(
		tokens,
		numbersLine,
		boost::is_any_of( ", " ),
		boost::token_compress_on );
#endif

	m_drawnNumbers.resize( tokens.size( ) );
	std::transform(
		tokens.begin( ),
		tokens.end( ),
		m_drawnNumbers.begin( ),
		[ ]( const std::string& token ) -> unsigned int
	{
		return std::strtoul(
			token.c_str( ),
			nullptr/*ignore*/,
			0/*auto detect*/ );
	} );
}

void
giant_squid::Result::Teardown( )
{
	m_data.reset( );
	m_drawnNumbers.clear( );
	m_boards.clear( );
}

bool
giant_squid::Result::ProcessGeneral( const AoC::DataPtr& data )
{
	const Data* ourData = dynamic_cast< const Data* >( data.get( ) );
	if( false == ourData->m_board.IsFilled( ) )
		return false;

	m_boards.push_back( ourData->m_board );

	return true;
}

uint64_t
giant_squid::Result::Finish( ) const
{
	uint64_t computedValue = 0;

	for( unsigned int number : m_drawnNumbers )
	{
		for( auto& board : m_boards )
		{
			board.MarkNumber( number );
			if( board.Bingo( computedValue ) )
				goto have_result;
		}
	}

	throw std::exception( "Failed to find result!" );

have_result:

	std::cout
		<< "result = "
		<< computedValue
		<< std::endl;

	return computedValue;
}

std::deque<std::string> 
giant_squid::Result::GetTokens( const std::string numbersLine ) const
{
	std::deque<std::string> result;
	std::string token;

	for( const char c : numbersLine )
	{
		if( false == std::isdigit( c ) )
		{
			if( false == token.empty( ) )
			{
				result.push_back( std::move( token ) );
			}
		}
		else
		{
			token.push_back( c );
		}
	}

	if( false == token.empty( ) )
	{
		result.push_back( std::move( token ) );
	}

	return result;
}
