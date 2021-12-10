module;

#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <algorithm>

export module giant_squid:data;

export import AoC;
import :data.board;

export namespace giant_squid
{
    struct Data : public AoC::Data
    {
        Board m_board;

        virtual void Process( const std::string& line ) override;
        virtual void Reset( ) override;
    };
}

void
giant_squid::Data::Process( const std::string& line )
{
    if( line.empty( ) )
        return;

    std::stringstream numbers( line );

    int processed = 0;
    unsigned int value;
    while( numbers >> value )
    {
        m_board.Push( value );
    }
}

void
giant_squid::Data::Reset( )
{
    m_board.Reset( );
}
