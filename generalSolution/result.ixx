module;

#include <iostream>

export module AoC;

export import :data;
import :input;

static const std::string FILENAME( "input.txt" );
static const std::string FILENAME_TEST( "input_test.txt" );

export namespace AoC
{
    enum class ResultType
    {
        FAILED,
        PASSED
    };

    class Result
    {

    public:
        Result( );
        virtual ~Result( );

        virtual void Init( ) = 0;
        virtual void Process( const Data* data ) = 0;
        virtual int Finish( ) const = 0;
        virtual void Teardown( ) = 0;

        virtual ResultType Execute(
            int expectedTestDataResult = -1, // known up front
            int expectedDataResult = -1 );   // known only after completing second half of puzzle

    protected:
        Data* m_data;

        int InternalExecute( const std::string& filename );
        ResultType CheckResult(
            const int computed,
            const int expected,
            const std::string& filename ) const;
    };
}

AoC::Result::Result( ) :
    m_data( nullptr )
{
}

AoC::Result::~Result( )
{
    delete m_data;
}

AoC::ResultType
AoC::Result::Execute(
    int expectedTestDataResult /*= -1*/, // known up front
    int expectedDataResult /*= -1*/ )    // known only after completing second half of puzzle
{
    std::ios::sync_with_stdio( false );

    ResultType selfCheckResult = ResultType::PASSED;

    if( expectedTestDataResult != -1 )
    {
        selfCheckResult = this->CheckResult(
            this->InternalExecute( FILENAME_TEST ),
            expectedTestDataResult,
            FILENAME_TEST );
        std::cout << std::endl;
    }

    if( ResultType::FAILED == this->CheckResult(
        this->InternalExecute( FILENAME ),
        expectedDataResult,
        FILENAME ) )
    {
        return ResultType::FAILED;
    }
    else
    {
        return selfCheckResult;
    }
}

int
AoC::Result::InternalExecute( const std::string& filename )
{
    AoC::Input input( filename );

    if( !input )
    {
        return -1;
    }

    std::cout << "INFO: analyzing data from " << filename << " ..." << std::endl;

    this->Init( );

    while( input.Next( m_data ) )
    {
        this->Process( m_data );
    }

    int accumulated = this->Finish( );

    this->Teardown( );

    return accumulated;
}

AoC::ResultType
AoC::Result::CheckResult( const int computed, const int expected, const std::string& filename ) const
{
    if( computed == -1 )
        return ResultType::FAILED;

    if( expected == -1 )
        return ResultType::PASSED;

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

        return ResultType::FAILED;
    }

    std::cout << "INFO: SUCCESS - computed value matches expected" << std::endl;

    return ResultType::PASSED;
}

