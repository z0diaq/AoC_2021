import binary_diagnostic;

#include <iostream>

int main( )
{
    binary_diagnostic::Result result;

    return result.Execute( 198u, 4'160'394u ) == AoC::ResultType::FAILED;
}
