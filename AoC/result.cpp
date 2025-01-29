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

	bool result{ ProcessFileIfExists( FILENAME_TEST_A ) };
	result &= ProcessFileIfExists( FILENAME_TEST_B );
	result &= ProcessFileIfExists( FILENAME_TEST_C );
	result &= ProcessFileIfExists( FILENAME );

	return result;
}

bool
AoC::Result::ProcessFileIfExists( const std::string& filename )
{
	TestData data;
	m_dataLoadingSec = Measure( &TestData::Load, data, filename, m_dataTag );

	if( false == data )
	{
		std::cout << std::endl << "DEBUG: " << filename << " could not be processed" << std::endl;
		return true;
	}

	std::cout << std::endl << "INFO: processing [" << filename << "]..." << std::endl;

	for( int partNo = 1; partNo <= 2; ++partNo )
	{
		PerformanceSummaryTrigger trigger( this );
		if( FAILED == CheckResult( InternalExecute( data.Data( ), partNo == 1 ),
								   partNo == 1 ? data.ExpectedResultPart1( ) : data.ExpectedResultPart2( ) ) )
			return false;
	}

	return true;
};

std::string
AoC::Result::InternalExecute( const AoC::TestLines& lines, bool isPartOne )
{
	m_isPartOne = isPartOne;

	std::cout << "\tPART " << ( m_isPartOne ? "1" : "2" ) << std::endl;

	std::string result;

	auto ProcessAllLines = [ this ]( const AoC::TestLines& lines ) -> void
	{
		for( const auto& line : lines )
			m_isPartOne ? ProcessOne( line ) : ProcessTwo( line );
	};

	auto PrepareResult = [ this ](std::string& result ) -> void
	{
		result = m_isPartOne ? this->FinishPartOne( ) : this->FinishPartTwo( );
	};

	try
	{
		this->Init( );

		m_dataProcessingSec = Measure( ProcessAllLines, lines );
		m_resultPrepareSec = Measure( PrepareResult, result );

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
AoC::Result::CheckResult( const std::string& computed, const std::string& expected ) const
{
	if( false == computed.empty( ) )
	{
		if( expected != computed )
		{
			std::cerr << " - ERROR: computed [" << computed << "], "
				"expected [" << expected << "]" << std::endl;

			return FAILED;
		}

		std::cout << " - OK";
	}
	std::cout << std::endl;

	return PASSED;
}

void
AoC::Result::DumpPerformanceSummary( ) const
{
	const auto default_precision{ std::cout.precision( ) };
	std::cout << std::setprecision( 3 ) << std::fixed;

	std::cout << "\t\tperformance summary - load [" << m_dataLoadingSec << " s] >> "
		"process: [" << m_dataProcessingSec << " s] >> "
		"result: [" << m_resultPrepareSec << " s]"
		<< std::endl;

	std::cout << std::setprecision( default_precision ) << std::defaultfloat;
}
