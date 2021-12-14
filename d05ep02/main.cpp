import hydrothermal_venture;

#include <iostream>

int main( )
{
    hydrothermal_venture::Result result;

    return result.Execute( 12, 19663 ) == AoC::ResultType::FAILED;
}
