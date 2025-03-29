export module alu:solver;

import :result;
import :types;

import <string>;
import <sstream>;

using namespace alu;

// based on very neat Python solution from EliteTK
// https://www.reddit.com/r/adventofcode/comments/rnejv5/comment/hpv7g7j/

DigitsMap
Result::ExtractDigitsMap( )
{
	DigitsMap digits;
	DigitsStack stack;

	int currentDigitPosition = 0;
	int lineNumber = 0;

	bool push = false;
	int sub = 0;

	for( const std::string& line : m_instructions )
	{
		std::string op, operand1, operand2;

		std::istringstream iss( line );
		iss >> op;
		if( iss >> operand1 )
			iss >> operand2;

		// is this is a "div z" instruction at position 4 in the block
		if( lineNumber % 18 == 4 )
			push = ( operand2 == "1" );

		// is this is an "add x" instruction at position 5 in the block
		if( lineNumber % 18 == 5 )
			sub = std::stoi( operand2 );

		// is this is an "add y" instruction at position 15 in the block
		if( lineNumber % 18 == 15 )
		{
			int add = std::stoi( operand2 );

			if( push )
			{
				// Push operation: store current digit and value
				stack.push( { currentDigitPosition, add } );
			}
			else
			{
				// Pop operation: calculate constraint between current and previous digit
				auto [sibling, add_val] = stack.top( );
				stack.pop( );

				int diff = add_val + sub;

				if( diff < 0 )
				{
					// For maximizing: previous digit = min possible, current digit = max possible
					digits[ sibling ] = { -diff + 1, 9 };
					digits[ currentDigitPosition ] = { 1, 9 + diff };
				}
				else
				{
					// For maximizing: previous digit = max possible, current digit = match constraint
					digits[ sibling ] = { 1, 9 - diff };
					digits[ currentDigitPosition ] = { 1 + diff, 9 };
				}
			}

			// Move to next digit
			currentDigitPosition++;
		}

		lineNumber++;
	}

	return digits;
}
