import dive;

#include <iostream>

int main( )
{
    dive::Result result;

    return result.Execute( 900, 1544000595 ) == AoC::ResultType::FAILED;
}
