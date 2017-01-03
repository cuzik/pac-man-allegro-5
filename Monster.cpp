#include "Monster.h"

Monster::Monster(int pos_x, int pos_y){
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->speed = 1;
	this->move_up = false;
	this->move_down = false;
	this->move_left = false;
	this->move_right = false;
	this->side_up_one = NULL;
	this->side_up_two = NULL;
	this->side_down_one = NULL;
	this->side_down_two = NULL;
	this->side_left_one = NULL;
	this->side_left_two = NULL;
	this->side_rigth_one = NULL;
	this->side_rigth_two = NULL;
}
// Decalração dos Sets
void Monster::setPos_x(int pos_x){
	this->pos_x = pos_x;
}
void Monster::setPos_y(int pos_y){
	this->pos_y = pos_y;
}
void Monster::setSpeed(int speed){
	this->speed = speed;
}
void Monster::setMove_up(bool move_up){
	this->move_up = move_up;
}
void Monster::setMove_down(bool move_down){
	this->move_down = move_down;
}
void Monster::setMove_left(bool move_left){
	this->move_left = move_left;
}
void Monster::setMove_right(bool move_right){
	this->move_right = move_right;
}
// // Decalração dos SetsDecalração dos Gets
int Monster::getPos_x(){
	return this->pos_x;
}
int Monster::getPos_y(){
	return this->pos_y;
}
int Monster::getSpeed(){
	return this->speed;
}
bool Monster::getMove_up(){
	return this->move_up;
}
bool Monster::getMove_down(){
	return this->move_down;
}
bool Monster::getMove_left(){
	return this->move_left;
}
bool Monster::getMove_right(){
	return this->move_right;
}
// Carregamento das imagens
void Monster::upload_images_red(){
	this->side_up_one = al_load_bitmap("./images/monster/red/up_one.png");
	this->side_up_two = al_load_bitmap("./images/monster/red/up_two.png");
	this->side_down_one = al_load_bitmap("./images/monster/red/down_one.png");
	this->side_down_two = al_load_bitmap("./images/monster/red/down_two.png");
	this->side_left_one = al_load_bitmap("./images/monster/red/left_one.png");
	this->side_left_two = al_load_bitmap("./images/monster/red/left_two.png");
	this->side_rigth_one = al_load_bitmap("./images/monster/red/right_one.png");
	this->side_rigth_two = al_load_bitmap("./images/monster/red/right_two.png");
}
void Monster::upload_images_pink(){
	this->side_up_one = al_load_bitmap("./images/monster/pink/up_one.png");
	this->side_up_two = al_load_bitmap("./images/monster/pink/up_two.png");
	this->side_down_one = al_load_bitmap("./images/monster/pink/down_one.png");
	this->side_down_two = al_load_bitmap("./images/monster/pink/down_two.png");
	this->side_left_one = al_load_bitmap("./images/monster/pink/left_one.png");
	this->side_left_two = al_load_bitmap("./images/monster/pink/left_two.png");
	this->side_rigth_one = al_load_bitmap("./images/monster/pink/right_one.png");
	this->side_rigth_two = al_load_bitmap("./images/monster/pink/right_two.png");
}
void Monster::upload_images_blue(){
	this->side_up_one = al_load_bitmap("./images/monster/blue/up_one.png");
	this->side_up_two = al_load_bitmap("./images/monster/blue/up_two.png");
	this->side_down_one = al_load_bitmap("./images/monster/blue/down_one.png");
	this->side_down_two = al_load_bitmap("./images/monster/blue/down_two.png");
	this->side_left_one = al_load_bitmap("./images/monster/blue/left_one.png");
	this->side_left_two = al_load_bitmap("./images/monster/blue/left_two.png");
	this->side_rigth_one = al_load_bitmap("./images/monster/blue/right_one.png");
	this->side_rigth_two = al_load_bitmap("./images/monster/blue/right_two.png");
}
void Monster::upload_images_yellow(){
	this->side_up_one = al_load_bitmap("./images/monster/yellow/up_one.png");
	this->side_up_two = al_load_bitmap("./images/monster/yellow/up_two.png");
	this->side_down_one = al_load_bitmap("./images/monster/yellow/down_one.png");
	this->side_down_two = al_load_bitmap("./images/monster/yellow/down_two.png");
	this->side_left_one = al_load_bitmap("./images/monster/yellow/left_one.png");
	this->side_left_two = al_load_bitmap("./images/monster/yellow/left_two.png");
	this->side_rigth_one = al_load_bitmap("./images/monster/yellow/right_one.png");
	this->side_rigth_two = al_load_bitmap("./images/monster/yellow/right_two.png");
}
// Funções de movimento
void Monster::move(unsigned char game_map[441][234]){
	if(!(game_map[this->getPos_x()][this->getPos_y()-1] == 1 ||
		game_map[this->getPos_x()+22][this->getPos_y()-1] == 1) &&
		this->getMove_up()){
		this->walk_up();
	}else if(!(game_map[this->getPos_x()][this->getPos_y()+23] == 1 ||
		game_map[this->getPos_x()+22][this->getPos_y()+23] == 1) &&
		this->getMove_down()){
		this->walk_down();
	}else if(!(game_map[this->getPos_x()-1][this->getPos_y()] == 1 || 
		game_map[this->getPos_x()-1][this->getPos_y()+22] == 1) &&
		this->getMove_left()){
		this->walk_left();
	}else if(!(game_map[this->getPos_x()+23][this->getPos_y()] == 1 ||
		game_map[this->getPos_x()+23][this->getPos_y()+22] == 1) &&
		this->getMove_right()){
		this->walk_right();
	}else{
		sorteia_move(game_map);
	}
}

