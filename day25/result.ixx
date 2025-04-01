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
		bool m_changed{};
	};

	class Result : public AoC::Result
	{
		friend class tests::SeaCucumberFixture;

	public:
		Result( )
		{
		}

		const SeafloorMap&
		InitialMap( ) const
		{
			return m_initialSeafloorMap;
		}

		IterationState
		Step( IterationState _state )
		{
			// Move east-facing cucumbers (>)
			auto [afterEast, changed] = MoveEastOnly( _state.m_currentMap, false);

			// Move south-facing cucumbers (v)
			auto [afterSouth, changedFinal] = MoveSouthOnly( afterEast, changed );

			return { afterSouth, _state.m_iterationNumber + 1, changedFinal };
		}

		std::pair<SeafloorMap, bool>
		MoveEastOnly( const SeafloorMap& _map, bool _changed ) const
		{
			auto newMap = _map;
			const size_t width = _map[ 0 ].size( );

			for( size_t rowIdx = 0; rowIdx < _map.size( ); ++rowIdx )
			{
				const auto& row = _map[ rowIdx ];

				std::vector<size_t> movableCucumbers;

				for( size_t colIdx = 0; colIdx < width; ++colIdx )
				{
					if( row[ colIdx ] == SeaCucumber::FacingEast )
					{
						size_t nextCol = ( colIdx + 1 ) % width;

						if( row[ nextCol ] == SeaCucumber::None )
							movableCucumbers.push_back( colIdx );
					}
				}

				for( const auto& colIdx : movableCucumbers )
				{
					size_t nextCol = ( colIdx + 1 ) % width;

					newMap[ rowIdx ][ colIdx ] = SeaCucumber::None;
					newMap[ rowIdx ][ nextCol ] = SeaCucumber::FacingEast;

					_changed = true;
				}
			}

			return { newMap, _changed };
		}

		std::pair<SeafloorMap, bool>
		MoveSouthOnly( const SeafloorMap& _map, bool _changed ) const
		{
			// Create a copy that we'll modify
			auto newMap = _map;
			const size_t height = _map.size( );
			const size_t width = _map[ 0 ].size( );

			std::vector<std::pair<size_t, size_t>> movableCucumbers;

			for( size_t rowIdx = 0; rowIdx < height; ++rowIdx )
			{
				const auto& row = _map[ rowIdx ];

				for( size_t colIdx = 0; colIdx < width; ++colIdx )
				{
					if( row[ colIdx ] == SeaCucumber::FacingSouth )
					{
						size_t nextRow = ( rowIdx + 1 ) % height;

						if( _map[ nextRow ][ colIdx ] == SeaCucumber::None )
							movableCucumbers.emplace_back( rowIdx, colIdx );
					}
				}
			}

			// Apply all movements for south-facing cucumbers
			for( const auto& [rowIdx, colIdx] : movableCucumbers )
			{
				size_t nextRow = ( rowIdx + 1 ) % height;

				newMap[ rowIdx ][ colIdx ] = SeaCucumber::None;
				newMap[ nextRow ][ colIdx ] = SeaCucumber::FacingSouth;

				_changed = true;
			}

			return { newMap, _changed };
		}

	protected:

		virtual void
		Init( ) override
		{
		}

		virtual void
		ProcessOne( const std::string& data ) override;

		virtual std::string
		FinishPartOne( ) override;

		virtual void
		ProcessTwo( const std::string& data ) override;

		virtual std::string
		FinishPartTwo( ) override;

		virtual void
		Teardown( ) override
		{
			m_initialSeafloorMap.clear( );
		}

	private:
		//data
		SeafloorMap m_initialSeafloorMap;
	};
}
