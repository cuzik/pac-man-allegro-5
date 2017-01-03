#include <iostream>
#include <allegro5/allegro.h>

class Player{
private:
	int pos_x;
	int pos_y;
	int speed;
	int lifes;
	long long int point;
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
	void setLifes(int lifes);
	void setPoint(long long int point);
	void setMove_up(bool move_up);
	void setMove_down(bool move_down);
	void setMove_left(bool move_left);
	void setMove_right(bool move_right);
	void position(int pos_x, int pos_y);
	// Decalração dos Gets
	int getPos_x();
	int getPos_y();
	int getSpeed();
	int getLifes();
	long long int getPoint();
	bool getMove_up();
	bool getMove_down();
	bool getMove_left();
	bool getMove_right();
	// Funções de andar
	int walk_up(int mov_anterior, unsigned char game_map[441][234]);
	int walk_down(int mov_anterior, unsigned char game_map[441][234]);
	int walk_left(int mov_anterior, unsigned char game_map[441][234]);
	int walk_right(int mov_anterior, unsigned char game_map[441][234]);
	// C
	void upload_images();
	void show(int boca_aberta, int mov_atual);
	int define_move(int mov_atual, unsigned char game_map[441][234]);
};