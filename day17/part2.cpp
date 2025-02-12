import trick_shot;

#include <string>

using namespace trick_shot;

void
Result::ProcessTwo(const std::string& data)
{
	m_targetAreaDescription = data;
}

std::string
Result::FinishPartTwo( )
{
	auto [_, validResultsCount] = Solve( m_targetAreaDescription );
	return std::to_string( validResultsCount );
}
