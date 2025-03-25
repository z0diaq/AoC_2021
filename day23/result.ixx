export module amphipod:result;

import :types;

import AoC;

import <string>;
import <vector>;
import <array>;

export namespace amphipod
{
	using Map = std::vector<std::string>;

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
		Map m_map;
	};
}
