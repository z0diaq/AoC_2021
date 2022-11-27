import syntax_scoring;

#include <iostream>

#define HAVE_PART2

int main( )
{
    syntax_scoring::Result result;

    std::cout << "#### PART 1:" << std::endl;
    auto resultPart1 = result.Execute( 26'397, 0 );

#ifdef HAVE_PART2
    std::cout << std::endl << "#### PART 2:" << std::endl;
    auto resultPart2 = result.Execute( 288'957u, 2'769'449'099u, AoC::Stage::PART_TWO );

    return
        resultPart1 == AoC::ResultType::FAILED ||
        resultPart2 == AoC::ResultType::FAILED;
#else
    return resultPart1 == AoC::ResultType::FAILED;
#endif
}
