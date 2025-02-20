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

		std::vector<Matrix> GetAllRotationMatrices( ) const;

	public:
		void AddPoint( Point&& point )
		{
			m_points.push_back( std::move( point ) );
		}

		std::vector<std::vector<Point>> GetAllRotations( ) const
		{
			std::vector<std::vector<Point>> rotations;
			rotations.reserve( 24 );

			for( const auto& rotation : GetAllRotationMatrices( ) )
			{
				std::vector<Point> rotated;
				rotated.reserve( m_points.size( ) );

				std::ranges::transform(
					m_points,
					std::back_inserter( rotated ),
					[&rotation]( const Point& point )
					{
						return point.ApplyRotation( rotation );
					}
				);

				rotations.push_back( std::move( rotated ) );
			}

			return rotations;
		}

		const std::vector<Point>& GetPoints( ) const { return m_points; }

	};
}
