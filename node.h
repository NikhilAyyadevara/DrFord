#include "game_state.h"

using namespace std;

class node
{
	public:
		double eval_value;
		double eval_func;
		int id;
		bool child;
		game_state* current_state;
		vector<node*> children;
		node(game_state* g, bool enemy);
		~node();
		//void delete_tree();
};
