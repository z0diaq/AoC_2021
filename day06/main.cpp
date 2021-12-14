import lanternfish;

#include <iostream>

int main( )
{
    lanternfish::Result result;

    std::cout << "#### PART 1:" << std::endl;
    auto resultPart1 = result.Execute( 5934        , 345387 );

    std::cout << std::endl << "#### PART 2:" << std::endl;
    auto resultPart2 = result.Execute( 26984457539u, 1574445493136u, AoC::Stage::PART_TWO );

    return
        resultPart1 == AoC::ResultType::FAILED ||
        resultPart2 == AoC::ResultType::FAILED;
}
