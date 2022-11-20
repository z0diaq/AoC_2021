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

    enum class Stage
    {
        PART_ONE,
        PART_TWO
    };

    class Result
    {

    public:
        Result( ) = default;
        virtual ~Result( ) = default;

        virtual void Init( ) = 0;
        //result eq true means source data was fully consumed and can be reset now
        //          false means it can't be cleared yet
        virtual bool Process( const DataPtr& data ) = 0;
        virtual uint64_t Finish( ) const = 0;
        virtual void Teardown( ) = 0;

        virtual ResultType Execute(
            uint64_t expectedTestDataResult = 0, // known up front
            uint64_t expectedDataResult = 0,     // known only after completing second half of puzzle
            Stage stage = Stage::PART_ONE );

    protected:
        AoC::Input m_input;
        DataPtr    m_data;

        bool IsPartOne( ) const;
        bool IsPartTwo( ) const;

    private:
        Stage      m_stage;


        unsigned long long InternalExecute( const std::string& filename );
        ResultType CheckResult(
            const uint64_t computed,
            const uint64_t expected,
            const std::string& filename ) const;
    };
}

AoC::ResultType
AoC::Result::Execute(
    uint64_t expectedTestDataResult /*= 0*/, // known up front
    uint64_t expectedDataResult /*= 0*/,     // known only after completing second half of puzzle
    Stage stage /*= Part::One*/ )
{
    std::ios::sync_with_stdio( false );
    m_stage = stage;

    ResultType selfCheckResult = ResultType::PASSED;

    if( expectedTestDataResult )
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

uint64_t
AoC::Result::InternalExecute( const std::string& filename )
{
    if( false == m_input.Init( filename ) )
    {
        return -1;
    }

    std::cout << "INFO: analyzing data from " << filename << " ..." << std::endl;

    uint64_t accumulated{0u};

    try
    {
        this->Init( );

        while( m_input.Next( m_data ) )
        {
            if( this->Process( m_data ) )
                m_data->Reset( );
        }

        accumulated = this->Finish( );
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

AoC::ResultType
AoC::Result::CheckResult( const uint64_t computed, const uint64_t expected, const std::string& filename ) const
{
    if( computed == 0 )
        return ResultType::FAILED;

    if( expected == 0 )
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

bool
AoC::Result::IsPartOne( ) const
{
    return m_stage == Stage::PART_ONE;
}

bool
AoC::Result::IsPartTwo( ) const
{
    return m_stage == Stage::PART_TWO;
}
