import giant_squid;

#include <iostream>

int main( )
{
    giant_squid::Result result;

    return result.Execute( 1924u, 3178u ) == AoC::ResultType::FAILED;
}
