//#include <bits/stdc++.h>
#include "game_state.h"

game_state::game_state(game_state* g)
{
	id=g->id;
	X=g->X;
	Y=g->Y;
	soldiers=g->soldiers;
	enemy_soldiers=g->enemy_soldiers;
	///Cannon orientation - 2nd parameter of pair
	//vertical -> 0
	//positive diagonal -> 1
	//horizontal -> 2
	//negative diagonal -> 3
	cannons=g->cannons;
	enemy_cannons=g->enemy_cannons;
	townhalls=g->townhalls;
	enemy_townhalls=g->enemy_townhalls;

}

game_state::game_state(int a, int x, int y)
{
	soldier *s, *s1;
	id=a;
	X=x;
	Y=y;
	if(a==0)
	{
		for(int i=0;i<(x/2);++i)
		{
			enemy_townhalls.push_back(make_pair(2*i,0));
			townhalls.push_back(make_pair((2*i+1), y-1));
			for(int j=0;j<3;++j)
			{
				s = new soldier(2*i, y-1-j);
				soldiers.push_back(*s);
				s1 = new soldier(2*i+1, j);
				enemy_soldiers.push_back(*s1);
				if(j==1)
				{
					cannons.push_back(make_pair(*s,0));
					enemy_cannons.push_back(make_pair(*s1,0));
				}
			}
		}
	}
	else if(a==1)
	{
		for(int i=0;i<(x/2);++i)
		{
			townhalls.push_back(make_pair(2*i, 0));
			enemy_townhalls.push_back(make_pair((2*i+1),y-1));
			for(int j=0;j<3;++j)
			{
				s = new soldier(2*i,y-1-j);
				enemy_soldiers.push_back(*s);
				s1 = new soldier(2*i+1,j);
				soldiers.push_back(*s1);
				if(j==1)
				{
					enemy_cannons.push_back(make_pair(*s,0));
					cannons.push_back(make_pair(*s1,0));
				}
			}
		}
	}
	delete s;
	delete s1;
}

vector<int> game_state::find_Cannon(int x1, int y1, bool enemy)
{
	vector<int> res;
	if(!enemy)
	{
		int cannons_size = cannons.size();
		for(int i=0;i<cannons_size;++i)
		{
			soldier s = cannons.at(i).first;
			int a = cannons.at(i).second;
			int x2 = s.getX();
			int y2 = s.getY();
			if(x1==x2 && y1==y2)
				res.push_back(i);
			if(a == 0)//vertical cannon
			{
				if((x1==x2) && (y1==(y2-1) || y1==(y2+1)))
					res.push_back(i);
			}
			else if(a == 1)// positive diagonal cannon
			{
				if((x1==x2+1 && y1==y2+1) || (x1==x2-1 && y1==y2-1))
					res.push_back(i);
			}
			else if(a == 2)//horizontal cannon
			{
				if((y1==y2) && (x1==(x2-1) || x1==(x2+1)))
					res.push_back(i);
			}
			else if(a == 3) // negative diagonal cannon
			{
				if((x1==x2+1 && y1==y2-1) || (x1==x2-1 && y1==y2+1))
					res.push_back(i);
			}
		}
	}
	else
	{
		int enemy_cannons_size = enemy_cannons.size();
		for(int i=0;i<enemy_cannons_size;++i)
		{
			soldier s = enemy_cannons.at(i).first;
			int a = enemy_cannons.at(i).second;
			int x2 = s.getX();
			int y2 = s.getY();
			if(x1==x2 && y1==y2)
				res.push_back(i);
			if(a==0)//vertical cannon
			{
				if((x1==x2) && (y1==(y2-1) || y1==(y2+1)))
					res.push_back(i);
			}
			else if(a==1)// positive diagonal cannon
			{
				if((x1==x2+1 && y1==y2+1) || (x1==x2-1 && y1==y2-1))
					res.push_back(i);
			}
			else if(a==2)//horizontal cannon
			{
				if((y1==y2) && (x1==(x2-1) || x1==(x2+1)))
					res.push_back(i);
			}
			else if(a==3) // negative diagonal cannon
			{
				if((x1==x2+1 && y1==y2-1) || (x1==x2-1 && y1==y2+1))
					res.push_back(i);
			}
		}
	}
	return res;
}

vector< pair<soldier, int> > game_state::find_new_Cannon(int x, int y, bool enemy)
{
	vector< pair<soldier, int> > res;
	int sold_index = find_soldier(x, y, enemy);
	//clockwise order
	int sold_1 = find_soldier(x, y-1, enemy);
	int sold_2 = find_soldier(x+1, y-1, enemy);
	int sold_3 = find_soldier(x+1, y, enemy);
	int sold_4 = find_soldier(x+1, y+1, enemy);
	int sold_5 = find_soldier(x, y+1, enemy);
	int sold_6 = find_soldier(x-1, y+1, enemy);
	int sold_7 = find_soldier(x-1, y, enemy);
	int sold_8 = find_soldier(x-1, y-1, enemy);
	if(sold_1 != -1)
	{
		int s_temp = find_soldier(x, y-2, enemy);
		if(s_temp != -1)
		{
			soldier s(-1,-1);
			if(!enemy) s = soldiers[sold_1]; else s = enemy_soldiers[sold_1];
			res.push_back(make_pair(s,0));
		}
		if(sold_5 != -1)
		{
			soldier s(-1,-1);
			if(!enemy) s = soldiers[sold_index]; else s = enemy_soldiers[sold_index];
			res.push_back(make_pair(s, 0));
		}
	}
	if(sold_2 != -1)
	{
		int s_temp = find_soldier(x+2, y-2, enemy);
		if(s_temp != -1)
		{
			soldier s(-1,-1);
			if(!enemy) s = soldiers[sold_2]; else s = enemy_soldiers[sold_2];
			res.push_back(make_pair(s,3));
		}
		if(sold_6 != -1)
		{
			soldier s(-1,-1);
			if(!enemy) s = soldiers[sold_index]; else s = enemy_soldiers[sold_index];
			res.push_back(make_pair(s, 3));
		}
	}
	if(sold_3 != -1)
	{
		int s_temp = find_soldier(x+2, y, enemy);
		if(s_temp != -1)
		{
			soldier s(-1,-1);
			if(!enemy) s = soldiers[sold_3]; else s = enemy_soldiers[sold_3];
			res.push_back(make_pair(s,2));
		}
		if(sold_7 != -1)
		{
			soldier s(-1,-1);
			if(!enemy) s = soldiers[sold_index]; else s = enemy_soldiers[sold_index];
			res.push_back(make_pair(s, 2));
		}
	}
	if(sold_4 != -1)
	{
		int s_temp = find_soldier(x+2, y+2, enemy);
		if(s_temp != -1)
		{
			soldier s(-1,-1);
			if(!enemy) s = soldiers[sold_4]; else s = enemy_soldiers[sold_4];
			res.push_back(make_pair(s,1));
		}
		if(sold_8 != -1)
		{
			soldier s(-1,-1);
			if(!enemy) s = soldiers[sold_index]; else s = enemy_soldiers[sold_index];
			res.push_back(make_pair(s, 1));
		}
	}
	if(sold_5 != -1)
	{
		int s_temp = find_soldier(x, y+2, enemy);
		if(s_temp != -1)
		{
			soldier s(-1,-1);
			if(!enemy) s = soldiers[sold_5]; else s = enemy_soldiers[sold_5];
			res.push_back(make_pair(s,0));
		}
	}
	if(sold_6 != -1)
	{
		int s_temp = find_soldier(x-2, y+2, enemy);
		if(s_temp != -1)
		{
			soldier s(-1,-1);
			if(!enemy) s = soldiers[sold_6]; else s = enemy_soldiers[sold_6];
			res.push_back(make_pair(s,3));
		}
	}
	if(sold_7 != -1)
	{
		int s_temp = find_soldier(x-2, y, enemy);
		if(s_temp != -1)
		{
			soldier s(-1,-1);
			if(!enemy) s = soldiers[sold_7]; else s = enemy_soldiers[sold_7];
			res.push_back(make_pair(s,2));
		}
	}
	if(sold_8 != -1)
	{
		int s_temp = find_soldier(x-2, y-2, enemy);
		if(s_temp != -1)
		{
			soldier s(-1,-1);
			if(!enemy) s = soldiers[sold_8]; else s = enemy_soldiers[sold_8];
			res.push_back(make_pair(s,1));
		}
	}
	return res;
}

