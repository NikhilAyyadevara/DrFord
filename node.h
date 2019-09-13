#include "game_state.h"

using namespace std;

class node
{
	public:
		game_state* current_state;
		vector<node*> children;
};