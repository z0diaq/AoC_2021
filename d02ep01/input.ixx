module;

#include <iostream>
#include <fstream>
#include <string>

#include <string.h> //strerror_s

export module input;

export import data;

static const std::string FILENAME( "input.txt" );
//see: https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strerror-s-strerror-s-wcserror-s-wcserror-s
constexpr size_t BUFF_SIZE = 94;

export class Input
{
public:
    Input( );

    bool Next( Data& data );
    operator bool( );

private:
    std::ifstream m_file;

};

Input::Input( )
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
Input::Next( Data& data )
{
    data.m_x = data.m_y = 0;

    std::string direction;
    int value{ 0 };

    m_file >> direction >> value;

    if( "forward" == direction )
    {
        data.m_x = value;
    }
    else if( "up" == direction )
    {
        data.m_y = -value;
    }
    else
    {
        data.m_y = value;
    }

    return ( false == m_file.fail( ) );
}

Input::operator bool( )
{
    return m_file.is_open( );
};