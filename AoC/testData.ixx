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
		std::string  m_expectedResultPart1;
		std::string  m_expectedResultPart2;

	public:
		void Load( const std::string& filename, const std::string& dataTag );

		operator bool( )const
		{
			return false == m_data.empty( );
		}

		const TestLines& Data( ) const
		{
			return m_data;
		}

		const std::string&
		ExpectedResultPart1( ) const
		{
			return m_expectedResultPart1;
		}

		const std::string&
		ExpectedResultPart2( ) const
		{
			return m_expectedResultPart2;
		}
	};
}
