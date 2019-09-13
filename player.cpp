#include "player.h"

player::player(int a, int x, int y, double time)
{
	current_state = new game_state(a,x,y);
	remaining_time = time;
}

node* player::tree_build(int depth, bool enemy, game_state* state)
{
	if(depth==0)
		return new node(state);
	else
	{
		node* root = new node(state);
		vector<pair<int, game_state*> > next_states = state->possible_states(enemy);
		for(int i=0;i<next_states.size();++i)
		{
			node* child = tree_build(depth-1, !enemy, next_states.at(i).second);
			root->children.push_back(child);
		}
		return root;
	}
}

int player::ids_pruning(int max_depth, node* root)
{
	
}

double min_val(node* state, double alpha, double beta, int depth)
{
	if(depth == 0) 
		return state->current_state->evaluation_function();
	//sort(state->children.begin(), state->children.end(), 
	vector<node*> childr = state->children;
	int num_child = childr.size();
	double res = INFINITY;
	for(int i=0; i<num_child; i++)
	{
		double temp = max_val(childr[i], alpha, beta, depth - 1);
		if(temp < res)
		{
			res = temp;
			beta = min(res, beta);
			if(beta <= alpha) return res;
		}
	}
	return res;
}

double max_val(node* state, double alpha, double beta, int depth)
{
	if(depth == 0) 
		return state->current_state->evaluation_function();
	vector<node*> childr = state->children;
	int num_child = childr.size();
	double res = -1*INFINITY;
	for(int i=0; i<num_child; i++)
	{
		double temp = min_val(childr[i], alpha, beta, depth - 1);
		if(temp > res)
		{
			res = temp;
			alpha = max(alpha, res);
			if(beta <= alpha) return res;
		}
	}
	return res;
}

int minimax_decision(node* state, double alpha, double beta, int depth)
{
	vector<node*> childr = state->children;
	int num_child = childr.size();
	for(int i=0; i< num_child; i++)
	{
		double temp = min_val(childr[i], alpha, beta, depth - 1);
		if(temp > res)
		{
			res = temp;
			alpha = max(alpha, res);
			if(beta <= alpha)
				break;
		}
	}
	vector<pair<int, game_state*> > states = state->current_state->possible_states(false);
	for(int i=0;i<states.size();++i)
	{
		double eval = states.at(i).second->evaluation_function();
		if(eval==res)
			return (states.at(i).first);
	}
	return -1;
}



