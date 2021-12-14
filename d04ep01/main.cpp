import giant_squid;

#include <iostream>

int main( )
{
    giant_squid::Result result;

    return result.Execute( 4512u, 41503u ) == AoC::ResultType::FAILED;
}
