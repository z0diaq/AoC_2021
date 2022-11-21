import giant_squid;

#include <iostream>

int main( )
{
    giant_squid::Result result;

    return result.Execute( 1924u, 17'435u ) == AoC::ResultType::FAILED;
}
