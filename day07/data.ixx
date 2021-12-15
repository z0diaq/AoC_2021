module;

#include <string>
#include <deque>
#include <algorithm>

#include <boost/algorithm/string.hpp>

export module whale:data;

export import AoC;

export namespace whale
{
    struct Data : public AoC::Data
    {
        virtual void Process( const std::string& line ) override;
        virtual void Reset( ) override;

        std::deque<unsigned long> m_positions;
    };
}

using namespace whale;

void
Data::Process( const std::string& line )
{
	std::deque<std::string> tokens;

	boost::split(
		tokens,
		line,
		boost::is_any_of( ", " ),
		boost::token_compress_on );

	m_positions.resize( tokens.size( ) );
	std::transform(
		tokens.begin( ),
		tokens.end( ),
		m_positions.begin( ),
		[ ]( const std::string& token ) -> unsigned long
		{
			return std::strtoul(
				token.c_str( ),
				nullptr/*ignore*/,
				0/*auto detect*/ );
		} );
}

void
Data::Reset( )
{
	m_positions.clear( );
}
