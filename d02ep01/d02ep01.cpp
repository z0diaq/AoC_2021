import dive;

#include <iostream>

int main( )
{
    dive::Result result;

    return result.Execute( 150u, 2215080u ) == AoC::ResultType::FAILED;
}