int game_state::find_soldier(int x, int y, bool enemy)
{
	if(!enemy)
	{
		int soldiers_size = soldiers.size();
		for(int i=0;i<soldiers_size;++i)
		{
			if(soldiers.at(i).getX()==x && soldiers.at(i).getY()==y)
				return i;
		}
	}
	else
	{
		int enemy_soldiers_size = enemy_soldiers.size();
		for(int i=0;i<enemy_soldiers_size;++i)
		{
			if(enemy_soldiers.at(i).getX()==x && enemy_soldiers.at(i).getY()==y)
				return i;
		}
	}
	return -1;
}

int game_state::find_townhall(int x, int y, bool enemy)
{
	if(!enemy)
	{
		int townhalls_size = townhalls.size();
		for(int i=0; i<townhalls_size; i++)
		{
			if(townhalls.at(i).first == x && townhalls.at(i).second == y)
			{
				return i;
			}
		}
	}
	else
	{
		int townhalls_size = enemy_townhalls.size();
		for(int i=0; i<townhalls_size; i++)
		{
			if(enemy_townhalls.at(i).first == x && enemy_townhalls.at(i).second == y)
			{
				return i;
			}
		}
	}
	return -1;
}

void game_state::remove_cannons (int x, int y, bool enemy)
{
	vector<int> cannon_indexes = find_Cannon(x, y, enemy);
	sort(cannon_indexes.begin(), cannon_indexes.end());
	int cannon_indexes_size = cannon_indexes.size();
	if(!enemy)
	{
		for(int i=cannon_indexes_size-1; i>=0; i--)
		{
			int cannon_index = cannon_indexes.at(i);
			if(cannon_index != -1)
			{
				cannons.erase( cannons.begin() +cannon_index);
			}
		}
	}
	else
	{
		for(int i=cannon_indexes_size-1; i>=0; i--)
		{
			int cannon_index = cannon_indexes.at(i);
			if(cannon_index != -1)
			{
				enemy_cannons.erase( enemy_cannons.begin() +cannon_index);
			}
		}
	}
	return;
}

void game_state::add_cannons (int x, int y, bool enemy)
{
	vector<pair<soldier, int>> new_cannons = find_new_Cannon( x, y, enemy);
	int new_cannons_size = new_cannons.size();
	if(!enemy)
	{
		for(int i=0; i<new_cannons_size; i++)
		{
			cannons.push_back(new_cannons.at(i));
		}
	}
	else
	{
		for(int i=0; i<new_cannons_size; i++)
		{
			enemy_cannons.push_back(new_cannons.at(i));
		}
	}
}

void game_state::change_state(int x1, int y1, int x2, int y2, bool bomb, bool enemy)
{
	if(!bomb)
	{
		if(!enemy)
		{
			if(find_soldier(x1,y1,false)!=-1)
			{
				int sold_index =find_soldier(x1,y1,false);
				//move
				soldiers.at(sold_index).move(x2,y2);
				//cannon removal
				remove_cannons(x1, y1, false);
				//cannon formation
				add_cannons(x2, y2, false);
				///enemy killing
				//soldier killing
				int killed_soldier = find_soldier(x2, y2, true);
				if(killed_soldier != -1)
				{
					enemy_soldiers.erase( enemy_soldiers.begin() +killed_soldier);
					//update enemy_cannons
					remove_cannons(x2, y2, true);
				}
				//townhall killing
				int killed_townhall = find_townhall(x2, y2, true);
				if(killed_townhall != -1)
				{
					enemy_townhalls.erase( enemy_townhalls.begin() +killed_townhall);
				}
			}
		}
		else if(enemy)
		{
			if(find_soldier(x1,y1,true)!=-1)
			{
				int sold_index =find_soldier(x1,y1,true);
				//move
				enemy_soldiers.at(sold_index).move(x2,y2);
				//enemy cannon removal
				remove_cannons(x1, y1, true);
				//enemy cannon formation
				add_cannons(x2, y2, true);
				///my coins dying
				//soldier dying
				int killed_soldier = find_soldier(x2, y2, false);
				if(killed_soldier != -1)
				{
					soldiers.erase( soldiers.begin() +killed_soldier);
					//update cannons
					remove_cannons(x2, y2, false);
				}
				//townhall dying
				int killed_townhall = find_townhall(x2, y2,	false);
				if(killed_townhall != -1)
				{
					townhalls.erase( townhalls.begin() +killed_townhall);
				}
			}
		}
	}
	else
	{
		if(!enemy)
		{
			///enemy killing
			//soldier killing
			int killed_soldier = find_soldier(x2, y2, true);
			if(killed_soldier != -1)
			{
				enemy_soldiers.erase( enemy_soldiers.begin() +killed_soldier);
				//update enemy_cannons
				remove_cannons(x2, y2, true);
			}
			//townhall killing
			int killed_townhall = find_townhall(x2, y2, true);
			if(killed_townhall != -1)
			{
				enemy_townhalls.erase( enemy_townhalls.begin() +killed_townhall);
			}
		}
		else
		{
			///my coins dying
			//soldier dying
			int killed_soldier = find_soldier(x2, y2, false);
			if(killed_soldier != -1)
			{
				soldiers.erase( soldiers.begin() +killed_soldier);
				//update cannons
				remove_cannons(x2, y2, false);
			}
			//townhall dying
			int killed_townhall = find_townhall(x2, y2,	false);
			if(killed_townhall != -1)
			{
				townhalls.erase( townhalls.begin() +killed_townhall);
			}
		}
	}
}

