module;

#include <iostream>
#include <fstream>
#include <string>

#include <string.h> //strerror_s

export module data;

static const std::string FILENAME( "input.txt" );
//see: https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strerror-s-strerror-s-wcserror-s-wcserror-s
constexpr size_t BUFF_SIZE = 94;

export struct Data
{
    std::ifstream m_file;

    Data( );
    bool Next( int& value );

    operator bool( );
};

Data::Data( )
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
Data::Next( int& value )
{
    if( false == m_file.is_open( ) || m_file.eof( ) )
        return false;

    m_file >> value;

    return ( false == m_file.fail( ) );
}

Data::operator bool( )
{
    return m_file.is_open( );
};
