module;

#include <stdexcept>

export module AoC;

export import :data;
import :input;

static const std::string FILENAME( "input.txt" );
static const std::string FILENAME_TEST( "input_test.txt" );

export constexpr int PASSED = 0;
export constexpr int FAILED = 1;

export namespace AoC
{
	class Result
	{

	public:
		Result( ) = default;
		virtual ~Result( ) = default;

		virtual void Init( ) = 0;
		//result eq true means source data was fully consumed and can be reset now
		//          false means it can't be cleared yet
		virtual bool ProcessOne( const DataPtr& data )
		{
			throw std::logic_error( "ProcessOne method should be overridden" );
		}

		virtual bool ProcessTwo( const DataPtr& data )
		{
			throw std::logic_error( "ProcessTwo method should be overridden" );
		}

		virtual bool ProcessGeneral( const DataPtr& data )
		{
			throw std::logic_error( "ProcessGeneral method should be overridden" );
		}

		virtual uint64_t Finish( ) const { return 0; }
		virtual uint64_t FinishMutate( ) { return 0; }
		virtual void Teardown( ) = 0;

		virtual int Execute( );

	protected:
		AoC::Input m_input;
		DataPtr    m_data;
		bool       m_haveDedicatedProcessing = false;

		bool IsPartOne( ) const;
		bool IsPartTwo( ) const;

	private:
		bool       m_isPartOne;

		unsigned long long InternalExecute( const std::string& filename, bool isPartOne );
		int CheckResult(
			const uint64_t computed,
			const uint64_t expected,
			const std::string& filename ) const;
	};
}
