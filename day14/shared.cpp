import extended_polymerization;

using namespace extended_polymerization;

Result::Result()
{

}

void
Result::Teardown()
{
	m_template.clear( );
	m_pairInsertionRules.clear( );
}
