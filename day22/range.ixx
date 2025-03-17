module;

#include <optional>

export module reactor_reboot:range;

export namespace reactor_reboot
{
	constexpr size_t X{ 0 };
	constexpr size_t Y{ 1 };
	constexpr size_t Z{ 2 };

	struct Range
	{
		int m_min;
		int m_max;

		//Range( const Range& _rhs ) = default;

		[[nodiscard]] size_t
		volume( ) const;

		[[nodiscard]] bool
		intersects( const Range& _other ) const;

		[[nodiscard]] std::optional<Range>
		intersection( const Range& _other ) const;

		[[nodiscard]] bool operator==( const Range& _rhs ) const;
	};
}