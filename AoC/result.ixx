module;

#include <stdexcept>
#include <chrono>

export module AoC;

export import :test_data;
export import :fs_helpers;

export constexpr int PASSED = 1;
export constexpr int FAILED = 0;

export namespace AoC
{
	class Result
	{
		struct PerformanceSummaryTrigger
		{
			AoC::Result* m_view;
			PerformanceSummaryTrigger( AoC::Result* view ) :
				m_view( view )
			{
			}
			~PerformanceSummaryTrigger( )
			{
				m_view->DumpPerformanceSummary( );
			}
		};

		friend struct PerformanceSummaryTrigger;

	public:
		Result( ) = default;
		virtual ~Result( ) = default;

		virtual bool Execute( int argc, char* argv[ ] );


	protected:

		bool IsPartOne( ) const { return m_isPartOne; }
		bool IsPartTwo( ) const { return false == m_isPartOne; }

		virtual void Init( ) { };

		//part one section
		virtual void ProcessOne( const std::string& data ) = 0;
		virtual std::string FinishPartOne( ) = 0;

		//part two section
		virtual void ProcessTwo( const std::string& data ) = 0;
		virtual std::string FinishPartTwo( ) = 0;

		virtual void Teardown( ) { };

	private:
		bool        m_isPartOne;
		std::string m_dataTag;//taken for application name - ie. 'day01', used for searching for data
		double      m_dataLoadingSec;
		double      m_dataProcessingSec;
		double      m_resultPrepareSec;

		bool ProcessFileIfExists( const std::string& filename );
		std::string InternalExecute( const TestLines& lines, bool isPartOne );
		int CheckResult(
			const std::string& computed,
			const std::string& expected ) const;

		template<typename Function, typename... Args>
		double Measure( Function&& toTime, Args&&... a )
		{
			//copied from: https://stackoverflow.com/a/50891840

			auto start{ std::chrono::steady_clock::now( ) };
				std::invoke( std::forward<Function>( toTime ), std::forward<Args>( a )... );
			auto stop{ std::chrono::steady_clock::now( ) };

			return std::chrono::duration_cast< std::chrono::duration< double > >( stop - start ).count( );
		}

		void DumpPerformanceSummary( ) const;
	};
}
