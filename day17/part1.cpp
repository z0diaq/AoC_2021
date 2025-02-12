import trick_shot;

#include <string>

using namespace trick_shot;

void
Result::ProcessOne( const std::string& data )
{
	m_targetAreaDescription = data;
}

std::string
Result::FinishPartOne( )
{
	auto [maxHeight, _] = Solve( m_targetAreaDescription );
	return std::to_string( maxHeight );
}
