import dive;

#include <iostream>

int main( )
{
    dive::Result result;

    return result.Execute( 900u, 1864715580u ) == AoC::ResultType::FAILED;
}
