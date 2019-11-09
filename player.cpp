#include "player.h"
int stalemate_scores[2][2] = {{600 ,400 },
							{ 800, 600}};


player::player(int a, int x, int y, double time)
{
	current_state = new game_state(a,x,y);
	remaining_time = time;
}

node* player::tree_build(int depth, bool enemy, game_state* state)
{
	if(depth==0)
	{
		return new node(state, enemy);
	}
	else
	{
		node* root = new node(state, enemy);
		// if(root->eval_value > 6) cerr<<"eval_value: "<<depth<<' '<<root->eval_value<<endl;
		std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
		vector<pair<int, game_state*> > next_states = state->possible_states(enemy);
		auto end = std::chrono::high_resolution_clock::now();
		root->child = true;
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


void player::build_children(node* root, bool enemy)
{
	 //cerr << "build_children hi!" << endl;
	if(root->child)
		return;
	 // cerr << "build_children let's possible_states!" << endl;
	vector<pair<int, game_state*> > next_states = root->current_state->possible_states(enemy);
	root->child = true;
	for(int i=0;i<next_states.size();++i)
	{
		node* child = new node(next_states.at(i).second, enemy);
		child->id = i;
		root->children.push_back(child);
	}
	// if(depth==7) cerr << "build_children bye!" << endl;
}


bool ascending(node* node1, node* node2)
{
	if(node1->eval_value == node2->eval_value)
		return node1->eval_func < node2->eval_func;
	return (node1->eval_value < node2->eval_value);
}

bool descending(node* node1, node* node2)
{
	if(node1->eval_value == node2->eval_value)
		return node1->eval_func > node2->eval_func;
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

double player::min_val(node* state, double alpha, double beta, int depth, double timeLeft)
{
	std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
	double res = INFINITY;
	if(depth == 0 || terminal(state))
	{
		res = state->eval_value;
		// res = state->current_state->evaluation_function();
		// state->eval_value = res;
		return res;
	}
	build_children(state, true);
	// vector<node*> childr = state->children;
	int num_child = state->children.size();
	//stalemate condition
	if(num_child==0)
	{
		res = stalemate_scores[((int)state->townhalls.size()-(( (state->X/2))+1)/2)-1][((int)state->enemy_townhalls.size()-(((state->X)/2)+1)/2)-1];
	}

	for(int i=0; i<num_child; i++)
	{
		if(timeLeft - ((std::chrono::duration_cast<std::chrono::duration<double> >(std::chrono::high_resolution_clock::now()-start)).count()) < 0.01)
			return -1;
		double temp = max_val(state->children[i], alpha, beta, depth - 1, timeLeft - ((std::chrono::duration_cast<std::chrono::duration<double> >(std::chrono::high_resolution_clock::now()-start)).count()));
		//if(temp < res)
		//{
		if(temp == -1)
			return -1;
		res = min(res,temp);
		beta = min(res, beta);
		if(beta <= alpha)
		{
			state->eval_value = res + 0.005*state->eval_func;
			sort(state->children.begin(), state->children.begin()+i, ascending);
			//if(res > 6) cerr << "min_prune " << depth << " " <<res << endl;
			return res;
		}
		//}
	}
	sort(state->children.begin(), state->children.end(), ascending);
	state->eval_value = res + 0.005*state->eval_func;
	//if(res > 6) cerr << "min " << depth << " " <<res << endl;
	return res;
}

double player::max_val(node* state, double alpha, double beta, int depth, double timeLeft)
{
	std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
	// if(depth==7) cerr << "hi max_val!" << endl;
	double res = -1*INFINITY;
	if(depth == 0 || terminal(state))
	{
		//res = state->current_state->evaluation_function();
		res = state->eval_value;
		return res;
	}
	// if(depth==7) cerr << "hi max_val let's build chidren!" << endl;
	build_children(state, false);
	// vector<node*> childr = state->children;
	int num_child = state->children.size();
	//stalemate condition
	if(num_child==0)
	{
		res = 1000 - stalemate_scores[((int)state->enemy_townhalls.size()-(( (state->X/2))+1)/2)-1][((int)state->townhalls.size()-(((state->X)/2)+1)/2)-1];
	}
	for(int i=0; i<num_child; i++)
	{
		if(timeLeft - ((std::chrono::duration_cast<std::chrono::duration<double> >(std::chrono::high_resolution_clock::now()-start)).count()) < 0.01)
			return -1;
		double temp = min_val(state->children[i], alpha, beta, depth - 1, timeLeft - ((std::chrono::duration_cast<std::chrono::duration<double> >(std::chrono::high_resolution_clock::now()-start)).count()));
		//if(temp > res)
		//{
		if(temp == -1)
			return -1;
		res = max(res,temp);
		alpha = max(alpha, res);
		if(beta <= alpha)
		{
			state->eval_value = res + 0.005*state->eval_func;
			sort(state->children.begin(), state->children.begin()+i, descending);
			//if(res > 6) cerr << "max_prune " << depth << " " <<res << endl; 
			return res;
		}
		//}
	}
	// if(depth==7) cerr << "max_val let's sort!" << endl;
	sort(state->children.begin(), state->children.end(), descending);
	// if(depth==7) cerr << "max_val bye!" << endl;
	state->eval_value = res + 0.005*state->eval_func;
	return res;
}

int player::minimax_decision(node* state, double alpha, double beta, int depth, int result,  double timeLeft)
{
	double res;
	// if(!state->enemy)
	res = max_val(state, alpha, beta, depth, timeLeft);
	// else
	// 	res = min_val(state, alpha, beta, depth, timeLeft);
	if(res==-1)
	{
		cerr << "oops! " << depth << "\n";
		return result;
	}
	// vector<node*> childr = state->children;
	if(state->children.size()==0)
		return -1;
	// int num_child = childr.size();
	// int ctr=0;
	// if(depth==7) cerr << "hi! " << childr.size()<<  endl;
	// for(;ctr<childr.size();++ctr)
	// {
	// 	if(childr[ctr]->eval_value != res)
	// 	{
	// 		break;
	// 	}
	// }
	// if(depth==7) cerr << "hi1!" << endl;
	// int max_index = 0;
	// double max_eval_func_val = 0.0;
	// for(int i=0;i<=ctr;++i)
	// {
	// 	double temp_val = childr[i]->current_state->evaluation_function();
	// 	if(temp_val > max_eval_func_val)
	// 	{
	// 		max_eval_func_val = temp_val;
	// 		max_index = i;
	// 	}

	// }
	// if(depth==7) cerr << "bye" << endl;
	// return childr[max_index]->id;
	return state->children[0]->id;
}

node* player::get_child(node* root, int path, int depth)
{
	if(depth == 0 || path>=root->children.size())
		return root;
	else
	{
		return get_child(root->children.at(path), 0, depth-1);
	}
}

int player::ids_pruning(int max_depth, node* root, double move_time)
{
	std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
	int res = 0;
	double alpha = -1*INFINITY;
	double beta = INFINITY;
	int count = 1;
	// for(int i=1; i< max_depth; i++)
	// {
	// 	minimax_decision(root, alpha, beta, i);	
	// }
	// res = minimax_decision(root, alpha, beta, max_depth);
	int path = 0;
	bool flag = max_depth % 2;
	bool nextbest = false;
	while(count<=max_depth)
	{
		if(move_time - ((std::chrono::duration_cast<std::chrono::duration<double> >(std::chrono::high_resolution_clock::now()-start)).count()) < 0.01)
			return res;
		res = minimax_decision(root, alpha, beta, count, res, move_time - ((std::chrono::duration_cast<std::chrono::duration<double> >(std::chrono::high_resolution_clock::now()-start)).count()));

		if(move_time - ((std::chrono::duration_cast<std::chrono::duration<double> >(std::chrono::high_resolution_clock::now()-start)).count()) < 0.01)
			return res;

		if(count==max_depth)
		{
			double temp_val = root->eval_value;
			while(path<root->children.size() && root->children[path]->eval_value == temp_val)
			{
				if(move_time - ((std::chrono::duration_cast<std::chrono::duration<double> >(std::chrono::high_resolution_clock::now()-start)).count()) < 0.01)
				{
					cerr << "no use!" << endl;
					return res;
				}
				node* best = get_child(root, path, max_depth);
				// node* best = root->children[path];
				if(!flag)
					max_val(best, alpha, beta, 4, move_time - ((std::chrono::duration_cast<std::chrono::duration<double> >(std::chrono::high_resolution_clock::now()-start)).count()));
				else
					min_val(best, alpha, beta, 4, move_time - ((std::chrono::duration_cast<std::chrono::duration<double> >(std::chrono::high_resolution_clock::now()-start)).count()));
				
				if(best->eval_value<temp_val-1.5)
				{
					// node* best2 = get_child(root, 1, max_depth);
					cerr << "wow! " <<flag<< "\n";
					path++;
				}
				else
				{
					nextbest = true;
					break;
				}
			}
		}
		if(nextbest && path>0)
		{
			cerr << "awesome! " <<path<< "\n";
			res = root->children[path]->id;
		}
		count++;
	}
	
	return res;
}

//
// int main()
// {
// }
