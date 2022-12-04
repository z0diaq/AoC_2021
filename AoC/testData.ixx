module;

#include <vector>
#include <string>

export module AoC:test_data;

export namespace AoC
{
	typedef std::vector<std::string> TestLines;

	class TestData
	{
	private:
		TestLines m_data;
		uint64_t  m_expectedResultPart1 = 0;
		uint64_t  m_expectedResultPart2 = 0;

	public:
		TestData( const std::string& filename, const std::string& dataTag );

		operator bool( )const
		{
			return false == m_data.empty( );
		}
		
		const TestLines& Data( ) const
		{
			return m_data;
		}

		uint64_t ExpectedResultPart1( ) const
		{
			return m_expectedResultPart1;
		}
		
		uint64_t ExpectedResultPart2( ) const
		{
			return m_expectedResultPart2;
		}
	};
}
