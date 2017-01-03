#include "Player.h"

Player::Player(){
	this->pos_x = 213;
	this->pos_y = 156;
	this->speed = 1;
	this->lifes = 3;
	this->point = 0;
	this->move_up = false;
	this->move_down = false;
	this->move_left = false;
	this->move_right = false;
	this->side_in_move = NULL;
	this->side_up = NULL;
	this->side_down = NULL;
	this->side_left = NULL;
	this->side_rigth = NULL;
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
int Player::walk_up(int mov_anterior, unsigned char game_map[441][234]){
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
int Player::walk_down(int mov_anterior, unsigned char game_map[441][234]){
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
int Player::walk_left(int mov_anterior, unsigned char game_map[441][234]){
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
int Player::walk_right(int mov_anterior, unsigned char game_map[441][234]){
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
    this->side_in_move = al_load_bitmap("./images/player/pac_man_boca_fechada.png");
	this->side_up = al_load_bitmap("./images/player/pac_man_up.png");
	this->side_up_half = al_load_bitmap("./images/player/pac_man_up_half.png");
    this->side_down = al_load_bitmap("./images/player/pac_man_down.png");
    this->side_down_half = al_load_bitmap("./images/player/pac_man_down_half.png");
    this->side_left = al_load_bitmap("./images/player/pac_man_left.png");
    this->side_left_half = al_load_bitmap("./images/player/pac_man_left_half.png");
    this->side_rigth = al_load_bitmap("./images/player/pac_man_rigth.png");
    this->side_rigth_half = al_load_bitmap("./images/player/pac_man_rigth_half.png");
}
void Player::position(int pos_x, int pos_y){
	this->pos_x = pos_x;
	this->pos_y = pos_y;
}

void Player::show(int boca_aberta, int mov_atual){
	if(boca_aberta==1){
		if(mov_atual==1){
			//al_draw_bitmap(background, 0, 0, 0);
            al_draw_bitmap(this->side_up, this->getPos_x(), this->getPos_y(), 0);
        }else if(mov_atual==2){
        	//al_draw_bitmap(background, 0, 0, 0);
            al_draw_bitmap(this->side_down, this->getPos_x(), this->getPos_y(), 0);
        }else if(mov_atual==3){
        	//al_draw_bitmap(background, 0, 0, 0);
            al_draw_bitmap(this->side_left, this->getPos_x(), this->getPos_y(), 0);
        }else if(mov_atual==4){
        	//al_draw_bitmap(background, 0, 0, 0);
            al_draw_bitmap(this->side_rigth, this->getPos_x(), this->getPos_y(), 0);
        }else{
        	al_draw_bitmap(this->side_in_move, this->getPos_x(), this->getPos_y(), 0);
        }
    }else if(boca_aberta==2 || boca_aberta==4){
		if(mov_atual==1){
			//al_draw_bitmap(background, 0, 0, 0);
            al_draw_bitmap(this->side_up_half, this->getPos_x(), this->getPos_y(), 0);
        }else if(mov_atual==2){
        	//al_draw_bitmap(background, 0, 0, 0);
            al_draw_bitmap(this->side_down_half, this->getPos_x(), this->getPos_y(), 0);
        }else if(mov_atual==3){
        	//al_draw_bitmap(background, 0, 0, 0);
            al_draw_bitmap(this->side_left_half, this->getPos_x(), this->getPos_y(), 0);
        }else if(mov_atual==4){
        	//al_draw_bitmap(background, 0, 0, 0);
            al_draw_bitmap(this->side_rigth_half, this->getPos_x(), this->getPos_y(), 0);
        }else{
        	al_draw_bitmap(this->side_in_move, this->getPos_x(), this->getPos_y(), 0);
        }
    }else{
    	//al_draw_bitmap(background, 0, 0, 0);
        al_draw_bitmap(this->side_in_move, this->getPos_x(), this->getPos_y(), 0);
    }
}
int Player::define_move(int mov_atual, unsigned char game_map[441][234]){
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