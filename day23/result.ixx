module;

#include <string>
#include <vector>
#include <array>

export module amphipod;

import AoC;

export namespace amphipod
{
	using Amphipod = std::uint16_t;
	using Map = std::vector<std::string>;

	constexpr Amphipod A{ 0 };
	constexpr Amphipod B{ 1 };
	constexpr Amphipod C{ 2 };
	constexpr Amphipod D{ 3 };

	using RoomNumber = std::uint16_t;
	constexpr RoomNumber Room1{ 0 };
	constexpr RoomNumber Room2{ 1 };
	constexpr RoomNumber Room3{ 2 };
	constexpr RoomNumber Room4{ 3 };

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
