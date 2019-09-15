#include "game_state.h"

using namespace std;

class node
{
	public:
		double eval_value;
		int id;
		game_state* current_state;
		vector<node*> children;
		node(game_state* g);
		~node();
		//void delete_tree();
};
