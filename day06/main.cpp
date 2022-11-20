import lanternfish;

#include <iostream>

int main( )
{
    lanternfish::Result result;

    std::cout << "#### PART 1:" << std::endl;
    auto resultPart1 = result.Execute( 5'934        , 359'344 );

    std::cout << std::endl << "#### PART 2:" << std::endl;
    auto resultPart2 = result.Execute( 26'984'457'539u, 1'629'570'219'571u, AoC::Stage::PART_TWO );

    return
        resultPart1 == AoC::ResultType::FAILED ||
        resultPart2 == AoC::ResultType::FAILED;
}
