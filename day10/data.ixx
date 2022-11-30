module;

#include <string>

export module syntax_scoring:data;

export import AoC;

export namespace syntax_scoring
{
	struct Data : public AoC::Data
	{
		virtual void Process( const std::string& line ) override;
		virtual void Reset( ) override;

		std::string m_line;
	};
}

using namespace syntax_scoring;

void
Data::Process( const std::string& line )
{
	m_line = line;
}

void
Data::Reset( )
{
	m_line.clear( );
}
