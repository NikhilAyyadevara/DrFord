#include "player.h"

player::player(int a, int x, int y, double time)
{
	current_state = new game_state(a,x,y);
	remaining_time = time;
}

node* player::tree_build(int depth, bool enemy, game_state* state)
{
	if(depth==0)
	{
		return new node(state);
	}
	else
	{
		node* root = new node(state);
		// if(root->eval_value > 6) cerr<<"eval_value: "<<depth<<' '<<root->eval_value<<endl;
		auto start = std::chrono::high_resolution_clock::now();
		vector<pair<int, game_state*> > next_states = state->possible_states(enemy);
		auto end = std::chrono::high_resolution_clock::now();
		for(int i=0;i<next_states.size();++i)
		{
			node* child = tree_build(depth-1, !enemy, next_states.at(i).second);
			child->id = i;
			root->children.push_back(child);
		}
		//cerr <<"possible states: "<<' '<<std::chrono::duration_cast<chrono::microseconds>(end-start).count() << endl;
		return root;
	}
}


bool ascending(node* node1, node* node2)
{
	return (node1->eval_value < node2->eval_value);
}

bool descending(node* node1, node* node2)
{
	return (node1->eval_value > node2->eval_value);
}

bool terminal(node* current)
{
	int s1 = current->current_state->soldiers.size();
	int s2 = current->current_state->enemy_soldiers.size();
	int c1 = current->current_state->townhalls.size();
	int c2 = current->current_state->enemy_townhalls.size();
	return (s1==0 ||s2==0 || c1<=2 || c2<=2);
}

double player::min_val(node* state, double alpha, double beta, int depth)
{
	double res = INFINITY;
	if(depth == 0 || terminal(state))
	{
		res = state->eval_value;
		// res = state->current_state->evaluation_function();
		// state->eval_value = res;
		return res;
	}
	vector<node*> childr = state->children;
	int num_child = childr.size();
	for(int i=0; i<num_child; i++)
	{
		double temp = max_val(childr[i], alpha, beta, depth - 1);
		//if(temp < res)
		//{
			res = min(res,temp);
			beta = min(res, beta);
			if(beta <= alpha)
			{
				state->eval_value = res;
				sort(childr.begin(), childr.begin()+i, ascending);
				//if(res > 6) cerr << "min_prune " << depth << " " <<res << endl;
				return res;
			}
		//}
	}
	sort(childr.begin(), childr.end(), ascending);
	state->eval_value = res;
	//if(res > 6) cerr << "min " << depth << " " <<res << endl;
	return res;
}

double player::max_val(node* state, double alpha, double beta, int depth)
{
	double res = -1*INFINITY;
	if(depth == 0 || terminal(state))
	{
				if(current_state->id==0 && terminal(state))
			cerr<<"cdef"<<endl;
		//res = state->current_state->evaluation_function();
		res = state->eval_value;
		return res;
	}
	vector<node*> childr = state->children;
	int num_child = childr.size();
	for(int i=0; i<num_child; i++)
	{
		double temp = min_val(childr[i], alpha, beta, depth - 1);
		//if(temp > res)
		//{
			res = max(res,temp);
			alpha = max(alpha, res);
			if(beta <= alpha)
			{
				state->eval_value = res;
				sort(childr.begin(), childr.begin()+i, descending);
				//if(res > 6) cerr << "max_prune " << depth << " " <<res << endl; 
				return res;
			}
		//}
	}
	sort(childr.begin(), childr.end(), descending);
	state->eval_value = res;
	return res;
}

int player::minimax_decision(node* state, double alpha, double beta, int depth)
{
	double res = max_val(state, alpha, beta, depth);
	vector<node*> childr = state->children;
	int num_child = childr.size();
	for(int i=0;i<num_child;++i)
	{
		if(state->children.at(i)->eval_value == res)
			return state->children[i]->id;
	}
	//vector<pair<int, game_state*> > states = state->current_state->possible_states(false);
	// for(int i=0;i<states.size();++i)
	// {
	// 	double eval = states.at(i).second->evaluation_function();
	// 	if(eval==res)
	// 		return (states.at(i).first);
	// }
	return -1;
}

int player::ids_pruning(int max_depth, node* root)
{
	int res;
	double alpha = -1*INFINITY;
	double beta = INFINITY;
	for(int i=1; i< max_depth; i++)
	{
		minimax_decision(root, alpha, beta, i);
		
	}
	res = minimax_decision(root, alpha, beta, max_depth);
	
	return res;
}

//
// int main()
// {
// }
