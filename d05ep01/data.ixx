module;

#include <string>
#include <regex>
#include <iostream>
#include <utility> //pair

export module hydrothermal_venture:data;

export import AoC;

export namespace hydrothermal_venture
{
    struct Point
    {
        unsigned int m_x;
        unsigned int m_y;

        void Reset( );
    };

    struct Line
    {
        Point m_start;
        Point m_end;

        void Reset( );
    };

    struct Data : public AoC::Data
    {
        Line m_line;

        virtual void Process( const std::string& line ) override;
        virtual void Reset( ) override;
    };
}

void
hydrothermal_venture::Data::Process( const std::string& line )
{
    if( line.empty( ) )
        return;

    std::regex lineRegex( "(\\d+),(\\d+) -> (\\d+),(\\d+)" );
    std::smatch match;

    if( false == std::regex_search( line, match, lineRegex ) )
    {
        std::cerr << "ERROR: invalid line [" << line << "] passed for processing!" << std::endl;
    }

    m_line.m_start.m_x  = strtoul( match[ 1 ].str( ).c_str( ), nullptr, 10 );
    m_line.m_start.m_y  = strtoul( match[ 2 ].str( ).c_str( ), nullptr, 10 );
    m_line.m_end.m_x    = strtoul( match[ 3 ].str( ).c_str( ), nullptr, 10 );
    m_line.m_end.m_y    = strtoul( match[ 4 ].str( ).c_str( ), nullptr, 10 );
}

void
hydrothermal_venture::Point::Reset( )
{
    m_x = m_y = std::numeric_limits<unsigned int>::max( );
}

void
hydrothermal_venture::Line::Reset( )
{
    m_start.Reset( );
    m_end.Reset( );
}

void
hydrothermal_venture::Data::Reset( )
{
    m_line.Reset( );
}
