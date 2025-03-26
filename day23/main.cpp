#include <gtest/gtest.h>

import amphipod;

int main( int argc, char* argv[ ] )
{
	testing::InitGoogleTest( &argc, argv );
	if( RUN_ALL_TESTS( ) )
		return 1;
	return static_cast< int >( amphipod::Result( ).Execute( argc, argv ) );
}
