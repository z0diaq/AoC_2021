import snailfish;

#include <gtest/gtest.h>

TEST( Node, Parse12 )
{
	auto root{ snailfish::Parse( "[1,2]" ) };
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
	auto root{ snailfish::Parse( "[[1,2],3]" ) };
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
	auto root{ snailfish::Parse( sourceText ) };
	auto formatted{ snailfish::Format( root.get( ) ) };
	ASSERT_EQ( sourceText, formatted );
}

namespace {
	std::string Normalize( std::string text );
};

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

class ExplodeOperationTest : public ::testing::TestWithParam<ExplodeOperationParams> {
protected:
};

TEST_P( ExplodeOperationTest, VerifyExplodeOperation ) {
	const auto& params = GetParam( );

	auto root{ snailfish::Parse( params.m_input ) };

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

TEST( Reduce, MultipleTimes )
{
	auto root{ snailfish::Parse( "[[[[[4,3],4],4],[7,[[8,4],9]]],[1,1]]" ) };

	snailfish::Reduce( root, true );
	std::string afterReduce{ snailfish::Format( root.get( ) ) };
	ASSERT_EQ( afterReduce, "[[[[0,7],4],[7,[[8,4],9]]],[1,1]]" );

	snailfish::Reduce( root, true );
	afterReduce = snailfish::Format( root.get( ) );
	ASSERT_EQ( afterReduce, "[[[[0,7],4],[15,[0,13]]],[1,1]]" );

	snailfish::Reduce( root, true );
	afterReduce = snailfish::Format( root.get( ) );
	ASSERT_EQ( afterReduce, "[[[[0,7],4],[[7,8],[0,13]]],[1,1]]" );

	snailfish::Reduce( root, true );
	afterReduce = snailfish::Format( root.get( ) );
	ASSERT_EQ( afterReduce, "[[[[0,7],4],[[7,8],[0,[6,7]]]],[1,1]]" );

	snailfish::Reduce( root, true );
	afterReduce = snailfish::Format( root.get( ) );
	ASSERT_EQ( afterReduce, "[[[[0,7],4],[[7,8],[6,0]]],[8,1]]" );
}

TEST( Reduce, Example1 )
{
	auto root{ snailfish::Parse( "[[[[1,1],[2,2]],[3,3]],[4,4]]" ) };

	snailfish::Reduce( root );
	std::string afterReduce{ snailfish::Format( root.get( ) ) };
	ASSERT_EQ( afterReduce, "[[[[1,1],[2,2]],[3,3]],[4,4]]" );
}

TEST( Reduce, Example2 )
{
	auto root{ snailfish::Parse( "[[[[[1,1],[2,2]],[3,3]],[4,4]],[5,5]]" ) };

	snailfish::Reduce( root );
	std::string afterReduce{ snailfish::Format( root.get( ) ) };
	ASSERT_EQ( afterReduce, "[[[[3,0],[5,3]],[4,4]],[5,5]]" );
}

TEST( Magnitude, Example1 )
{
	auto root{ snailfish::Parse( "[[1,2],[[3,4],5]]" ) };
	ASSERT_EQ( snailfish::Magnitude( root ), 143 );
}

TEST( Magnitude, Example2 )
{
	auto root{ snailfish::Parse( "[[[[0,7],4],[[7,8],[6,0]]],[8,1]]" ) };
	ASSERT_EQ( snailfish::Magnitude( root ), 1384 );
}

TEST( Magnitude, Example3 )
{
	auto root{ snailfish::Parse( "[[[[1,1],[2,2]],[3,3]],[4,4]]" ) };
	ASSERT_EQ( snailfish::Magnitude( root ), 445 );
}

TEST( Magnitude, Example4 )
{
	auto root{ snailfish::Parse( "[[[[3,0],[5,3]],[4,4]],[5,5]]" ) };
	ASSERT_EQ( snailfish::Magnitude( root ), 791 );
}

TEST( Magnitude, Example5 )
{
	auto root{ snailfish::Parse( "[[[[5,0],[7,4]],[5,5]],[6,6]]" ) };
	ASSERT_EQ( snailfish::Magnitude( root ), 1137 );
}

TEST( Magnitude, Example6 )
{
	auto root{ snailfish::Parse( "[[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]" ) };
	ASSERT_EQ( snailfish::Magnitude( root ), 3488 );
}

TEST( Magnitude, Example7 )
{
	auto root{ snailfish::Parse( "[[[[6,6],[7,6]],[[7,7],[7,0]]],[[[7,7],[7,7]],[[7,8],[9,9]]]]" ) };
	ASSERT_EQ( snailfish::Magnitude( root ), 4140 );
}

TEST( Add, Example1 )
{
	auto root{ snailfish::Parse( "[1,1]" ) };
	root = snailfish::Add( std::move( root ), snailfish::Parse( "[2,2]" ) );
	root = snailfish::Add( std::move( root ), snailfish::Parse( "[3,3]" ) );
	root = snailfish::Add( std::move( root ), snailfish::Parse( "[4,4]" ) );

	auto result{ snailfish::Format( root.get( ) ) };
	ASSERT_EQ( result, std::string( "[[[[1,1],[2,2]],[3,3]],[4,4]]" ) );
}

TEST( Add, Example2 )
{
	auto root{ snailfish::Parse( "[1,1]" ) };
	root = snailfish::Add( std::move( root ), snailfish::Parse( "[2,2]" ) );
	root = snailfish::Add( std::move( root ), snailfish::Parse( "[3,3]" ) );
	root = snailfish::Add( std::move( root ), snailfish::Parse( "[4,4]" ) );
	root = snailfish::Add( std::move( root ), snailfish::Parse( "[5,5]" ) );

	auto result{ snailfish::Format( root.get( ) ) };
	ASSERT_EQ( result, std::string( "[[[[3,0],[5,3]],[4,4]],[5,5]]" ) );
}

TEST( Add, Example3 )
{
	auto root{ snailfish::Parse( "[1,1]" ) };
	root = snailfish::Add( std::move( root ), snailfish::Parse( "[2,2]" ) );
	root = snailfish::Add( std::move( root ), snailfish::Parse( "[3,3]" ) );
	root = snailfish::Add( std::move( root ), snailfish::Parse( "[4,4]" ) );
	root = snailfish::Add( std::move( root ), snailfish::Parse( "[5,5]" ) );
	root = snailfish::Add( std::move( root ), snailfish::Parse( "[6,6]" ) );

	auto result{ snailfish::Format( root.get( ) ) };
	ASSERT_EQ( result, std::string( "[[[[5,0],[7,4]],[5,5]],[6,6]]" ) );
}
