module;

#include <string>
#include <array>

export module reactor_reboot;

export import :cuboid;
export import :range;

import AoC;

export namespace reactor_reboot
{
	struct Command
	{
		const bool m_isOn;
		std::array<Range, 3> m_ranges;
	};

	class Result : public AoC::Result
	{

	protected:
		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override;

		virtual void Teardown() override;

	private:
		//data
		std::vector<Command> m_commands;
	};
}
