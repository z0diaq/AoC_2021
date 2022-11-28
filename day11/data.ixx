module;

#include <string>

export module dumbo_octopus:data;

export import AoC;

export namespace dumbo_octopus
{
	struct Data : public AoC::Data
	{
		std::string m_data;

		virtual void Process( const std::string& line ) override;
		virtual void Reset( ) override;
	};
}

using namespace dumbo_octopus;

void
Data::Process( const std::string& line )
{
	m_data = line;
}

void
Data::Reset( )
{
}
