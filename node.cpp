#include "node.h"

using namespace std;

node::node(game_state* g)
{
	current_state = g;
	eval_value = g->evaluation_function();
	id=0;
	child = false;
}

node::~node()
{
	for(int i=0; i<children.size(); i++)
	{
		delete children[i]->current_state;
		delete children[i];
	}
}
