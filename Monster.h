#include <iostream>
#include <allegro5/allegro.h>

class Monster{
private:
	int pos_x;
	int pos_y;
	int speed;
	bool move_up;
	bool move_down;
	bool move_left;
	bool move_right;
public:
	ALLEGRO_BITMAP *side_up_one;
	ALLEGRO_BITMAP *side_up_two;
	ALLEGRO_BITMAP *side_down_one;
	ALLEGRO_BITMAP *side_down_two;
	ALLEGRO_BITMAP *side_left_one;
	ALLEGRO_BITMAP *side_left_two;
	ALLEGRO_BITMAP *side_rigth_one;
	ALLEGRO_BITMAP *side_rigth_two;
	Monster(int pos_x, int pos_y);
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
	// Funções de Carregamento das imagens
	void upload_images_red();
    void upload_images_pink();
    void upload_images_blue();
    void upload_images_yellow();
    // Funções de movimento
    void move(unsigned char game_map[441][234]);
    void sorteia_move(unsigned char game_map[441][234]);
    void walk_up();
	void walk_down();
	void walk_left();
	void walk_right();
	void position(int pos_x, int pos_y);
	//colisão
	bool collision(int pos_player_x, int pos_player_y);
	//
	void show_monster(bool monster_sprit_one);
};