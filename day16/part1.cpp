import packet_decoder;

#include <string>

using namespace packet_decoder;

class BinaryHolder;

void
Result::ProcessOne( const std::string& data )
{
	m_packet = data;
}

std::string
Result::FinishPartOne( )
{
	unsigned int sumOfPacketVersions{ 0 };
	BinaryHolder holder( utils::HexToBinary( m_packet ) );
	utils::DecodePacket( holder, sumOfPacketVersions );

	return std::to_string( sumOfPacketVersions );
}
