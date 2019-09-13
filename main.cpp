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
	//cerr<<id<<"==1"<<endl;

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
			//cerr<<"surprise1!" << endl;
		random_player->current_state->change_state(x1,y1,x2,y2,bomb,true);
			//cerr<<"surprise2!" << endl;
	}

	while(true)
	{
		//our move
		vector<Move> moves = random_player->current_state->possible_moves(false);
		//cerr<<moves.size()<<' '<<"hi"<<endl;
		int ran = rand()%moves.size();
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
		random_player->current_state->change_state(moves.at(ran).x1, moves.at(ran).y1, moves.at(ran).x2, moves.at(ran).y2, moves.at(ran).bomb, false);
		if(moves.at(ran).bomb)
			temp='B';
		else
			temp = 'M';
		//this_thread::sleep_for(chrono::milliseconds(2000));
		cout<< 'S'<<' '<<moves.at(ran).x1<<' '<<moves.at(ran).y1<<' '<<temp<<' '<<moves.at(ran).x2<<' '<<moves.at(ran).y2<<endl;
		printcn(random_player->current_state->cannons);
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
	}
}
