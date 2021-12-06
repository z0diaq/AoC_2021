#include <cstdio>
#include <algorithm>//std::swap

import data;

int main( )
{
    int sums[ 4 ] = { 0 },
        count[ 4 ] = { 0 };
    int current{ 0 }, increases{ 0 };

    Data d;

    if( !d )
    {
        return 0;
    }

    while( d.Next( current ) )
    {
        int fills = count[ 0 ] + 1;
        for( int pos = 0; pos < 4 && fills; ++pos, --fills )
        {
            if( count[ pos ] < 3 )
            {
                sums[ pos ] += current;
                ++count[ pos ];
            }
        }

        if( count[ 1 ] == 3 )
        {
            if( sums[ 1 ] > sums[ 0 ] )
                ++increases;
            //move all elements left one place
            for( int pos = 0; pos < 3; ++pos )
            {
                std::swap( sums[ pos ], sums[ pos + 1 ] );
                std::swap( count[ pos ], count[ pos + 1 ] );
            }
            sums[ 3 ] = count[ 3 ] = 0;
        }
    }

    fprintf( stdout, "result = %d\n", increases );

    return 0;
}
