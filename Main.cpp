#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <stdio.h>
#include <stdlib.h>
#include "Player.h"
#include "Monster.h"

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
	int res_monitor_x;
	int res_monitor_y;
	int dist_cap = 10;
	float res_x;
	float res_y;
	bool isRunning = true;
	bool game_over = false;
	int boca_aberta = 0;
	bool exit_game = false;
	bool big_boll_white = false;
	bool monster_sprit_one = false;
    int count = 0;
    int count2 = 0;
    int count3 = 0;
    int count4 = 0;
    int mov_atual = 0;
    srand((unsigned)time(NULL));
	// Criando as Variáveis do Player
	Player* player = new Player();

	// Criando os Monstros
	Monster* monster_red = new Monster(18,18);//(179, 110);
	Monster* monster_pink = new Monster(18,18);//(202, 110);
	Monster* monster_blue = new Monster(18,18);//(223, 110);
	Monster* monster_yellow = new Monster(18,18);//(248, 110);

	// Criando os objetos
	ALLEGRO_BITMAP *background = NULL;
	ALLEGRO_BITMAP *img_small_boll = NULL;
	ALLEGRO_BITMAP *img_big_boll_white = NULL;
	ALLEGRO_BITMAP *img_big_boll_yellow = NULL;

	ALLEGRO_BITMAP *pac_man_die_stage_01 = NULL;
	ALLEGRO_BITMAP *pac_man_die_stage_02 = NULL;
	ALLEGRO_BITMAP *pac_man_die_stage_03 = NULL;
	ALLEGRO_BITMAP *pac_man_die_stage_04 = NULL;
	ALLEGRO_BITMAP *pac_man_die_stage_05 = NULL;
	ALLEGRO_BITMAP *pac_man_die_stage_06 = NULL;
	ALLEGRO_BITMAP *pac_man_die_stage_07 = NULL;
	ALLEGRO_BITMAP *pac_man_die_stage_08 = NULL;
	ALLEGRO_BITMAP *pac_man_die_stage_09 = NULL;
	ALLEGRO_BITMAP *pac_man_die_stage_10 = NULL;
	ALLEGRO_BITMAP *pac_man_die_stage_11 = NULL;

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_MONITOR_INFO info;
	ALLEGRO_EVENT_QUEUE *queue_event = NULL;
	ALLEGRO_FONT *font_message = NULL;
	ALLEGRO_SAMPLE *pacman_trilha = NULL;
	ALLEGRO_SAMPLE *pacman_beginning = NULL;
	ALLEGRO_SAMPLE *pacman_chomp = NULL;
	ALLEGRO_SAMPLE *pacman_death = NULL;
	ALLEGRO_SAMPLE *pacman_eatfruit = NULL;
	ALLEGRO_SAMPLE *pacman_eatghost = NULL;
	ALLEGRO_SAMPLE *pacman_extrapac = NULL;
	ALLEGRO_SAMPLE *pacman_intermission = NULL;
	ALLEGRO_SAMPLE_INSTANCE *inst_pacman_trilha = NULL;
	ALLEGRO_SAMPLE_INSTANCE *inst_pacman_beginning = NULL;
	ALLEGRO_SAMPLE_INSTANCE *inst_pacman_chomp = NULL;
	ALLEGRO_SAMPLE_INSTANCE *inst_pacman_death = NULL;
	ALLEGRO_SAMPLE_INSTANCE *inst_pacman_eatfruit = NULL;
	ALLEGRO_SAMPLE_INSTANCE *inst_pacman_eatghost = NULL;
	ALLEGRO_SAMPLE_INSTANCE *inst_pacman_extrapac = NULL;
	ALLEGRO_SAMPLE_INSTANCE *inst_pacman_intermission = NULL;
	ALLEGRO_TRANSFORM redimencionamento;

	// Iniciando o programa
	if(!al_init()){
		al_show_native_message_box(display,"Erro","Descrição do Erro:","Não foi possivel Iniciar",NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	//Pegando as resoluções do Munitor
	al_get_monitor_info(0,&info);
	res_monitor_x = info.x2 - info.x1;
	res_monitor_y = info.y2 - info.y1;
	res_x = res_monitor_x / (float) DISPLAY_WIDTH;
	res_y = res_monitor_y / (float) DISPLAY_HEIGHT;
	// Criando a Tela
	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	display = al_create_display(res_monitor_x,res_monitor_y);
	if(!display){
		al_show_native_message_box(display,"Erro","Descrição do Erro:","Não foi possivel criar o 'Display'",NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	al_set_window_title(display, "PAC-MAN");

	// Redimencionando a Tela do JOGO
	al_identity_transform(&redimencionamento);
	al_scale_transform(&redimencionamento,res_x,res_y);
	al_use_transform(&redimencionamento);

	// Instalação de addon
	al_install_keyboard();
	al_install_audio();

	// Criação de addos
	al_init_primitives_addon();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_acodec_addon();

	al_reserve_samples(10);

	// Carregando as imagens do JOGO
	background = al_load_bitmap("./images/background.png");
	img_small_boll = al_load_bitmap("./images/small_boll.png");
	img_big_boll_white = al_load_bitmap("./images/big_boll_white.png");
	img_big_boll_yellow = al_load_bitmap("./images/big_boll_yellow.png");
	pac_man_die_stage_01 = al_load_bitmap("./images/player/die/pac_man_die_stage_01.png");
	pac_man_die_stage_02 = al_load_bitmap("./images/player/die/pac_man_die_stage_02.png");
	pac_man_die_stage_03 = al_load_bitmap("./images/player/die/pac_man_die_stage_03.png");
	pac_man_die_stage_04 = al_load_bitmap("./images/player/die/pac_man_die_stage_04.png");
	pac_man_die_stage_05 = al_load_bitmap("./images/player/die/pac_man_die_stage_05.png");
	pac_man_die_stage_06 = al_load_bitmap("./images/player/die/pac_man_die_stage_06.png");
	pac_man_die_stage_07 = al_load_bitmap("./images/player/die/pac_man_die_stage_07.png");
	pac_man_die_stage_08 = al_load_bitmap("./images/player/die/pac_man_die_stage_08.png");
	pac_man_die_stage_09 = al_load_bitmap("./images/player/die/pac_man_die_stage_09.png");
	pac_man_die_stage_10 = al_load_bitmap("./images/player/die/pac_man_die_stage_10.png");
	pac_man_die_stage_11 = al_load_bitmap("./images/player/die/pac_man_die_stage_11.png");

	//Crregando os Sons do JOGO
	pacman_trilha = al_load_sample("sounds/pacman_trilha.wav");
	pacman_beginning = al_load_sample("sounds/pacman_beginning.wav");
	pacman_chomp = al_load_sample("sounds/pacman_chomp.wav");
	pacman_death = al_load_sample("sounds/pacman_death.wav");
	pacman_eatfruit = al_load_sample("sounds/pacman_eatfruit.wav");
	pacman_eatghost = al_load_sample("sounds/pacman_eatghost.wav");
	pacman_extrapac = al_load_sample("sounds/pacman_extrapac.wav");
	pacman_intermission = al_load_sample("sounds/pacman_intermission.wav");

	inst_pacman_trilha = al_create_sample_instance(pacman_trilha);
	inst_pacman_beginning = al_create_sample_instance(pacman_beginning);
	inst_pacman_chomp = al_create_sample_instance(pacman_chomp);
	inst_pacman_death = al_create_sample_instance(pacman_death);
	inst_pacman_eatfruit = al_create_sample_instance(pacman_eatfruit);
	inst_pacman_eatghost = al_create_sample_instance(pacman_eatghost);
	inst_pacman_extrapac = al_create_sample_instance(pacman_extrapac);
	inst_pacman_intermission = al_create_sample_instance(pacman_intermission);

	al_attach_sample_instance_to_mixer(inst_pacman_trilha, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(inst_pacman_beginning, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(inst_pacman_chomp, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(inst_pacman_death, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(inst_pacman_eatfruit, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(inst_pacman_eatghost, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(inst_pacman_extrapac, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(inst_pacman_intermission, al_get_default_mixer());

	//al_set_sample_instance_playmode(inst_pacman_trilha, ALLEGRO_PLAYMODE_LOOP);
	//al_set_sample_instance_gain(inst_pacman_trilha, 0.5);

    //Carregando as imagens do personagem
    player->upload_images();

    // Carregando as imagens dos monstros
    monster_red->upload_images_red();
    monster_pink->upload_images_pink();
    monster_blue->upload_images_blue();
    monster_yellow->upload_images_yellow();

    // Inicia a bolinhas
    Boll small_boll[96];
    Boll big_boll[4];
    int total_bolls = 100;
    int bolls_pull = 0;
    
    // Criando a Matriz do jogo
	int i,j,k=0,l=0;
	unsigned char game_map[441][234];
	//unsigned char r;
	//unsigned char g;
	//unsigned char b;
	FILE *in = fopen("game_map.txt","r");
	for(i=0;i<441;i++){
		for(j=0;j<234;j++){
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
	// Desativando o mouse
	al_hide_mouse_cursor(display);

	// Criação da Fila de Eventos
	queue_event = al_create_event_queue();

	// Carregando fonts
	font_message = al_load_font("fonts/Font.ttf", 16, 0);

	// Resgistro do source que podera ser lido pela Fila de eventos
	al_register_event_source(queue_event, al_get_keyboard_event_source());
	al_register_event_source(queue_event, al_get_display_event_source(display));

	// Inicia o Background e os atores
	al_draw_bitmap(background, 0, 0, 0);

	// Laço insfinito para atualização da tela
	al_play_sample_instance(inst_pacman_beginning);
	//al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_textf(font_message, al_map_rgb(255,255,0), 192, 114, 0, "READING!");
	al_flip_display();
	while(al_get_sample_instance_playing(inst_pacman_beginning)){
	}
	while(!exit_game){
		//zera tudo para começa novo jogo
		isRunning = true;
		monster_red->position(18,18);
		monster_pink->position(18,18);
		monster_blue->position(18,18);
		monster_yellow->position(18,18);
		player->position(213,156);
		game_over = false;
		/*
		for(i=0;i<96;i++){
        	small_boll[i].active = true;
        }
        for(i=0;i<4;i++){
        	big_boll[i].active = true;
        }
        */
		while(isRunning){
		//al_play_sample_instance(inst_pacman_trilha);
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
							exit_game = true;
							break;
						default:
							//any key press
							break;
					}
				}else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
					isRunning = false;
				}
			}
			//Lógica de movimento dos monstros
			monster_red->move(game_map);
			monster_pink->move(game_map);
			monster_blue->move(game_map);
			monster_yellow->move(game_map);

			game_over = monster_red->collision(player->getPos_x(),player->getPos_y()) ||
						monster_pink->collision(player->getPos_x(),player->getPos_y()) ||
						monster_blue->collision(player->getPos_x(),player->getPos_y()) ||
						monster_yellow->collision(player->getPos_x(),player->getPos_y());

			//Lógica de movimento do Player
			mov_atual = player->define_move(mov_atual,game_map);
			if(mov_atual==-1){
				count--;
			}

			if(count == 5){
	            boca_aberta++;
	            if(boca_aberta == 5){
	            	boca_aberta = 1;
	            }
	            count = 0;
	        }else{
	            count++;
	        }
	        al_draw_bitmap(background, 0, 0, 0);
			// Coloca a imagem adequada do Player para dar a impressão de movimento
			player->show(boca_aberta, mov_atual);
	        //Colocando as bolinhas
	        if(count2 == 5){
	            big_boll_white = !big_boll_white;
	            count2 = 0;
	        }else{
	            count2++;
	        }
	        for(i=0;i<96;i++){
	        	if((player->getPos_x()+11==small_boll[i].pos_x && player->getPos_y()+11-dist_cap==small_boll[i].pos_y || 
	        		player->getPos_x()+11==small_boll[i].pos_x && player->getPos_y()+11+dist_cap==small_boll[i].pos_y || 
	        		player->getPos_x()+11-dist_cap==small_boll[i].pos_x && player->getPos_y()+11==small_boll[i].pos_y || 
	        		player->getPos_x()+11+dist_cap==small_boll[i].pos_x && player->getPos_y()+11==small_boll[i].pos_y) &&
	        		small_boll[i].active){
	        		small_boll[i].active = false;
	        		player->setPoint(player->getPoint()+100);
	        		al_play_sample_instance(inst_pacman_chomp);
	        	}
	        	if(small_boll[i].active){
	        		al_draw_bitmap(img_small_boll, small_boll[i].pos_x-2, small_boll[i].pos_y-2, 0);
	        	}

	        }
	        if(big_boll_white){
		        for(i=0;i<4;i++){
		        	if(player->getPos_x()+11==big_boll[i].pos_x && player->getPos_y()+11==big_boll[i].pos_y && big_boll[i].active){
		        		big_boll[i].active = false;
		        		al_play_sample_instance(inst_pacman_chomp);
		        	}
		        	if(big_boll[i].active){
			        	al_draw_bitmap(img_big_boll_white, big_boll[i].pos_x-5, big_boll[i].pos_y-5, 0);
		        	}
		        }
	        }else{
	        	for(i=0;i<4;i++){
	        		if(player->getPos_x()+11==big_boll[i].pos_x && player->getPos_y()+11==big_boll[i].pos_y && big_boll[i].active){
		        		big_boll[i].active = false;
		        		al_play_sample_instance(inst_pacman_chomp);

		        	}
		        	if(big_boll[i].active){
			        	al_draw_bitmap(img_big_boll_yellow, big_boll[i].pos_x-5, big_boll[i].pos_y-5, 0);
		        	}
		        }
	        }
	        if(count4 == 5){
	            monster_sprit_one = !monster_sprit_one;
	            count4 = 0;
	        }else{
	            count4++;
	        }
	        //Coloando os Monstros
	        monster_red->show_monster(monster_sprit_one);
	        monster_pink->show_monster(monster_sprit_one);
	        monster_blue->show_monster(monster_sprit_one);
	        monster_yellow->show_monster(monster_sprit_one);

	        //Atualizando a pontuação e outros
	        al_draw_textf(font_message, al_map_rgb(0,57,0), 465, 46, 0, "Points: %lli", player->getPoint());
	        al_draw_textf(font_message, al_map_rgb(0,57,0), 465, 70, 0, "Lifes : %i", 0);
	        al_draw_textf(font_message, al_map_rgb(0,57,0), 465, 135, 0, "Ftns: %.4f", 0.0);
	        al_draw_textf(font_message, al_map_rgb(0,57,0), 465, 159, 0, "Ger : %i", 0);
	        al_draw_textf(font_message, al_map_rgb(0,57,0), 465, 183, 0, "Ind : %i", 0);
	        al_draw_textf(font_message, al_map_rgb(0,57,0), 465, 207, 0, "BFts: %.4f", 0.0);

	        if(game_over){
	        	al_play_sample_instance(inst_pacman_death);
	        	int asd; 
	        	int time_load = 54000000;
	        	asd = 0;
	        	while(asd<time_load){
	        		asd++;
	        	}
	        	al_draw_bitmap(background, 0, 0, 0);
	        	al_draw_bitmap(pac_man_die_stage_01, player->getPos_x(), player->getPos_y(), 0);
				al_draw_textf(font_message, al_map_rgb(255,255,0), 192, 114, 0, "GAME OVER");
				al_flip_display();
				asd = 0;
	        	while(asd<time_load){
	        		asd++;
	        	}
	        	al_draw_bitmap(background, 0, 0, 0);
	        	al_draw_bitmap(pac_man_die_stage_02, player->getPos_x(), player->getPos_y(), 0);
				al_draw_textf(font_message, al_map_rgb(255,255,0), 192, 114, 0, "GAME OVER");
				al_flip_display();
				asd = 0;
	        	while(asd<time_load){
	        		asd++;
	        	}
	        	al_draw_bitmap(background, 0, 0, 0);
	        	al_draw_bitmap(pac_man_die_stage_03, player->getPos_x(), player->getPos_y(), 0);
				al_draw_textf(font_message, al_map_rgb(255,255,0), 192, 114, 0, "GAME OVER");
				al_flip_display();
				asd = 0;
	        	while(asd<time_load){
	        		asd++;
	        	}
	        	al_draw_bitmap(background, 0, 0, 0);
	        	al_draw_bitmap(pac_man_die_stage_04, player->getPos_x(), player->getPos_y(), 0);
				al_draw_textf(font_message, al_map_rgb(255,255,0), 192, 114, 0, "GAME OVER");
				al_flip_display();
				asd = 0;
	        	while(asd<time_load){
	        		asd++;
	        	}
	        	al_draw_bitmap(background, 0, 0, 0);
	        	al_draw_bitmap(pac_man_die_stage_05, player->getPos_x(), player->getPos_y(), 0);
				al_draw_textf(font_message, al_map_rgb(255,255,0), 192, 114, 0, "GAME OVER");
				al_flip_display();
				asd = 0;
	        	while(asd<time_load){
	        		asd++;
	        	}
	        	al_draw_bitmap(background, 0, 0, 0);
	        	al_draw_bitmap(pac_man_die_stage_06, player->getPos_x(), player->getPos_y(), 0);
				al_draw_textf(font_message, al_map_rgb(255,255,0), 192, 114, 0, "GAME OVER");
				al_flip_display();
				asd = 0;
	        	while(asd<time_load){
	        		asd++;
	        	}
	        	al_draw_bitmap(background, 0, 0, 0);
	        	al_draw_bitmap(pac_man_die_stage_07, player->getPos_x(), player->getPos_y(), 0);
				al_draw_textf(font_message, al_map_rgb(255,255,0), 192, 114, 0, "GAME OVER");
				al_flip_display();
				asd = 0;
	        	while(asd<time_load){
	        		asd++;
	        	}
	        	al_draw_bitmap(background, 0, 0, 0);
	        	al_draw_bitmap(pac_man_die_stage_08, player->getPos_x(), player->getPos_y(), 0);
				al_draw_textf(font_message, al_map_rgb(255,255,0), 192, 114, 0, "GAME OVER");
				al_flip_display();
				asd = 0;
	        	while(asd<time_load){
	        		asd++;
	        	}
	        	al_draw_bitmap(background, 0, 0, 0);
	        	al_draw_bitmap(pac_man_die_stage_09, player->getPos_x(), player->getPos_y(), 0);
				al_draw_textf(font_message, al_map_rgb(255,255,0), 192, 114, 0, "GAME OVER");
				al_flip_display();
				asd = 0;
	        	while(asd<time_load){
	        		asd++;
	        	}
	        	al_draw_bitmap(background, 0, 0, 0);
	        	al_draw_bitmap(pac_man_die_stage_10, player->getPos_x(), player->getPos_y(), 0);
				al_draw_textf(font_message, al_map_rgb(255,255,0), 192, 114, 0, "GAME OVER");
				al_flip_display();
				asd = 0;
	        	while(asd<time_load){
	        		asd++;
	        	}
	        	al_draw_bitmap(background, 0, 0, 0);
	        	al_draw_bitmap(pac_man_die_stage_11, player->getPos_x(), player->getPos_y(), 0);
				al_draw_textf(font_message, al_map_rgb(255,255,0), 192, 114, 0, "GAME OVER");
				al_flip_display();
				asd = 0;
	        	while(asd<time_load){
	        		asd++;
	        	}
				isRunning = false;
				player->setLifes(player->getLifes()-1);
	        }
			if(count3 == 0){
	            al_flip_display();
	            count3 = 0;
	        }else{
	            count3++;
	        }
		}
		if(!exit_game){
			exit_game = player->getLifes()==0;
		}
	}
	// Destruindo tudo para finaliza o programa
	al_destroy_display(display);
	al_destroy_event_queue(queue_event);
	al_destroy_sample(pacman_beginning);
	al_destroy_sample_instance(inst_pacman_beginning);
	return 0;
}