import AoC;

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

static const std::string FILENAME( "input.txt" );
static const std::string FILENAME_TEST_A( "sample_input_a.txt" );
static const std::string FILENAME_TEST_B( "sample_input_b.txt" );
static const std::string FILENAME_TEST_C( "sample_input_c.txt" );

bool
AoC::Result::Execute( int argc, char* argv[ ] )
{
	if( argc >= 1 )
	{
		m_dataTag = fs::path( argv[ 0 ] ).stem( ).string( );
		std::cout << "DEBUG: tag: [" << m_dataTag << "]" << std::endl;
	}

	// process all known files - abort on first computation failure
	return
		ProcessFileIfExists( FILENAME_TEST_A ) &&
		ProcessFileIfExists( FILENAME_TEST_B ) &&
		ProcessFileIfExists( FILENAME_TEST_C ) &&
		ProcessFileIfExists( FILENAME );
}

bool
AoC::Result::ProcessFileIfExists( const std::string& filename )
{
	TestData data( filename, m_dataTag );

	if( false == data )
	{
		std::cout << std::endl << std::endl << "DEBUG: " << filename << " could not be processed" << std::endl;
		return true;
	}

	std::cout << std::endl << "INFO: processing [" << filename << "]..." << std::endl;

	for( int partNo = 1; partNo <= 2; ++partNo )
	{
		if( FAILED == CheckResult(
			InternalExecute( data.Data( ), partNo == 1 ),
			partNo == 1 ? data.ExpectedResultPart1( ) : data.ExpectedResultPart2( ) ) )
		{
			return false;
		}
	}

	return true;
};

uint64_t
AoC::Result::InternalExecute( const AoC::TestLines& lines, bool isPartOne )
{
	m_isPartOne = isPartOne;

	std::cout << "\tPART " << ( isPartOne ? "1" : "2" ) << std::endl;

	uint64_t result{ 0u };

	try
	{
		this->Init( );

		for( auto line : lines )
			isPartOne ? ProcessOne( line ) : ProcessTwo( line );

		result = this->Finish( );
	}
	catch( const std::exception& e )
	{
		std::cerr << "\tFATAL: exception [" << e.what( ) << "] caught while processing data!" << std::endl;
	}
	catch( ... )
	{
		std::cerr << "\tFATAL: unknown exception caught while processing data!" << std::endl;
	}

	this->Teardown( );

	std::cout << "\t\tresult: " << result;

	return result;
}

int
AoC::Result::CheckResult( const uint64_t computed, const uint64_t expected ) const
{
	// ignore not ready solution results
	if( computed == 0 )
		return PASSED;

	if( expected != computed )
	{
		std::cerr << " - ERROR: computed [" << computed << "], "
			"expected [" << expected << "]" << std::endl;

		return FAILED;
	}

	std::cout << " - OK" << std::endl;

	return PASSED;
}
