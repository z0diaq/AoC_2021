import hydrothermal_venture;

#include <iostream>

int main( )
{
    hydrothermal_venture::Result result;

    return result.Execute( 5, 6548 ) == AoC::ResultType::FAILED;
}
