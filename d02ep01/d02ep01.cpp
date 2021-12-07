import input;
import result;

#include <iostream>

int main( )
{
    std::ios::sync_with_stdio( false );

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
