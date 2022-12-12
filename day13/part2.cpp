import transparent_origami;

#include <iostream>
#include <string>

using namespace transparent_origami;

void
Result::ProcessTwo(const std::string& data)
{
	Process( data );
}

std::string
Result::FinishPartTwo()
{
	std::cout << "after fold:" << std::endl;
	for( size_t lineNo = 0; lineNo != m_sheet.size( ); ++lineNo )
		std::cout << lineNo << "] " << m_sheet[ lineNo ] << std::endl;

	//ocr? maybe other time...
	//for now read above output and fill result

	std::cout << std::endl << "READ ABOVE :D" << std::endl;

	return "0";//result from sample data
}
