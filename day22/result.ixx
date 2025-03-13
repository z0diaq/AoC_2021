module;

#include <string>
#include <array>

export module reactor_reboot;

import AoC;

export namespace reactor_reboot
{
	constexpr size_t X{ 0 };
	constexpr size_t Y{ 1 };
	constexpr size_t Z{ 2 };

	struct Range
	{
		const int m_min;
		const int m_max;
	};

	struct Command
	{
		const bool m_isOn;
		std::array<Range, 3> m_ranges;
	};

	using Point3D = std::array<int, 3>;

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
		std::vector<Command> m_commands;
		
	};
}

namespace std
{
	template<>
	struct hash< reactor_reboot::Point3D >
	{
		size_t operator()( reactor_reboot::Point3D const& _point ) const noexcept
		{
			using namespace reactor_reboot;

			size_t xHash{ hash<int>{}( _point[ X ] ) };
			size_t yHash{ hash<int>{}( _point[ Y ] ) };
			size_t zHash{ hash<int>{}( _point[ Z ] ) };

			// one of many possible hash combining methods
			return xHash ^ ( yHash << 1 ) ^ ( zHash << 2 );
		}
	};

} // namespace std