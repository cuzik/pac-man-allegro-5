#include "Player.h"

Player::Player(){
	this->pos_x = 213;
	this->pos_y = 156;
	this->speed = 1;
	this->lifes = 3;
	this->point = 0;
	//UP
	this->side_up_one = NULL;
	this->side_up_two = NULL;
	this->side_up_tree = NULL;
	//DOWN
	this->side_down_one = NULL;
	this->side_down_two = NULL;
	this->side_down_tree = NULL;
	//LEFT
	this->side_left_one = NULL;
	this->side_left_two = NULL;
	this->side_left_tree = NULL;
	//RIGHT
	this->side_right_one = NULL;
	this->side_right_two = NULL;
	this->side_right_tree = NULL;
}
// Decalração dos Sets
void Player::setPos_x(int pos_x){
	this->pos_x = pos_x;
}
void Player::setPos_y(int pos_y){
	this->pos_y = pos_y;
}
void Player::setSpeed(int speed){
	this->speed = speed;
}
void Player::setLifes(int lifes){
	this->lifes = lifes;
}
void Player::setPoint(long long int point){
	this->point = point;
}
void Player::setMove_up(bool move_up){
	this->move_up = move_up;
}
void Player::setMove_down(bool move_down){
	this->move_down = move_down;
}
void Player::setMove_left(bool move_left){
	this->move_left = move_left;
}
void Player::setMove_right(bool move_right){
	this->move_right = move_right;
}
// // Decalração dos SetsDecalração dos Gets
int Player::getPos_x(){
	return this->pos_x;
}
int Player::getPos_y(){
	return this->pos_y;
}
int Player::getSpeed(){
	return this->speed;
}
int Player::getLifes(){
	return this->lifes;
}
long long int Player::getPoint(){
	return this->point; 
}
bool Player::getMove_up(){
	return this->move_up;
}
bool Player::getMove_down(){
	return this->move_down;
}
bool Player::getMove_left(){
	return this->move_left;
}
bool Player::getMove_right(){
	return this->move_right;
}
// Funções de andar
int Player::walk_up(int mov_anterior, unsigned char **game_map){
	if( game_map[this->getPos_x()][this->getPos_y()-1] == 1 ||
		game_map[this->getPos_x()+22][this->getPos_y()-1] == 1){
		if(mov_anterior==2){
			return this->walk_down(0, game_map);
		}else if(mov_anterior==3){
			return this->walk_left(0, game_map);
		}else if(mov_anterior==4){
			return this->walk_right(0, game_map);
		}else{
			return -1;
		}
	}else{
		this->pos_y -= this->speed;
		return 1;
	}
	return mov_anterior;
}
int Player::walk_down(int mov_anterior, unsigned char **game_map){
	if( game_map[this->getPos_x()][this->getPos_y()+23] == 1 ||
		game_map[this->getPos_x()+22][this->getPos_y()+23] == 1){
		if(mov_anterior==1){
			return this->walk_up(0, game_map);
		}else if(mov_anterior==3){
			return this->walk_left(0, game_map);
		}else if(mov_anterior==4){
			return this->walk_right(0, game_map);
		}else{
			return -1;
		}
	}else{
		this->pos_y += this->speed;
		return 2;
	}
	return mov_anterior;
}
int Player::walk_left(int mov_anterior, unsigned char **game_map){
	if( game_map[this->getPos_x()-1][this->getPos_y()] == 1 || 
		game_map[this->getPos_x()-1][this->getPos_y()+22] == 1){
		if(mov_anterior==1){
			return this->walk_up(0, game_map);
		}else if(mov_anterior==2){
			return this->walk_down(0, game_map);
		}else if(mov_anterior==4){
			return this->walk_right(0, game_map);
		}else{
			return -1;
		}
	}else{
		this->pos_x -= this->speed;
		return 3;
	}
	return mov_anterior;
}
int Player::walk_right(int mov_anterior, unsigned char **game_map){
	if( game_map[this->getPos_x()+23][this->getPos_y()] == 1 ||
		game_map[this->getPos_x()+23][this->getPos_y()+22] == 1){
		if(mov_anterior==1){
			return this->walk_up(0, game_map);
		}else if(mov_anterior==3){
			return this->walk_left(0, game_map);
		}else if(mov_anterior==2){
			return this->walk_down(0, game_map);
		}else{
			return -1;
		}
	}else{
		this->pos_x += this->speed;
		return 4;
	}
	return mov_anterior;
}
// Carregar as imagens do plesonagem
void Player::upload_images(){
	//UP
    this->side_up_one = al_load_bitmap("./images/player/up_one.png");
    this->side_up_two = al_load_bitmap("./images/player/up_two.png");
    this->side_up_tree = al_load_bitmap("./images/player/up_tree.png");
    //DOWN
    this->side_down_one = al_load_bitmap("./images/player/down_one.png");
    this->side_down_two = al_load_bitmap("./images/player/down_two.png");
    this->side_down_tree = al_load_bitmap("./images/player/down_tree.png");
    //LEFT
    this->side_left_one = al_load_bitmap("./images/player/left_one.png");
    this->side_left_two = al_load_bitmap("./images/player/left_two.png");
    this->side_left_tree = al_load_bitmap("./images/player/left_tree.png");
    //RIGHT
    this->side_right_one = al_load_bitmap("./images/player/right_one.png");
    this->side_right_two = al_load_bitmap("./images/player/right_two.png");
    this->side_right_tree = al_load_bitmap("./images/player/right_tree.png");
}
void Player::position(int pos_x, int pos_y){
	this->pos_x = pos_x;
	this->pos_y = pos_y;
}

