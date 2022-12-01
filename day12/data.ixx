module;

#include <string>

export module passage_pathing:data;

export import AoC;

export namespace passage_pathing
{
	struct Data : public AoC::Data
	{
		typedef std::pair<std::string, std::string> Connection;
		Connection m_connection;

		virtual void Process( const std::string& line ) override;
		virtual void Reset( ) override;
	};
}

using namespace passage_pathing;

void
Data::Process( const std::string& line )
{
	auto splitPos = line.find( '-' );
	m_connection.first = line.substr( 0, splitPos );
	m_connection.second = line.substr( splitPos + 1 );
}

void
Data::Reset( )
{
	m_connection = { "", "" };
}
