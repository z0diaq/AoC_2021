module;

#include <sstream>
#include <string>

export module dive:data;

export import AoC;

export namespace dive
{
    struct Data : public AoC::Data
    {
        int m_x = 0;
        int m_y = 0;

        virtual void Process( const std::string& line ) override;
    };
}

void
dive::Data::Process( const std::string& line )
{
    m_x = m_y = 0;

    std::string direction;
    int value{0};

    std::stringstream ss( line );
    ss >> direction >> value;

    if( "forward" == direction )
    {
        m_x = value;
    }
    else if( "up" == direction )
    {
        m_y = -value;
    }
    else
    {
        m_y = value;
    }
}
