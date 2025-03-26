export module amphipod:result;

import :types;
import :state;
import :solver;

import AoC;

import <string>;
import <vector>;
import <iostream>;

export namespace amphipod {

	/**
	 * @brief Main result class that handles input processing and solution generation
	 */
	class Result : public AoC::Result {
	public:
		Result( ) = default;

	protected:
		void Init( ) override { }

		void ProcessOne( const std::string& data ) override {
			m_map.push_back( data );
		}

		std::string FinishPartOne( ) override {
			if( m_map.size( ) != 5 )
				return 0;

			StateT<2> initialState;
			// 1st room
			initialState.m_rooms[ Room1 ][ 0 ] = GetAmphipod( 2, 3, m_map );
			initialState.m_rooms[ Room1 ][ 1 ] = GetAmphipod( 3, 3, m_map );

			// 2nd room
			initialState.m_rooms[ Room2 ][ 0 ] = GetAmphipod( 2, 5, m_map );
			initialState.m_rooms[ Room2 ][ 1 ] = GetAmphipod( 3, 5, m_map );

			// 3rd room
			initialState.m_rooms[ Room3 ][ 0 ] = GetAmphipod( 2, 7, m_map );
			initialState.m_rooms[ Room3 ][ 1 ] = GetAmphipod( 3, 7, m_map );

			// 4th room
			initialState.m_rooms[ Room4 ][ 0 ] = GetAmphipod( 2, 9, m_map );
			initialState.m_rooms[ Room4 ][ 1 ] = GetAmphipod( 3, 9, m_map );

			auto result = SolveWithDijkstra( initialState );

			if( result )
				return std::to_string( *result );
			else
			{
				std::cerr << "No solution found!" << std::endl;
				return std::to_string( 0 );
			}
		}

		void ProcessTwo( const std::string& data ) override {
			// Part 2 uses the same input as part 1
			ProcessOne( data );
		}

		std::string FinishPartTwo( ) override {
			// Insert the extra lines for part 2
			std::vector<std::string> extraLines = { "  #D#C#B#A#", "  #D#B#A#C#" };
			m_map.insert( m_map.begin( ) + 3, extraLines.begin( ), extraLines.end( ) );

			if( m_map.size( ) != 7 )
				return std::to_string( 0 );

			StateT<4> initialState;
			// Initialize hallway as empty
			std::fill( initialState.m_hallway.begin( ), initialState.m_hallway.end( ), std::nullopt );

			// 1st room
			initialState.m_rooms[ Room1 ][ 0 ] = GetAmphipod( 2, 3, m_map );
			initialState.m_rooms[ Room1 ][ 1 ] = GetAmphipod( 3, 3, m_map );
			initialState.m_rooms[ Room1 ][ 2 ] = GetAmphipod( 4, 3, m_map );
			initialState.m_rooms[ Room1 ][ 3 ] = GetAmphipod( 5, 3, m_map );

			// 2nd room
			initialState.m_rooms[ Room2 ][ 0 ] = GetAmphipod( 2, 5, m_map );
			initialState.m_rooms[ Room2 ][ 1 ] = GetAmphipod( 3, 5, m_map );
			initialState.m_rooms[ Room2 ][ 2 ] = GetAmphipod( 4, 5, m_map );
			initialState.m_rooms[ Room2 ][ 3 ] = GetAmphipod( 5, 5, m_map );

			// 3rd room
			initialState.m_rooms[ Room3 ][ 0 ] = GetAmphipod( 2, 7, m_map );
			initialState.m_rooms[ Room3 ][ 1 ] = GetAmphipod( 3, 7, m_map );
			initialState.m_rooms[ Room3 ][ 2 ] = GetAmphipod( 4, 7, m_map );
			initialState.m_rooms[ Room3 ][ 3 ] = GetAmphipod( 5, 7, m_map );

			// 4th room
			initialState.m_rooms[ Room4 ][ 0 ] = GetAmphipod( 2, 9, m_map );
			initialState.m_rooms[ Room4 ][ 1 ] = GetAmphipod( 3, 9, m_map );
			initialState.m_rooms[ Room4 ][ 2 ] = GetAmphipod( 4, 9, m_map );
			initialState.m_rooms[ Room4 ][ 3 ] = GetAmphipod( 5, 9, m_map );

			auto result = SolveWithDijkstra( initialState );

			if( result )
				return std::to_string( *result );
			else
			{
				std::cerr << "No solution found!" << std::endl;
				return std::to_string( 0 );
			}
		}

		void Teardown( ) override
		{
			m_map.clear( );
		}

		Amphipod GetAmphipod( size_t _row, size_t _column, const Map& _map )
		{
			if( _row >= _map.size( ) )
			{
				std::cerr << "Requested row " << _row << " but map has only " << _map.size( ) << " rows" << std::endl;
				throw std::runtime_error( "Invalid row index" );
			}

			const auto& row = _map[ _row ];

			if( _column >= row.length( ) )
			{
				std::cerr << "Requested column " << _column << " but row " << _row << " has only " << row.length( ) << " columns" << std::endl;
				throw std::runtime_error( "Invalid column index" );
			}

			char c = row[ _column ];
			if( c < 'A' || c > 'D' )
			{
				std::cerr << "[" << c << "] from line [" << row << "] at (" << _column << ", " << _row << ") is not a valid Amphipod (A-D)" << std::endl;
				throw std::runtime_error( "Not a valid amphipod" );
			}

			return static_cast< Amphipod >( c - 'A' );
		}

	private:
		Map m_map;  // Stores the input map
	};

}
