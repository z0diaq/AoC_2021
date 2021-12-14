module;

#include <string>
#include <deque>
#include <algorithm>

#include <boost/algorithm/string.hpp>

export module lanternfish:data;

export import AoC;

export namespace lanternfish
{
    struct Data : public AoC::Data
    {
        virtual void Process( const std::string& line ) override;
        virtual void Reset( ) override;

        std::deque<signed char> m_population;
    };
}

using namespace lanternfish;

void
Data::Process( const std::string& line )
{
	std::deque<std::string> tokens;

	boost::split(
		tokens,
		line,
		boost::is_any_of( ", " ),
		boost::token_compress_on );

	m_population.resize( tokens.size( ) );
	std::transform(
		tokens.begin( ),
		tokens.end( ),
		m_population.begin( ),
		[ ]( const std::string& token ) -> unsigned int
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

}
