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
		virtual void Process( const AoC::Data* data ) override;
		virtual int Finish( ) const override;
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
	m_data = new dive::Data( );
	m_position = Position( );
}

void
dive::Result::Teardown( )
{
	delete m_data;
	m_data = nullptr;
}

void
dive::Result::Process( const AoC::Data* data )
{
	const dive::Data* ourData = static_cast< const dive::Data* >( data );
	m_position.m_x += ourData->m_x;
	m_position.m_y += ourData->m_y;
}

int
dive::Result::Finish( ) const
{
	std::cout
		<< "final position - "
		"x:[ " << m_position.m_x << " ], "
		"y: [ " << m_position.m_y << " ]"
		<< std::endl;

	int accumulated = m_position.m_x * m_position.m_y;

	std::cout
		<< "result = "
		<< accumulated
		<< std::endl;

	return accumulated;
}
