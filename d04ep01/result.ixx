module;

#include <iostream>
#include <deque>
#include <algorithm>
#include <sstream>

#include <boost/algorithm/string.hpp>

export module giant_squid;

export import :data;

export namespace giant_squid
{

	class Result : public AoC::Result
	{

	public:
		Result( );

		virtual void Init( ) override;
		virtual bool Process( const AoC::DataPtr& data ) override;
		virtual int Finish( ) const override;
		virtual void Teardown( ) override;

	private:

		void ReadDrawnNumbers( );
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

	std::deque<std::string> tokens;

	boost::split(
		tokens,
		numbersLine,
		boost::is_any_of( ", " ),
		boost::token_compress_on );

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
giant_squid::Result::Process( const AoC::DataPtr& data )
{
	const giant_squid::Data* ourData = static_cast< const giant_squid::Data* >( data.get( ) );
	if( false == ourData->m_board.IsFilled( ) )
		return false;

	m_boards.push_back( ourData->m_board );

	return true;
}

int
giant_squid::Result::Finish( ) const
{
	unsigned int computedValue = 0;

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
