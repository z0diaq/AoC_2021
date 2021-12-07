module;

#include <cstdio>
#include <string>

export module input;

export import data;

static const errno_t c_noError{0};

export class Input
{
public:
    Input( );

    bool Next( Data& data );
    operator bool( );

private:
    FILE* m_fp;

};

Input::Input( )
{
    //expecting to have input data in current working directory
    //which might be different that where binary is built
    auto result = fopen_s( &m_fp, "input.txt", "r" );
    if( c_noError != result )
    {
        fprintf(
            stderr,
            "Could not open input file! Errno = %u\n",
            result );
    }
}

bool
Input::Next( Data& data )
{
    data.m_x = data.m_y = 0;

    static char direction[ 8 ];
    int value{0};
    if( EOF == fscanf_s(
        m_fp,
        "%s %d",
        direction, static_cast< unsigned int >( _countof( direction ) ),
        &value ) )
    {
        return false;
    }

    if( 0 == strcmp( direction, "forward" ) )
    {
        data.m_x = value;
    }
    else if( 0 == strcmp( direction, "up" ) )
    {
        data.m_y = -value;
    }
    else
    {
        data.m_y = value;
    }

    return true;
}

Input::operator bool( )
{
    return m_fp != nullptr;
};