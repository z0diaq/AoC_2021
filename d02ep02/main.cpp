import dive;

#include <iostream>

int main( )
{
    dive::Result result;

    return result.Execute( 900u, 1544000595u ) == AoC::ResultType::FAILED;
}
