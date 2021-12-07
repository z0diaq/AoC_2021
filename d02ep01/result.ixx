module;

#include <cstdio>

export module result;

import data;

struct Position
{
	int m_x = 0;
	int m_y = 0;
};

export class Result
{
public:
	Result( );

	void Process( const Data& data );

	void Finish( ) const;

private:

	Position m_position;
};

Result::Result( )
{
}

void
Result::Process( const Data& data )
{
	m_position.m_x += data.m_x;
	m_position.m_y += data.m_y;
}

void
Result::Finish( ) const
{
	printf(
		"final position - x:[ %d ], y:[ %d ]\n",
		m_position.m_x,
		m_position.m_y );

	fprintf(
		stdout,
		"result = %d\n",
		m_position.m_x * m_position.m_y );
}
