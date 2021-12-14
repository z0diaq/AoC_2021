import binary_diagnostic;

#include <iostream>

int main( )
{
    binary_diagnostic::Result result;

    return result.Execute( 198u, 1'092'896u ) == AoC::ResultType::FAILED;
}
