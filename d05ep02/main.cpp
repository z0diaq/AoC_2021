import hydrothermal_venture;

#include <iostream>

int main( )
{
    hydrothermal_venture::Result result;

    return result.Execute( 12u, 20012u ) == AoC::ResultType::FAILED;
}
