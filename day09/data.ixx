module;

#include <string>
#include <vector>
#include <algorithm>

export module smoke:data;

export import AoC;

export namespace smoke
{
    struct Data : public AoC::Data
    {
        virtual void Process( const std::string& line ) override;
        virtual void Reset( ) override;

        typedef std::vector<uint8_t> DataLine;
        DataLine m_dataLine;

    };
}

using namespace smoke;

void
Data::Process( const std::string& line )
{
    m_dataLine.resize( line.length( ) );
    std::transform(
        line.begin( ),
        line.end( ),
        m_dataLine.begin( ),
        [ ]( char ch ) -> uint8_t
    {
        return static_cast< uint8_t >( ch - '0' );
    } );

}

void
Data::Reset( )
{
    m_dataLine.clear( );
}
