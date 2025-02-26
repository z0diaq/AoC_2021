#include <gtest/gtest.h>
#include <optional>

import beacon_scanner;

using namespace beacon_scanner;

extern std::optional<std::pair<Point, std::vector<Point>>>
FindMatch( const Scanner& m_scanner1, const Scanner& m_scanner2, const size_t requiredMatches );

class MatchingTest : public ::testing::Test
{
protected:
	void SetUp( ) override
	{
		// Create two scanners with overlapping points
		// Scanner 1 at origin (0,0,0)
        // Create scanner1 at origin (0,0,0)
        m_scanner1.AddPoint( Point{ {0, 2, 0} } );
        m_scanner1.AddPoint( Point{ {4, 1, 0} } );
        m_scanner1.AddPoint( Point{ {3, 3, 0} } );
        m_scanner1.AddPoint( Point{ {-1, -1, 0} } );
        m_scanner1.AddPoint( Point{ {-5, 0, 0} } );
        m_scanner1.AddPoint( Point{ {-2, 1, 0} } );
        m_scanner1.AddPoint( Point{ {0, 0, 0} } );
        m_scanner1.AddPoint( Point{ {-2, -2, 0} } );
        m_scanner1.AddPoint( Point{ {2, -2, 0} } );
        m_scanner1.AddPoint( Point{ {-2, -4, 0} } );
        m_scanner1.AddPoint( Point{ {-1, 1, 0} } );
        m_scanner1.AddPoint( Point{ {1, 1, 0} } );

        // Scanner 2 at position (5,0,0) and rotated 180 degrees around Z-axis
        // Applying the transformation: (x,y,z) -> (-x+5,-y,z)
        // All points actually map to scanner1 points
        m_scanner2.AddPoint( Point{ {-5, 0, 0} } );     // (0,0,0) in scanner1 coords
        m_scanner2.AddPoint( Point{ {-9, -1, 0} } );    // (4,1,0) in scanner1 coords
        m_scanner2.AddPoint( Point{ {-8, -3, 0} } );    // (3,3,0) in scanner1 coords
        m_scanner2.AddPoint( Point{ {-6, 1, 0} } );     // (1,1,0) in scanner1 coords
        m_scanner2.AddPoint( Point{ {-7, 2, 0} } );     // (2,-2,0) in scanner1 coords
        m_scanner2.AddPoint( Point{ {-4, -1, 0} } );    // (-1,1,0) in scanner1 coords
        m_scanner2.AddPoint( Point{ {-10, 0, 0} } );    // (-5,0,0) in scanner1 coords
        m_scanner2.AddPoint( Point{ {-5, -2, 0} } );    // (0,2,0) in scanner1 coords
        // Adding a few more to match scanner1
        m_scanner2.AddPoint( Point{ {-3, -2, 0} } );    // (-2,2,0) in scanner1 coords
        m_scanner2.AddPoint( Point{ {-3, 4, 0} } );     // (-2,-4,0) in scanner1 coords
        m_scanner2.AddPoint( Point{ {-7, -1, 0} } );    // (2,1,0) in scanner1 coords
        m_scanner2.AddPoint( Point{ {-6, -1, 0} } );    // (1,1,0) in scanner1 coords
	}

	Scanner m_scanner1;
	Scanner m_scanner2;
};

TEST_F( MatchingTest, FindMatchWithStandardRequirement )
{
	// Should find a match with default requirement (12), but our test data has only 8 matching points
	auto match = FindMatch( m_scanner1, m_scanner2, 8 );

	ASSERT_TRUE( match.has_value( ) );

	// Check the scanner position is correctly identified
	EXPECT_EQ( match->first, ( Point{ {5, 0, 0} } ) );

	// Scanner2 has unique points so vector can't be empty
	EXPECT_FALSE( match->second.empty( ) );
}

TEST_F( MatchingTest, FindMatchNoMatch )
{
	// Create a scanner with no overlap
	Scanner noOverlapScanner;
	noOverlapScanner.AddPoint( Point{ {100, 100, 100} } );
	noOverlapScanner.AddPoint( Point{ {101, 101, 101} } );
	noOverlapScanner.AddPoint( Point{ {102, 102, 102} } );

	auto match = FindMatch( m_scanner1, noOverlapScanner, 3 );

	EXPECT_FALSE( match.has_value( ) );
}

TEST_F( MatchingTest, FindMatchHigherRequirement )
{
	// With a requirement of more than available matching points (8), it should fail
	auto match = FindMatch( m_scanner1, m_scanner2, 9 );

	EXPECT_FALSE( match.has_value( ) );
}
