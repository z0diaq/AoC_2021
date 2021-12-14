import hydrothermal_venture;

#include <iostream>

int main( )
{
    hydrothermal_venture::Result result;

    return result.Execute( 5u, 6548u ) == AoC::ResultType::FAILED;
}
