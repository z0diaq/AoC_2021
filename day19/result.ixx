module;

#include <string>

export module beacon_scanner;

export import :point;
export import :scanner;

import AoC;

export namespace beacon_scanner
{
	class Result : public AoC::Result
	{
	protected:
		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override;

		virtual void Teardown() override;

	private:
		//data
		std::vector<Scanner> m_scanners;

		std::pair<size_t, std::vector<Point>>
		CountUniqueBeaconsWithScannerPositions( ) const;
	};
}
