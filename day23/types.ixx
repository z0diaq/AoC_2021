export module amphipod:types;

import <cstdint>;
import <array>;

export namespace amphipod
{
	using Amphipod = std::uint16_t;

	constexpr Amphipod A{ 0 };
	constexpr Amphipod B{ 1 };
	constexpr Amphipod C{ 2 };
	constexpr Amphipod D{ 3 };

	using RoomNumber = std::uint16_t;
	constexpr RoomNumber Room1{ 0 };
	constexpr RoomNumber Room2{ 1 };
	constexpr RoomNumber Room3{ 2 };
	constexpr RoomNumber Room4{ 3 };

	constexpr std::array<std::uint32_t, 4> MOVE_COSTS{ 1, 10, 100, 1000 };
}
