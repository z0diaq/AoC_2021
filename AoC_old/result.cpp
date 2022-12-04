import AoC;

#include <iostream>
#include <fstream>
//#include <algorithm>
#include <filesystem>

#include <boost/format.hpp>

namespace fs = std::filesystem;

static const std::string FILENAME( "input.txt" );
static const std::string FILENAME_TEST_A( "sample_input_a.txt" );
static const std::string FILENAME_TEST_B( "sample_input_b.txt" );
static const std::string FILENAME_TEST_C( "sample_input_c.txt" );

int
AoC::Result::Execute( )
{
	std::ios::sync_with_stdio( false );

	int result = PASSED;

	auto ProcessFileIfExists = [ &result, this ]( const std::string& filename ) -> void
	{
		if( false == fs::exists( fs::path( filename ) ) )
		{
			std::cout << std::endl << "DEBUG: " << filename << " does not exist - processing skipped" << std::endl;
			return;
		}

		//check part 1
		for( int partNo = 1; partNo <= 2; ++partNo )
		{
			std::string resultFilenamePart = ( boost::format( "%1%_result_part%2%.%3%" )
				% filename.substr( 0, filename.length( ) - 4 ) // filestem
				% partNo
				% filename.substr( filename.length( ) - 3 ) ).str( ); // extension

			fs::path resultPath( resultFilenamePart );

			std::uint64_t expectedResult = 0;

			if( fs::exists( resultPath ) && fs::file_size( resultPath ) > 0 )
			{
				std::ifstream resultStream;
				resultStream.open( resultPath );
				if( resultStream.is_open( ) )
					resultStream >> expectedResult;
			}

			if( FAILED == this->CheckResult(
				this->InternalExecute( filename, partNo == 1 ),
				expectedResult,
				filename ) )
			{
				result = FAILED;
			}
		}
	};

	ProcessFileIfExists( FILENAME_TEST_A );
	ProcessFileIfExists( FILENAME_TEST_B );
	ProcessFileIfExists( FILENAME_TEST_C );

	ProcessFileIfExists( FILENAME );

	return result;
}

uint64_t
AoC::Result::InternalExecute( const std::string& filename, bool isPartOne )
{
	m_isPartOne = isPartOne;

	if( false == m_input.Init( filename ) )
	{
		return -1;
	}

	std::cout << std::endl << "INFO: PART " << ( isPartOne ? "1" : "2" ) << " [" << filename << "]" << std::endl;

	uint64_t accumulated{ 0u };

	try
	{
		this->Init( );

		auto Process = &Result::ProcessGeneral;
		if( m_haveDedicatedProcessing )
			Process = ( isPartOne ? &Result::ProcessOne : &Result::ProcessTwo );

		while( m_input.Next( m_data ) )
		{
			if( ( this->*Process )( m_data ) )
				m_data->Reset( );
		}

		accumulated = this->Finish( ) + this->FinishMutate( );
	}
	catch( const std::exception& e )
	{
		std::cerr << "FATAL: exception [" << e.what( ) << "] caught while processing data!" << std::endl;
	}
	catch( ... )
	{
		std::cerr << "FATAL: unknown exception caught while processing data!" << std::endl;
	}

	this->Teardown( );

	return accumulated;
}

int
AoC::Result::CheckResult( const uint64_t computed, const uint64_t expected, const std::string& filename ) const
{
	if( computed == 0 )
		return FAILED;

	if( expected == 0 )
		return PASSED;

	if( expected != computed )
	{
		std::cerr << "ERROR: computed value of "
			<< computed
			<< " does NOT match expected value of "
			<< expected
			<< " from "
			<< filename
			<< " data analysis"
			<< std::endl;

		return FAILED;
	}

	std::cout << "INFO: SUCCESS - computed value matches expected" << std::endl;

	return PASSED;
}

bool
AoC::Result::IsPartOne( ) const
{
	return m_isPartOne;
}

bool
AoC::Result::IsPartTwo( ) const
{
	return false == m_isPartOne;
}
