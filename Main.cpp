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
	int mapa_atual = 2;
	int DISPLAY_WIDTH;
	int DISPLAY_HEIGHT;
	int num_bolls_small;
	int num_bolls_big;
	int pixel_width;
	int pixel_height;
	if(mapa_atual == 1){
		DISPLAY_WIDTH = 600;
		DISPLAY_HEIGHT = 300;
		num_bolls_small = 96;
		num_bolls_big = 4;
		pixel_width = 441;
		pixel_height = 234;

	}else if(mapa_atual == 2){
		DISPLAY_WIDTH = 783;
		DISPLAY_HEIGHT = 759;
		num_bolls_small = 242;
		num_bolls_big = 4;
		pixel_width = 625;
		pixel_height = 694;
	}

	// Criando as variáveis do jogo
	int res_monitor_x;
	int res_monitor_y;
	int dist_cap = 10;
	int nivel = 0;
	bool isRunning = true;
	bool game_win = false;
	bool game_over = false;
	bool pacman_die = false;
	bool exit_game = false;
	bool big_boll_white = false;
	int estagio_sprite_player = 0;
	float res_x;
	float res_y;
	int monster_sprit_one = 1;
    int count = 0;
    int count2 = 0;
    int count3 = 0;
    int count4 = 0;
    int mov_atual = 0;
    srand((unsigned)time(NULL));
	// Criando as Variáveis do Player
	Player* player = new Player();

	// Criando os Monstros
	Monster* monster_01 = new Monster(18,18);//(179, 110);
	Monster* monster_02 = new Monster(18,18);//(202, 110);
	Monster* monster_03 = new Monster(18,18);//(223, 110);
	Monster* monster_04 = new Monster(18,18);//(248, 110);

	// Criando os objetos
	ALLEGRO_BITMAP *grama_fundo = NULL;
	ALLEGRO_BITMAP *background = NULL;
	ALLEGRO_BITMAP *triangulado = NULL;
	ALLEGRO_BITMAP *img_small_boll = NULL;
	ALLEGRO_BITMAP *img_big_boll_white = NULL;
	ALLEGRO_BITMAP *img_big_boll_yellow = NULL;

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_MONITOR_INFO info;
	ALLEGRO_EVENT_QUEUE *queue_event = NULL;
	ALLEGRO_FONT *font_message = NULL;
	ALLEGRO_SAMPLE *pacman_beginning = NULL;
	ALLEGRO_SAMPLE *pacman_chomp = NULL;
	ALLEGRO_SAMPLE *pacman_death = NULL;
	ALLEGRO_SAMPLE *pacman_eatfruit = NULL;
	ALLEGRO_SAMPLE *pacman_eatghost = NULL;
	ALLEGRO_SAMPLE_INSTANCE *inst_pacman_beginning = NULL;
	ALLEGRO_SAMPLE_INSTANCE *inst_pacman_chomp = NULL;
	ALLEGRO_SAMPLE_INSTANCE *inst_pacman_death = NULL;
	ALLEGRO_SAMPLE_INSTANCE *inst_pacman_eatfruit = NULL;
	ALLEGRO_SAMPLE_INSTANCE *inst_pacman_eatghost = NULL;
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
	grama_fundo = al_load_bitmap("./images/grama_fundo.png");
	if(mapa_atual == 1){
		background = al_load_bitmap("./images/background_01.png");
		triangulado = al_load_bitmap("./images/mata_triangulado_01.png");
	}else if(mapa_atual == 2){		
		background = al_load_bitmap("./images/background_02.png");
		triangulado = al_load_bitmap("./images/mata_triangulado_02.png");
	}
	img_small_boll = al_load_bitmap("./images/small_boll.png");
	img_big_boll_white = al_load_bitmap("./images/big_boll_white.png");
	img_big_boll_yellow = al_load_bitmap("./images/big_boll_yellow.png");

	//Crregando os Sons do JOGO
	pacman_beginning = al_load_sample("sounds/pacman_beginning.wav");
	pacman_chomp = al_load_sample("sounds/pacman_chomp.wav");
	pacman_death = al_load_sample("sounds/pacman_death.wav");
	pacman_eatfruit = al_load_sample("sounds/pacman_eatfruit.wav");
	pacman_eatghost = al_load_sample("sounds/pacman_eatghost.wav");

	inst_pacman_beginning = al_create_sample_instance(pacman_beginning);
	inst_pacman_chomp = al_create_sample_instance(pacman_chomp);
	inst_pacman_death = al_create_sample_instance(pacman_death);
	inst_pacman_eatfruit = al_create_sample_instance(pacman_eatfruit);
	inst_pacman_eatghost = al_create_sample_instance(pacman_eatghost);

	al_attach_sample_instance_to_mixer(inst_pacman_beginning, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(inst_pacman_chomp, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(inst_pacman_death, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(inst_pacman_eatfruit, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(inst_pacman_eatghost, al_get_default_mixer());

    //Carregando as imagens do personagem
    player->upload_images();

    // Carregando as imagens dos monstros
    monster_01->upload_images_red();
    monster_02->upload_images_pink();
    monster_03->upload_images_blue();
    monster_04->upload_images_yellow();

    // Inicia a bolinhas e superbools
    Boll small_boll[num_bolls_small];
    Boll big_boll[num_bolls_big];
    int total_bolls;
    if(mapa_atual==1){
    	total_bolls = 100;
    }else if(mapa_atual==2){
    	total_bolls = 246;
    }
    int bolls_pull = 0;
    
    // Criando a Matriz do jogo
	int i,j,k=0,l=0;
	unsigned char **game_map;
	game_map = (unsigned char**) calloc (pixel_width,sizeof(unsigned char*));
	for(i=0;i<pixel_width;i++){
		game_map[i] = (unsigned char*) calloc (pixel_height,sizeof(unsigned char));
	}
	
	if(false){ // função de coleta de informações do mapa_triangulado e escrita no txt
		unsigned char r;
		unsigned char g;
		unsigned char b;
		FILE *out;
		if(mapa_atual==1){
			out = fopen("game_map_01.txt","w");
		}else if(mapa_atual==2){
			out = fopen("game_map_02.txt","w");
		}
		for(i=0;i<pixel_width;i++){
			for(j=0;j<pixel_height;j++){
				al_unmap_rgb(al_get_pixel(triangulado,i,j), &r, &g, &b);
				if(r+g+b == 0){
					fprintf(out, "%i",0);
				}else if(r == 255){	
					fprintf(out, "%i",2);
				}else if(b == 255){	
					fprintf(out, "%i",3);
				}else{
					fprintf(out, "%i",1);
				}
			}
			if(i%60==0){
				cout << i/60.0 << endl;
			}
		}
		fclose(out);
	}
	if(true){ // função de coleta de informações do txt
		FILE *in;
		if(mapa_atual==1){
			in = fopen("game_map_01.txt","r");
		}else if(mapa_atual==2){
			in = fopen("game_map_02.txt","r");
		}
		for(i=0;i<pixel_width;i++){
			for(j=0;j<pixel_height;j++){
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
			}
		}
		fclose(in);
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
	if(mapa_atual==1){
		al_draw_textf(font_message, al_map_rgb(255,255,0), 192, 114, 0, "READING!");
	}else if(mapa_atual==2){
		al_draw_textf(font_message, al_map_rgb(255,255,0), 289, 314, 0, "READING!");
	}
	al_flip_display();
	while(al_get_sample_instance_playing(inst_pacman_beginning)){
		//só pra esperar pra musica carregar toda
	}
	while(!exit_game){
		/***************************************************************



		//se tver "Indivíduo" a ser testado nessa "Geração"
			//realiza a troca de Indivíduo há ser testado
		//se não tiver mais "Indivíduo" a ser testado
			//realiza a  escolha do "Indivíduo" mais "Apto" a gerar a nova "Geração"
			//realiza a "Evolução da Especie"
			//coloca o primeiro "Indivíduo" a ser testado no caso de teste



		***************************************************************/
		game_over = false;
		player->setLifes(3);
		player->setPoint(0);
		nivel = 0;
		while(!game_over){
			//zera tudo para começa novo jogo
			isRunning = true;
			monster_01->position(18,18);
			monster_02->position(18,18);
			monster_03->position(18,18);
			monster_04->position(18,18);
			if(mapa_atual==1){
				player->position(213,156);
			}else if(mapa_atual==2){
				player->position(306,386);
			}
			if(game_win || nivel==0){
				nivel++;
				game_win = false;
				bolls_pull = 0;
				
				for(i=0;i<num_bolls_small;i++){
		        	small_boll[i].active = true;
		        }
		        for(i=0;i<num_bolls_big;i++){
		        	big_boll[i].active = true;
		        }
			}
			pacman_die = false;
			while(isRunning){
				/***************************************************************



				//Trocar o evento do teclado para tocar a direção do player pela saida da rede neural
				//Fazendo o "Indivíduo" escolher a ação que realizara



				***************************************************************/
				ALLEGRO_EVENT event;
				while(!al_is_event_queue_empty(queue_event)){
		            al_wait_for_event(queue_event, &event);
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
							case ALLEGRO_KEY_ESCAPE://verifica se precionou a tecla esc para sair
								isRunning = false;
								game_over = true;
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
				monster_01->move(game_map);
				monster_02->move(game_map);
				monster_03->move(game_map);
				monster_04->move(game_map);

				pacman_die = monster_01->collision(player->getPos_x(),player->getPos_y()) ||
							 monster_02->collision(player->getPos_x(),player->getPos_y()) ||
							 monster_03->collision(player->getPos_x(),player->getPos_y()) ||
							 monster_04->collision(player->getPos_x(),player->getPos_y());

				//Lógica de movimento do Player
				int aux = mov_atual;
				mov_atual = player->define_move(mov_atual,game_map);
				if(mov_atual==-1){
					count--;
					mov_atual = aux;
				}

				if(count == 5){
		            estagio_sprite_player++;
		            if(estagio_sprite_player == 5){
		            	estagio_sprite_player = 1;
		            }
		            count = 0;
		        }else{
		            count++;
		        }
		        //al_clear_to_color(al_map_rgb(0,0,0));
		        al_draw_bitmap(grama_fundo, 0, 0, 0);
		        al_draw_bitmap(background, 0, 0, 0);
				// Coloca a imagem adequada do Player para dar a impressão de movimento
				player->show(estagio_sprite_player, mov_atual);
		        //Colocando as bolinhas
		        if(count2 == 5){
		            big_boll_white = !big_boll_white;
		            count2 = 0;
		        }else{
		            count2++;
		        }
		        for(i=0;i<num_bolls_small;i++){
		        	if((player->getPos_x()+11==small_boll[i].pos_x && player->getPos_y()+11-dist_cap==small_boll[i].pos_y || 
		        		player->getPos_x()+11==small_boll[i].pos_x && player->getPos_y()+11+dist_cap==small_boll[i].pos_y || 
		        		player->getPos_x()+11-dist_cap==small_boll[i].pos_x && player->getPos_y()+11==small_boll[i].pos_y || 
		        		player->getPos_x()+11+dist_cap==small_boll[i].pos_x && player->getPos_y()+11==small_boll[i].pos_y) &&
		        		small_boll[i].active){
		        		small_boll[i].active = false;
		        		player->setPoint(player->getPoint()+100);
		        		al_play_sample_instance(inst_pacman_chomp);
		        		bolls_pull++;
		        	}
		        	if(small_boll[i].active){
		        		al_draw_bitmap(img_small_boll, small_boll[i].pos_x-2, small_boll[i].pos_y-2, 0);
		        	}
		        }
		        if(big_boll_white){
			        for(i=0;i<num_bolls_big;i++){
			        	if(player->getPos_x()+11==big_boll[i].pos_x && player->getPos_y()+11==big_boll[i].pos_y && big_boll[i].active){
			        		big_boll[i].active = false;
			        		al_play_sample_instance(inst_pacman_chomp);
			        		bolls_pull++;
			        	}
			        	if(big_boll[i].active){
				        	al_draw_bitmap(img_big_boll_white, big_boll[i].pos_x-5, big_boll[i].pos_y-5, 0);
			        	}
			        }
		        }else{
		        	for(i=0;i<num_bolls_big;i++){
		        		if(player->getPos_x()+11==big_boll[i].pos_x && player->getPos_y()+11==big_boll[i].pos_y && big_boll[i].active){
			        		big_boll[i].active = false;
			        		al_play_sample_instance(inst_pacman_chomp);
			        		bolls_pull++;

			        	}
			        	if(big_boll[i].active){
				        	al_draw_bitmap(img_big_boll_yellow, big_boll[i].pos_x-5, big_boll[i].pos_y-5, 0);
			        	}
			        }
		        }
		        if(bolls_pull==total_bolls){
		        	game_win = true;
		        }
		        if(count4 == 5){
		        	monster_sprit_one++;
		            if(monster_sprit_one == 5){
		            	monster_sprit_one = 1;
		            }
		            count4 = 0;
		        }else{
		            count4++;
		        }
		        //Coloando os Monstros
		        monster_01->show_monster(monster_sprit_one);
		        monster_02->show_monster(monster_sprit_one);
		        monster_03->show_monster(monster_sprit_one);
		        monster_04->show_monster(monster_sprit_one);

		        //Atualizando a pontuação e outros
		        if(mapa_atual==1){
			        al_draw_textf(font_message, al_map_rgb(255, 255, 0), 467, 46, 0, "Points: %lli", player->getPoint());
			        al_draw_textf(font_message, al_map_rgb(255, 255, 0), 467, 70, 0, "Lifes : %i", player->getLifes());
			        al_draw_textf(font_message, al_map_rgb(255, 255, 0), 467, 135, 0, "Ftns: %.4f", 0.0);
			        al_draw_textf(font_message, al_map_rgb(255, 255, 0), 467, 159, 0, "Ger : %i", 0);
			        al_draw_textf(font_message, al_map_rgb(255, 255, 0), 467, 183, 0, "Ind : %i", 0);
			        al_draw_textf(font_message, al_map_rgb(255, 255, 0), 467, 207, 0, "nvl : %i", nivel);
			    }else if(mapa_atual==2){
			        al_draw_textf(font_message, al_map_rgb(255, 255, 0), 650, 46, 0, "Points: %lli", player->getPoint());
			        al_draw_textf(font_message, al_map_rgb(255, 255, 0), 650, 70, 0, "Lifes : %i", player->getLifes());
			        al_draw_textf(font_message, al_map_rgb(255, 255, 0), 650, 135, 0, "Ftns: %.4f", 0.0);
			        al_draw_textf(font_message, al_map_rgb(255, 255, 0), 650, 159, 0, "Ger : %i", 0);
			        al_draw_textf(font_message, al_map_rgb(255, 255, 0), 650, 183, 0, "Ind : %i", 0);
			        al_draw_textf(font_message, al_map_rgb(255, 255, 0), 650, 207, 0, "nvl : %i", nivel);
			    }
			    if(game_win){
			    	isRunning = false;
					player->setLifes(player->getLifes()+1);
			    }
		        if(pacman_die){
					isRunning = false;
					player->setLifes(player->getLifes()-1);
		        }
				if(count3 == nivel){
		            al_flip_display();
		            count3 = 0;
		        }else{
		            count3++;
		        }
			}
			if(player->getLifes() == 0){
				game_over = true;
			}
		}
		/***************************************************************


		
			//testa se o "Indivíduo" atingio a meta estipulada de fitness ou outra ondição de parada de "Evolução"
			//se sim exit_game = true; 



		***************************************************************/
	}
	// Destruindo tudo para finaliza o programa
	al_destroy_display(display);
	al_destroy_event_queue(queue_event);
	al_destroy_sample(pacman_beginning);
	al_destroy_sample_instance(inst_pacman_beginning);
	return 0;
}