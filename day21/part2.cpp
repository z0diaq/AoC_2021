import dirac_dice;

#include <string>
#include <unordered_map>

#include "gameState.h"

using namespace dirac_dice;

void
Result::ProcessTwo(const std::string& _data)
{
	ProcessOne( _data );
}

using Memoization = std::unordered_map<GameState, Wins>;

const Wins&
CountWinsRecursive( const GameState& _state, Memoization& _memo );

std::string
Result::FinishPartTwo()
{
	Memoization memoization;
	GameState initialState( m_players[ 0 ], m_players[ 1 ], true );
	const auto [player1Wins, player2Wins] = CountWinsRecursive( initialState, memoization );
	return std::to_string( std::max( player1Wins, player2Wins ) );
}

const Wins&
CountWinsRecursive( const GameState& _state, Memoization& _memo )
{
	{
		auto exists{ _memo.find( _state ) };
		if( exists != _memo.end( ) )
			return exists->second;
	}

	auto gameOver{ _state.IsGameOver( ) };
	if( gameOver )
		return gameOver.value( );

	static const std::vector<std::pair<int, int>>
	diceRollSums = {
		{3, 1},  // 1+1+1
		{4, 3},  // 1+1+2, 1+2+1, 2+1+1
		{5, 6},  // 1+1+3, 1+3+1, 3+1+1, 1+2+2, 2+1+2, 2+2+1
		{6, 7},  // 2+2+2, 1+2+3, 1+3+2, 2+1+3, 2+3+1, 3+1+2, 3+2+1
		{7, 6},  // 2+2+3, 2+3+2, 3+2+2, 1+3+3, 3+1+3, 3+3+1
		{8, 3},  // 2+3+3, 3+2+3, 3+3+2
		{9, 1}   // 3+3+3
	};

	std::uint64_t player1Wins = 0;
	std::uint64_t player2Wins = 0;

	for( const auto& [sum, frequency] : diceRollSums ) {
		// Create new game state after this move
		GameState newState = _state.ApplyMove( sum );

		// Recursively calculate wins from the new state
		auto [wins1, wins2] = CountWinsRecursive( newState, _memo );

		// Add to total wins, multiplied by the frequency of this dice roll
		player1Wins += wins1 * frequency;
		player2Wins += wins2 * frequency;
	}

	// Store result in cache and return that element (avoids UB as we return ref)
	auto insertResult = _memo.insert( { _state, Wins{ player1Wins, player2Wins } } );
	return insertResult.first->second;
}
