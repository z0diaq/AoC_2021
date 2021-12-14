import dive;

#include <iostream>

int main( )
{
    dive::Result result;

    return result.Execute( 150u, 1727835u ) == AoC::ResultType::FAILED;
}
