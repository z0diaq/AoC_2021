#include <cstdio>

int main( )
{
    int previous{ 0 },
        current{ 0 },
        increases{ 0 };
    bool isFirst{ true };

    while( EOF != fscanf_s( stdin, "%d", &current ) )
    {
        if( isFirst )
        {
            isFirst = false;//ignore first element
        }
        else if( current > previous )
            ++increases;
        previous = current;
    }

    printf( "result: %d\n", increases );

    return 0;
}
