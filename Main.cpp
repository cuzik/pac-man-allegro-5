#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(){
	// Definindos as contantes;
	const int DISPLAY_WIDTH = 451;
	const int DISPLAY_HEIGHT = 249;

	// Criando as variáveis do jogo
	bool isRunning = true;
	bool boca_aberta = false;
    int count = 0;
	// Criando as Variáveis do Player
	int player_pos_x = 20;
	int player_pos_y = 20;
	int player_speed = 1;
	bool player_move_up = false;
	bool player_move_down = false;
	bool player_move_left = false;
	bool player_move_right = false;
	ALLEGRO_BITMAP *player_side_in_move = NULL;
	ALLEGRO_BITMAP *player_side_up = NULL;
	ALLEGRO_BITMAP *player_side_down = NULL;
	ALLEGRO_BITMAP *player_side_left = NULL;
	ALLEGRO_BITMAP *player_side_rigth = NULL;

	// Criando os objetos
	ALLEGRO_BITMAP *background = NULL;
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

    //Carregando as imagens do personagem
    player_side_up = al_load_bitmap("./images/pac_man_up.png");
    player_side_down = al_load_bitmap("./images/pac_man_down.png");
    player_side_left = al_load_bitmap("./images/pac_man_left.png");
    player_side_rigth = al_load_bitmap("./images/pac_man_rigth.png");
    player_side_in_move = al_load_bitmap("./images/pac_man_boca_fechada.png");

	// Criando a Matriz do jogo
	unsigned char game_map[DISPLAY_WIDTH][DISPLAY_HEIGHT];
	int i,j;
	//unsigned char r;
	//unsigned char g;
	//unsigned char b;
	FILE *in = fopen("game_map.txt","r");
	for(i=0;i<DISPLAY_WIDTH;i++){
		for(j=0;j<DISPLAY_HEIGHT;j++){
			//al_unmap_rgb(al_get_pixel(background,i,j), &r, &g, &b);
			//if(r+g+b == 0){
				//game_map[i][j] = fgetc(in);
				//fprintf(out, "%i",0);
			//}else{	
				game_map[i][j] = fgetc(in) - 48;
				//fprintf(out, "%i",1);
			//}
		}
	}

	// Criação da Fila de Eventos
	queue_event = al_create_event_queue();

	// Resgistro do source que podera ser lido pela Fila de eventos
	al_register_event_source(queue_event, al_get_keyboard_event_source());
	al_register_event_source(queue_event, al_get_display_event_source(display));

	// Inicia o Background e os atores
	al_draw_bitmap(background, 0, 0, 0);

	// Laço insfinito para atualização da tela
	while(isRunning){
		ALLEGRO_EVENT event;
		while(!al_is_event_queue_empty(queue_event)){
            al_wait_for_event(queue_event, &event);
			//verifica se precionou a tecla esc para sair
			if(event.type == ALLEGRO_EVENT_KEY_DOWN){
				switch(event.keyboard.keycode){
					case ALLEGRO_KEY_UP:
						player_move_up = true;
						player_move_down = false;
						player_move_left = false;
						player_move_right = false;
						break;
					case ALLEGRO_KEY_DOWN:
						player_move_up = false;
						player_move_down = true;
						player_move_left = false;
						player_move_right = false;
						break;
					case ALLEGRO_KEY_LEFT:
						player_move_up = false;
						player_move_down = false;
						player_move_left = true;
						player_move_right = false;
						break;
					case ALLEGRO_KEY_RIGHT:
						player_move_up = false;
						player_move_down = false;
						player_move_left = false;
						player_move_right = true;
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
		if(count == 10){
            boca_aberta = !boca_aberta;
            count = 0;
        }else{
            count++;
        }
		if(player_move_up){
			if(game_map[player_pos_x][player_pos_y-1] + game_map[player_pos_x+7][player_pos_y-1] + game_map[player_pos_x+14][player_pos_y-1] + game_map[player_pos_x+21][player_pos_y-1] == 0){
				player_pos_y -= player_speed;
			}else{
				count--;
			}
		}
		if(player_move_down){
			if(game_map[player_pos_x][player_pos_y+22] + game_map[player_pos_x+7][player_pos_y+22] + game_map[player_pos_x+14][player_pos_y+22] + game_map[player_pos_x+21][player_pos_y+22] == 0){
				player_pos_y += player_speed;
			}else{
				count--;
			}
		}
		if(player_move_left){
			if(game_map[player_pos_x-1][player_pos_y] + game_map[player_pos_x-1][player_pos_y+7] + game_map[player_pos_x-1][player_pos_y+14] + game_map[player_pos_x-1][player_pos_y+21] == 0){
				player_pos_x -= player_speed;
			}else{
				count--;
			}
		}
		if(player_move_right){
			if(game_map[player_pos_x+22][player_pos_y] + game_map[player_pos_x+22][player_pos_y+7] + game_map[player_pos_x+22][player_pos_y+14] + game_map[player_pos_x+22][player_pos_y+21] == 0){
				player_pos_x += player_speed;
			}else{
				count--;
			}
		}
		//Lógica de atualização e movimento
		
		if(boca_aberta){
			if(player_move_up){
				al_draw_bitmap(background, 0, 0, 0);
	            al_draw_bitmap(player_side_up, player_pos_x, player_pos_y, 0);
	            al_draw_bitmap(player_side_down, -50, -50, 0);
	            al_draw_bitmap(player_side_left, -50, -50, 0);
	            al_draw_bitmap(player_side_rigth, -50, -50, 0);
	            al_draw_bitmap(player_side_in_move, -50, -50, 0);
	        }else if(player_move_down){
	        	al_draw_bitmap(background, 0, 0, 0);
	            al_draw_bitmap(player_side_up, -50, -50, 0);
	            al_draw_bitmap(player_side_down, player_pos_x, player_pos_y, 0);
	            al_draw_bitmap(player_side_left, -50, -50, 0);
	            al_draw_bitmap(player_side_rigth, -50, -50, 0);
	            al_draw_bitmap(player_side_in_move, -50, -50, 0);
	        }else if(player_move_left){
	        	al_draw_bitmap(background, 0, 0, 0);
	            al_draw_bitmap(player_side_up, -50, -50, 0);
	            al_draw_bitmap(player_side_down, -50, -50, 0);
	            al_draw_bitmap(player_side_left, player_pos_x, player_pos_y, 0);
	            al_draw_bitmap(player_side_rigth, -50, -50, 0);
	            al_draw_bitmap(player_side_in_move, -50, -50, 0);
	        }else if(player_move_right){
	        	al_draw_bitmap(background, 0, 0, 0);
	            al_draw_bitmap(player_side_up, -50, -50, 0);
	            al_draw_bitmap(player_side_down, -50, -50, 0);
	            al_draw_bitmap(player_side_left, -50, -50, 0);
	            al_draw_bitmap(player_side_rigth, player_pos_x, player_pos_y, 0);
	            al_draw_bitmap(player_side_in_move, -50, -50, 0);
	        }
	    }else{
	    	al_draw_bitmap(background, 0, 0, 0);
        	al_draw_bitmap(player_side_up, -50, -50, 0);
            al_draw_bitmap(player_side_down, -50, -50, 0);
            al_draw_bitmap(player_side_left, -50, -50, 0);
            al_draw_bitmap(player_side_rigth, -50, -50, 0);
            al_draw_bitmap(player_side_in_move, player_pos_x, player_pos_y, 0);
        }
		al_flip_display();
	}
	// Destruindo tudo para finaliza o programa
	al_destroy_display(display);
	al_destroy_event_queue(queue_event);
	return 0;
}