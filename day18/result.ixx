module;

#include <string>
#include <vector>

export module snailfish;

export import :node;
export import :utils;

import AoC;

export namespace snailfish
{
	class Result : public AoC::Result
	{
	protected:

		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override;

		virtual void Teardown() override;

	private:
		std::vector<std::string> m_numbers;
	};
}
