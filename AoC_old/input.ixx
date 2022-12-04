module;

#include <iostream>
#include <fstream>
#include <string>

#include <string.h> //strerror_s

export module AoC:input;

import :data;

//see: https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strerror-s-strerror-s-wcserror-s-wcserror-s
constexpr size_t BUFF_SIZE = 94;

export namespace AoC
{
    class Input
    {

    public:
        Input( ) = default;
        
        bool Init( const std::string& filename );

        bool Next( std::string& line );
        bool Next( DataPtr& data );
        operator bool( );

    private:
        std::ifstream m_file;

    };
}

bool
AoC::Input::Init( const std::string& filename )
{
    if( m_file.is_open( ) )
        m_file.close( );
    m_file.clear( );
    m_file.open( filename );
    if( false == m_file.is_open( ) )
    {
        char errmsg[ BUFF_SIZE ];
        strerror_s( errmsg, BUFF_SIZE, errno );
        std::cerr
            << "Could not open " << filename
            << ", error: " << errmsg << std::endl;
        return false;
    }

    return true;
}

bool
AoC::Input::Next( std::string& line )
{
    if( m_file.fail( ) )
        return false;

    std::getline( m_file, line );

    return ( false == m_file.fail( ) );
}

bool
AoC::Input::Next( DataPtr& data )
{
    static std::string line;
    const bool readResult = this->Next( line );

    if( readResult )
        data->Process( line );

    return readResult;
}

AoC::Input::operator bool( )
{
    return m_file.is_open( );
};