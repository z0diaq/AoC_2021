module;

#include <iostream>
#include <vector>

export module dumbo_octopus;

export import :data;

// flashed octopuses have these constrains:
// (a) one flash per step
// (b) flash power ups neighbours
static constexpr char FLASHED = '0';

export namespace dumbo_octopus
{
	class Result : public AoC::Result
	{

	public:
		Result( );

		virtual void Init( ) override;
		virtual bool ProcessGeneral( const AoC::DataPtr& data ) override;
		virtual uint64_t FinishMutate( ) override;
		virtual void Teardown( ) override;

	private:

		//shared section
		size_t                   m_width;
		std::vector<std::string> m_cavernMap;
		uint64_t                 m_totalFlashes;

		void Iterate( );
		bool Step( size_t row, size_t column, bool skipFlashed = false );
		uint32_t TestFlash( size_t row, size_t column );

		//part one section
		virtual uint64_t FinishPartOne( );

		//part two section
		virtual uint64_t FinishPartTwo( );
	};
}

using namespace dumbo_octopus;

Result::Result( )
{
}

void
Result::Init( )
{
	m_data.reset( new dumbo_octopus::Data( ) );
	m_haveDedicatedProcessing = false;
	m_totalFlashes = 0;
}

void
Result::Teardown( )
{
	m_data.reset( );
	m_cavernMap.clear( );
}

bool
Result::ProcessGeneral( const AoC::DataPtr& data )
{
	m_cavernMap.push_back( std::move( static_cast< dumbo_octopus::Data* >( data.get( ) )->m_data ) );
	m_width = m_cavernMap[ 0 ].length( );
	return true;//drop data, we used all
}

uint64_t
Result::FinishMutate( )
{
	const uint64_t result = IsPartOne( ) ? FinishPartOne( ) : FinishPartTwo( );
	std::cout
		<< "result = "
		<< result
		<< std::endl;

	return result;
}

uint64_t
Result::FinishPartOne( )
{
	for( int step = 0; step != 100; ++step )
		Iterate( );

	return m_totalFlashes;
}

void
Result::Iterate( )
{
	typedef std::pair<size_t, size_t> Position;

	std::vector<Position> flashed;

	//two stages for each step
	// increase location value for each position
	// test flash and each flashed location propagate around - make sure to flash once each step
	for( size_t row = 0; row != m_cavernMap.size( ); ++row )
	{
		for( size_t column = 0; column != m_width; ++column )
			if( Step( row, column ) )
				flashed.push_back( { row, column } );
	}

	if( false == flashed.empty( ) )
	{
		for( auto position : flashed )
			m_totalFlashes += TestFlash( position.first, position.second );
	}
}

bool
Result::Step( size_t row, size_t column, bool skipFlashed /*= false*/ )
{
	// make sure contrain (a) holds
	if( skipFlashed && m_cavernMap[ row ][ column ] == FLASHED )
		return false;
	return ++m_cavernMap[ row ][ column ] > '9';
}

uint32_t
Result::TestFlash( size_t row, size_t column )
{
	uint32_t totalFlashes = 0;
	if( m_cavernMap[ row ][ column ] > '9' )
	{
		m_cavernMap[ row ][ column ] = FLASHED;

		++totalFlashes;

		// (b) propagate to all neighbours - make sure we don't underflow or overflow position
		for( size_t testRow = ( row > 0 ? row - 1 : 0 ); testRow < std::min( row + 2, m_cavernMap.size( ) ); ++testRow )
		{
			for( size_t testColumn = ( column > 0 ? column - 1 : 0 ); testColumn < std::min( column + 2, m_width ); ++testColumn )
			{
				if( testRow == row && testColumn == column )
					continue;

				if( Step( testRow, testColumn, true ) )
					totalFlashes += TestFlash( testRow, testColumn );
			}
		}
	}

	return totalFlashes;
}

uint64_t
Result::FinishPartTwo( )
{
	const size_t allFlashed = m_width * m_cavernMap.size( );
	for( size_t step = 0; ; ++step )
	{
		m_totalFlashes = 0;
		Iterate( );
		if( m_totalFlashes == allFlashed )
			return step + 1;
	}
}