export module sea_cucumber:types;

import <vector>;

export namespace sea_cucumber
{
	//module wide types go here
	enum class SeaCucumber { None, FacingEast, FacingSouth };

	using SeafloorRow = std::vector<SeaCucumber>;
	using SeafloorMap = std::vector<SeafloorRow>;
}
