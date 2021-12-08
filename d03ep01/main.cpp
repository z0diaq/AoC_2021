import binary_diagnostic;

#include <iostream>

int main( )
{
    binary_diagnostic::Result result;

    return result.Execute( 198, 1092896 ) == AoC::ResultType::FAILED;
}
