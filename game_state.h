#include <bits/stdc++.h>
#include "soldier.h"
#include "Move.h"

using namespace std;

class game_state
{
	public:
		int id;
		int X;
		int Y;
		vector<soldier> soldiers;
		vector<soldier> enemy_soldiers;
		///Cannon orientation - 2nd parameter of pair
		//vertical -> 0
		//positive diagonal -> 1
		//horizontal -> 2
		//negative diagonal -> 3
		vector<pair<soldier, int> > cannons;
		vector<pair<soldier, int> > enemy_cannons;
		vector<pair<int, int> > townhalls;
		vector<pair<int, int> > enemy_townhalls;
		vector<vector<short> > board;

	public:
		//functions
		//game_state(int, int, int, double);
		vector<int> find_Cannon(int, int, bool);
		vector< pair<soldier, int> > find_new_Cannon(int, int, bool);
		int find_soldier(int, int, bool);
		int find_townhall(int, int, bool);
		void change_state(int, int, int, int, bool, bool);
		game_state(int, int, int);
		void remove_cannons (int, int, bool);
		void add_cannons(int, int, bool);
		game_state(game_state* g);
		double evaluation_function(bool enemy);
		vector<pair<int,game_state*> > possible_states(bool);
		vector<Move> possible_moves(bool);
		bool find_soldier_grid(int , int , bool );
		bool find_townhall_grid(int , int , bool );
		double mob(bool enemy);
};
