#include <bits/stdc++.h>
#include "node.h"

using namespace std;

class player
{
	public:
		game_state* current_state;
		double remaining_time;

	public:
		player(int, int, int, double);
		node* tree_build(int, bool, game_state*);
};