void Player::show(int sprit, int mov_atual){
	if(sprit==1){
		if(mov_atual==1){
			//al_draw_bitmap(background, 0, 0, 0);
            al_draw_bitmap(this->side_up_one, this->getPos_x()-6, this->getPos_y()-6, 0);
        }else if(mov_atual==2){
        	//al_draw_bitmap(background, 0, 0, 0);
            al_draw_bitmap(this->side_down_one, this->getPos_x()-6, this->getPos_y()-6, 0);
        }else if(mov_atual==3){
        	//al_draw_bitmap(background, 0, 0, 0);
            al_draw_bitmap(this->side_left_one, this->getPos_x()-6, this->getPos_y()-6, 0);
        }else if(mov_atual==4){
        	//al_draw_bitmap(background, 0, 0, 0);
            al_draw_bitmap(this->side_right_one, this->getPos_x()-6, this->getPos_y()-6, 0);
        }
    }else if(sprit==2 || sprit==4){
		if(mov_atual==1){
			//al_draw_bitmap(background, 0, 0, 0);
            al_draw_bitmap(this->side_up_two, this->getPos_x()-6, this->getPos_y()-6, 0);
        }else if(mov_atual==2){
        	//al_draw_bitmap(background, 0, 0, 0);
            al_draw_bitmap(this->side_down_two, this->getPos_x()-6, this->getPos_y()-6, 0);
        }else if(mov_atual==3){
        	//al_draw_bitmap(background, 0, 0, 0);
            al_draw_bitmap(this->side_left_two, this->getPos_x()-6, this->getPos_y()-6, 0);
        }else if(mov_atual==4){
        	//al_draw_bitmap(background, 0, 0, 0);
            al_draw_bitmap(this->side_right_two, this->getPos_x()-6, this->getPos_y()-6, 0);
        }
    }else{
    	if(mov_atual==1){
			//al_draw_bitmap(background, 0, 0, 0);
            al_draw_bitmap(this->side_up_tree, this->getPos_x()-6, this->getPos_y()-6, 0);
        }else if(mov_atual==2){
        	//al_draw_bitmap(background, 0, 0, 0);
            al_draw_bitmap(this->side_down_tree, this->getPos_x()-6, this->getPos_y()-6, 0);
        }else if(mov_atual==3){
        	//al_draw_bitmap(background, 0, 0, 0);
            al_draw_bitmap(this->side_left_tree, this->getPos_x()-6, this->getPos_y()-6, 0);
        }else if(mov_atual==4){
        	//al_draw_bitmap(background, 0, 0, 0);
            al_draw_bitmap(this->side_right_tree, this->getPos_x()-6, this->getPos_y()-6, 0);
        }
    }
}
int Player::define_move(int mov_atual, unsigned char **game_map){
	if(this->getMove_up()){
		mov_atual = this->walk_up(mov_atual, game_map);
	}
	else if(this->getMove_down()){
		mov_atual = this->walk_down(mov_atual, game_map);
	}
	else if(this->getMove_left()){
		mov_atual = this->walk_left(mov_atual, game_map);
	}
	else if(this->getMove_right()){
		mov_atual = this->walk_right(mov_atual, game_map);
	}
	return mov_atual; 
}