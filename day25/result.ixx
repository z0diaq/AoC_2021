export module sea_cucumber:result;

import :types;

import AoC;

import <string>;

export namespace sea_cucumber
{
	namespace tests
	{
		class SeaCucumberFixture;
	}
	struct IterationState
	{
		SeafloorMap m_currentMap;
		size_t m_iterationNumber{};
	};

	class Result : public AoC::Result
	{
		friend class tests::SeaCucumberFixture;

	public:
		Result( )
		{
		}

		IterationState Step( IterationState _state );

		const SeafloorMap& InitialMap( ) const
		{
			return m_initialSeafloorMap;
		}

		IterationState Step( IterationState _state )
		{
			bool hasMoved = false;
			// Move east-facing cucumbers (>)
			auto [afterEast, hasMoved] = MoveEastOnly( _state.m_currentMap, hasMoved);

			// Move south-facing cucumbers (v)
			auto afterSouth = MoveSouthOnly( afterEast );

			// Check if any movement happened
			bool hasMoved = !IsEqual( afterSouth, _state.m_currentMap );

			// Return the new state with updated iteration count
			return { afterSouth, _state.m_iterationNumber + 1 };
		}

		std::pair<SeafloorMap, bool>
		MoveEastOnly( const SeafloorMap& _map, bool _hasMoved ) const
		{
			// Create a copy that we'll modify
			auto newMap = _map;
			const size_t width = _map[ 0 ].size( );

			// For each row
			for( size_t rowIdx = 0; rowIdx < _map.size( ); ++rowIdx )
			{
				const auto& row = map[ rowIdx ];

				// Find all east-facing cucumbers that can move
				std::vector<size_t> movableCucumbers;

				for( size_t colIdx = 0; colIdx < width; ++colIdx )
				{
					// Check if this is an east-facing cucumber
					if( row[ colIdx ] == SeaCucumber::FacingEast )
					{
						// Calculate destination with wrapping
						size_t nextCol = ( colIdx + 1 ) % width;

						// Check if destination is empty
						if( row[ nextCol ] == SeaCucumber::None )
						{
							movableCucumbers.push_back( colIdx );
						}
					}
				}

				// Apply all movements for this row
				for( const auto& colIdx : movableCucumbers )
				{
					size_t nextCol = ( colIdx + 1 ) % width;

					// Move the cucumber
					newMap[ rowIdx ][ colIdx ] = SeaCucumber::None;
					newMap[ rowIdx ][ nextCol ] = SeaCucumber::FacingEast;
				}
			}

			return std::make_pair(newMap, _hasMoved);
		}

		SeafloorMap
		MoveSouthOnly( const SeafloorMap& map ) const
		{
			// Create a copy that we'll modify
			auto newMap = map;
			const size_t height = map.size( );
			const size_t width = map[ 0 ].size( );

			// Find all south-facing cucumbers that can move
			std::vector<std::pair<size_t, size_t>> movableCucumbers;

			for( size_t rowIdx = 0; rowIdx < height; ++rowIdx )
			{
				const auto& row = map[ rowIdx ];

				for( size_t colIdx = 0; colIdx < width; ++colIdx )
				{
					// Check if this is a south-facing cucumber
					if( row[ colIdx ] == SeaCucumber::FacingSouth )
					{
						// Calculate destination with wrapping
						size_t nextRow = ( rowIdx + 1 ) % height;

						// Check if destination is empty
						if( map[ nextRow ][ colIdx ] == SeaCucumber::None )
						{
							movableCucumbers.emplace_back( rowIdx, colIdx );
						}
					}
				}
			}

			// Apply all movements for south-facing cucumbers
			for( const auto& [rowIdx, colIdx] : movableCucumbers )
			{
				size_t nextRow = ( rowIdx + 1 ) % height;

				// Move the cucumber
				newMap[ rowIdx ][ colIdx ] = SeaCucumber::None;
				newMap[ nextRow ][ colIdx ] = SeaCucumber::FacingSouth;
			}

			return newMap;
		}

	protected:
		virtual void Init( ) override
		{
		}

		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override;

		virtual void Teardown( ) override
		{
			m_initialSeafloorMap.clear( );
		}

	private:
		//data
		SeafloorMap m_initialSeafloorMap;
	};
}
