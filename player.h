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
		void build_children(node*, bool);
		double min_val(node*, double, double, int, double);
		double max_val(node*, double, double, int, double);
		int minimax_decision(node*, double, double, int, int, double);
		int ids_pruning(int, node*, double, int);
		node* get_child(node*, int, int);
};