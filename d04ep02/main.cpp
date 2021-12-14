import giant_squid;

#include <iostream>

int main( )
{
    giant_squid::Result result;

    return result.Execute( 1924, 3178 ) == AoC::ResultType::FAILED;
}