int townhall_scores[3][3] = {	{0,2,0},
															{8,5,3},
															{10,7,5}	};
double game_state::evaluation_function()
{
	double res = 0;
	double soldiers_wt = 0.01*((double)soldiers.size() - (double)enemy_soldiers.size());
	//cerr << soldiers_wt << endl;
	double cannon_wt = 0.003*((double)cannons.size() - (double)enemy_cannons.size());
	//cerr << "cannons_size: "<< cannons.size()<<endl;
	//cerr << "enemY_cannons_size: "<< enemy_cannons.size()<<endl;
	//cerr << cannon_wt << endl;
	double townhalls_wt = townhall_scores[((int)townhalls.size()-2)][((int)enemy_townhalls.size()-2)];
	//cerr << townhalls_wt << endl;
	res = soldiers_wt + townhalls_wt + cannon_wt;
	//cerr << res << endl;
	return res;
}

vector<pair<int,game_state*> > game_state::possible_states(bool enemy)
{
	vector<pair<int, game_state*> > moves;
	int x_dim = this->X;
	int y_dim = this->Y;
	if(!enemy)
	{
		vector<soldier> soldiers = this->soldiers;
		vector<pair<soldier, int> > cannons = this->cannons;
		int id = this->id;
		//Soldier moves
		for(int i=0;i<soldiers.size();++i)
		{
			int x = soldiers.at(i).getX();
			int y = soldiers.at(i).getY();
			if(id==1)//we are white
			{
				//forward soldier
				if(y<(y_dim-1) && this->find_soldier(x,(y+1),enemy)==-1)//forward move
				{
					//game_state g = *this;
					game_state* g = new game_state(this);
					g->change_state(x,y,x,y+1,0,enemy);
					moves.push_back(make_pair(moves.size(),g));
				}
				if(y<(y_dim-1) && (x<x_dim-1) && this->find_soldier(x+1,y+1,enemy)==-1)//positive diagonal move
				{
					//game_state g = *this;
					game_state* g = new game_state(this);
					g->change_state(x,y,x+1,y+1,0,enemy);
					moves.push_back(make_pair(moves.size(),g));
				}
				if(y<(y_dim-1) && (x>0) && this->find_soldier(x-1,y+1,enemy)==-1)//negative diagonal move
				{
					//game_state g = *this;
					game_state* g = new game_state(this);
					g->change_state(x,y,x-1,y+1,0,enemy);
					moves.push_back(make_pair(moves.size(),g));
				}
				//sideways killer moves
				if(x < (x_dim -1) && (this->find_soldier(x+1,y,!enemy)!=-1 || this->find_townhall(x+1,y,!enemy)!=-1))//positive horiontal killer move
				{
					//game_state g = *this;
					game_state* g = new game_state(this);
					g->change_state(x,y,x+1,y,0,enemy);
					moves.push_back(make_pair(moves.size(),g));
				}
				if(x > 0 && (this->find_soldier(x-1,y,!enemy)!=-1 || this->find_townhall(x-1,y,!enemy)!=-1) )//negative horiontal killer move
				{
					//game_state g = *this;
					game_state* g = new game_state(this);
					g->change_state(x,y,x-1,y,0,enemy);
					moves.push_back(make_pair(moves.size(),g));
				}
				//retreat backard moves
				if(this->find_soldier(x-1,y,!enemy) != -1 || this->find_soldier(x+1,y,!enemy) != -1 || this->find_soldier(x-1,y+1,!enemy) != -1
					|| this->find_soldier(x+1,y+1,!enemy) != -1 || this->find_soldier(x,y+1,!enemy) != -1)
				{
					//backward
					if((y-2) >= 0 && this->find_soldier(x,y-2,enemy) == -1 && this->find_townhall(x,y-2,enemy) == -1)
					{
						//game_state g = *this;
						game_state* g = new game_state(this);
						g->change_state(x,y,x,y-2,0,enemy);
						moves.push_back(make_pair(moves.size(),g));
					}
					//positive diagonal
					if((y-2)>=0 && (x-2)>=0 && this->find_soldier(x-2,y-2,enemy) == -1 && this->find_townhall(x-2,y-2,enemy) == -1)
					{
						//game_state g = *this;
						game_state* g = new game_state(this);
						g->change_state(x,y,x-2,y-2,0,enemy);
						moves.push_back(make_pair(moves.size(),g));
					}
					//negative diagonal
					if((y-2)>=0 && (x+2)< x_dim && this->find_soldier(x+2,y-2,enemy)==-1 && this->find_townhall(x+2,y-2,enemy)==-1)
					{
						//game_state g = *this;
						game_state* g = new game_state(this);
						g->change_state(x,y,x+2,y-2,0,enemy);
						moves.push_back(make_pair(moves.size(),g));
					}
				}
			}
			else if(id==0)//we are black
			{
				//forward soldier
				if(y>0 && this->find_soldier(x,(y-1),enemy)==-1)//forward move
				{
					//game_state g = *this;
					game_state* g = new game_state(this);
					g->change_state(x,y,x,y-1,0,enemy);
					moves.push_back(make_pair(moves.size(),g));
				}
				if(y>0 && x>0 && this->find_soldier(x-1,y-1,enemy)==-1)//positive diagonal move
				{
					//game_state g = *this;
					game_state* g = new game_state(this);
					g->change_state(x,y,x-1,y-1,0,enemy);
					moves.push_back(make_pair(moves.size(),g));
				}
				if(y>0 && (x<x_dim-1) && this->find_soldier(x+1,y-1,enemy)==-1)//negative diagonal move
				{
					//game_state g = *this;
					game_state* g = new game_state(this);
					g->change_state(x,y,x+1,y-1,0,enemy);
					moves.push_back(make_pair(moves.size(),g));
				}
				//sideways killer moves
				if(x < (x_dim -1) && (this->find_soldier(x+1,y,!enemy)!=-1 || this->find_townhall(x+1,y,!enemy)!=-1 ) )//positive horiontal killer move
				{
					//game_state g = *this;
					game_state* g = new game_state(this);
					g->change_state(x,y,x+1,y,0,enemy);
					moves.push_back(make_pair(moves.size(),g));
				}
				if(x > 0 && (this->find_soldier(x-1,y,!enemy)!=-1 || this->find_townhall(x-1,y,!enemy)!=-1))//negative horiontal killer move
				{
					//game_state g = *this;
					game_state* g = new game_state(this);
					g->change_state(x,y,x-1,y,0,enemy);
					moves.push_back(make_pair(moves.size(),g));
				}
				//retreat backard moves
				if(this->find_soldier(x-1,y,!enemy) != -1 || this->find_soldier(x+1,y,!enemy) != -1 || this->find_soldier(x-1,y-1,!enemy) != -1
					|| this->find_soldier(x+1,y-1,!enemy) != -1 || this->find_soldier(x,y-1,!enemy) != -1)
				{
					//backward
					if((y+2<y_dim) && this->find_soldier(x,y+2,enemy) == -1 && this->find_townhall(x,y+2,enemy) == -1 )
					{
						//game_state g = *this;
						game_state* g = new game_state(this);
						g->change_state(x,y,x,y+2,0,enemy);
						moves.push_back(make_pair(moves.size(),g));
					}
					//positive diagonal
					if((y+2<y_dim) && (x+2<x_dim) && this->find_soldier(x+2,y+2,enemy) == -1 && this->find_townhall(x+2,y+2,enemy) == -1)
					{
						//game_state g = *this;
						game_state* g = new game_state(this);
						g->change_state(x,y,x+2,y+2,0,enemy);
						moves.push_back(make_pair(moves.size(),g));
					}
					//negative diagonal
					if((y+2<y_dim) && (x-2>=0) && this->find_soldier(x-2,y+2,enemy)==-1 && this->find_townhall(x-2,y+2,enemy)==-1)
					{
						//game_state g = *this;
						game_state* g = new game_state(this);
						g->change_state(x,y,x-2,y+2,0,enemy);
						moves.push_back(make_pair(moves.size(),g));
					}
				}
			}
		}

		///Cannon
		for(int i=0; i<cannons.size(); i++)
		{
			int orientation = cannons.at(i).second;
			int x_par,y_par;
			if(orientation == 0)
			{
				x_par = 0;
				y_par = -1;
			}
			else if(orientation == 1)
			{
				x_par = -1;
				y_par = -1;
			}
			else if(orientation == 2)
			{
				x_par = -1;
				y_par = 0;
			}
			else if(orientation == 3)
			{
				x_par = -1;
				y_par = 1;
			}
			int x = cannons.at(i).first.getX();
			int y = cannons.at(i).first.getY();
			// cannon moves
			int x_temp_1 = x + 2*x_par;
			int y_temp_1 = y + 2*y_par;
			int x_temp_2 = x - 2*x_par;
			int y_temp_2 = y - 2*y_par;
			if(x_temp_1 >= 0 && x_temp_1 < x_dim && y_temp_1 >= 0 && y_temp_1 <y_dim && this->find_soldier(x_temp_1, y_temp_1, true) == -1 &&
			 this->find_soldier(x_temp_1, y_temp_1, false) == -1 && this->find_townhall(x_temp_1, y_temp_1, true) == -1 &&
			 this->find_townhall(x_temp_1, y_temp_1, false) == -1 )
			{
				//game_state g = *this;
				game_state* g = new game_state(this);
				g->change_state(x-x_par,y-y_par,x_temp_1,y_temp_1 ,0,enemy);
				moves.push_back(make_pair(moves.size(),g));
				// cannon bombs
				if(x+3*x_par >= 0 && x+3*x_par < x_dim && y+3*y_par >= 0 && y+3*y_par < y_dim && this->find_soldier(x+3*x_par, y+3*y_par, false) == -1 &&
				 this->find_townhall(x+3*x_par, y+3*y_par, false) == -1 )
				{
					//game_state g = *this;
					game_state* g = new game_state(this);
					g->change_state(x,y,x+3*x_par,y+3*y_par,1,enemy);
					moves.push_back(make_pair(moves.size(),g));
				}
				if(x+4*x_par >= 0 && x+4*x_par < x_dim && y+4*y_par >= 0 && y+4*y_par < y_dim && this->find_soldier(x+4*x_par, y+4*y_par, false) == -1 &&
				 this->find_townhall(x+4*x_par, y+4*y_par, false) == -1)
				{
					//game_state g = *this;
					game_state* g = new game_state(this);
					g->change_state(x,y,x+4*x_par,y+4*y_par,1,enemy);
					moves.push_back(make_pair(moves.size(),g));
				}
			}
			if(x_temp_2 >= 0 && x_temp_2 < x_dim && y_temp_2 >= 0 && y_temp_2 <y_dim && this->find_soldier(x_temp_2, y_temp_2, true) == -1 &&
			 this->find_soldier(x_temp_2, y_temp_2, false) == -1 && this->find_soldier(x_temp_2, y_temp_2, true) == -1 &&
			 this->find_soldier(x_temp_2, y_temp_2, false) == -1)
			{
				//game_state g = *this;
				game_state* g = new game_state(this);
				g->change_state(x+x_par,y+y_par,x_temp_2,y_temp_2 ,0,enemy);
				moves.push_back(make_pair(moves.size(),g));
				// cannon bombs
				if(x-3*x_par >= 0 && x-3*x_par < x_dim && y-3*y_par >= 0 && y-3*y_par < y_dim && this->find_soldier(x-3*x_par, y-3*y_par, false) == -1 &&
				 this->find_townhall(x-3*x_par, y-3*y_par, false) == -1)
				{
					//game_state g = *this;
					game_state* g = new game_state(this);
					g->change_state(x,y,x-3*x_par,y-3*y_par,1,enemy);
					moves.push_back(make_pair(moves.size(),g));
				}
				if(x-4*x_par >= 0 && x-4*x_par < x_dim && y-4*y_par >= 0 && y-4*y_par < y_dim && this->find_soldier(x-4*x_par, y-4*y_par, false) == -1 &&
				 this->find_townhall(x-4*x_par, y-4*y_par, false) == -1)
				{
					//game_state g = *this;
					game_state* g = new game_state(this);
					g->change_state(x,y,x-4*x_par,y-4*y_par,1,enemy);
					moves.push_back(make_pair(moves.size(),g));
				}
			}

		}
	}
	else
	{
		vector<soldier> soldiers = this->enemy_soldiers;
		vector<pair<soldier, int> > cannons = this->enemy_cannons;
		int id = this->id;
		//Soldier moves
		for(int i=0;i<soldiers.size();++i)
		{
			int x = soldiers.at(i).getX();
			int y = soldiers.at(i).getY();
			if(id==0)//enemy is white
			{
				//forward soldier
				if(y<(y_dim-1) && this->find_soldier(x,(y+1),enemy)==-1)//forward move
				{
					//game_state g = *this;
					game_state* g = new game_state(this);
					g->change_state(x,y,x,y+1,0,enemy);
					moves.push_back(make_pair(moves.size(),g));
				}
				if(y<(y_dim-1) && (x<x_dim-1) && this->find_soldier(x+1,y+1,enemy)==-1)//positive diagonal move
				{
					//game_state g = *this;
					game_state* g = new game_state(this);
					g->change_state(x,y,x+1,y+1,0,enemy);
					moves.push_back(make_pair(moves.size(),g));
				}
				if(y<(y_dim-1) && (x>0) && this->find_soldier(x-1,y+1,enemy)==-1)//negative diagonal move
				{
					//game_state g = *this;
					game_state* g = new game_state(this);
					g->change_state(x,y,x-1,y+1,0,enemy);
					moves.push_back(make_pair(moves.size(),g));
				}
				//sideways killer moves
				if(x < (x_dim -1) && (this->find_soldier(x+1,y,!enemy)!=-1 || this->find_townhall(x+1,y,!enemy)!=-1) )//positive horiontal killer move
				{
					//game_state g = *this;
					game_state* g = new game_state(this);
					g->change_state(x,y,x+1,y,0,enemy);
					moves.push_back(make_pair(moves.size(),g));
				}
				if(x > 0 && (this->find_soldier(x-1,y,!enemy)!=-1 || this->find_townhall(x-1,y,!enemy)!=-1))//negative horiontal killer move
				{
					//game_state g = *this;
					game_state* g = new game_state(this);
					g->change_state(x,y,x-1,y,0,enemy);
					moves.push_back(make_pair(moves.size(),g));
				}
				//retreat backard moves
				if(this->find_soldier(x-1,y,!enemy) != -1 || this->find_soldier(x+1,y,!enemy) != -1 || this->find_soldier(x-1,y+1,!enemy) != -1
					|| this->find_soldier(x+1,y+1,!enemy) != -1 || this->find_soldier(x,y+1,!enemy) != -1)
				{
					//backward
					if((y-2) >= 0 && this->find_soldier(x,y-2,enemy) == -1 && this->find_townhall(x,y-2,enemy) == -1)
					{
						//game_state g = *this;
						game_state* g = new game_state(this);
						g->change_state(x,y,x,y-2,0,enemy);
						moves.push_back(make_pair(moves.size(),g));
					}
					//positive diagonal
					if((y-2)>=0 && (x-2)>=0 && this->find_soldier(x-2,y-2,enemy) == -1 && this->find_townhall(x-2,y-2,enemy) == -1)
					{
						//game_state g = *this;
						game_state* g = new game_state(this);
						g->change_state(x,y,x-2,y-2,0,enemy);
						moves.push_back(make_pair(moves.size(),g));
					}
					//negative diagonal
					if((y-2)>=0 && (x+2)< x_dim && this->find_soldier(x+2,y-2,enemy)==-1 && this->find_townhall(x+2,y-2,enemy)==-1)
					{
						//game_state g = *this;
						game_state* g = new game_state(this);
						g->change_state(x,y,x+2,y-2,0,enemy);
						moves.push_back(make_pair(moves.size(),g));
					}
				}
			}
			else if(id==1)//enemy is black
			{
				//forward soldier
				if(y>0 && this->find_soldier(x,(y-1),enemy)==-1)//forward move
				{
					//game_state g = *this;
					game_state* g = new game_state(this);
					g->change_state(x,y,x,y-1,0,enemy);
					moves.push_back(make_pair(moves.size(),g));
				}
				if(y>0 && x>0 && this->find_soldier(x-1,y-1,enemy)==-1)//positive diagonal move
				{
					//game_state g = *this;
					game_state* g = new game_state(this);
					g->change_state(x,y,x-1,y-1,0,enemy);
					moves.push_back(make_pair(moves.size(),g));
				}
				if(y>0 && (x<x_dim-1) && this->find_soldier(x+1,y-1,enemy)==-1)//negative diagonal move
				{
					//game_state g = *this;
					game_state* g = new game_state(this);
					g->change_state(x,y,x+1,y-1,0,enemy);
					moves.push_back(make_pair(moves.size(),g));
				}
				//sideways killer moves
				if(x < (x_dim -1) && (this->find_soldier(x+1,y,!enemy)!=-1  || this->find_townhall(x+1,y,!enemy)!=-1))//positive horiontal killer move
				{
					//game_state g = *this;
					game_state* g = new game_state(this);
					g->change_state(x,y,x+1,y,0,enemy);
					moves.push_back(make_pair(moves.size(),g));
				}
				if(x > 0 && (this->find_soldier(x-1,y,!enemy)!=-1 || this->find_townhall(x-1,y,!enemy)!=-1))//negative horiontal killer move
				{
					//game_state g = *this;
					game_state* g = new game_state(this);
					g->change_state(x,y,x-1,y,0,enemy);
					moves.push_back(make_pair(moves.size(),g));
				}
				//retreat backard moves
				if(this->find_soldier(x-1,y,!enemy) != -1 || this->find_soldier(x+1,y,!enemy) != -1 || this->find_soldier(x-1,y-1,!enemy) != -1
					|| this->find_soldier(x+1,y-1,!enemy) != -1 || this->find_soldier(x,y-1,!enemy) != -1)
				{
					//backward
					if((y+2<y_dim) && this->find_soldier(x,y+2,enemy) == -1 && this->find_townhall(x,y+2,enemy) == -1)
					{
						//game_state g = *this;
						game_state* g = new game_state(this);
						g->change_state(x,y,x,y+2,0,enemy);
						moves.push_back(make_pair(moves.size(),g));
					}
					//positive diagonal
					if((y+2<y_dim) && (x+2<x_dim) && this->find_soldier(x+2,y+2,enemy) == -1 && this->find_townhall(x+2,y+2,enemy) == -1)
					{
						//game_state g = *this;
						game_state* g = new game_state(this);
						g->change_state(x,y,x+2,y+2,0,enemy);
						moves.push_back(make_pair(moves.size(),g));
					}
					//negative diagonal
					if((y+2<y_dim) && (x-2>=0) && this->find_soldier(x-2,y+2,enemy)==-1 && this->find_townhall(x-2,y+2,enemy)==-1)
					{
						//game_state g = *this;
						game_state* g = new game_state(this);
						g->change_state(x,y,x-2,y+2,0,enemy);
						moves.push_back(make_pair(moves.size(),g));
					}
				}
			}
		}

		///Cannon
		for(int i=0; i<cannons.size(); i++)
		{
			int orientation = cannons.at(i).second;
			int x_par,y_par;
			if(orientation == 0)
			{
				x_par = 0;
				y_par = -1;
			}
			else if(orientation == 1)
			{
				x_par = -1;
				y_par = -1;
			}
			else if(orientation == 2)
			{
				x_par = -1;
				y_par = 0;
			}
			else if(orientation == 3)
			{
				x_par = -1;
				y_par = 1;
			}
			int x = cannons.at(i).first.getX();
			int y = cannons.at(i).first.getY();
			// cannon moves
			int x_temp_1 = x + 2*x_par;
			int y_temp_1 = y + 2*y_par;
			int x_temp_2 = x - 2*x_par;
			int y_temp_2 = y - 2*y_par;
			if(x_temp_1 >= 0 && x_temp_1 < x_dim && y_temp_1 >= 0 && y_temp_1 <y_dim && this->find_soldier(x_temp_1, y_temp_1, true) == -1 &&
			 this->find_soldier(x_temp_1, y_temp_1, false) == -1 && this->find_townhall(x_temp_1, y_temp_1, true) == -1 &&
			 this->find_townhall(x_temp_1, y_temp_1, false) == -1 )
			{
				//game_state g = *this;
				game_state* g = new game_state(this);
				g->change_state(x-x_par,y-y_par,x_temp_1,y_temp_1 ,0,enemy);
				moves.push_back(make_pair(moves.size(),g));
				// cannon bombs
				if(x+3*x_par >= 0 && x+3*x_par < x_dim && y+3*y_par >= 0 && y+3*y_par < y_dim && this->find_soldier(x+3*x_par, y+3*y_par, true) == -1 &&
				 this->find_townhall(x+3*x_par, y+3*y_par, true) == -1 )
				{
					//game_state g = *this;
					game_state* g = new game_state(this);
					g->change_state(x,y,x+3*x_par,y+3*y_par,1,enemy);
					moves.push_back(make_pair(moves.size(),g));
				}
				if(x+4*x_par >= 0 && x+4*x_par < x_dim && y+4*y_par >= 0 && y+4*y_par < y_dim && this->find_soldier(x+4*x_par, y+4*y_par, true) == -1 &&
				 this->find_townhall(x+4*x_par, y+4*y_par, true) == -1)
				{
					//game_state g = *this;
					game_state* g = new game_state(this);
					g->change_state(x,y,x+4*x_par,y+4*y_par,1,enemy);
					moves.push_back(make_pair(moves.size(),g));
				}
			}
			if(x_temp_2 >= 0 && x_temp_2 < x_dim && y_temp_2 >= 0 && y_temp_2 <y_dim && this->find_soldier(x_temp_2, y_temp_2, true) == -1 &&
			 this->find_soldier(x_temp_2, y_temp_2, false) == -1 && this->find_soldier(x_temp_2, y_temp_2, true) == -1 &&
			 this->find_soldier(x_temp_2, y_temp_2, false) == -1)
			{
				//game_state g = *this;
				game_state* g = new game_state(this);
				g->change_state(x+x_par,y+y_par,x_temp_2,y_temp_2 ,0,enemy);
				moves.push_back(make_pair(moves.size(),g));
				// cannon bombs
				if(x-3*x_par >= 0 && x-3*x_par < x_dim && y-3*y_par >= 0 && y-3*y_par < y_dim && this->find_soldier(x-3*x_par, y-3*y_par, true) == -1 &&
				 this->find_townhall(x-3*x_par, y-3*y_par, true) == -1)
				{
					//game_state g = *this;
					game_state* g = new game_state(this);
					g->change_state(x,y,x-3*x_par,y-3*y_par,1,enemy);
					moves.push_back(make_pair(moves.size(),g));
				}
				if(x-4*x_par >= 0 && x-4*x_par < x_dim && y-4*y_par >= 0 && y-4*y_par < y_dim && this->find_soldier(x-4*x_par, y-4*y_par, true) == -1 &&
				 this->find_townhall(x-4*x_par, y-4*y_par, true) == -1)
				{
					//game_state g = *this;
					game_state* g = new game_state(this);
					g->change_state(x,y,x-4*x_par,y-4*y_par,1,enemy);
					moves.push_back(make_pair(moves.size(),g));
				}
			}
		}
	}
	return moves;
}

