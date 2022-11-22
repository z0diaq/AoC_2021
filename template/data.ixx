module;

#include <string>

export module aoc_template:data;

export import AoC;

export namespace aoc_template
{
    struct Data : public AoC::Data
    {
        virtual void Process( const std::string& line ) override;
        virtual void Reset( ) override;
    };
}

using namespace aoc_template;

void
Data::Process( const std::string& line )
{
}

void
Data::Reset( )
{
}
