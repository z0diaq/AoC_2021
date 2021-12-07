//doesn't work as of 07.12.2021
//import std.core;

#include <iostream>
#include <fstream>
#include <string>

#include <string.h> //strerror

static const std::string FILENAME( "input.txt" );

int main( )
{
    std::ios::sync_with_stdio( false );

    int previous{ 0 },
        current{ 0 },
        increases{ 0 };
    bool isFirst{ true };

    std::ifstream file( FILENAME );

    if( false == file.is_open( ) )
    {
        perror( "Could not open input file" );
        
        return 1;
    }

    while( file >> current )
    {
        if( isFirst )
        {
            isFirst = false;//ignore first element
        }
        else if( current > previous )
            ++increases;
        previous = current;
    }

    std::cout << "result: " << increases << std::endl;

    return 0;
}
