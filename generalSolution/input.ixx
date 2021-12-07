module;

#include <iostream>
#include <fstream>
#include <string>

#include <string.h> //strerror_s

export module AoC:input;

import :data;

static const std::string FILENAME( "input.txt" );
//see: https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strerror-s-strerror-s-wcserror-s-wcserror-s
constexpr size_t BUFF_SIZE = 94;

export namespace AoC
{
    class Input
    {
    public:
        Input( );

        bool Next( Data* data );
        operator bool( );

    private:
        std::ifstream m_file;

    };
}

AoC::Input::Input( )
{
    m_file.open( FILENAME );
    if( false == m_file.is_open( ) )
    {
        char errmsg[ BUFF_SIZE ];
        strerror_s( errmsg, BUFF_SIZE, errno );
        std::cerr
            << "Could not open " << FILENAME
            << ", error: " << errmsg << std::endl;
    }
}

bool
AoC::Input::Next( Data* data )
{
    if( m_file.fail( ) )
        return false;

    static std::string line;

    std::getline( m_file, line );

    data->Process( line );

    return ( false == m_file.fail( ) );
}

AoC::Input::operator bool( )
{
    return m_file.is_open( );
};