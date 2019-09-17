#include <bits/stdc++.h>
#include "player.h"

using namespace std;

void printcn(vector<pair<soldier, int> > cannons)
{
	for(int i=0; i<cannons.size(); i++)
	{
		cerr << "orient: " << cannons[i].second << " " << "sold_x: " << cannons[i].first.getX() << " " << "sold_y: " << cannons[i].first.getY() << endl;
	}
	cerr << "----------------------------------------------" << endl;
}

int main()
{
	int id;
	cin>>id;
	int x_dim;
	cin>>x_dim;
	int y_dim;
	cin>>y_dim;
	double time_left;
	cin>>time_left;
	srand(time(0));

	id--;
	player* random_player = new player(id,x_dim,y_dim,time_left);
	if(id==1)
	{
		//waiting for opponents move
		char s,b;
		cin>>s;
		int x1,y1,x2,y2;
		bool bomb;
		if(s=='S')
		{
			cin>>x1;
			cin>>y1;
			cin>>b;
			cin>>x2;
			cin>>y2;
			bomb = (b=='B');
		}
	random_player->current_state->change_state(x1,y1,x2,y2,bomb,true);
	}


	int depth = 0;
	int count=0;
	while(true)
	{
		//our move
		if(count==0)
		{
			if(id==0)
			{
				if(rand()%2 == 0)
				{
					cout << "S 2 7 M 1 6" << endl;
					random_player->current_state->change_state(2,7,1,6,0,false);
				}

				else
				{
					cout << "S 2 7 M 3 6" << endl;
					random_player->current_state->change_state(2,7,3,6,0,false);
				}

			}
			else if(id==1)
			{
				if(rand()%2 == 0)
				{
					cout << "S 5 0 M 6 1" << endl;
					random_player->current_state->change_state(5,0,6,1,0,false);
				}
				else
				{
					cout << "S 5 0 M 4 1" << endl;
					random_player->current_state->change_state(5,0,4,1,0,false);
				}
			}
			cerr << "Random move" << endl;
		}
		else
		{
			vector<Move> moves = random_player->current_state->possible_moves(false);
			int b = moves.size();
			if(b>30)
				depth=3;
			else if(b>20)
				depth=4;
			else if(b>10)
				depth=5;
			else
				depth=6;
			// double remaining_time = random_player->remaining_time;
			// //if(remaining_time<15)
			// auto start = std::chrono::high_resolution_clock::now();
			node* tree = random_player->tree_build(depth, false, random_player->current_state);
			// auto end = std::chrono::high_resolution_clock::now();
			
			//vector<pair<int, game_state*> > vc = random_player->current_state->possible_states(false);
			int ran = random_player->ids_pruning(depth, tree);
			//int ran = random_player->minimax_decision(tree, -1*INFINITY, INFINITY, depth);
			//cerr << "ran " << ran << endl;
			// cerr<<"final eval: "<<tree->eval_value<<endl;
			// //int ran = rand()%moves.size();
			char temp;
			// char z,h;
			// cin>>z;
			// int a1,b1,a2,b2;
			// cin>>a1;
			// cin>>b1;
			// cin>>h;
			// cin>>a2;
			// cin>>b2;
			// random_player->current_state->change_state(a1,b1,a2,b2,(h=='B'),false);
			

			if(moves.at(ran).bomb)
				temp='B';
			else
				temp = 'M';
			
			//cerr<< std::chrono::duration_cast<chrono::milliseconds>(end-start).count() << endl;
			//cerr<<moves.size()<<"=="<<tree->children.size()<<endl;
			cout<< 'S'<<' '<<moves.at(ran).x1<<' '<<moves.at(ran).y1<<' '<<temp<<' '<<moves.at(ran).x2<<' '<<moves.at(ran).y2<<endl;
			random_player->current_state->change_state(moves.at(ran).x1, moves.at(ran).y1, moves.at(ran).x2, moves.at(ran).y2, moves.at(ran).bomb, false);
			cerr << "eval: " << random_player->current_state->evaluation_function() <<endl;
			// double please = random_player->current_state->evaluation_function() ;
			// double please2 =  vc.at(ran).second->evaluation_function();
			// cerr<<"Validation: "<< please <<' '<<please2 << endl;
			
			// if(please!=please2)
			// 	return 0;
			delete tree;
		}
		//opponents move
		char s,b;
		cin>>s;
		int x1,y1,x2,y2;
		bool bomb;
		if(s=='S')
		{
			cin>>x1;
			cin>>y1;
			cin>>b;
			cin>>x2;
			cin>>y2;
			bomb = (b=='B');
		}
		random_player->current_state->change_state(x1,y1,x2,y2,bomb,true);

		//this_thread::sleep_for(chrono::milliseconds(2000));
		count++;
	}
}
