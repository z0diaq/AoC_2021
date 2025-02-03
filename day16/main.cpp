import packet_decoder;

#include <compare>

int main(int argc, char* argv[])
{
	return static_cast< int >( packet_decoder::Result().Execute(argc, argv));
}
