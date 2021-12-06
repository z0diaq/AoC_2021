#include <cstdio>

int main( )
{
    int previous{ 0 }, current{ 0 };
    bool isFirst{ true };
    int increases{ 0 };

    while( false == feof( stdin ) )
    {
        fscanf_s( stdin, "%d", &current );
        if( isFirst )
        {
            isFirst = false;//ignore first element
        }
        else if( current > previous )
            ++increases;
        previous = current;
    }

    return increases;
}
