#pragma once

#include <tuple>

namespace dirac_dice
{
	struct PlayerInfo
	{
		std::uint32_t m_position;
		std::uint32_t m_score;
	};

	__forceinline bool
	operator==( const PlayerInfo& _lhs, const PlayerInfo& _rhs )
	{
		return std::tie( _lhs.m_position, _lhs.m_score ) == std::tie( _rhs.m_position, _rhs.m_score );
	}
}
