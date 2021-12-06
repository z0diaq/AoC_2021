module;

#include <cstdio>
//struct FILE;

export module data;

static const errno_t c_noError{ 0 };

export struct Data
{
    FILE* m_fp;

    Data( );
    bool Next( int& value );

    operator bool( );
};

Data::Data( )
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
Data::Next( int& value )
{
    return EOF != fscanf_s( m_fp, "%d", &value );
}

Data::operator bool( )
{
    return m_fp != nullptr;
};
