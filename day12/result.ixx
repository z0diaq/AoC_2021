module;

#include <string>
#include <vector>
#include <map>

export module passage_pathing;

import AoC;

export namespace passage_pathing
{
	class Result : public AoC::Result
	{

	public:
		typedef std::vector<std::string> ConnectionList;

		void Process( const std::string& data );

		virtual void ProcessOne( const std::string& data ) override;
		virtual std::string FinishPartOne( ) override;

		virtual void ProcessTwo( const std::string& data ) override;
		virtual std::string FinishPartTwo( ) override;

		virtual void Teardown( ) override;

	private:
		std::map<std::string, ConnectionList > m_caveMap;

		std::vector<std::string>
		GetAllPaths(
			std::map<std::string, Result::ConnectionList> caveMap,
			std::string                                   currentPath,
			const std::string&                            startingPoint,
			bool                                          allowSecondVisit );
	};
}
