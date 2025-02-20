import beacon_scanner;

#include <gtest/gtest.h>

int main( int argc, char* argv[ ] )
{
	testing::InitGoogleTest( &argc, argv );
	if( RUN_ALL_TESTS( ) )
		return 1;
	return static_cast< int >( beacon_scanner::Result( ).Execute( argc, argv ) );
}
