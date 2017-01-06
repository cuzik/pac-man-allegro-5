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
	//UP
	ALLEGRO_BITMAP *side_up_one;
	ALLEGRO_BITMAP *side_up_two;
	ALLEGRO_BITMAP *side_up_tree;
	//DOWN
	ALLEGRO_BITMAP *side_down_one;
	ALLEGRO_BITMAP *side_down_two;
	ALLEGRO_BITMAP *side_down_tree;
	//LEFT
	ALLEGRO_BITMAP *side_left_one;
	ALLEGRO_BITMAP *side_left_two;
	ALLEGRO_BITMAP *side_left_tree;
	//RIGHT
	ALLEGRO_BITMAP *side_right_one;
	ALLEGRO_BITMAP *side_right_two;
	ALLEGRO_BITMAP *side_right_tree;
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
	int walk_up(int mov_anterior, unsigned char **game_map);
	int walk_down(int mov_anterior, unsigned char **game_map);
	int walk_left(int mov_anterior, unsigned char **game_map);
	int walk_right(int mov_anterior, unsigned char **game_map);
	// C
	void upload_images();
	void show(int boca_aberta, int mov_atual);
	int define_move(int mov_atual, unsigned char **game_map);
};