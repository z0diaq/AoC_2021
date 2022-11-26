module;

#include <array>

export module smoke:partTwoSolver;

export namespace smoke
{
	class Result;

	typedef std::pair<uint32_t, uint32_t> Point;
	struct PartTwoSolver
	{
		const Result* m_parent = nullptr;
		uint32_t m_width;
		std::array<uint32_t, 3> m_largestBasins;

		PartTwoSolver( const Result* parent );
		uint32_t Index( const Point& point ) const;
		void AnalyzeBasin( const Point& point );
		uint32_t ComputeBasinSize( const Point& point );
		uint32_t ComputeResult( ) const;
	};
}
