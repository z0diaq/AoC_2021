import giant_squid;

#include <iostream>

int main( )
{
    giant_squid::Result result;

    return result.Execute( 4512, 41503 ) == AoC::ResultType::FAILED;
}
