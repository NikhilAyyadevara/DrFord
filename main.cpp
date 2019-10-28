#include <bits/stdc++.h>
#include "player.h"

using namespace std;


int main()
{
	int id;
	cin>>id;
	int y_dim;
	cin>>y_dim;
	int x_dim;
	cin>>x_dim;
	double time_left;
	cin>>time_left;
	srand(time(0));

	cerr << x_dim << " " << y_dim << "\n";

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
		if(false)
		{}
		//our move
		if(count==0 && id==0)
		{

			if(rand()%2 == 0)
			{
				cout << "S 2 7 M 1 6" << "\n";
				random_player->current_state->change_state(2,7,1,6,0,false);
			}

			else
			{
				cout << "S 2 7 M 3 6" << "\n";
				random_player->current_state->change_state(2,7,3,6,0,false);
			}
			
			// else if(id==1)
			// {
			// 	if(rand()%2 == 0)
			// 	{
			// 		cout << "S 5 0 M 6 1" << "\n";
			// 		random_player->current_state->change_state(5,0,6,1,0,false);
			// 	}
			// 	else
			// 	{
			// 		cout << "S 5 0 M 4 1" << "\n";
			// 		random_player->current_state->change_state(5,0,4,1,0,false);
			// 	}
			// }
			
			// cerr << "Random move" << "\n";
			
		}
		else
		{
			vector<Move> moves = random_player->current_state->possible_moves(false);
			int b1 = random_player->current_state->possible_moves(true).size();
			int b = ((int)moves.size()+b1)/2;
			if(b>30)
				depth=5;
			else if(b>24)
				depth=5;
			else if(b>15)
				depth=6;
			else if(b>10)
				depth=7;
			else
				depth=10;
			// double remaining_time = random_player->remaining_time;
			// auto start = std::chrono::high_resolution_clock::now();
			cerr << "depth: "<< depth << "\n";
			node* tree = random_player->tree_build(0, false, random_player->current_state);
			if(depth==7)
				cerr << "tree build done" << "\n";
			// auto end = std::chrono::high_resolution_clock::now();
			
			int ran = random_player->ids_pruning(depth, tree);

			if(depth==7)
				cerr << "ids_pruning done" << "\n";

			char temp;
			// testing begin
			// vector<pair<int, game_state*> > vc1 = random_player->current_state->possible_states(true);
			// for(int i=0;i<moves.size();++i)
			// {
			// 	cerr<< 'S'<<' '<<moves.at(i).x1<<' '<<moves.at(i).y1<<' '<<moves[i].bomb<<' '<<moves.at(i).x2<<' '<<moves.at(i).y2<<"\n";
			// }
			// char z,h;
			// cin>>z;
			// int a1,b1,a2,b2;
			// cin>>a1;
			// cin>>b1;
			// cin>>h;
			// cin>>a2;
			// cin>>b2;
			// random_player->current_state->change_state(a1,b1,a2,b2,(h=='B'),false);

			// cerr << random_player->current_state->soldiers.size() << ' ' << random_player->current_state->enemy_soldiers.size() << "\n";
			// vector<pair<int, game_state*> > vc = random_player->current_state->possible_states(false);
			// for(int i=0;i<vc.size();++i)
			// {
			// 	cerr << "eval_value: " << vc.at(i).second->evaluation_function() << "\n";
			// }
			// testing end
			

			if(moves.at(ran).bomb)
				temp='B';
			else
				temp = 'M';
			
			//cerr<< std::chrono::duration_cast<chrono::milliseconds>(end-start).count() << "\n";
			cout<< 'S'<<' '<<moves.at(ran).x1<<' '<<moves.at(ran).y1<<' '<<temp<<' '<<moves.at(ran).x2<<' '<<moves.at(ran).y2<<"\n";
			random_player->current_state->change_state(moves.at(ran).x1, moves.at(ran).y1, moves.at(ran).x2, moves.at(ran).y2, moves.at(ran).bomb, false);
			if(depth==7)
				cerr << "change_state done" << "\n";
			cerr << "eval: " << tree->eval_value <<"\n";
			cerr << "branching factor: " << b << "\n";
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
