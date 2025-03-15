module;

export module reactor_reboot:range;

namespace std
{
	template<typename T>
	class optional;
}

export namespace reactor_reboot
{
	struct Range
	{
		const int m_min;
		const int m_max;

		[[nodiscard]] size_t
		volume( ) const;

		[[nodiscard]] bool
		intersects( const Range& _other ) const;

		[[nodiscard]] std::optional<Range>
		intersection( const Range& _other ) const;
	};
}