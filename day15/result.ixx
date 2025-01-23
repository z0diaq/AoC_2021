module;

#include <string>
#include <deque>

export module chitons;

import AoC;

export namespace chitons
{
	class Result : public AoC::Result
	{

	public:
		Result();

	protected:
		virtual void Init() override;

		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override;

		virtual void Teardown() override;

	private:
		//data
		std::deque<std::string> m_map;
	};
}
