import life_support_data;

#include <iostream>

int main( )
{
    life_support_data::Result result;

    return result.Execute( 230u, 4'672'151u ) == AoC::ResultType::FAILED;
}
