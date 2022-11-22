module;

#include <string>

export module smoke:data;

export import AoC;

export namespace smoke
{
    struct Data : public AoC::Data
    {
        virtual void Process( const std::string& line ) override;
        virtual void Reset( ) override;
    };
}

using namespace smoke;

void
Data::Process( const std::string& line )
{
}

void
Data::Reset( )
{
}
