module;

#include <string>

export module trick_shot;

export import :target_area;
export import :utils;

import AoC;

export namespace trick_shot
{
	class Result : public AoC::Result
	{

	public:
		Result( ) = default;

	protected:
		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override;

		virtual void Teardown() override;

	private:
		//data
		std::string m_targetAreaDescription;

		std::pair<int, int> Solve( const std::string& targetAreaDescription ) const;
	};
}
