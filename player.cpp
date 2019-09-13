#include "player.h"

player::player(int a, int x, int y, double time)
{
	current_state = new game_state(a,x,y);
	remaining_time = time;
}

double player::evaluation_function()
{
	return 0;
}

vector<game_state> player::possible_states(bool enemy)
{
	vector<game_state> moves;
	int x_dim = current_state->X;
	int y_dim = current_state->Y;
	if(!enemy)
	{
		vector<soldier> soldiers = current_state->soldiers;
		vector<pair<soldier, int> > cannons = current_state->cannons;
		int id = current_state->id;
		//Soldier moves
		for(int i=0;i<soldiers.size();++i)
		{
			int x = soldiers.at(i).getX();
			int y = soldiers.at(i).getY();
			if(id==1)//we are white
			{
				//forward soldier
				if(y<(y_dim-1) && current_state->find_soldier(x,(y+1),enemy)==-1)//forward move
				{
					game_state g = *current_state;
					g.change_state(x,y,x,y+1,0,enemy);
					moves.push_back(g);
				}
				if(y<(y_dim-1) && (x<x_dim-1) && current_state->find_soldier(x+1,y+1,enemy)==-1)//positive diagonal move
				{
					game_state g = *current_state;
					g.change_state(x,y,x+1,y+1,0,enemy);
					moves.push_back(g);					
				}
				if(y<(y_dim-1) && (x>0) && current_state->find_soldier(x-1,y+1,enemy)==-1)//negative diagonal move
				{
					game_state g = *current_state;
					g.change_state(x,y,x-1,y+1,0,enemy);
					moves.push_back(g);					
				}
				//sideways killer moves
				if(x < (x_dim -1) && current_state->find_soldier(x+1,y,!enemy)!=-1)//positive horiontal killer move 
				{
					game_state g = *current_state;
					g.change_state(x,y,x+1,y,0,enemy);
					moves.push_back(g);					
				}
				if(x > 0 && current_state->find_soldier(x-1,y,!enemy)!=-1)//negative horiontal killer move 
				{
					game_state g = *current_state;
					g.change_state(x,y,x-1,y,0,enemy);
					moves.push_back(g);					
				}
				//retreat backard moves
				if(current_state->find_soldier(x-1,y,!enemy) != -1 || current_state->find_soldier(x+1,y,!enemy) != -1 || current_state->find_soldier(x-1,y+1,!enemy) != -1
					|| current_state->find_soldier(x+1,y+1,!enemy) != -1 || current_state->find_soldier(x,y+1,!enemy) != -1)
				{
					//backward
					if((y-2) >= 0 && current_state->find_soldier(x,y-2,enemy) == -1 && current_state->find_townhall(x,y-2,enemy) == -1)
					{
						game_state g = *current_state;
						g.change_state(x,y,x,y-2,0,enemy);
						moves.push_back(g);
					}
					//positive diagonal
					if((y-2)>=0 && (x-2)>=0 && current_state->find_soldier(x-2,y-2,enemy) == -1 && current_state->find_townhall(x-2,y-2,enemy) == -1)
					{
						game_state g = *current_state;
						g.change_state(x,y,x-2,y-2,0,enemy);
						moves.push_back(g);
					}
					//negative diagonal
					if((y-2)>=0 && (x+2)< x_dim && current_state->find_soldier(x+2,y-2,enemy)==-1 && current_state->find_townhall(x+2,y-2,enemy)==-1)
					{
						game_state g = *current_state;
						g.change_state(x,y,x+2,y-2,0,enemy);
						moves.push_back(g);
					}
				}
			}
			else if(id==0)//we are black 
			{
				//forward soldier
				if(y>0 && current_state->find_soldier(x,(y-1),enemy)==-1)//forward move
				{
					game_state g = *current_state;
					g.change_state(x,y,x,y-1,0,enemy);
					moves.push_back(g);
				}
				if(y>0 && x>0 && current_state->find_soldier(x-1,y-1,enemy)==-1)//positive diagonal move
				{
					game_state g = *current_state;
					g.change_state(x,y,x-1,y-1,0,enemy);
					moves.push_back(g);					
				}
				if(y>0 && (x<x_dim-1) && current_state->find_soldier(x+1,y-1,enemy)==-1)//negative diagonal move
				{
					game_state g = *current_state;
					g.change_state(x,y,x+1,y-1,0,enemy);
					moves.push_back(g);					
				}
				//sideways killer moves
				if(x < (x_dim -1) && current_state->find_soldier(x+1,y,!enemy)!=-1)//positive horiontal killer move 
				{
					game_state g = *current_state;
					g.change_state(x,y,x+1,y,0,enemy);
					moves.push_back(g);					
				}
				if(x > 0 && current_state->find_soldier(x-1,y,!enemy)!=-1)//negative horiontal killer move 
				{
					game_state g = *current_state;
					g.change_state(x,y,x-1,y,0,enemy);
					moves.push_back(g);					
				}
				//retreat backard moves
				if(current_state->find_soldier(x-1,y,!enemy) != -1 || current_state->find_soldier(x+1,y,!enemy) != -1 || current_state->find_soldier(x-1,y-1,!enemy) != -1
					|| current_state->find_soldier(x+1,y-1,!enemy) != -1 || current_state->find_soldier(x,y-1,!enemy) != -1)
				{
					//backward
					if((y+2<y_dim) && current_state->find_soldier(x,y+2,enemy) == -1 && current_state->find_townhall(x,y+2,enemy) == -1 )
					{
						game_state g = *current_state;
						g.change_state(x,y,x,y+2,0,enemy);
						moves.push_back(g);
					}
					//positive diagonal
					if((y+2<y_dim) && (x+2<x_dim) && current_state->find_soldier(x+2,y+2,enemy) == -1 && current_state->find_townhall(x+2,y+2,enemy) == -1)
					{
						game_state g = *current_state;
						g.change_state(x,y,x+2,y+2,0,enemy);
						moves.push_back(g);
					}
					//negative diagonal
					if((y+2<y_dim) && (x-2>=0) && current_state->find_soldier(x-2,y+2,enemy)==-1 && current_state->find_townhall(x-2,y+2,enemy)==-1)
					{
						game_state g = *current_state;
						g.change_state(x,y,x-2,y+2,0,enemy);
						moves.push_back(g);
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
			if(x_temp_1 >= 0 && x_temp_1 < x_dim && y_temp_1 >= 0 && y_temp_1 <y_dim && current_state->find_soldier(x_temp_1, y_temp_1, true) == -1 &&
			 current_state->find_soldier(x_temp_1, y_temp_1, false) == -1 && current_state->find_townhall(x_temp_1, y_temp_1, true) == -1 &&
			 current_state->find_townhall(x_temp_1, y_temp_1, false) == -1 )
			{
				game_state g = *current_state;
				g.change_state(x-x_par,y-y_par,x_temp_1,y_temp_1 ,0,enemy); 
				moves.push_back(g);
				// cannon bombs
				if(x+3*x_par >= 0 && x+3*x_par < x_dim && y+3*y_par >= 0 && y+3*y_par < y_dim && current_state->find_soldier(x+3*x_par, y+3*y_par, false) == -1 &&
				 current_state->find_townhall(x+3*x_par, y+3*y_par, false) == -1 )
				{
					game_state g = *current_state;
					g.change_state(x,y,x+3*x_par,y+3*y_par,1,enemy);
					moves.push_back(g);
				}
				if(x+4*x_par >= 0 && x+4*x_par < x_dim && y+4*y_par >= 0 && y+4*y_par < y_dim && current_state->find_soldier(x+4*x_par, y+4*y_par, false) == -1 &&
				 current_state->find_townhall(x+4*x_par, y+4*y_par, false) == -1)
				{
					game_state g = *current_state;
					g.change_state(x,y,x+4*x_par,y+4*y_par,1,enemy);
					moves.push_back(g);
				}
			}
			if(x_temp_2 >= 0 && x_temp_2 < x_dim && y_temp_2 >= 0 && y_temp_2 <y_dim && current_state->find_soldier(x_temp_2, y_temp_2, true) == -1 &&
			 current_state->find_soldier(x_temp_2, y_temp_2, false) == -1 && current_state->find_soldier(x_temp_2, y_temp_2, true) == -1 &&
			 current_state->find_soldier(x_temp_2, y_temp_2, false) == -1)
			{
				game_state g = *current_state;
				g.change_state(x+x_par,y+y_par,x_temp_2,y_temp_2 ,0,enemy);
				moves.push_back(g);
				// cannon bombs
				if(x-3*x_par >= 0 && x-3*x_par < x_dim && y-3*y_par >= 0 && y-3*y_par < y_dim && current_state->find_soldier(x-3*x_par, y-3*y_par, false) == -1 &&
				 current_state->find_townhall(x-3*x_par, y-3*y_par, false) == -1)
				{
					game_state g = *current_state;
					g.change_state(x,y,x-3*x_par,y-3*y_par,1,enemy);
					moves.push_back(g);
				}
				if(x-4*x_par >= 0 && x-4*x_par < x_dim && y-4*y_par >= 0 && y-4*y_par < y_dim && current_state->find_soldier(x-4*x_par, y-4*y_par, false) == -1 &&
				 current_state->find_townhall(x-4*x_par, y-4*y_par, false) == -1)
				{
					game_state g = *current_state;
					g.change_state(x,y,x-4*x_par,y-4*y_par,1,enemy);
					moves.push_back(g);
				}
			}
			
		}
	}
	else
	{
		vector<soldier> soldiers = current_state->enemy_soldiers;
		vector<pair<soldier, int> > cannons = current_state->enemy_cannons;
		int id = current_state->id;
		//Soldier moves
		for(int i=0;i<soldiers.size();++i)
		{
			int x = soldiers.at(i).getX();
			int y = soldiers.at(i).getY();
			if(id==0)//enemy is white
			{
				//forward soldier
				if(y<(y_dim-1) && current_state->find_soldier(x,(y+1),enemy)==-1)//forward move
				{
					game_state g = *current_state;
					g.change_state(x,y,x,y+1,0,enemy);
					moves.push_back(g);
				}
				if(y<(y_dim-1) && (x<x_dim-1) && current_state->find_soldier(x+1,y+1,enemy)==-1)//positive diagonal move
				{
					game_state g = *current_state;
					g.change_state(x,y,x+1,y+1,0,enemy);
					moves.push_back(g);					
				}
				if(y<(y_dim-1) && (x>0) && current_state->find_soldier(x-1,y+1,enemy)==-1)//negative diagonal move
				{
					game_state g = *current_state;
					g.change_state(x,y,x-1,y+1,0,enemy);
					moves.push_back(g);					
				}
				//sideways killer moves
				if(x < (x_dim -1) && current_state->find_soldier(x+1,y,!enemy)!=-1)//positive horiontal killer move 
				{
					game_state g = *current_state;
					g.change_state(x,y,x+1,y,0,enemy);
					moves.push_back(g);					
				}
				if(x > 0 && current_state->find_soldier(x-1,y,!enemy)!=-1)//negative horiontal killer move 
				{
					game_state g = *current_state;
					g.change_state(x,y,x-1,y,0,enemy);
					moves.push_back(g);					
				}
				//retreat backard moves
				if(current_state->find_soldier(x-1,y,!enemy) != -1 || current_state->find_soldier(x+1,y,!enemy) != -1 || current_state->find_soldier(x-1,y+1,!enemy) != -1
					|| current_state->find_soldier(x+1,y+1,!enemy) != -1 || current_state->find_soldier(x,y+1,!enemy) != -1)
				{
					//backward
					if((y-2) >= 0 && current_state->find_soldier(x,y-2,enemy) == -1 && current_state->find_townhall(x,y-2,enemy) == -1)
					{
						game_state g = *current_state;
						g.change_state(x,y,x,y-2,0,enemy);
						moves.push_back(g);
					}
					//positive diagonal
					if((y-2)>=0 && (x-2)>=0 && current_state->find_soldier(x-2,y-2,enemy) == -1 && current_state->find_townhall(x-2,y-2,enemy) == -1)
					{
						game_state g = *current_state;
						g.change_state(x,y,x-2,y-2,0,enemy);
						moves.push_back(g);
					}
					//negative diagonal
					if((y-2)>=0 && (x+2)< x_dim && current_state->find_soldier(x+2,y-2,enemy)==-1 && current_state->find_townhall(x+2,y-2,enemy)==-1)
					{
						game_state g = *current_state;
						g.change_state(x,y,x+2,y-2,0,enemy);
						moves.push_back(g);
					}
				}
			}
			else if(id==1)//enemy is black
			{
				//forward soldier
				if(y>0 && current_state->find_soldier(x,(y-1),enemy)==-1)//forward move
				{
					game_state g = *current_state;
					g.change_state(x,y,x,y-1,0,enemy);
					moves.push_back(g);
				}
				if(y>0 && x>0 && current_state->find_soldier(x-1,y-1,enemy)==-1)//positive diagonal move
				{
					game_state g = *current_state;
					g.change_state(x,y,x-1,y-1,0,enemy);
					moves.push_back(g);					
				}
				if(y>0 && (x<x_dim-1) && current_state->find_soldier(x+1,y-1,enemy)==-1)//negative diagonal move
				{
					game_state g = *current_state;
					g.change_state(x,y,x+1,y-1,0,enemy);
					moves.push_back(g);					
				}
				//sideways killer moves
				if(x < (x_dim -1) && current_state->find_soldier(x+1,y,!enemy)!=-1)//positive horiontal killer move 
				{
					game_state g = *current_state;
					g.change_state(x,y,x+1,y,0,enemy);
					moves.push_back(g);					
				}
				if(x > 0 && current_state->find_soldier(x-1,y,!enemy)!=-1)//negative horiontal killer move 
				{
					game_state g = *current_state;
					g.change_state(x,y,x-1,y,0,enemy);
					moves.push_back(g);					
				}
				//retreat backard moves
				if(current_state->find_soldier(x-1,y,!enemy) != -1 || current_state->find_soldier(x+1,y,!enemy) != -1 || current_state->find_soldier(x-1,y-1,!enemy) != -1
					|| current_state->find_soldier(x+1,y-1,!enemy) != -1 || current_state->find_soldier(x,y-1,!enemy) != -1)
				{
					//backward
					if((y+2<y_dim) && current_state->find_soldier(x,y+2,enemy) == -1 && current_state->find_townhall(x,y+2,enemy) == -1)
					{
						game_state g = *current_state;
						g.change_state(x,y,x,y+2,0,enemy);
						moves.push_back(g);
					}
					//positive diagonal
					if((y+2<y_dim) && (x+2<x_dim) && current_state->find_soldier(x+2,y+2,enemy) == -1 && current_state->find_townhall(x+2,y+2,enemy) == -1)
					{
						game_state g = *current_state;
						g.change_state(x,y,x+2,y+2,0,enemy);
						moves.push_back(g);
					}
					//negative diagonal
					if((y+2<y_dim) && (x-2>=0) && current_state->find_soldier(x-2,y+2,enemy)==-1 && current_state->find_townhall(x-2,y+2,enemy)==-1)
					{
						game_state g = *current_state;
						g.change_state(x,y,x-2,y+2,0,enemy);
						moves.push_back(g);
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
			if(x_temp_1 >= 0 && x_temp_1 < x_dim && y_temp_1 >= 0 && y_temp_1 <y_dim && current_state->find_soldier(x_temp_1, y_temp_1, true) == -1 &&
			 current_state->find_soldier(x_temp_1, y_temp_1, false) == -1 && current_state->find_townhall(x_temp_1, y_temp_1, true) == -1 &&
			 current_state->find_townhall(x_temp_1, y_temp_1, false) == -1 )
			{
				game_state g = *current_state;
				g.change_state(x-x_par,y-y_par,x_temp_1,y_temp_1 ,0,enemy); 
				moves.push_back(g);
				// cannon bombs
				if(x+3*x_par >= 0 && x+3*x_par < x_dim && y+3*y_par >= 0 && y+3*y_par < y_dim && current_state->find_soldier(x+3*x_par, y+3*y_par, true) == -1 &&
				 current_state->find_townhall(x+3*x_par, y+3*y_par, true) == -1 )
				{
					game_state g = *current_state;
					g.change_state(x,y,x+3*x_par,y+3*y_par,1,enemy);
					moves.push_back(g);
				}
				if(x+4*x_par >= 0 && x+4*x_par < x_dim && y+4*y_par >= 0 && y+4*y_par < y_dim && current_state->find_soldier(x+4*x_par, y+4*y_par, true) == -1 &&
				 current_state->find_townhall(x+4*x_par, y+4*y_par, true) == -1)
				{
					game_state g = *current_state;
					g.change_state(x,y,x+4*x_par,y+4*y_par,1,enemy);
					moves.push_back(g);
				}
			}
			if(x_temp_2 >= 0 && x_temp_2 < x_dim && y_temp_2 >= 0 && y_temp_2 <y_dim && current_state->find_soldier(x_temp_2, y_temp_2, true) == -1 &&
			 current_state->find_soldier(x_temp_2, y_temp_2, false) == -1 && current_state->find_soldier(x_temp_2, y_temp_2, true) == -1 &&
			 current_state->find_soldier(x_temp_2, y_temp_2, false) == -1)
			{
				game_state g = *current_state;
				g.change_state(x+x_par,y+y_par,x_temp_2,y_temp_2 ,0,enemy);
				moves.push_back(g);
				// cannon bombs
				if(x-3*x_par >= 0 && x-3*x_par < x_dim && y-3*y_par >= 0 && y-3*y_par < y_dim && current_state->find_soldier(x-3*x_par, y-3*y_par, true) == -1 &&
				 current_state->find_townhall(x-3*x_par, y-3*y_par, true) == -1)
				{
					game_state g = *current_state;
					g.change_state(x,y,x-3*x_par,y-3*y_par,1,enemy);
					moves.push_back(g);
				}
				if(x-4*x_par >= 0 && x-4*x_par < x_dim && y-4*y_par >= 0 && y-4*y_par < y_dim && current_state->find_soldier(x-4*x_par, y-4*y_par, true) == -1 &&
				 current_state->find_townhall(x-4*x_par, y-4*y_par, true) == -1)
				{
					game_state g = *current_state;
					g.change_state(x,y,x-4*x_par,y-4*y_par,1,enemy);
					moves.push_back(g);
				}
			}
		}
	}
	return moves;
}

vector<Move> player::possible_moves(bool enemy)
{
	vector<Move> moves;
	int x_dim = current_state->X;
	int y_dim = current_state->Y;
	if(!enemy)
	{
		vector<soldier> soldiers = current_state->soldiers;
		vector<pair<soldier, int> > cannons = current_state->cannons;
		int id = current_state->id;
		//Soldier moves
		for(int i=0;i<soldiers.size();++i)
		{
			int x = soldiers.at(i).getX();
			int y = soldiers.at(i).getY();
			if(id==1)//we are white
			{
				//forward soldier
				if(y<(y_dim-1) && current_state->find_soldier(x,(y+1),enemy)==-1)//forward move
				{

					Move* g = new Move(x,y,x,y+1,0);
					moves.push_back(*g);
					delete g;
				}
				if(y<(y_dim-1) && (x<x_dim-1) && current_state->find_soldier(x+1,y+1,enemy)==-1)//positive diagonal move
				{

					Move* g = new Move(x,y,x+1,y+1,0);
					moves.push_back(*g);
					delete g;					
				}
				if(y<(y_dim-1) && (x>0) && current_state->find_soldier(x-1,y+1,enemy)==-1)//negative diagonal move
				{

					Move* g = new Move(x,y,x-1,y+1,0);
					moves.push_back(*g);
					delete g;					
				}
				//sideways killer moves
				if(x < (x_dim -1) && current_state->find_soldier(x+1,y,!enemy)!=-1)//positive horiontal killer move 
				{

					Move* g = new Move(x,y,x+1,y,0);
					moves.push_back(*g);
					delete g;					
				}
				if(x > 0 && current_state->find_soldier(x-1,y,!enemy)!=-1)//negative horiontal killer move 
				{

					Move* g = new Move(x,y,x-1,y,0);
					moves.push_back(*g);
					delete g;					
				}
				//retreat backard moves
				if(current_state->find_soldier(x-1,y,!enemy) != -1 || current_state->find_soldier(x+1,y,!enemy) != -1 || current_state->find_soldier(x-1,y+1,!enemy) != -1
					|| current_state->find_soldier(x+1,y+1,!enemy) != -1 || current_state->find_soldier(x,y+1,!enemy) != -1)
				{
					//backward
					if((y-2) >= 0 && current_state->find_soldier(x,y-2,enemy) == -1 && current_state->find_townhall(x,y-2,enemy) == -1)
					{
	
						Move* g = new Move(x,y,x,y-2,0);
						moves.push_back(*g);
						delete g;
					}
					//positive diagonal
					if((y-2)>=0 && (x-2)>=0 && current_state->find_soldier(x-2,y-2,enemy) == -1 && current_state->find_townhall(x-2,y-2,enemy) == -1)
					{
	
						Move* g = new Move(x,y,x-2,y-2,0);
						moves.push_back(*g);
						delete g;
					}
					//negative diagonal
					if((y-2)>=0 && (x+2)< x_dim && current_state->find_soldier(x+2,y-2,enemy)==-1 && current_state->find_townhall(x+2,y-2,enemy)==-1)
					{
	
						Move* g = new Move(x,y,x+2,y-2,0);
						moves.push_back(*g);
						delete g;
					}
				}
			}
			else if(id==0)//we are black 
			{
				//forward soldier
				if(y>0 && current_state->find_soldier(x,(y-1),enemy)==-1)//forward move
				{

					Move* g = new Move(x,y,x,y-1,0);
					moves.push_back(*g);
					delete g;
				}
				if(y>0 && x>0 && current_state->find_soldier(x-1,y-1,enemy)==-1)//positive diagonal move
				{

					Move* g = new Move(x,y,x-1,y-1,0);
					moves.push_back(*g);
					delete g;					
				}
				if(y>0 && (x<x_dim-1) && current_state->find_soldier(x+1,y-1,enemy)==-1)//negative diagonal move
				{

					Move* g = new Move(x,y,x+1,y-1,0);
					moves.push_back(*g);
					delete g;					
				}
				//sideways killer moves
				if(x < (x_dim -1) && current_state->find_soldier(x+1,y,!enemy)!=-1)//positive horiontal killer move 
				{

					Move* g = new Move(x,y,x+1,y,0);
					moves.push_back(*g);
					delete g;					
				}
				if(x > 0 && current_state->find_soldier(x-1,y,!enemy)!=-1)//negative horiontal killer move 
				{

					Move* g = new Move(x,y,x-1,y,0);
					moves.push_back(*g);
					delete g;					
				}
				//retreat backard moves
				if(current_state->find_soldier(x-1,y,!enemy) != -1 || current_state->find_soldier(x+1,y,!enemy) != -1 || current_state->find_soldier(x-1,y-1,!enemy) != -1
					|| current_state->find_soldier(x+1,y-1,!enemy) != -1 || current_state->find_soldier(x,y-1,!enemy) != -1)
				{
					//backward
					if((y+2<y_dim) && current_state->find_soldier(x,y+2,enemy) == -1 && current_state->find_townhall(x,y+2,enemy) == -1)
					{
	
						Move* g = new Move(x,y,x,y+2,0);
						moves.push_back(*g);
						delete g;
					}
					//positive diagonal
					if((y+2<y_dim) && (x+2<x_dim) && current_state->find_soldier(x+2,y+2,enemy) == -1 && current_state->find_townhall(x+2,y+2,enemy) == -1)
					{
	
						Move* g = new Move(x,y,x+2,y+2,0);
						moves.push_back(*g);
						delete g;
					}
					//negative diagonal
					if((y+2<y_dim) && (x-2>=0) && current_state->find_soldier(x-2,y+2,enemy)==-1 && current_state->find_townhall(x-2,y+2,enemy)==-1)
					{
	
						Move* g = new Move(x,y,x-2,y+2,0);
						moves.push_back(*g);
						delete g;
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
			if(x_temp_1 >= 0 && x_temp_1 < x_dim && y_temp_1 >= 0 && y_temp_1 <y_dim && current_state->find_soldier(x_temp_1, y_temp_1, true) == -1 &&
			 current_state->find_soldier(x_temp_1, y_temp_1, false) == -1 && current_state->find_townhall(x_temp_1, y_temp_1, true) == -1 &&
			 current_state->find_townhall(x_temp_1, y_temp_1, false) == -1 )
			{
				Move* g = new Move(x-x_par,y-y_par,x_temp_1,y_temp_1 ,0); 
				moves.push_back(*g);
				delete g;
				// cannon bombs
				if(x+3*x_par >= 0 && x+3*x_par < x_dim && y+3*y_par >= 0 && y+3*y_par < y_dim && current_state->find_soldier(x+3*x_par, y+3*y_par, false) == -1 &&
				 current_state->find_townhall(x+3*x_par, y+3*y_par, false) == -1 )
				{

					Move* g = new Move(x,y,x+3*x_par,y+3*y_par,1);
					moves.push_back(*g);
					delete g;
				}
				if(x+4*x_par >= 0 && x+4*x_par < x_dim && y+4*y_par >= 0 && y+4*y_par < y_dim && current_state->find_soldier(x+4*x_par, y+4*y_par, false) == -1 &&
				 current_state->find_townhall(x+4*x_par, y+4*y_par, false) == -1)
				{

					Move* g = new Move(x,y,x+4*x_par,y+4*y_par,1);
					moves.push_back(*g);
					delete g;
				}
			}
			if(x_temp_2 >= 0 && x_temp_2 < x_dim && y_temp_2 >= 0 && y_temp_2 <y_dim && current_state->find_soldier(x_temp_2, y_temp_2, true) == -1 &&
			 current_state->find_soldier(x_temp_2, y_temp_2, false) == -1 && current_state->find_soldier(x_temp_2, y_temp_2, true) == -1 &&
			 current_state->find_soldier(x_temp_2, y_temp_2, false) == -1)
			{
				Move* g = new Move(x+x_par,y+y_par,x_temp_2,y_temp_2 ,0);
				moves.push_back(*g);
				delete g;
				// cannon bombs
				if(x-3*x_par >= 0 && x-3*x_par < x_dim && y-3*y_par >= 0 && y-3*y_par < y_dim && current_state->find_soldier(x-3*x_par, y-3*y_par, false) == -1 &&
				 current_state->find_townhall(x-3*x_par, y-3*y_par, false) == -1)
				{

					Move* g = new Move(x,y,x-3*x_par,y-3*y_par,1);
					moves.push_back(*g);
					delete g;
				}
				if(x-4*x_par >= 0 && x-4*x_par < x_dim && y-4*y_par >= 0 && y-4*y_par < y_dim && current_state->find_soldier(x-4*x_par, y-4*y_par, false) == -1 &&
				 current_state->find_townhall(x-4*x_par, y-4*y_par, false) == -1)
				{

					Move* g = new Move(x,y,x-4*x_par,y-4*y_par,1);
					moves.push_back(*g);
					delete g;
				}
			}
		}
	}
	else
	{
		vector<soldier> soldiers = current_state->enemy_soldiers;
		vector<pair<soldier, int> > cannons = current_state->enemy_cannons;
		int id = current_state->id;
		//Soldier moves
		for(int i=0;i<soldiers.size();++i)
		{
			int x = soldiers.at(i).getX();
			int y = soldiers.at(i).getY();
			if(id==0)//enemy is white
			{
				//forward soldier
				if(y<(y_dim-1) && current_state->find_soldier(x,(y+1),enemy)==-1)//forward move
				{

					Move* g = new Move(x,y,x,y+1,0);
					moves.push_back(*g);
					delete g;

				}
				if(y<(y_dim-1) && (x<x_dim-1) && current_state->find_soldier(x+1,y+1,enemy)==-1)//positive diagonal move
				{

					Move* g = new Move(x,y,x+1,y+1,0);
					moves.push_back(*g);
					delete g;					
				}
				if(y<(y_dim-1) && (x>0) && current_state->find_soldier(x-1,y+1,enemy)==-1)//negative diagonal move
				{

					Move* g = new Move(x,y,x-1,y+1,0);
					moves.push_back(*g);
					delete g;					
				}
				//sideways killer moves
				if(x < (x_dim -1) && current_state->find_soldier(x+1,y,!enemy)!=-1)//positive horiontal killer move 
				{

					Move* g = new Move(x,y,x+1,y,0);
					moves.push_back(*g);
					delete g;					
				}
				if(x > 0 && current_state->find_soldier(x-1,y,!enemy)!=-1)//negative horiontal killer move 
				{

					Move* g = new Move(x,y,x-1,y,0);
					moves.push_back(*g);
					delete g;					
				}
				//retreat backard moves
				if(current_state->find_soldier(x-1,y,!enemy) != -1 || current_state->find_soldier(x+1,y,!enemy) != -1 || current_state->find_soldier(x-1,y+1,!enemy) != -1
					|| current_state->find_soldier(x+1,y+1,!enemy) != -1 || current_state->find_soldier(x,y+1,!enemy) != -1)
				{
					//backward
					if((y-2) >= 0 && current_state->find_soldier(x,y-2,enemy) == -1 && current_state->find_townhall(x,y-2,enemy) == -1)
					{
	
						Move* g = new Move(x,y,x,y-2,0);
						moves.push_back(*g);
						delete g;
					}
					//positive diagonal
					if((y-2)>=0 && (x-2)>=0 && current_state->find_soldier(x-2,y-2,enemy) == -1 && current_state->find_townhall(x-2,y-2,enemy) == -1)
					{
	
						Move* g = new Move(x,y,x-2,y-2,0);
						moves.push_back(*g);
						delete g;
					}
					//negative diagonal
					if((y-2)>=0 && (x+2)< x_dim && current_state->find_soldier(x+2,y-2,enemy)==-1 && current_state->find_townhall(x+2,y-2,enemy)==-1)
					{
	
						Move* g = new Move(x,y,x+2,y-2,0);
						moves.push_back(*g);
						delete g;
					}
				}
			}
			else if(id==1)//enemy is black
			{
				//forward soldier
				if(y>0 && current_state->find_soldier(x,(y-1),enemy)==-1)//forward move
				{

					Move* g = new Move(x,y,x,y-1,0);
					moves.push_back(*g);
					delete g;
				}
				if(y>0 && x>0 && current_state->find_soldier(x-1,y-1,enemy)==-1)//positive diagonal move
				{

					Move* g = new Move(x,y,x-1,y-1,0);
					moves.push_back(*g);
					delete g;					
				}
				if(y>0 && (x<x_dim-1) && current_state->find_soldier(x+1,y-1,enemy)==-1)//negative diagonal move
				{

					Move* g = new Move(x,y,x+1,y-1,0);
					moves.push_back(*g);
					delete g;					
				}
				//sideways killer moves
				if(x < (x_dim -1) && current_state->find_soldier(x+1,y,!enemy)!=-1)//positive horiontal killer move 
				{

					Move* g = new Move(x,y,x+1,y,0);
					moves.push_back(*g);
					delete g;					
				}
				if(x > 0 && current_state->find_soldier(x-1,y,!enemy)!=-1)//negative horiontal killer move 
				{

					Move* g = new Move(x,y,x-1,y,0);
					moves.push_back(*g);
					delete g;					
				}
				//retreat backard moves
				if(current_state->find_soldier(x-1,y,!enemy) != -1 || current_state->find_soldier(x+1,y,!enemy) != -1 || current_state->find_soldier(x-1,y-1,!enemy) != -1
					|| current_state->find_soldier(x+1,y-1,!enemy) != -1 || current_state->find_soldier(x,y-1,!enemy) != -1)
				{
					//backward
					if((y+2<y_dim) && current_state->find_soldier(x,y+2,enemy) == -1 && current_state->find_townhall(x,y+2,enemy) == -1)
					{
	
						Move* g = new Move(x,y,x,y+2,0);
						moves.push_back(*g);
						delete g;
					}
					//positive diagonal
					if((y+2<y_dim) && (x+2<x_dim) && current_state->find_soldier(x+2,y+2,enemy) == -1 && current_state->find_townhall(x+2,y+2,enemy) == -1)
					{
	
						Move* g = new Move(x,y,x+2,y+2,0);
						moves.push_back(*g);
						delete g;
					}
					//negative diagonal
					if((y+2<y_dim) && (x-2>=0) && current_state->find_soldier(x-2,y+2,enemy)==-1 && current_state->find_townhall(x-2,y+2,enemy)==-1)
					{
	
						Move* g = new Move(x,y,x-2,y+2,0);
						moves.push_back(*g);
						delete g;
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
			if(x_temp_1 >= 0 && x_temp_1 < x_dim && y_temp_1 >= 0 && y_temp_1 <y_dim && current_state->find_soldier(x_temp_1, y_temp_1, true) == -1 &&
			 current_state->find_soldier(x_temp_1, y_temp_1, false) == -1 && current_state->find_townhall(x_temp_1, y_temp_1, true) == -1 &&
			 current_state->find_townhall(x_temp_1, y_temp_1, false) == -1 )
			{
				Move* g = new Move(x-x_par,y-y_par,x_temp_1,y_temp_1 ,0); 
				moves.push_back(*g);
				delete g;
				// cannon bombs
				if(x+3*x_par >= 0 && x+3*x_par < x_dim && y+3*y_par >= 0 && y+3*y_par < y_dim && current_state->find_soldier(x+3*x_par, y+3*y_par, true) == -1 &&
				 current_state->find_townhall(x+3*x_par, y+3*y_par, true) == -1 )
				{

					Move* g = new Move(x,y,x+3*x_par,y+3*y_par,1);
					moves.push_back(*g);
					delete g;
				}
				if(x+4*x_par >= 0 && x+4*x_par < x_dim && y+4*y_par >= 0 && y+4*y_par < y_dim && current_state->find_soldier(x+4*x_par, y+4*y_par, true) == -1 &&
				 current_state->find_townhall(x+4*x_par, y+4*y_par, true) == -1)
				{

					Move* g = new Move(x,y,x+4*x_par,y+4*y_par,1);
					moves.push_back(*g);
					delete g;
				}
			}
			if(x_temp_2 >= 0 && x_temp_2 < x_dim && y_temp_2 >= 0 && y_temp_2 <y_dim && current_state->find_soldier(x_temp_2, y_temp_2, true) == -1 &&
			 current_state->find_soldier(x_temp_2, y_temp_2, false) == -1 && current_state->find_soldier(x_temp_2, y_temp_2, true) == -1 &&
			 current_state->find_soldier(x_temp_2, y_temp_2, false) == -1)
			{
				Move* g = new Move(x+x_par,y+y_par,x_temp_2,y_temp_2 ,0);
				moves.push_back(*g);
				delete g;
				// cannon bombs
				if(x-3*x_par >= 0 && x-3*x_par < x_dim && y-3*y_par >= 0 && y-3*y_par < y_dim && current_state->find_soldier(x-3*x_par, y-3*y_par, true) == -1 &&
				 current_state->find_townhall(x-3*x_par, y-3*y_par, true) == -1)
				{

					Move* g = new Move(x,y,x-3*x_par,y-3*y_par,1);
					moves.push_back(*g);
					delete g;
				}
				if(x-4*x_par >= 0 && x-4*x_par < x_dim && y-4*y_par >= 0 && y-4*y_par < y_dim && current_state->find_soldier(x-4*x_par, y-4*y_par, true) == -1 &&
				 current_state->find_townhall(x-4*x_par, y-4*y_par, true) == -1)
				{

					Move* g = new Move(x,y,x-4*x_par,y-4*y_par,1);
					moves.push_back(*g);
					delete g;
				}
			}
		}
	}
	return moves;
}

