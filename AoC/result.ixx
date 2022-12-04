module;

#include <stdexcept>

export module AoC;

export import :test_data;
export import :fs_helpers;

export constexpr int PASSED = 1;
export constexpr int FAILED = 0;

export namespace AoC
{
	class Result
	{

	public:
		Result( ) = default;
		virtual ~Result( ) = default;

		virtual bool Execute( int argc, char* argv[ ] );

		virtual void Init( ) = 0;
		virtual void ProcessOne( const std::string& data )
		{
			throw std::logic_error( "ProcessOne method should be overridden" );
		}

		virtual void ProcessTwo( const std::string& data )
		{
			throw std::logic_error( "ProcessTwo method should be overridden" );
		}

		virtual uint64_t Finish( ) { return 0; }
		virtual void Teardown( ) = 0;


	protected:

		bool IsPartOne( ) const { return m_isPartOne; }
		bool IsPartTwo( ) const { return false == m_isPartOne; }

	private:
		bool        m_isPartOne;
		std::string m_dataTag;//taken for application name - ie. 'day01', used for searching for data
		
		bool ProcessFileIfExists( const std::string& filename );
		unsigned long long InternalExecute( const TestLines& lines, bool isPartOne );
		int CheckResult(
			const uint64_t computed,
			const uint64_t expected ) const;
	};
}
