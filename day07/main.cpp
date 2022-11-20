import whale;

#include <iostream>

#define HAVE_PART2

int main( )
{
    whale::Result result;

    std::cout << "#### PART 1:" << std::endl;
    auto resultPart1 = result.Execute( 37, 328'187 );

#ifdef HAVE_PART2
    std::cout << std::endl << "#### PART 2:" << std::endl;
    auto resultPart2 = result.Execute( 168, 91'257'582, AoC::Stage::PART_TWO );

    return
        resultPart1 == AoC::ResultType::FAILED ||
        resultPart2 == AoC::ResultType::FAILED;
#else
    return resultPart1 == AoC::ResultType::FAILED;
#endif
}