vector<Move> game_state::possible_moves(bool enemy)
{
	vector<Move> moves;
	int x_dim = this->X;
	int y_dim = this->Y;
	if(!enemy)
	{
		vector<soldier> soldiers = this->soldiers;
		vector<pair<soldier, int> > cannons = this->cannons;
		int id = this->id;
		//Soldier moves
		for(int i=0;i<soldiers.size();++i)
		{
			int x = soldiers.at(i).getX();
			int y = soldiers.at(i).getY();
			if(id==1)//we are white
			{
				//forward soldier
				if(y<(y_dim-1) && this->find_soldier(x,(y+1),enemy)==-1)//forward move
				{

					moves.push_back(Move(x,y,x,y+1,0));

				}
				if(y<(y_dim-1) && (x<x_dim-1) && this->find_soldier(x+1,y+1,enemy)==-1)//positive diagonal move
				{

					moves.push_back(Move(x,y,x+1,y+1,0));

				}
				if(y<(y_dim-1) && (x>0) && this->find_soldier(x-1,y+1,enemy)==-1)//negative diagonal move
				{

					moves.push_back(Move(x,y,x-1,y+1,0));

				}
				//sideways killer moves
				if(x < (x_dim -1) && (this->find_soldier(x+1,y,!enemy)!=-1 || this->find_townhall(x+1,y,!enemy)!=-1) )//positive horiontal killer move
				{

					moves.push_back(Move(x,y,x+1,y,0));

				}
				if(x > 0 && (this->find_soldier(x-1,y,!enemy)!=-1 || this->find_townhall(x-1,y,!enemy)!=-1))//negative horiontal killer move
				{

					moves.push_back(Move(x,y,x-1,y,0));

				}
				//retreat backard moves
				if(this->find_soldier(x-1,y,!enemy) != -1 || this->find_soldier(x+1,y,!enemy) != -1 || this->find_soldier(x-1,y+1,!enemy) != -1
					|| this->find_soldier(x+1,y+1,!enemy) != -1 || this->find_soldier(x,y+1,!enemy) != -1)
				{
					//backward
					if((y-2) >= 0 && this->find_soldier(x,y-2,enemy) == -1 && this->find_townhall(x,y-2,enemy) == -1)
					{

						moves.push_back(Move(x,y,x,y-2,0));

					}
					//positive diagonal
					if((y-2)>=0 && (x-2)>=0 && this->find_soldier(x-2,y-2,enemy) == -1 && this->find_townhall(x-2,y-2,enemy) == -1)
					{

						moves.push_back(Move(x,y,x-2,y-2,0));

					}
					//negative diagonal
					if((y-2)>=0 && (x+2)< x_dim && this->find_soldier(x+2,y-2,enemy)==-1 && this->find_townhall(x+2,y-2,enemy)==-1)
					{

						moves.push_back(Move(x,y,x+2,y-2,0));

					}
				}
			}
			else if(id==0)//we are black
			{
				//forward soldier
				if(y>0 && this->find_soldier(x,(y-1),enemy)==-1)//forward move
				{

					moves.push_back(Move(x,y,x,y-1,0));

				}
				if(y>0 && x>0 && this->find_soldier(x-1,y-1,enemy)==-1)//positive diagonal move
				{

					moves.push_back(Move(x,y,x-1,y-1,0));

				}
				if(y>0 && (x<x_dim-1) && this->find_soldier(x+1,y-1,enemy)==-1)//negative diagonal move
				{

					moves.push_back(Move(x,y,x+1,y-1,0));

				}
				//sideways killer moves
				if(x < (x_dim -1) && (this->find_soldier(x+1,y,!enemy)!=-1 || this->find_townhall(x+1,y,!enemy)!=-1) )//positive horiontal killer move
				{

					moves.push_back(Move(x,y,x+1,y,0));

				}
				if(x > 0 && (this->find_soldier(x-1,y,!enemy)!=-1 || this->find_townhall(x-1,y,!enemy)!=-1))//negative horiontal killer move
				{

					moves.push_back(Move(x,y,x-1,y,0));

				}
				//retreat backard moves
				if(this->find_soldier(x-1,y,!enemy) != -1 || this->find_soldier(x+1,y,!enemy) != -1 || this->find_soldier(x-1,y-1,!enemy) != -1
					|| this->find_soldier(x+1,y-1,!enemy) != -1 || this->find_soldier(x,y-1,!enemy) != -1)
				{
					//backward
					if((y+2<y_dim) && this->find_soldier(x,y+2,enemy) == -1 && this->find_townhall(x,y+2,enemy) == -1)
					{

						moves.push_back(Move(x,y,x,y+2,0));

					}
					//positive diagonal
					if((y+2<y_dim) && (x+2<x_dim) && this->find_soldier(x+2,y+2,enemy) == -1 && this->find_townhall(x+2,y+2,enemy) == -1)
					{

						moves.push_back(Move(x,y,x+2,y+2,0));

					}
					//negative diagonal
					if((y+2<y_dim) && (x-2>=0) && this->find_soldier(x-2,y+2,enemy)==-1 && this->find_townhall(x-2,y+2,enemy)==-1)
					{

						moves.push_back(Move(x,y,x-2,y+2,0));

					}
				}
			}
		}

		///Cannon
		for(int i=0; i<cannons.size(); i++)
		{
			int orientation = cannons.at(i).second;
			int x_par,y_par;
			if(orientation == 0)
			{
				x_par = 0;
				y_par = -1;
			}
			else if(orientation == 1)
			{
				x_par = -1;
				y_par = -1;
			}
			else if(orientation == 2)
			{
				x_par = -1;
				y_par = 0;
			}
			else if(orientation == 3)
			{
				x_par = -1;
				y_par = 1;
			}
			int x = cannons.at(i).first.getX();
			int y = cannons.at(i).first.getY();
			// cannon moves
			int x_temp_1 = x + 2*x_par;
			int y_temp_1 = y + 2*y_par;
			int x_temp_2 = x - 2*x_par;
			int y_temp_2 = y - 2*y_par;
			if(x_temp_1 >= 0 && x_temp_1 < x_dim && y_temp_1 >= 0 && y_temp_1 <y_dim && this->find_soldier(x_temp_1, y_temp_1, true) == -1 &&
			 this->find_soldier(x_temp_1, y_temp_1, false) == -1 && this->find_townhall(x_temp_1, y_temp_1, true) == -1 &&
			 this->find_townhall(x_temp_1, y_temp_1, false) == -1 )
			{
				moves.push_back(Move(x-x_par,y-y_par,x_temp_1,y_temp_1 ,0));

				// cannon bombs
				if(x+3*x_par >= 0 && x+3*x_par < x_dim && y+3*y_par >= 0 && y+3*y_par < y_dim && this->find_soldier(x+3*x_par, y+3*y_par, false) == -1 &&
				 this->find_townhall(x+3*x_par, y+3*y_par, false) == -1 )
				{

					moves.push_back(Move(x,y,x+3*x_par,y+3*y_par,1));

				}
				if(x+4*x_par >= 0 && x+4*x_par < x_dim && y+4*y_par >= 0 && y+4*y_par < y_dim && this->find_soldier(x+4*x_par, y+4*y_par, false) == -1 &&
				 this->find_townhall(x+4*x_par, y+4*y_par, false) == -1)
				{

					moves.push_back(Move(x,y,x+4*x_par,y+4*y_par,1));

				}
			}
			if(x_temp_2 >= 0 && x_temp_2 < x_dim && y_temp_2 >= 0 && y_temp_2 <y_dim && this->find_soldier(x_temp_2, y_temp_2, true) == -1 &&
			 this->find_soldier(x_temp_2, y_temp_2, false) == -1 && this->find_soldier(x_temp_2, y_temp_2, true) == -1 &&
			 this->find_soldier(x_temp_2, y_temp_2, false) == -1)
			{
				moves.push_back(Move(x+x_par,y+y_par,x_temp_2,y_temp_2 ,0));

				// cannon bombs
				if(x-3*x_par >= 0 && x-3*x_par < x_dim && y-3*y_par >= 0 && y-3*y_par < y_dim && this->find_soldier(x-3*x_par, y-3*y_par, false) == -1 &&
				 this->find_townhall(x-3*x_par, y-3*y_par, false) == -1)
				{

					moves.push_back(Move(x,y,x-3*x_par,y-3*y_par,1));

				}
				if(x-4*x_par >= 0 && x-4*x_par < x_dim && y-4*y_par >= 0 && y-4*y_par < y_dim && this->find_soldier(x-4*x_par, y-4*y_par, false) == -1 &&
				 this->find_townhall(x-4*x_par, y-4*y_par, false) == -1)
				{

					moves.push_back(Move(x,y,x-4*x_par,y-4*y_par,1));

				}
			}
		}
	}
	else
	{
		vector<soldier> soldiers = this->enemy_soldiers;
		vector<pair<soldier, int> > cannons = this->enemy_cannons;
		int id = this->id;
		//Soldier moves
		for(int i=0;i<soldiers.size();++i)
		{
			int x = soldiers.at(i).getX();
			int y = soldiers.at(i).getY();
			if(id==0)//enemy is white
			{
				//forward soldier
				if(y<(y_dim-1) && this->find_soldier(x,(y+1),enemy)==-1)//forward move
				{

					moves.push_back(Move(x,y,x,y+1,0));


				}
				if(y<(y_dim-1) && (x<x_dim-1) && this->find_soldier(x+1,y+1,enemy)==-1)//positive diagonal move
				{

					moves.push_back(Move(x,y,x+1,y+1,0));

				}
				if(y<(y_dim-1) && (x>0) && this->find_soldier(x-1,y+1,enemy)==-1)//negative diagonal move
				{

					moves.push_back(Move(x,y,x-1,y+1,0));

				}
				//sideways killer moves
				if(x < (x_dim -1) && (this->find_soldier(x+1,y,!enemy)!=-1 ||this->find_townhall(x+1,y,!enemy)!=-1) )//positive horiontal killer move
				{

					moves.push_back(Move(x,y,x+1,y,0));

				}
				if(x > 0 && (this->find_soldier(x-1,y,!enemy)!=-1 || this->find_townhall(x-1,y,!enemy)!=-1))//negative horiontal killer move
				{

					moves.push_back(Move(x,y,x-1,y,0));

				}
				//retreat backard moves
				if(this->find_soldier(x-1,y,!enemy) != -1 || this->find_soldier(x+1,y,!enemy) != -1 || this->find_soldier(x-1,y+1,!enemy) != -1
					|| this->find_soldier(x+1,y+1,!enemy) != -1 || this->find_soldier(x,y+1,!enemy) != -1)
				{
					//backward
					if((y-2) >= 0 && this->find_soldier(x,y-2,enemy) == -1 && this->find_townhall(x,y-2,enemy) == -1)
					{

						moves.push_back(Move(x,y,x,y-2,0));

					}
					//positive diagonal
					if((y-2)>=0 && (x-2)>=0 && this->find_soldier(x-2,y-2,enemy) == -1 && this->find_townhall(x-2,y-2,enemy) == -1)
					{

						moves.push_back(Move(x,y,x-2,y-2,0));

					}
					//negative diagonal
					if((y-2)>=0 && (x+2)< x_dim && this->find_soldier(x+2,y-2,enemy)==-1 && this->find_townhall(x+2,y-2,enemy)==-1)
					{

						moves.push_back(Move(x,y,x+2,y-2,0));

					}
				}
			}
			else if(id==1)//enemy is black
			{
				//forward soldier
				if(y>0 && this->find_soldier(x,(y-1),enemy)==-1)//forward move
				{

					moves.push_back(Move(x,y,x,y-1,0));

				}
				if(y>0 && x>0 && this->find_soldier(x-1,y-1,enemy)==-1)//positive diagonal move
				{

					moves.push_back(Move(x,y,x-1,y-1,0));

				}
				if(y>0 && (x<x_dim-1) && this->find_soldier(x+1,y-1,enemy)==-1)//negative diagonal move
				{

					moves.push_back(Move(x,y,x+1,y-1,0));

				}
				//sideways killer moves
				if(x < (x_dim -1) && (this->find_soldier(x+1,y,!enemy)!=-1 || this->find_townhall(x+1,y,!enemy)!=-1))//positive horiontal killer move
				{

					moves.push_back(Move(x,y,x+1,y,0));

				}
				if(x > 0 && (this->find_soldier(x-1,y,!enemy)!=-1 || this->find_townhall(x-1,y,!enemy)!=-1))//negative horiontal killer move
				{

					moves.push_back(Move(x,y,x-1,y,0));

				}
				//retreat backard moves
				if(this->find_soldier(x-1,y,!enemy) != -1 || this->find_soldier(x+1,y,!enemy) != -1 || this->find_soldier(x-1,y-1,!enemy) != -1
					|| this->find_soldier(x+1,y-1,!enemy) != -1 || this->find_soldier(x,y-1,!enemy) != -1)
				{
					//backward
					if((y+2<y_dim) && this->find_soldier(x,y+2,enemy) == -1 && this->find_townhall(x,y+2,enemy) == -1)
					{

						moves.push_back(Move(x,y,x,y+2,0));

					}
					//positive diagonal
					if((y+2<y_dim) && (x+2<x_dim) && this->find_soldier(x+2,y+2,enemy) == -1 && this->find_townhall(x+2,y+2,enemy) == -1)
					{

						moves.push_back(Move(x,y,x+2,y+2,0));

					}
					//negative diagonal
					if((y+2<y_dim) && (x-2>=0) && this->find_soldier(x-2,y+2,enemy)==-1 && this->find_townhall(x-2,y+2,enemy)==-1)
					{

						moves.push_back(Move(x,y,x-2,y+2,0));

					}
				}
			}
		}

		///Cannon
		for(int i=0; i<cannons.size(); i++)
		{
			int orientation = cannons.at(i).second;
			int x_par,y_par;
			if(orientation == 0)
			{
				x_par = 0;
				y_par = -1;
			}
			else if(orientation == 1)
			{
				x_par = -1;
				y_par = -1;
			}
			else if(orientation == 2)
			{
				x_par = -1;
				y_par = 0;
			}
			else if(orientation == 3)
			{
				x_par = -1;
				y_par = 1;
			}
			int x = cannons.at(i).first.getX();
			int y = cannons.at(i).first.getY();
			// cannon moves
			int x_temp_1 = x + 2*x_par;
			int y_temp_1 = y + 2*y_par;
			int x_temp_2 = x - 2*x_par;
			int y_temp_2 = y - 2*y_par;
			if(x_temp_1 >= 0 && x_temp_1 < x_dim && y_temp_1 >= 0 && y_temp_1 <y_dim && this->find_soldier(x_temp_1, y_temp_1, true) == -1 &&
			 this->find_soldier(x_temp_1, y_temp_1, false) == -1 && this->find_townhall(x_temp_1, y_temp_1, true) == -1 &&
			 this->find_townhall(x_temp_1, y_temp_1, false) == -1 )
			{
				moves.push_back(Move(x-x_par,y-y_par,x_temp_1,y_temp_1 ,0));

				// cannon bombs
				if(x+3*x_par >= 0 && x+3*x_par < x_dim && y+3*y_par >= 0 && y+3*y_par < y_dim && this->find_soldier(x+3*x_par, y+3*y_par, true) == -1 &&
				 this->find_townhall(x+3*x_par, y+3*y_par, true) == -1 )
				{

					moves.push_back(Move(x,y,x+3*x_par,y+3*y_par,1));

				}
				if(x+4*x_par >= 0 && x+4*x_par < x_dim && y+4*y_par >= 0 && y+4*y_par < y_dim && this->find_soldier(x+4*x_par, y+4*y_par, true) == -1 &&
				 this->find_townhall(x+4*x_par, y+4*y_par, true) == -1)
				{

					moves.push_back(Move(x,y,x+4*x_par,y+4*y_par,1));

				}
			}
			if(x_temp_2 >= 0 && x_temp_2 < x_dim && y_temp_2 >= 0 && y_temp_2 <y_dim && this->find_soldier(x_temp_2, y_temp_2, true) == -1 &&
			 this->find_soldier(x_temp_2, y_temp_2, false) == -1 && this->find_soldier(x_temp_2, y_temp_2, true) == -1 &&
			 this->find_soldier(x_temp_2, y_temp_2, false) == -1)
			{
				moves.push_back(Move(x+x_par,y+y_par,x_temp_2,y_temp_2 ,0));

				// cannon bombs
				if(x-3*x_par >= 0 && x-3*x_par < x_dim && y-3*y_par >= 0 && y-3*y_par < y_dim && this->find_soldier(x-3*x_par, y-3*y_par, true) == -1 &&
				 this->find_townhall(x-3*x_par, y-3*y_par, true) == -1)
				{

					moves.push_back(Move(x,y,x-3*x_par,y-3*y_par,1));

				}
				if(x-4*x_par >= 0 && x-4*x_par < x_dim && y-4*y_par >= 0 && y-4*y_par < y_dim && this->find_soldier(x-4*x_par, y-4*y_par, true) == -1 &&
				 this->find_townhall(x-4*x_par, y-4*y_par, true) == -1)
				{

					moves.push_back(Move(x,y,x-4*x_par,y-4*y_par,1));

				}
			}
		}
	}
	return moves;
}