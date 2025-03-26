export module amphipod:solver;

import :types;
import :state;

import <optional>;
import <queue>;
import <unordered_map>;
import <functional>;
import <algorithm>;
import <stdexcept>;

export namespace amphipod
{
	// Dijkstra algorithm
	template <typename StateType>
	std::optional<int>
		SolveWithDijkstra( const StateType& _initialState )
	{
		std::priority_queue<StateType> queue;
		std::unordered_map<StateType, std::uint32_t> visited;

		queue.push( _initialState );
		visited[ _initialState ] = _initialState.m_usedEnergy;

		while( !queue.empty( ) )
		{
			StateType currentState = queue.top( );
			queue.pop( );

			auto it = visited.find( currentState );
			if( it != visited.end( ) && it->second < currentState.m_usedEnergy )
				continue;

			if( currentState.IsSolved( ) )
				return currentState.m_usedEnergy;

			auto nextStates = currentState.GenerateMoves( );

			for( const auto& nextState : nextStates )
			{
				auto it = visited.find( nextState );

				// If we haven't visited this state or found a better path, update it
				if( it == visited.end( ) || nextState.m_usedEnergy < it->second )
				{
					visited[ nextState ] = nextState.m_usedEnergy;
					queue.push( nextState );
				}
			}
		}

		return std::nullopt; // No solution found

	}
}
