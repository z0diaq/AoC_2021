module;

#include <iostream>
#include <sstream>
#include <string>
#include <bitset>

export module life_support_data:data;

export import AoC;

export namespace life_support_data
{
    typedef std::bitset<12> Item;

    struct Data : public AoC::Data
    {
        Item m_bits;//full test data has 12 bits
        size_t m_usedBits;

        virtual void Process( const std::string& line ) override;
    };
}

void
life_support_data::Data::Process( const std::string& line )
{
    m_usedBits = line.length( );
    for( int bit = 0; bit != line.length( ); ++bit )
    {
        m_bits.set( bit, ( line[ bit ] == '1' ) );
    }
}
