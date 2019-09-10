#include <bits/stdc++.h>
#include "game_state.h"

game_state::game_state(int a, int x, int y, double t)
{
	id=a;
	X=x;
	Y=y;
	time = t;
	if(a==0)
	{
		for(int i=0;i<(x/2);++i)
		{
			enemy_townhalls.push_back(make_pair(0,2*i));
			townhalls.push_back(make_pair(y-1,(2*i+1)));
			for(int j=0;j<3;++j)
			{
				soldier* s = new soldier(0,0);
				s->move(y-1-j,2*i);
				soldiers.push_back(*s);
				soldier* s1 = new soldier(0,0);
				s->move(j,(2*i+1));
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
			townhalls.push_back(make_pair(0,2*i));
			enemy_townhalls.push_back(make_pair(y-1,(2*i+1)));
			for(int j=0;j<3;++j)
			{
				soldier* s = new soldier(0,0);
				s->move(y-1-j,2*i);
				enemy_soldiers.push_back(*s);
				soldier* s1 = new soldier(0,0);
				s->move(j,(2*i+1));
				soldiers.push_back(*s1);
				if(j==1)
				{
					enemy_cannons.push_back(make_pair(*s,0));
					cannons.push_back(make_pair(*s1,0));
				}
			}
		}		
	}
}

vector<int> game_state::find_Cannon(int x1, int y1, bool enemy)
{
	vector<int> res;
	if(!enemy)
	{
		for(int i=0;i<cannons.size();++i)
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
			if(a == 1)// positive diagonal cannon
			{
				if((x1==x2+1 && y1==y2+1) || (x1==x2-1 && y1==y2-1))
					res.push_back(i);
			}
			if(a == 2)//horizontal cannon
			{
				if((y1==y2) && (x1==(x2-1) || x1==(x2+1)))
					res.push_back(i);
			}
			if(a == 3) // negative diagonal cannon
			{
				if((x1==x2+1 && y1==y2-1) || (x1==x2-1 && y1==y2+1))
					res.push_back(i);
			}
		}
	}
	else
	{
		for(int i=0;i<enemy_cannons.size();++i)
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
			if(a==1)// positive diagonal cannon
			{
				if((x1==x2+1 && y1==y2+1) || (x1==x2-1 && y1==y2-1))
					res.push_back(i);
			}
			if(a==2)//horizontal cannon
			{
				if((y1==y2) && (x1==(x2-1) || x1==(x2+1)))
					res.push_back(i);
			}
			if(a==3) // negative diagonal cannon
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
			soldier s;
			if(!enemy) s = soldiers[sold_1]; else s = enemy_soldiers[sold_1];
			res.push_back(make_pair(s,0));
		}
		if(sold_5 != -1)
		{
			soldier s;
			if(!enemy) s = soldiers[sold_index]; else s = enemy_soldiers[sold_index];
			res.push_back(make_pair(s, 0));
		}
	}
	if(sold_2 != -1)
	{
		int s_temp = find_soldier(x+2, y-2, enemy);
		if(s_temp != -1)
		{
			soldier s;
			if(!enemy) s = soldiers[sold_2]; else s = enemy_soldiers[sold_2];
			res.push_back(make_pair(s,3));
		}
		if(sold_6 != -1)
		{
			soldier s;
			if(!enemy) s = soldiers[sold_index]; else s = enemy_soldiers[sold_index];
			res.push_back(make_pair(s, 3));
		}
	}
	if(sold_3 != -1)
	{
		int s_temp = find_soldier(x+2, y, enemy);
		if(s_temp != -1)
		{
			soldier s;
			if(!enemy) s = soldiers[sold_3]; else s = enemy_soldiers[sold_3];
			res.push_back(make_pair(s,2));
		}
		if(sold_7 != -1)
		{
			soldier s;
			if(!enemy) s = soldiers[sold_index]; else s = enemy_soldiers[sold_index];
			res.push_back(make_pair(s, 2));
		}
	}
	if(sold_4 != -1)
	{
		int s_temp = find_soldier(x+2, y+2, enemy);
		if(s_temp != -1)
		{
			soldier s;
			if(!enemy) s = soldiers[sold_4]; else s = enemy_soldiers[sold_4];
			res.push_back(make_pair(s,1));
		}
		if(sold_8 != -1)
		{
			soldier s;
			if(!enemy) s = soldiers[sold_index]; else s = enemy_soldiers[sold_index];
			res.push_back(make_pair(s, 1));
		}
	}
	if(sold_5 != -1)
	{
		int s_temp = find_soldier(x, y+2, enemy);
		if(s_temp != -1)
		{
			soldier s;
			if(!enemy) s = soldiers[sold_5]; else s = enemy_soldiers[sold_5];
			res.push_back(make_pair(s,0));
		}
	}
	if(sold_6 != -1)
	{
		int s_temp = find_soldier(x-2, y+2, enemy);
		if(s_temp != -1)
		{
			soldier s;
			if(!enemy) s = soldiers[sold_6]; else s = enemy_soldiers[sold_6];
			res.push_back(make_pair(s,3));
		}
	}
	if(sold_7 != -1)
	{
		int s_temp = find_soldier(x-2, y, enemy);
		if(s_temp != -1)
		{
			soldier s;
			if(!enemy) s = soldiers[sold_7]; else s = enemy_soldiers[sold_7];
			res.push_back(make_pair(s,2));
		}
	}
	if(sold_8 != -1)
	{
		int s_temp = find_soldier(x-2, y-2, enemy);
		if(s_temp != -1)
		{
			soldier s;
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
		for(int i=0;i<soldiers.size();++i)
		{
			if(soldiers.at(i).getX()==x && soldiers.at(i).getY()==y)
				return i;
		}
	}
	else
	{
		for(int i=0;i<enemy_soldiers.size();++i)
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

void remove_cannons (int x, int y, bool enemy)
{
	vector<int> cannon_indexes = find_Cannon(x, y, enemy);
	if(!enemy)
	{
		for(int i=0; i<cannon_indexes.size(); i++)
		{
			int cannon_index = cannon_indexes.at(i);
			if(cannon_index != -1)
			{
				cannons.remove(cannon_index);
			}
		}
	}
	else
	{
		for(int i=0; i<cannon_indexes.size(); i++)
		{
			int cannon_index = cannon_indexes.at(i);
			if(cannon_index != -1)
			{
				enemy_cannons.remove(cannon_index);
			}
		}
	}
	return;
}

void add_cannons (int x, int y, bool enemy)
{
	vector<pair<soldier, int>> new_cannons = find_new_Cannon( x, y, enemy);
	if(!enemy)
	{
		for(int i=0; i<new_cannons.sie(); i++)
		{
			cannons.push_back(new_cannons.at(i));
		}
	}
	else
	{
		for(int i=0; i<new_cannons.sie(); i++)
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
					enemy_soldiers.remove(killed_soldier);
					//update enemy_cannons
					remove_cannons(x2, y2, true);
				}
				//townhall killing
				int killed_townhall = find_townhall(x2, y2, true);
				if(killed_townhall != -1)
				{
					enemy_townhalls.remove(killed_townhall);
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
					soldiers.remove(killed_soldier);
					//update cannons
					remove_cannons(x2, y2, false);
				}
				//townhall dying
				int killed_townhall = find_townhall(x2, y2,	false);
				if(killed_townhall != -1)
				{
					townhalls.remove(killed_townhall);
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
				enemy_soldiers.remove(killed_soldier);
				//update enemy_cannons
				remove_cannons(x2, y2, true);
			}
			//townhall killing
			int killed_townhall = find_townhall(x2, y2, true);
			if(killed_townhall != -1)
			{
				enemy_townhalls.remove(killed_townhall);
			}
		}
		else
		{
			///my coins dying
			//soldier dying 
			int killed_soldier = find_soldier(x2, y2, false);
			if(killed_soldier != -1)
			{
				soldiers.remove(killed_soldier);
				//update cannons
				remove_cannons(x2, y2, false);
			}
			//townhall dying
			int killed_townhall = find_townhall(x2, y2,	false);
			if(killed_townhall != -1)
			{
				townhalls.remove(killed_townhall);
			}
		}
	}
}