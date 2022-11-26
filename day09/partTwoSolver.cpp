import smoke;

#include <deque>
#include <algorithm>

using namespace smoke;

PartTwoSolver::PartTwoSolver( const Result* parent ) :
	m_parent( parent ),
	m_width( parent->Width( ) ),
	m_largestBasins( { 0, 0, 0 } )
{
}

uint32_t
PartTwoSolver::Index( const Point& point ) const
{
	return point.second * m_width + point.first;
}

uint32_t
PartTwoSolver::ComputeBasinSize( const Point& point )
{
	//bfs flood fill
	std::vector<bool> visitedPoints( m_parent->Height( ) * m_parent->Width( ), false );

	visitedPoints[ Index( point ) ] = true;
	std::deque< Point > newPoints( 1, point );

	const uint32_t
		width = m_parent->Width( ),
		height = m_parent->Height( );
	uint32_t fillSize = 1;

	auto Process = [ &visitedPoints, &newPoints, this ]( const Point& point ) -> uint32_t
	{
		if( false == visitedPoints[ Index( point ) ] && m_parent->Value( point ) != 9 )
		{
			newPoints.push_back( point );
			visitedPoints[ Index( point ) ] = true;
			return 1;
		}
		return 0;
	};

	while( false == newPoints.empty( ) )
	{
		auto point = newPoints.front( );
		newPoints.pop_front( );

		if( point.first > 0 )
			fillSize += Process( { point.first - 1, point.second } );
		if( point.second > 0 )
			fillSize += Process( { point.first, point.second - 1 } );
		if( point.first < width - 1 )
			fillSize += Process( { point.first + 1, point.second } );
		if( point.second < height - 1 )
			fillSize += Process( { point.first, point.second + 1 } );
	}

	return fillSize;
}

void
PartTwoSolver::AnalyzeBasin( const Point& point )
{
	const uint32_t basinSize = ComputeBasinSize( { point.first, point.second } );

	// find insert position (first smaller element)
	// if before end then shift all element values and store value
	auto shiftIt = std::find_if( std::begin( m_largestBasins ),
								 std::end( m_largestBasins ),
								 [ basinSize ]( const uint32_t previousSize ) -> bool
	{
		return basinSize > previousSize;
	} );

	if( shiftIt != std::end( m_largestBasins ) )
	{
		std::copy_backward(
			shiftIt,
			std::end( m_largestBasins ) - 1,
			std::end( m_largestBasins ) );
		*shiftIt = basinSize;
	}
}

uint32_t
PartTwoSolver::ComputeResult( ) const
{
	return
		m_largestBasins[ 0 ] *
		m_largestBasins[ 1 ] *
		m_largestBasins[ 2 ];
}
