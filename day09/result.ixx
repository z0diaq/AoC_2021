module;

#include <deque>

export module smoke;

export import :data;
export import :partTwoSolver;

export namespace smoke
{
	class Result : public AoC::Result
	{
	public:
		Result( );

		virtual void Init( ) override;
		virtual bool ProcessGeneral( const AoC::DataPtr& data ) override;
		virtual uint64_t Finish( ) const override;
		virtual void Teardown( ) override;
		uint8_t Value( const Point& point ) const;
		uint32_t Width( ) const;
		uint32_t Height( ) const;

	private:
		std::deque<Data::DataLine> m_heightmap;

		bool IsLowPoint( const Point& point ) const;

		//stage one only
		uint32_t RiskLevel( const Point& point ) const;
	};
}
