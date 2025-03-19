import reactor_reboot;

using namespace reactor_reboot;

void
Result::Teardown()
{
	m_commands.clear( );
}
