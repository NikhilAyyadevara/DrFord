#include "node.h"

using namespace std;

node::node(game_state* g)
{
	current_state = g;
	eval_value = g->evaluation_function();
	id=0; 
}
