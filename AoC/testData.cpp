import AoC;

#include <string>
#include <filesystem>
#include <iostream>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>

//using AoC::TestData;
using AoC::TestData;

TestData::TestData( const std::string& filename, const std::string& dataTag )
{
	fs::path path;
	
	if( AoC::FindFileInPredefinedLocations( filename, path, dataTag ) )
	{
		try
		{
			boost::split( m_data, ReadFileContents( path ), boost::is_any_of( "\r\n" ) );
			m_expectedResultPart1 = boost::lexical_cast< uint64_t >( ReadFileContents( GetPathVariant( path, DataType::RESULT_PART_1 ) ) );
			m_expectedResultPart2 = boost::lexical_cast< uint64_t >( ReadFileContents( GetPathVariant( path, DataType::RESULT_PART_2 ) ) );
		}
		catch( std::exception& e )
		{
			std::cerr << "FATAL: exception [" << e.what( ) << "] caught while preparring data!" << std::endl;
		}
	}
}
