module;

#include <string>
#include <list>
#include <map>
#include <array>

export module extended_polymerization;

import AoC;

export namespace extended_polymerization
{
	using CharList = std::list<char>;//for simpler part 1 solution
	using CharPair = std::array<char, 2>;
	using PairInsertionRulesMap = std::map<CharPair, char>;

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
		CharList m_template;
		PairInsertionRulesMap m_pairInsertionRules;
	};
}
