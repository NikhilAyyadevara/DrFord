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
	map<vector<vector<int> >, int> m;
	double total_time = time_left;
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
				cout << "S "<<2<<" " <<y_dim-1<<" M "<< 1<<" "<< y_dim-2 << "\n";
				random_player->current_state->change_state(2,(y_dim-1),1,(y_dim-2),0,false);
			}

			else
			{
				cout << "S "<<4<<" " <<y_dim-1<<" M "<< 5<<" "<< y_dim-2 << "\n";
				random_player->current_state->change_state(4,(y_dim-1),5,(y_dim-2),0,false);
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
			auto start = std::chrono::high_resolution_clock::now();
			vector<Move> moves = random_player->current_state->possible_moves(false);
			int lavda = random_player->current_state->possible_states(false).size();
			int l1= random_player->current_state->possible_moves(true).size();
			int l2 = random_player->current_state->possible_states(true).size();
			if(moves.size()!=lavda || l1!=l2)
			{
				cerr << l1 << " " << l2<<endl;
				cerr << "dengindhi po" <<"\n";
				return 0;
			}
			int b1 = random_player->current_state->possible_moves(true).size();
			int b = ((int)moves.size()+b1)/2;
			if(b>39)
				depth=4;
			else if(b>29)
				depth=5;
			else if(b>22)
				depth=6;
			else if(b>13)
				depth=7;
			else if(b>10)
				depth=9;
			else
				depth=10;
			// double remaining_time = random_player->remaining_time;
			// auto start = std::chrono::high_resolution_clock::now();
			
			node* tree = random_player->tree_build(0, false, random_player->current_state);
			// auto end = std::chrono::high_resolution_clock::now();
			int ran;
			double moveTime;
			if(time_left<1)
				moveTime = 0.1;
			else if(time_left<5)
				moveTime = 0.3;
			else if(time_left>(4*total_time)/5)
				moveTime = 2;
			else if(time_left<total_time/6)
				moveTime = 1;
			else if(time_left<total_time/4)
				moveTime = 2;
			else
				moveTime = 5;
			ran = random_player->ids_pruning(depth, tree, moveTime);


			char temp;
			// testing begin
			// vector<pair<int, game_state*> > vc1 = random_player->current_state->possible_states(true);
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
			// for(int i=0;i<moves.size();++i)
			// {
			// 	int ind = tree->children[i]->id;
			// 	cerr<< ind <<" "<<tree->children[i]->eval_value<<" "<<moves.at(ind).x1<<' '<<moves.at(ind).y1<<' '<<moves[ind].bomb<<' '<<moves.at(ind).x2<<' '<<moves.at(ind).y2<<"\n";
			// }
			random_player->current_state->change_state(moves.at(ran).x1, moves.at(ran).y1, moves.at(ran).x2, moves.at(ran).y2, moves.at(ran).bomb, false);
			auto end = std::chrono::high_resolution_clock::now();
			time_left -= std::chrono::duration_cast<std::chrono::duration<double> >(end-start).count();
			cerr << "depth: "<< depth << "\n";
			cerr << "branching factor: " << b << "\n";
			cerr << "eval: " << tree->eval_value <<"\n";
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
