module;

#include <array>
#include <vector>

export module reactor_reboot:cuboid;

import :range;

namespace std
{
	template<typename T>
	class optional;
}

export namespace reactor_reboot
{
	struct Cuboid
	{
		Range m_xRange;
		Range m_yRange;
		Range m_zRange;

		[[nodiscard]] int64_t
			volume( ) const;

		[[nodiscard]] bool
			intersects( const Cuboid& other ) const;

		[[nodiscard]] std::optional<Cuboid>
			intersection( const Cuboid& other ) const;

		[[nodiscard]] std::vector<Cuboid>
			subtract( const Cuboid& other ) const;
	};
}
