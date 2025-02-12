import trick_shot;

#include <gtest/gtest.h>

using trick_shot::FindMaxHeight;
using trick_shot::TargetArea;

TEST( FindMaxHeight, UseTrainingData )
{
	auto [maxHeight, validResultsCount] = FindMaxHeight( TargetArea( 20, 30, -10, -5 ) );
	EXPECT_EQ( maxHeight, 45 );
	EXPECT_EQ( validResultsCount, 112 );
}

