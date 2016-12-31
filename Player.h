#include <iostream>
#include <allegro5/allegro.h>

class Player{
private:
	int pos_x;
	int pos_y;
	int speed;
	bool move_up;
	bool move_down;
	bool move_left;
	bool move_right;
public:
	ALLEGRO_BITMAP *side_in_move;
	ALLEGRO_BITMAP *side_up;
	ALLEGRO_BITMAP *side_up_half;
	ALLEGRO_BITMAP *side_down;
	ALLEGRO_BITMAP *side_down_half;
	ALLEGRO_BITMAP *side_left;
	ALLEGRO_BITMAP *side_left_half;
	ALLEGRO_BITMAP *side_rigth;
	ALLEGRO_BITMAP *side_rigth_half;
	Player();
	// Decalração dos Sets
	void setPos_x(int pos_x);
	void setPos_y(int pos_y);
	void setSpeed(int speed);
	void setMove_up(bool move_up);
	void setMove_down(bool move_down);
	void setMove_left(bool move_left);
	void setMove_right(bool move_right);
	// Decalração dos Gets
	int getPos_x();
	int getPos_y();
	int getSpeed();
	bool getMove_up();
	bool getMove_down();
	bool getMove_left();
	bool getMove_right();
	// Funções de andar
	void walk_up();
	void walk_down();
	void walk_left();
	void walk_right();
	// C
	void upload_images();
};