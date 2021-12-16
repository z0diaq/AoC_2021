module;

#include <string>
#include <array>
#include <string>
#include <algorithm>
#include <stdexcept>

#include <boost/algorithm/string.hpp>

export module sesese:data;

export import AoC;

export namespace sesese
{
    struct Data : public AoC::Data
    {
        virtual void Process( const std::string& line ) override;
        virtual void Reset( ) override;

        std::array<std::string, 10> m_digits;
		std::array<std::string, 4> m_testData;
    };
}

using namespace sesese;

void
Data::Process( const std::string& line )
{
	std::deque<std::string> tokens;

	boost::split(
		tokens,
		line,
		boost::is_any_of( ", |" ),
		boost::token_compress_on );

	if( tokens.size( ) != 14 )
		throw std::logic_error( "Expecting exactly 14 items!" );

	std::copy_n( tokens.begin( ), 10, m_digits.begin( ) );
	std::copy_n( tokens.begin( ) + 10, 4, m_testData.begin( ) );
}

void
Data::Reset( )
{
}
