export module alu:types;

import <stack>;
import <map>;
//import <pair>;

export namespace alu
{
	//module wide types go here
	using Range = std::pair<int, int>;
	using DigitsMap = std::map<int, Range>; // maps digit position to (min, max) values
	using DigitsStack = std::stack<std::pair<int, int>>;// for storing paired digits and values

}
