import reactor_reboot;

#include <gtest/gtest.h>

int main( int argc, char* argv[ ] )
{
	testing::InitGoogleTest( &argc, argv );
	if( RUN_ALL_TESTS( ) )
		return 1;
	return static_cast< int >( reactor_reboot::Result( ).Execute( argc, argv ) );
}
