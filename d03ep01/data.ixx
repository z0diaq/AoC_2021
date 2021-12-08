module;

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

export module binary_diagnostic:data;

export import AoC;

export namespace binary_diagnostic
{
    struct Data : public AoC::Data
    {
        std::vector<unsigned int> m_bits;

        virtual void Process( const std::string& line ) override;
    };
}

void
binary_diagnostic::Data::Process( const std::string& line )
{
    m_bits = std::vector<unsigned int>( line.length( ), 0 );
    for( int bit = 0; bit != line.length( ); ++bit )
    {
        m_bits[ bit ] = ( line[ bit ] == '1' );
    }
}
