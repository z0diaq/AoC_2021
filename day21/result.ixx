module;

#include <string>
#include <array>

#include "playerInfo.h"

export module dirac_dice;

import AoC;

export namespace dirac_dice
{
	class Result : public AoC::Result
	{
	protected:
		virtual void Init() override;

		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override;

	private:
		//data
		std::array<PlayerInfo, 2> m_players{};

		std::uint32_t m_lastDiceResult;
		std::uint32_t m_timesDiceRolled;
	};
}
