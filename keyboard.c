#include "keyboard.h"

int keyboard(SDL_Event *event) {
	// On traite l'évènement
	switch (event->type) {
		case SDL_QUIT:
			// On a fermé la fenetre
			return 0;
		break;
		case SDL_KEYDOWN:
			// On a appuyé sur une touche
			lock = 1;
		break;
	}
	if (lock == 1) {
		switch (event->key.keysym.sym) {
			case SDLK_KP_MINUS : 	
				whereiamz += whereiamz < 1000. ? 10 : 0;
			break;
			
			case SDLK_KP_PLUS :
				whereiamz -= whereiamz > 10. ? 10 : 0;
			break;
			
			case SDLK_UP :
				whereiamy += whereiamy < 750. ? 10 : 0;
			break;
			
			case SDLK_DOWN :
				whereiamy -= whereiamy > -750. ? 10 : 0;
			break;
			
			case SDLK_LEFT :
				whereiamx -= whereiamx > -500. ? 10 : 0;
			break;
			
			case SDLK_RIGHT :
				whereiamx += whereiamx < 500. ? 10 : 0;
			break;
			
			case SDLK_z :
				whereilooky += 10;
			break;
			
			case  SDLK_s :
				whereilooky -= 10;
			break;
			
			case SDLK_d :
				whereilookx += 10;
			break;
			
			case SDLK_q :
				whereilookx -= 10;
			break;
			
			case SDLK_a :
				whereilookz -= 10;
			break;
			
			case SDLK_e :
				whereilookz += 10;
			break;   
			     
			case SDLK_w :
				anim_bras_pw(1);
			break;
			
			case SDLK_x :
				anim_bras_pw(-1);
			break;
			
			case SDLK_c :
				desk_slaming_pw();
				chunk = musique_slam;
				Mix_PlayChannel(-1, chunk, 0);
			break;
			
			case SDLK_v :
				musique = musique_foule;
				Mix_PlayMusic(musique, 1);
				public_noding();
			break;
			
			case SDLK_j :
				lookfromjudge();
			break;
			
			case SDLK_u :
				lookjudge();
			break;
			case SDLK_p :
				lookphoenix();
			break;
			
			case SDLK_o :
				lookpublic();
			break;
			
			case SDLK_i :
				lookpayne();
			break;
			
			case SDLK_m :
				look_mia_from_phoenix();
			break;
			
			case SDLK_y :
				lookwitness();
			break;
			
			case SDLK_h :
				musique = musique_marteau;
				anim_marteau();
				Mix_PlayMusic(musique, 0);
			break;
			
			case SDLK_r :
				chunk = musique_holdit;
				Mix_PlayChannel(-1, chunk, 0);	
			break;
			
			case SDLK_f :
				chunk = musique_takethat;
				Mix_PlayChannel(-1, chunk, 0);
			break;

			case SDLK_g :
			chunk = musique_payne;
			Mix_PlayChannel(-1, chunk, 0);

			break;
			
			case SDLK_n :
				chunk = musique_phoenix;
				if(good_objection) {
					Mix_HaltMusic();
				}
				good_objection = 0;
				Mix_PlayChannel(-1, chunk, 0);
			break;
			
			case SDLK_l :
				musique = musique_trial;
				Mix_PlayMusic(musique, -1);
			break;
			
			case SDLK_SEMICOLON :
				musique = musique_moderate;
				Mix_PlayMusic(musique, -1);
			break;
			
			case SDLK_t :
				musique = musique_allegro;
				Mix_PlayMusic(musique, -1);
			break;
			
			case SDLK_EXCLAIM:
				musique = musique_objection;
				Mix_PlayMusic(musique, -1);
			break;
			
			case SDLK_ASTERISK:
				musique = musique_cornered;
				Mix_PlayMusic(musique, -1);
			break;
			
			case SDLK_DOLLAR:
				musique = musique_examination;
				Mix_PlayMusic(musique, 0);
			break;
			
			case SDLK_b :
				printf("%f, %f, %f, %f, %f, %f\n", whereiamx, whereiamy, whereiamz, whereilookx, whereilooky, whereilookz);
			break;
			
			case SDLK_COLON:
				Mix_HaltMusic();
			break;
			
			case SDLK_COMMA:
				if( Mix_PausedMusic() == 1 ) {
					Mix_ResumeMusic();
				} else {
					Mix_PauseMusic();
				}
			break;
		}
		lock = 0;
	}

	return 1;
}
