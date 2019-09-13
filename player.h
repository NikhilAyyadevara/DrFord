#include <bits/stdc++.h>
#include "game_state.h"
#include "Move.h"

using namespace std;

class player
{
	public:
		game_state* current_state;
		double remaining_time;

	public:
		player(int, int, int, double);
		double evaluation_function();
		vector<game_state> possible_states(bool);
		vector<Move> possible_moves(bool);

};