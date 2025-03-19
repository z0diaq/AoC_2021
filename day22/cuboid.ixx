module;

#include <array>
#include <vector>
#include <optional>

export module reactor_reboot:cuboid;

import :range;

export namespace reactor_reboot
{
	struct Cuboid
	{
		std::array<Range, 3> m_ranges;

		[[nodiscard]] size_t
			volume( ) const;

		[[nodiscard]] bool
			intersects( const Cuboid& other ) const;

		[[nodiscard]] std::optional<Cuboid>
			intersection( const Cuboid& other ) const;
	};
}
