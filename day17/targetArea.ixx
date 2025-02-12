module;

#include<utility>

export module trick_shot:target_area;

export namespace trick_shot
{
	struct Point {
		int m_x, m_y;
	};

	struct Range
	{
		int m_min, m_max;

		bool InRange( int value ) const
		{
			return value >= m_min && value <= m_max;
		}
	};

	// Thread-safe target area representation
	class TargetArea {
	private:
		Range m_rangeX, m_rangeY;

	public:
		TargetArea( int minX, int maxX, int minY, int maxY )
			: m_rangeX{ minX, maxX }, m_rangeY{ minY, maxY } {
		}

		bool Contains( const Point& p ) const {
			return m_rangeX.InRange( p.m_x ) && m_rangeY.InRange( p.m_y );
		}

		auto Bounds( ) const {
			return std::make_pair( m_rangeX, m_rangeY );
		}

		bool Overshoot( const Point& pt ) const
		{
			return pt.m_x > m_rangeX.m_max || pt.m_y < m_rangeY.m_min;
		}
	};
}



