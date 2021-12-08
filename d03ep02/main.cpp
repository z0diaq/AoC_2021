import life_support_data;

#include <iostream>

int main( )
{
    life_support_data::Result result;

    return result.Execute( 230, 4'672'151 ) == AoC::ResultType::FAILED;
}
