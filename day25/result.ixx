export module sea_cucumber:result;

import :types;

import AoC;

import <string>;

export namespace sea_cucumber
{
	struct IterationState
	{
		SeafloorMap m_currentMap;
		size_t m_iterationNumber{};
	};

	class Result : public AoC::Result
	{

	public:
		Result( )
		{
		}

		IterationState Step( IterationState _state );

		const SeafloorMap& InitialMap( ) const
		{
			return m_initialSeafloorMap;
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
