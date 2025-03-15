import reactor_reboot;

//leave what is needed
#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>

//containers
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <array>

//boost
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/replace.hpp>

using namespace reactor_reboot;

void
Result::ProcessTwo(const std::string& _data)
{
	ProcessOne( _data );
}

std::string
Result::FinishPartTwo()
{
	return std::to_string(0);
}