void Monster::sorteia_move(unsigned char game_map[441][234]){
	int vetor[4] = {0,0,0,0};
	if( game_map[this->getPos_x()][this->getPos_y()-1] == 1 ||
		game_map[this->getPos_x()+22][this->getPos_y()-1] == 1){
	}else{
		vetor[0] = 1;
	}
	if( game_map[this->getPos_x()][this->getPos_y()+23] == 1 ||
		game_map[this->getPos_x()+22][this->getPos_y()+23] == 1){
	}else{
		vetor[1] = 1;
	}
	if( game_map[this->getPos_x()-1][this->getPos_y()] == 1 || 
		game_map[this->getPos_x()-1][this->getPos_y()+22] == 1){
	}else{
		vetor[2] = 1;
	}
	if( game_map[this->getPos_x()+23][this->getPos_y()] == 1 ||
		game_map[this->getPos_x()+23][this->getPos_y()+22] == 1){
	}else{
		vetor[3] = 1;
	}
	int i = rand() % 4;
	while(vetor[i]==0){
		i = rand() % 4;
	}
	if(i==0){
		this->walk_up();
	}else if(i==1){
		this->walk_down();
	}else if(i==2){
		this->walk_left();
	}else if(i==3){
		this->walk_right();
	}
}
void Monster::walk_up(){
	this->move_up = true;
	this->move_down = false;
	this->move_left = false;
	this->move_right = false;
	this->pos_y -= this->speed;
}
void Monster::walk_down(){
	this->move_up = false;
	this->move_down = true;
	this->move_left = false;
	this->move_right = false;
	this->pos_y += this->speed;
}
void Monster::walk_left(){
	this->move_up = false;
	this->move_down = false;
	this->move_left = true;
	this->move_right = false;
	this->pos_x -= this->speed;
}
void Monster::walk_right(){
	this->move_up = false;
	this->move_down = false;
	this->move_left = false;
	this->move_right = true;
	this->pos_x += this->speed;
}
bool Monster::collision(int pos_player_x, int pos_player_y){
	int i,j;
	int spectro_inf = 6;
	int spectro_sup = 16;
	for(i=spectro_inf;i<=spectro_sup;i++){
		for(j=spectro_inf;j<=spectro_sup;j++){
			//teste de colisão a cima de um mostro
			if(this->pos_x+i==pos_player_x+j &&
			   this->pos_y+spectro_inf==pos_player_y+spectro_sup){
				return true;
			}
			if(this->pos_x+i==pos_player_x+j &&
			   this->pos_y+spectro_inf+1==pos_player_y+spectro_sup){
				return true;
			}
			//teste de colisão a baixo de um mostro
			if(this->pos_x+j==pos_player_x+i &&
			   this->pos_y+spectro_sup==pos_player_y+spectro_inf){
				return true;
			}
			if(this->pos_x+j==pos_player_x+i &&
			   this->pos_y+spectro_sup==pos_player_y+spectro_inf+1){
				return true;
			}
			//teste de colisão da esquerda de um mostro
			if(this->pos_x+spectro_inf==pos_player_x+spectro_sup &&
			   this->pos_y+i==pos_player_y+j){
				return true;
			}
			if(this->pos_x+spectro_inf+1==pos_player_x+spectro_sup &&
			   this->pos_y+i==pos_player_y+j){
				return true;
			}
			//teste de colisão da direita de um mostro
			if(this->pos_x+spectro_sup==pos_player_x+spectro_inf &&
			   this->pos_y+j==pos_player_y+i){
				return true;
			}
			if(this->pos_x+spectro_sup==pos_player_x+spectro_inf+1 &&
			   this->pos_y+j==pos_player_y+i){
				return true;
			}
		}	
	}
	return false;
}
void Monster::position(int pos_x, int pos_y){
	this->pos_x = pos_x;
	this->pos_y = pos_y;
}
void Monster::show_monster(bool monster_sprit_one){
	if(monster_sprit_one){
        if(this->getMove_up()){
        	al_draw_bitmap(this->side_up_one, this->getPos_x(), this->getPos_y(), 0);
        }else if(this->getMove_down()){
        	al_draw_bitmap(this->side_down_one, this->getPos_x(), this->getPos_y(), 0);
        }else if(this->getMove_left()){
        	al_draw_bitmap(this->side_left_one, this->getPos_x(), this->getPos_y(), 0);
        }else if(this->getMove_right()){
        	al_draw_bitmap(this->side_rigth_one, this->getPos_x(), this->getPos_y(), 0);
        }
    }else{
    	if(this->getMove_up()){
        	al_draw_bitmap(this->side_up_two, this->getPos_x(), this->getPos_y(), 0);
        }else if(this->getMove_down()){
        	al_draw_bitmap(this->side_down_two, this->getPos_x(), this->getPos_y(), 0);
        }else if(this->getMove_left()){
        	al_draw_bitmap(this->side_left_two, this->getPos_x(), this->getPos_y(), 0);
        }else if(this->getMove_right()){
        	al_draw_bitmap(this->side_rigth_two, this->getPos_x(), this->getPos_y(), 0);
        }
    }
}