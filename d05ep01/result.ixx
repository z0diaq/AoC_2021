module;

#include <iostream>
#include <deque>
#include <algorithm>
//#include <sstream>

export module hydrothermal_venture;

export import :data;
import :ocean_floor_map;

export namespace hydrothermal_venture
{

	class Result : public AoC::Result
	{

	public:
		Result( );

		virtual void Init( ) override;
		virtual bool Process( const AoC::DataPtr& data ) override;
		virtual int Finish( ) const override;
		virtual void Teardown( ) override;

	private:
		//gathered data
		std::deque<Line> m_lines;
		Point            m_max;
	};
}

using namespace hydrothermal_venture;

Result::Result( )
{
}

void
Result::Init( )
{
	m_data.reset( new hydrothermal_venture::Data( ) );
	m_max.m_x = m_max.m_y = 0;
}

void
Result::Teardown( )
{
	m_data.reset( );
	m_lines.clear( );
}

bool
Result::Process( const AoC::DataPtr& data )
{
	const Data* ourData = dynamic_cast< const Data* >( data.get( ) );

	m_lines.push_back( ourData->m_line );
	m_max.m_x = std::max( {
		m_max.m_x,
		ourData->m_line.m_start.m_x,
		ourData->m_line.m_end.m_x } );
	m_max.m_y = std::max( {
		m_max.m_y,
		ourData->m_line.m_start.m_y,
		ourData->m_line.m_end.m_y } );

	return true;
}

int
Result::Finish( ) const
{
	OceanFloorMap map;
	
	map.Init(
		m_max.m_x + 1,
		m_max.m_y + 1 );

	for( const auto& line : m_lines )
		map.Process( line );

	const auto computedValue = map.CountPointCoveredByTwoAndMore( );

	std::cout
		<< "result = "
		<< computedValue
		<< std::endl;

	return computedValue;
}
