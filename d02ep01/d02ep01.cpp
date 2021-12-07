#include <cstdio>
#include <algorithm>//std::swap

import input;
import result;

int main( )
{
    Result result;

    Input input;
    Data data;

    if( !input )
    {
        return 0;
    }

    while( input.Next( data ) )
    {
        result.Process( data );
    }

    result.Finish( );

    return 0;
}
