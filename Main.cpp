#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include <stdio.h>
#include <stdlib.h>
#include "Player.h"

using namespace std;

typedef struct ${
	int pos_x;    	
	int pos_y;
	bool active;   	
}Boll;

int main(){
	// Definindos as contantes;
	const int DISPLAY_WIDTH = 600;
	const int DISPLAY_HEIGHT = 300;

	// Criando as variáveis do jogo
	bool isRunning = true;
	int boca_aberta = 0;
	bool big_boll_white = false;
    int count = 0;
    int count2 = 0;
	// Criando as Variáveis do Player
	Player* player = new Player();

	// Criando os objetos
	ALLEGRO_BITMAP *background = NULL;
	ALLEGRO_BITMAP *img_small_boll = NULL;
	ALLEGRO_BITMAP *img_big_boll_white = NULL;
	ALLEGRO_BITMAP *img_big_boll_yellow = NULL;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *queue_event = NULL;

	// Iniciando o programa
	if(!al_init()){
		al_show_native_message_box(display,"Erro","Descrição do Erro:","Não foi possivel Iniciar",NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	// Criando a Tela
	display = al_create_display(DISPLAY_WIDTH,DISPLAY_HEIGHT);
	if(!display){
		al_show_native_message_box(display,"Erro","Descrição do Erro:","Não foi possivel criar o 'Display'",NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	al_set_window_title(display, "PAC-MAN");
	// Instalação de addon
	al_install_keyboard();

	// Criação de addos
	al_init_primitives_addon();
	al_init_image_addon();

	// Carregando as imagens do JOGO
	background = al_load_bitmap("./images/fundo.png");
	img_small_boll = al_load_bitmap("./images/small_boll.png");
	img_big_boll_white = al_load_bitmap("./images/big_boll_white.png");
	img_big_boll_yellow = al_load_bitmap("./images/big_boll_yellow.png");

    //Carregando as imagens do personagem
    player->upload_images();

    // Inicia a bolinhas
    Boll small_boll[96];
    Boll big_boll[4];
    
    // Criando a Matriz do jogo
	int i,j,k=0,l=0;
	unsigned char game_map[443][245];
	//unsigned char r;
	//unsigned char g;
	//unsigned char b;
	FILE *in = fopen("game_map.txt","r");
	for(i=0;i<443;i++){
		for(j=0;j<245;j++){
			game_map[i][j] = fgetc(in) - 48;
			if(game_map[i][j]==2){
				small_boll[k].pos_x = i;
				small_boll[k].pos_y = j;
				small_boll[k].active = true;
				k++;
			}else if(game_map[i][j]==3){
				big_boll[l].pos_x = i;
				big_boll[l].pos_y = j;
				big_boll[l].active = true;
				l++;
			}
			/*al_unmap_rgb(al_get_pixel(background,i,j), &r, &g, &b);
			if(r+g+b == 0){
				fprintf(out, "%i",0);
			}else if(r == 255){	
				fprintf(out, "%i",2);
			}else if(b == 255){	
				fprintf(out, "%i",3);
				cout << "yeap" << endl;
			}else{
				fprintf(out, "%i",1);
			}*/
		}
	}
	// Criação da Fila de Eventos
	queue_event = al_create_event_queue();

	// Resgistro do source que podera ser lido pela Fila de eventos
	al_register_event_source(queue_event, al_get_keyboard_event_source());
	al_register_event_source(queue_event, al_get_display_event_source(display));

	// Inicia o Background e os atores
	al_draw_bitmap(background, 0, 0, 0);
	cout << "chaega aqui" << endl;

	// Laço insfinito para atualização da tela
	while(isRunning){
		ALLEGRO_EVENT event;
		while(!al_is_event_queue_empty(queue_event)){
            al_wait_for_event(queue_event, &event);
			//verifica se precionou a tecla esc para sair
			if(event.type == ALLEGRO_EVENT_KEY_DOWN){
				switch(event.keyboard.keycode){
					case ALLEGRO_KEY_UP:
						player->setMove_up(true);
						player->setMove_down(false);
						player->setMove_left(false);
						player->setMove_right(false);
						break;
					case ALLEGRO_KEY_DOWN:
						player->setMove_up(false);
						player->setMove_down(true);
						player->setMove_left(false);
						player->setMove_right(false);
						break;
					case ALLEGRO_KEY_LEFT:
						player->setMove_up(false);
						player->setMove_down(false);
						player->setMove_left(true);
						player->setMove_right(false);
						break;
					case ALLEGRO_KEY_RIGHT:
						player->setMove_up(false);
						player->setMove_down(false);
						player->setMove_left(false);
						player->setMove_right(true);
						break;
					case ALLEGRO_KEY_ESCAPE:
						isRunning = false;
						break;
					default:
						//any key press
						break;
				}
			}else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
				isRunning = false;
			}
		}
        //Verifica se tem parede na pra cima em 4 pontos diferentes espalhados pela parte de cima do player
		if(player->getMove_up()){
			if( game_map[player->getPos_x()][player->getPos_y()-1] == 1 ||
				game_map[player->getPos_x()+35][player->getPos_y()-1] == 1){
				count--;
			}else{
				player->walk_up();
			}
		}
        //Verifica se tem parede na pra biaxo em 4 pontos diferentes espalhados pela parte de baixo do player
		if(player->getMove_down()){
			if( game_map[player->getPos_x()][player->getPos_y()+36] == 1 ||
				game_map[player->getPos_x()+35][player->getPos_y()+36] == 1){
				count--;
			}else{
				player->walk_down();
			}
		}
        //Verifica se tem parede na pra esquerda em 4 pontos diferentes espalhados pela parte de esquerda do player
		if(player->getMove_left()){
			if( game_map[player->getPos_x()-1][player->getPos_y()] == 1 || 
				game_map[player->getPos_x()-1][player->getPos_y()+35] == 1){
				count--;
			}else{
				player->walk_left();
			}
		}
        //Verifica se tem parede na pra direita em 4 pontos diferentes espalhados pela parte de direita do player
		if(player->getMove_right()){
			if( game_map[player->getPos_x()+36][player->getPos_y()] == 1 ||
				game_map[player->getPos_x()+36][player->getPos_y()+35] == 1){
				count--;
			}else{
				player->walk_right();
			}
		}
		if(count == 10){
            boca_aberta++;
            if(boca_aberta == 3){
            	boca_aberta = 0;
            }
            count = 0;
        }else{
            count++;
        }
		
		// Coloca a imagem adequada para dar a impressão de movimento
		if(boca_aberta==1){
			if(player->getMove_up()){
				al_draw_bitmap(background, 0, 0, 0);
	            al_draw_bitmap(player->side_up, player->getPos_x(), player->getPos_y(), 0);
	        }else if(player->getMove_down()){
	        	al_draw_bitmap(background, 0, 0, 0);
	            al_draw_bitmap(player->side_down, player->getPos_x(), player->getPos_y(), 0);
	        }else if(player->getMove_left()){
	        	al_draw_bitmap(background, 0, 0, 0);
	            al_draw_bitmap(player->side_left, player->getPos_x(), player->getPos_y(), 0);
	        }else if(player->getMove_right()){
	        	al_draw_bitmap(background, 0, 0, 0);
	            al_draw_bitmap(player->side_rigth, player->getPos_x(), player->getPos_y(), 0);
	        }
	    }else if(boca_aberta==2){
			if(player->getMove_up()){
				al_draw_bitmap(background, 0, 0, 0);
	            al_draw_bitmap(player->side_up_half, player->getPos_x(), player->getPos_y(), 0);
	        }else if(player->getMove_down()){
	        	al_draw_bitmap(background, 0, 0, 0);
	            al_draw_bitmap(player->side_down_half, player->getPos_x(), player->getPos_y(), 0);
	        }else if(player->getMove_left()){
	        	al_draw_bitmap(background, 0, 0, 0);
	            al_draw_bitmap(player->side_left_half, player->getPos_x(), player->getPos_y(), 0);
	        }else if(player->getMove_right()){
	        	al_draw_bitmap(background, 0, 0, 0);
	            al_draw_bitmap(player->side_rigth_half, player->getPos_x(), player->getPos_y(), 0);
	        }
	    }else{
	    	al_draw_bitmap(background, 0, 0, 0);
            al_draw_bitmap(player->side_in_move, player->getPos_x(), player->getPos_y(), 0);
        }
        //Coocando as bolinhas
        if(count2 == 5){
            big_boll_white = !big_boll_white;
            count2 = 0;
        }else{
            count2++;
        }
        for(i=0;i<96;i++){
        	if(small_boll[i].active){
        		al_draw_bitmap(img_small_boll, small_boll[i].pos_x-2, small_boll[i].pos_y-2, 0);
        	}

        }
        if(big_boll_white){
	        for(i=0;i<4;i++){
	        	if(big_boll[i].active){
		        	al_draw_bitmap(img_big_boll_white, big_boll[i].pos_x-5, big_boll[i].pos_y-5, 0);
	        	}
	        }
        }else{
        	for(i=0;i<4;i++){
	        	if(big_boll[i].active){
		        	al_draw_bitmap(img_big_boll_yellow, big_boll[i].pos_x-5, big_boll[i].pos_y-5, 0);
	        	}
	        }
        }
		al_flip_display();
	}
	// Destruindo tudo para finaliza o programa
	al_destroy_display(display);
	al_destroy_event_queue(queue_event);
	return 0;
}