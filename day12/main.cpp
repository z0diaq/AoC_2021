import passage_pathing;

#include <compare>

int main( int argc, char* argv[ ] )
{
	return static_cast<int>( passage_pathing::Result( ).Execute( argc, argv ));
}
