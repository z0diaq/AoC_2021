import packet_decoder;

#include <string>

using namespace packet_decoder;

void
Result::ProcessTwo(const std::string& data)
{
	m_packet = data;
}

std::string
Result::FinishPartTwo( )
{
	unsigned int sumOfPacketVersions{ 0 };
	BinaryHolder holder( utils::HexToBinary( m_packet ) );
	return std::to_string( utils::DecodePacket( holder, sumOfPacketVersions ) );
}
