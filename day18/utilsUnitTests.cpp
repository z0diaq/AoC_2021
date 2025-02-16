import snailfish;

#include <gtest/gtest.h>

TEST( Node, Parse12 )
{
	auto root{ snailfish::Parse( nullptr, "[1,2]" ) };
	ASSERT_TRUE( root );
	ASSERT_TRUE( root->m_left );
	ASSERT_TRUE( root->m_right );
	ASSERT_EQ( root->m_left->m_value, 1 );
	ASSERT_EQ( root->m_right->m_value, 2 );
	ASSERT_TRUE( root->m_left->IsLeaf( ) );
	ASSERT_TRUE( root->m_right->IsLeaf( ) );
}

TEST( Node, Parse123 )
{
	auto root{ snailfish::Parse( nullptr, "[[1,2],3]" ) };
	ASSERT_TRUE( root );
	ASSERT_TRUE( root->m_left );
	ASSERT_TRUE( root->m_right );
	ASSERT_EQ( root->m_left->m_value, 0 );
	ASSERT_EQ( root->m_right->m_value, 3 );
	ASSERT_FALSE( root->m_left->IsLeaf( ) );
	ASSERT_TRUE( root->m_right->IsLeaf( ) );

	auto& left = root->m_left;
	ASSERT_TRUE( left->m_left->IsLeaf( ) );
	ASSERT_EQ( left->m_left->m_value, 1 );
	ASSERT_EQ( left->m_right->m_value, 2 );
}




class ParseTest : public ::testing::TestWithParam<std::string> {
protected:
};

TEST_P( ParseTest, VerifyParse ) {
	const std::string sourceText{ GetParam( ) };
	auto root{ snailfish::Parse( nullptr, sourceText ) };
	auto formatted{ snailfish::Format( root.get( ) ) };
	ASSERT_EQ( sourceText, formatted );
}

namespace {
	std::string Normalize( std::string text );
};

// Instantiate the test suite with test cases
INSTANTIATE_TEST_SUITE_P(
	ParseTests,
	ParseTest,
	::testing::Values(
		std::string{ "[1,2]" },
		std::string{ "[[1,2],3]" },
		std::string{ "[9,[8,7]]" },
		std::string{ "[[1,9],[8,5]]" },
		std::string{ "[[[[1,2],[3,4]],[[5,6],[7,8]]],9]" },
		std::string{ "[[[9,[3,8]],[[0,9],6]],[[[3,7],[4,9]],3]]" },
		std::string{ "[[[[1,3],[5,3]],[[1,3],[8,7]]],[[[4,9],[6,9]],[[8,2],[7,3]]]]" }
	),
[ ]( const testing::TestParamInfo<std::string>& info ) {
		return "Verify_" + Normalize( info.param );
	}
);

namespace
{
	std::string Normalize( std::string text )
	{
		for( char& c : text )
		{
			if( c == '[' ) c = 'C';
			if( c == ']' ) c = 'D';
			if( c == ',' ) c = '_';
		}

		return text;
	}
}


struct ExplodeOperationParams {
	std::string m_input;
	std::string m_expectedOutput;
};

// Create a test fixture that inherits from TestWithParam
class ExplodeOperationTest : public ::testing::TestWithParam<ExplodeOperationParams> {
protected:
};


TEST_P( ExplodeOperationTest, VerifyExplodeOperation ) {
	const auto& params = GetParam( );

	auto root{ snailfish::Parse( nullptr, params.m_input ) };

	const bool result{ Explode( root ) };
	ASSERT_TRUE( result );
	std::string afterExplode{ snailfish::Format( root.get( ) ) };
	ASSERT_EQ( afterExplode, params.m_expectedOutput );
}

INSTANTIATE_TEST_SUITE_P(
	ExplodeOperations,
	ExplodeOperationTest,
	::testing::Values(
		ExplodeOperationParams{ "[[[[[9,8],1],2],3],4]", "[[[[0,9],2],3],4]" },
		ExplodeOperationParams{ "[7,[6,[5,[4,[3,2]]]]]", "[7,[6,[5,[7,0]]]]" },
		ExplodeOperationParams{ "[[6,[5,[4,[3,2]]]],1]", "[[6,[5,[7,0]]],3]" },
		ExplodeOperationParams{ "[[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]]", "[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]" },
		ExplodeOperationParams{ "[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]", "[[3,[2,[8,0]]],[9,[5,[7,0]]]]" }
),
[ ]( const testing::TestParamInfo<ExplodeOperationParams>& info ) {
		return Normalize( info.param.m_input ) + "_to_" + Normalize( info.param.m_expectedOutput );
	}
);

