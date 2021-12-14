import hydrothermal_venture;

#include <iostream>

int main( )
{
    hydrothermal_venture::Result result;

    return result.Execute( 12u, 19663u ) == AoC::ResultType::FAILED;
}
