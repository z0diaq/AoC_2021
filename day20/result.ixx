module;

#include <string>
#include <unordered_set>
#include <array>

export module trench_map;

import AoC;

export namespace trench_map
{
	struct PairHash
	{
		std::size_t operator()( const std::pair<int, int>& _pair ) const
		{
			return std::hash<int>{}( _pair.first ) ^ ( std::hash<int>{}( _pair.second ) << 1 );
		}
	};

	using Pixel = std::pair<int, int>;
	using LitPixelsSet = std::unordered_set<Pixel, PairHash>;
	using Bounds = std::array<int, 4>;

	constexpr size_t MIN_X{ 0 };
	constexpr size_t MAX_X{ 1 };
	constexpr size_t MIN_Y{ 2 };
	constexpr size_t MAX_Y{ 3 };


	class Result : public AoC::Result
	{

	protected:
		virtual void Init() override;

		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override;

		virtual void Teardown() override;

	private:
		//data
		std::string m_enhanceAlgorithm;
		LitPixelsSet m_litPixelsSet;
		Bounds m_bounds;

		// temp during processing;
		bool m_inImage;
		int m_scanLineNumber;

		
	};
}
