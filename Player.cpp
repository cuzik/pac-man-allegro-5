#include "Player.h"

Player::Player(){
	pos_x = 20;
	pos_y = 20;
	speed = 1;
	move_up = false;
	move_down = false;
	move_left = false;
	move_right = false;
	side_in_move = NULL;
	side_up = NULL;
	side_down = NULL;
	side_left = NULL;
	side_rigth = NULL;
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
void Player::walk_up(){
	this->pos_y -= this->speed;
}
void Player::walk_down(){
	this->pos_y += this->speed;
}
void Player::walk_left(){
	this->pos_x -= this->speed;
}
void Player::walk_right(){
	this->pos_x += this->speed;
}
// Carregar as imagens do plesonagem
void Player::upload_images(){
    this->side_in_move = al_load_bitmap("./images/pac_man_boca_fechada.png");
	this->side_up = al_load_bitmap("./images/pac_man_up.png");
	this->side_up_half = al_load_bitmap("./images/pac_man_up_half.png");
    this->side_down = al_load_bitmap("./images/pac_man_down.png");
    this->side_down_half = al_load_bitmap("./images/pac_man_down_half.png");
    this->side_left = al_load_bitmap("./images/pac_man_left.png");
    this->side_left_half = al_load_bitmap("./images/pac_man_left_half.png");
    this->side_rigth = al_load_bitmap("./images/pac_man_rigth.png");
    this->side_rigth_half = al_load_bitmap("./images/pac_man_rigth_half.png");
}