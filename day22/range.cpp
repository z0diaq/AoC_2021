module;

#include <optional>

module reactor_reboot:range;

using reactor_reboot::Range;

[[nodiscard]] size_t
Range::volume( ) const
{
	return static_cast< size_t >( m_max - m_min );
}

[[nodiscard]] bool
Range::intersects( const Range& _other ) const
{
	return m_min <= _other.m_max && m_max >= _other.m_min;
}

[[nodiscard]] std::optional<Range>
Range::intersection( const Range& _other ) const
{
	if( !intersects( _other ) )
		return std::nullopt;
	return Range{ std::max( m_min, _other.m_min ), std::min( m_max, _other.m_max ) };
}
