module;

#include <iostream>

export module dive;

export import :data;

struct Position
{
	int m_x = 0;
	int m_y = 0;
};

export namespace dive
{
	class Result : public AoC::Result
	{

	public:
		Result( );

		virtual void Init( ) override;
		virtual bool Process( const AoC::DataPtr& data ) override;
		virtual uint64_t Finish( ) const override;
		virtual void Teardown( ) override;

	private:
		Position m_position;
	};
}

dive::Result::Result( )
{
}

void
dive::Result::Init( )
{
	m_data.reset( new dive::Data( ) );
	m_position = Position( );
}

void
dive::Result::Teardown( )
{
	m_data.reset( );
}

bool
dive::Result::Process( const AoC::DataPtr& data )
{
	const dive::Data* ourData = static_cast< const dive::Data* >( data.get( ) );
	m_position.m_x += ourData->m_x;
	m_position.m_y += ourData->m_y;

	return true;
}

uint64_t
dive::Result::Finish( ) const
{
	std::cout
		<< "final position - "
		"x:[ " << m_position.m_x << " ], "
		"y: [ " << m_position.m_y << " ]"
		<< std::endl;

	uint64_t accumulated = static_cast< uint64_t >( m_position.m_x * m_position.m_y );

	std::cout
		<< "result = "
		<< accumulated
		<< std::endl;

	return accumulated;
}
