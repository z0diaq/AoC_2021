import aoc_template;

#include <gtest/gtest.h>

int main( int argc, char* argv[ ] )
{
	testing::InitGoogleTest( &argc, argv );
	if( RUN_ALL_TESTS( ) )
		return 1;
	return static_cast< int >( aoc_template::Result( ).Execute( argc, argv ) );
}
