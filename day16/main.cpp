import packet_decoder;

#include <gtest/gtest.h>

int main(int argc, char* argv[])
{
	testing::InitGoogleTest( &argc, argv );
	if( RUN_ALL_TESTS( ) )
		return 1;
	return static_cast< int >( packet_decoder::Result().Execute(argc, argv));
}
