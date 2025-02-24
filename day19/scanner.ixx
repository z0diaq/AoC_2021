module;

#include <vector>
#include <algorithm>
#include <iterator>

export module beacon_scanner:scanner;
import :point;

export namespace beacon_scanner
{
	class Scanner
	{

	private:
		std::vector<Point> m_points;

	public:
		void AddPoint( Point&& point )
		{
			m_points.push_back( std::move( point ) );
		}

		std::vector<std::vector<Point>> GetAllRotations( ) const
		{
			std::vector<std::vector<Point>> rotations;
			rotations.reserve( m_points.size( ) );

			for( const auto& point : m_points )
				rotations.push_back( point.GenerateRotations( ) );

			return rotations;
		}

		const std::vector<Point>& GetPoints( ) const { return m_points; }

	};
}
