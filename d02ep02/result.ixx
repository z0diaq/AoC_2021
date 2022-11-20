module;

#include <iostream>

export module dive;

export import :data;

export namespace dive
{
	class Result : public AoC::Result
	{

	public:
		Result( );

		virtual void Init( ) override;
		virtual bool ProcessGeneral( const AoC::DataPtr& data ) override;
		virtual uint64_t Finish( ) const override;
		virtual void Teardown( ) override;

	private:
		int m_aim = 0;
		int m_position = 0;
		int m_depth = 0;
	};
}

dive::Result::Result( )
{
}

void
dive::Result::Init( )
{
	m_data.reset( new dive::Data( ) );
	m_aim = m_position = m_depth = 0;
}

void
dive::Result::Teardown( )
{
	m_data.reset( );
}

bool
dive::Result::ProcessGeneral( const AoC::DataPtr& data )
{
	const dive::Data* ourData = static_cast< const dive::Data* >( data.get( ) );
	if( ourData->m_y )
	{
		m_aim += ourData->m_y;
	}
	else
	{
		m_position += ourData->m_x;
		m_depth += m_aim * ourData->m_x;
	}

	return true;
}

uint64_t
dive::Result::Finish( ) const
{
	std::cout
		<< "final values - "
		"position:[ " << m_position << " ], "
		"depth: [ " << m_depth << " ]"
		<< std::endl;

	uint64_t accumulated = static_cast< uint64_t >( m_position * m_depth );

	std::cout
		<< "result = "
		<< ( m_position * m_depth )
		<< std::endl;

	return accumulated;
}
