import dive;

#include <iostream>

int main( )
{
    dive::Result result;

    return result.Execute( 150, 1727835 ) == AoC::ResultType::FAILED;
}
