#include "courtroom.h"



int main(int argc, char **argv) {
	if (argc != 1) {
		fprintf(stderr, "Usage %s\n", argv[0]);
		exit(EXIT_FAILURE);
	}	
	init();
	pthread_t th;
	int errnum = 0;
	if ((errnum = pthread_create(&th, NULL, (start_routine_type) run, NULL)) != 0) {
		fprintf(stderr, "pthread_create(): %s\n", strerror(errnum));
		exit(EXIT_FAILURE);
	}
	SDL_ShowWindow(fenetre);
	
	game_loop();

	quit_all();
  
	return EXIT_SUCCESS;
}



int keyboard(SDL_Event *event) {
	if (event->type == SDL_KEYDOWN) {
		switch(event->key.keysym.sym) {
			case SDLK_ESCAPE:
				return 0;
			default:
			break;
		}
	} 
  
  return 1;
}

// INIT FUNCTIONS
void init(void) {
	init_globals();
	init_SDL();
	init_GL();
	initTexture();
	printGLInfos();
}

void init_globals(void) {
	whereiamx = -0.000000;
	whereiamy = -760.000000;
	whereiamz = 690.000000;
    
	whereilookx = 0.000000;
	whereilooky = 100.000000;
	whereilookz = 180.000000;

	near = 10.;
	far = 3000.;
	lock = 0;
	deskslaming = 0;
	noding = 0;
	langledubrasdephoenixwright = 0;
	mouvementmarteau = 0;
}


void init_SDL(void) {
	if (SDL_VideoInit(NULL) < 0) {
		fprintf(stderr, "Couldn't initialize video driver: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

	fenetre = SDL_CreateWindow("The first Turnabout",
		0,
		0,
		640, 640,
		SDL_WINDOW_OPENGL);

	if (fenetre == 0) {
		fprintf(stderr, "Erreur lors de la création de la fenêtre (SDL)\n");
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	context = SDL_GL_CreateContext(fenetre);
	if (context == 0) {
		fprintf(stderr, "Erreur lors de la création du contexte OpenGL (SDL)\n");
		SDL_DestroyWindow(fenetre);
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
	if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
		printf("SDL_Mixer Error: %s\n", Mix_GetError());
	}
	Mix_AllocateChannels(32);


	musique_allegro = Mix_LoadMUS("music/Examination_Allegro.ogg");
	musique_moderate = Mix_LoadMUS("music/Examination_Moderate.ogg");
	musique_examination = Mix_LoadMUS("music/Start_Examination.ogg");
	musique_objection = Mix_LoadMUS("music/Objection.ogg");
	musique_cornered = Mix_LoadMUS("music/Cornered.ogg");
	musique_trial = Mix_LoadMUS("music/Trial.ogg");
	musique_foule = Mix_LoadMUS("music/Bruit_Foule.ogg");
	musique_marteau = Mix_LoadMUS("music/Marteau.ogg");
	musique_slam = Mix_LoadWAV("music/Desk_Slaming.ogg");
	musique_takethat = Mix_LoadWAV("music/TakeThat.ogg");
	musique_holdit = Mix_LoadWAV("music/HoldIt.ogg");
	musique_phoenix = Mix_LoadWAV("music/Objection_Phoenix.ogg");
	musique_payne = Mix_LoadWAV("music/Objection_Payne.ogg");
}


void init_GL(void) {
	glClearColor(1., 1., 1., 0.);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	// glEnable(GL_LIGHT2);
	GLfloat intensite[] = {0.2,0.2,0.2, 1.};

	//glLightfv(GL_LIGHT1, GL_DIFFUSE, intensite);
	glLightfv(GL_LIGHT0, GL_AMBIENT, intensite);
	//glLightfv(GL_LIGHT2, GL_DIFFUSE, intensite);
	// glLightfv(GL_LIGHT2, GL_SPECULAR, intensite);



	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	quad = gluNewQuadric();
	gluQuadricOrientation(quad, GLU_OUTSIDE);
	gluQuadricNormals(quad, GLU_SMOOTH);
	gluQuadricTexture(quad, GL_TRUE);
}

void printGLInfos(void) {
	const GLubyte* string;

	string = glGetString(GL_VENDOR);
	printf("Marque fournissant l'implémentation OpenGL : %s\n", string);

	string = glGetString(GL_RENDERER);
	printf("Configuration graphique : %s\n", string);

	string = glGetString(GL_VERSION);
	printf("Version : %s\n", string);
}

void initTexture() {
	glEnable(GL_TEXTURE_2D);
	glGenTextures(122, tex);

	// On définit la première texture
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	defTexture("textures/texture_sol.bmp");
	
	// On définit la deuxième texture
	glBindTexture(GL_TEXTURE_2D, tex[1]);
	defTexture("textures/texture_meuble.bmp");

	glBindTexture(GL_TEXTURE_2D, tex[2]);
	defTexture("textures/argent.bmp");

	glBindTexture(GL_TEXTURE_2D, tex[3]);
	defTexture("textures/argent_balance.bmp");

	glBindTexture(GL_TEXTURE_2D, tex[4]);
	defTexture("textures/gold.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[5]);
	defTexture("textures/wall.bmp");
	
	glBindTexture(GL_TEXTURE_2D, tex[6]);
	defTexture("textures/phoenix.bmp");
	
	glBindTexture(GL_TEXTURE_2D, tex[7]);
	defTexture("textures/face_pw.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[8]);
	defTexture("textures/face_arriere_pw.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[9]);
	defTexture("textures/face_dessous_pw.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[10]);
	defTexture("textures/face_dessus_pw.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[11]);
	defTexture("textures/face_droit_pw.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[12]);
	defTexture("textures/face_gauche_pw.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[13]);
	defTexture("textures/corps_arriere_pw.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[14]);
	defTexture("textures/corps_pw.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[15]);
	defTexture("textures/corps_cote_pw.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[16]);
	defTexture("textures/corps_haut_pw.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[17]);
	defTexture("textures/corps_bas_pw.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[18]);
	defTexture("textures/bras_pw.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[19]);
	defTexture("textures/main_pw.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[20]);
	defTexture("textures/jambe_dessus_pw.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[21]);
	defTexture("textures/jambe_pw.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[22]);
	defTexture("textures/pied_pw.png"); 
	
	glBindTexture(GL_TEXTURE_2D, tex[23]);
	defTexture("textures/face_wp.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[24]);
	defTexture("textures/face_arriere_wp.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[25]);
	defTexture("textures/face_dessous_wp.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[26]);
	defTexture("textures/face_dessus_wp.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[27]);
	defTexture("textures/face_droit_wp.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[28]);
	defTexture("textures/face_gauche_wp.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[29]);
	defTexture("textures/corps_arriere_wp.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[30]);
	defTexture("textures/corps_wp.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[31]);
	defTexture("textures/corps_cote_wp.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[32]);
	defTexture("textures/corps_haut_wp.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[33]);
	defTexture("textures/corps_bas_wp.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[34]);
	defTexture("textures/bras_wp.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[35]);
	defTexture("textures/main_wp.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[36]);
	defTexture("textures/jambe_dessus_wp.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[37]);
	defTexture("textures/jambe_wp.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[38]);
	defTexture("textures/pied_wp.png"); 
	
	glBindTexture(GL_TEXTURE_2D, tex[39]);
	defTexture("textures/face_mia.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[40]);
	defTexture("textures/face_arriere_mia.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[41]);
	defTexture("textures/face_dessous_mia.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[42]);
	defTexture("textures/face_dessus_mia.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[43]);
	defTexture("textures/face_droit_mia.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[44]);
	defTexture("textures/face_gauche_mia.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[45]);
	defTexture("textures/corps_arriere_mia.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[46]);
	defTexture("textures/corps_mia.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[47]);
	defTexture("textures/corps_cote_mia.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[48]);
	defTexture("textures/corps_haut_mia.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[49]);
	defTexture("textures/corps_bas_mia.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[50]);
	defTexture("textures/bras_mia.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[51]);
	defTexture("textures/main_mia.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[52]);
	defTexture("textures/jambe_dessus_mia.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[53]);
	defTexture("textures/jambe_mia.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[54]);
	defTexture("textures/pied_mia.png");  
	
	glBindTexture(GL_TEXTURE_2D, tex[55]);
	defTexture("textures/face_j.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[56]);
	defTexture("textures/face_arriere_j.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[57]);
	defTexture("textures/face_dessous_j.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[58]);
	defTexture("textures/face_dessus_j.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[59]);
	defTexture("textures/face_droit_j.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[60]);
	defTexture("textures/face_gauche_j.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[61]);
	defTexture("textures/corps_arriere_j.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[62]);
	defTexture("textures/corps_j.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[63]);
	defTexture("textures/corps_cote_j.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[64]);
	defTexture("textures/corps_haut_j.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[65]);
	defTexture("textures/corps_bas_j.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[66]);
	defTexture("textures/bras_j.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[67]);
	defTexture("textures/main_j.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[68]);
	defTexture("textures/jambe_dessus_j.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[69]);
	defTexture("textures/jambe_j.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[70]);
	defTexture("textures/pied_j.png"); 
	
	glBindTexture(GL_TEXTURE_2D, tex[71]);
	defTexture("textures/face_lb.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[72]);
	defTexture("textures/face_arriere_lb.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[73]);
	defTexture("textures/face_dessous_lb.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[74]);
	defTexture("textures/face_dessus_lb.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[75]);
	defTexture("textures/face_droit_lb.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[76]);
	defTexture("textures/face_gauche_lb.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[77]);
	defTexture("textures/corps_arriere_lb.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[78]);
	defTexture("textures/corps_lb.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[79]);
	defTexture("textures/corps_cote_lb.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[80]);
	defTexture("textures/corps_haut_lb.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[81]);
	defTexture("textures/corps_bas_lb.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[82]);
	defTexture("textures/bras_lb.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[83]);
	defTexture("textures/main_lb.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[84]);
	defTexture("textures/jambe_dessus_lb.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[85]);
	defTexture("textures/jambe_lb.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[86]);
	defTexture("textures/pied_lb.png"); 
	
	glBindTexture(GL_TEXTURE_2D, tex[87]);
	defTexture("textures/face_yg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[88]);
	defTexture("textures/face_arriere_yg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[89]);
	defTexture("textures/face_dessous_yg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[90]);
	defTexture("textures/face_dessus_yg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[91]);
	defTexture("textures/face_droit_yg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[92]);
	defTexture("textures/face_gauche_yg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[93]);
	defTexture("textures/corps_arriere_yg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[94]);
	defTexture("textures/corps_yg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[95]);
	defTexture("textures/corps_cote_yg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[96]);
	defTexture("textures/corps_haut_yg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[97]);
	defTexture("textures/corps_bas_yg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[98]);
	defTexture("textures/bras_yg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[99]);
	defTexture("textures/main_yg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[100]);
	defTexture("textures/jambe_dessus_yg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[101]);
	defTexture("textures/jambe_yg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[102]);
	defTexture("textures/pied_yg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[103]);
	defTexture("textures/face_dg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[104]);
	defTexture("textures/face_arriere_dg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[105]);
	defTexture("textures/face_dessous_dg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[106]);
	defTexture("textures/face_dessus_dg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[107]);
	defTexture("textures/face_droit_dg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[108]);
	defTexture("textures/face_gauche_dg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[109]);
	defTexture("textures/corps_arriere_dg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[110]);
	defTexture("textures/corps_dg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[111]);
	defTexture("textures/corps_cote_dg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[112]);
	defTexture("textures/corps_haut_dg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[113]);
	defTexture("textures/corps_bas_dg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[114]);
	defTexture("textures/bras_dg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[115]);
	defTexture("textures/main_dg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[116]);
	defTexture("textures/jambe_dessus_dg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[117]);
	defTexture("textures/jambe_dg.png");
	
	glBindTexture(GL_TEXTURE_2D, tex[118]);
	defTexture("textures/pied_dg.png");  

	glBindTexture(GL_TEXTURE_2D, tex[119]);
	defTexture("textures/porte1.png"); 
	
	glBindTexture(GL_TEXTURE_2D, tex[120]);
	defTexture("textures/porte2.png"); 
	
	glBindTexture(GL_TEXTURE_2D, tex[121]);
	defTexture("textures/bras_alternative_j.png");

	// On spécifie comment les textures seront plaquées sur les facettes
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	GLenum erreur;
	if ((erreur = glGetError()) != GL_NO_ERROR) {
		fprintf(stderr, "Erreur OpenGL dans setTexture : %s\n", gluErrorString(erreur));
	}

}



void defTexture(const char * filename) {
	// On fixe les paramètres de la texture,
	// i.e. comment on calcule les coordonnées pixels -> texels.
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);

	// On charge l'image qui va nous servir de texture via la SDL
	SDL_Surface* image = IMG_Load(filename);
	if(!image) {
		fprintf(stderr, "Impossible de charger l'image : %s\n", IMG_GetError());
		exit(EXIT_FAILURE);
	}

	// On verrouille l'image pendant qu'on l'utilise
	if (SDL_MUSTLOCK(image)) {
		SDL_LockSurface(image);
	}

	// On envoie le tableau contenant les texels de la texture à OpenGL
	if (image->format->BytesPerPixel == 3) {
		// L'image d'origine n'a que trois composantes
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	} else if (image->format->BytesPerPixel == 4) {
		// L'image d'origine à quatre composantes
		// (la dernière est le paramètre alpha qui va nous servir à gérer la transparence)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
	} else {
		fprintf(stderr, "Nombre de composants de l'image différent de 3 et 4\n");
		exit(EXIT_FAILURE);
	}

	// On libère les ressources occupées par l'image
	if (SDL_MUSTLOCK(image)) {
		SDL_UnlockSurface(image);
	}
	SDL_FreeSurface(image);
}

void game_loop() {
	int continuer = 1;
	SDL_Event event;
	while (continuer) {
		// On attend le prochain évènement
		SDL_WaitEvent(&event);
		// On traite l'évènement
		switch (event.type) {
			case SDL_QUIT:
				// On a fermé la fenetre
				continuer = 0;
			break;
			case SDL_KEYDOWN:
				// On a appuyé sur une touche
				lock = 1;
				continuer = keyboard(&event);
			break;
		}
		if (lock == 1) {
			switch (event.key.keysym.sym) {
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
		display();
	}
}

// DRAW FUNCTIONS
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	gluLookAt(whereiamx,whereiamy,whereiamz,whereilookx, whereilooky, whereilookz ,- whereiamx + whereilookx ,-whereiamy + whereilooky , whereilookz );
	
	GLfloat pos[] = {0, 0, 1000, 1};
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	pos[2] = -50.;
	glLightfv(GL_LIGHT1, GL_POSITION, pos);
	pos[1] = -650.;
	glLightfv(GL_LIGHT2, GL_POSITION, pos);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpeculaire);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, matShininess);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matBeige);
	sol(-500,-750, 0, -250);
	sol(-500,-250, 0, 250);
	sol(-500, 250, 0, 750); 
	sol(0,-750, 500, -250);
	sol(0,-250, 500, 250);
	sol(0,250, 500, 750);

	glBindTexture(GL_TEXTURE_2D, tex[1]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matBrunClair);

	creer_pave_2(-150., 200., 50., 100., 400., 100.); // bureau du procureur
	creer_pave_2(150., 200., 50., 100., 400., 100.);  // bureau de l'avocat
	creer_pave_2(-250., 375., 50., 100., 50., 100.);  // jonction gauche
	creer_pave_2(250., 375., 50., 100., 50., 100.);   // jonction droite

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matBrun); 
	creer_pave_2(-325., 50., 100., 50., 700., 200.); //Gradins hauts
	creer_pave_2(325., 50., 100., 50., 700., 200.);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matBrunClair);
	creer_pave_2(-377.5, 50., 50., 55., 700., 100.); //Gradins medians
	creer_pave_2(377.5, 50., 50., 55., 700., 100.);

	creer_pave_2(-425., 50., 25., 40., 700., 50.); //Gradins bas
	creer_pave_2(425., 50., 25., 40., 700., 50.);

	creer_pave_2(-250., 625., 150., 200., 100., 300.); // bureaux du juge gauche
	creer_pave_2(250., 625., 150., 200., 100., 300.);  // droit
	creer_pave_2(0., 600., 150., 300., 100., 300.);    // centre

	creer_pave_2(-250., 712.5, 100., 200., 75., 200.);   // estrade
	creer_pave_2(250., 712.5, 100., 200., 75., 200.);
	creer_pave_2(0., 700., 100., 300., 100., 200.);


	creer_pave_2(0., 739, 350., 200., 22., 300.);  // manteau sous le blason

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matBeige);
	glBindTexture(GL_TEXTURE_2D, tex[6]);  
	creer_phoenix();
	creer_winston();
	creer_mia();
	creer_juge();
	switch(witness) {
		case 1:
			creer_witness_1();
		break;
		case 2:
			creer_witness_2();
		break;
	}
	
	creer_public();
	creer_arcade();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matOr);
	glBindTexture(GL_TEXTURE_2D, tex[4]);  
	creer_pave_2(-125.,725.,350.,50.,50.,300.);  //montants derriere le juge
	creer_pave_2(125.,725.,350.,50.,50.,300.);
	creer_pave_2(0., 718., 475., 200., 20., 50.); //revetement derriere le juge 

	creer_witness_stand();

    creer_marteau();
	draw_support();


	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matBeigeClair);
	glBindTexture(GL_TEXTURE_2D, tex[5]);
	creer_murs(0., 0., 500, 1000., 1500., 1000.);

	glBindTexture(GL_TEXTURE_2D, tex[1]); 
	glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matBrun);
		glTranslatef(0., 730., 500.);
		glRotatef(90., 1., 0., 0.); 
		gluDisk(quad, 0., 150., 20., 1.);  //cercle bois situé derriere le juge
	glPopMatrix();

	glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matBrun);
		glTranslatef(0., 750., 500.);
		glRotatef(-90., 1., 0., 0.); 
		gluDisk(quad, 0., 150., 20., 1.);  //cercle bois situé derriere le juge -- coté mur
	glPopMatrix();

	glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matBrun);
		glTranslatef(0., 750., 500.);
		glRotatef(90., 1., 0., 0.); 
		gluCylinder(quad,    150.,    150.,    20.,    20.,    1.); // cylindre reliant les deux cercles 
	glPopMatrix();


	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, tex[3]);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matArgent);
		glTranslatef(0., 710., 550.);
		glRotatef(90., 1., 0., 0.); 
		gluDisk(quad, 0., 50., 20., 1.);  //blason coté face
	glPopMatrix();

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, tex[2]);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matArgent);
		glTranslatef(0., 730., 550.);
		glRotatef(-90., 1., 0., 0.); 
		gluDisk(quad, 0., 50., 20., 1.);   //blason coté mur
	glPopMatrix();

	glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matArgent);
		glTranslatef(0., 730., 550.);
		glRotatef(90., 1., 0., 0.); 
		gluCylinder(quad,    50.,    50.,    20.,    20.,    1.); // tranche du blason
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.,1.,near,far);

	glMatrixMode(GL_MODELVIEW);

	SDL_GL_SwapWindow(fenetre);

	GLenum erreur;
	if ((erreur = glGetError()) != GL_NO_ERROR) {
		fprintf(stderr, "Erreur OpenGL dans display : %s\n", gluErrorString(erreur));
	}
}

void sol(int x0, int y0, int x1, int y1) {
   int step = 250;
   for (int i = x0; i < x1; i+= step) {
	   for (int j = y0; j < y1; j += step) {
			  glBindTexture(GL_TEXTURE_2D, tex[0]);
			  glNormal3f(0, 0, 1);

			  glBegin(GL_QUADS);

			  glTexCoord2f(0., 0.); glVertex3f(i , j, 0.); 
              glTexCoord2f(1., 0.); glVertex3f(i + step, j,0.);
			  glTexCoord2f(1., 1.); glVertex3f(i + step , j + step, 0.);
              glTexCoord2f(0., 1.); glVertex3f(i , j + step, 0.);
			  glEnd(); 
		   
	   }
	   
   }
	   
}
   
void creer_pave_2 (GLfloat centrex, GLfloat centrey, GLfloat centrez, GLfloat largeur,
                    GLfloat profondeur, GLfloat hauteur) {
              
	GLfloat cx = centrex;
	GLfloat cy = centrey;
	GLfloat cz = centrez;
	GLfloat h = hauteur / 2;
	GLfloat l = largeur / 2;
	GLfloat p = profondeur / 2; 

	// On dessine un carré sur le plan -z
	glBegin(GL_QUADS);
		glNormal3f(0, 0, -1);
		glTexCoord2f(0., 0.); glVertex3f(cx - l, cy - p, cz - h); 
		glTexCoord2f(0., 1.); glVertex3f(cx - l, cy + p, cz - h); 
		glTexCoord2f(1., 1.); glVertex3f(cx + l, cy + p, cz - h);
		glTexCoord2f(1., 0.); glVertex3f(cx + l, cy - p, cz - h);
	glEnd();
	
	// On dessine un carré sur le plan z
	glBegin(GL_QUADS);
		glNormal3f(0, 0, 1);
		glTexCoord2f(0., 0.); glVertex3f(cx - l, cy - p, cz + h); 
		glTexCoord2f(0., 1.); glVertex3f(cx + l, cy - p, cz + h); 
		glTexCoord2f(1., 1.); glVertex3f(cx + l, cy + p, cz + h);
		glTexCoord2f(1., 0.); glVertex3f(cx - l, cy + p, cz + h);
	glEnd();
	
	//On dessine un carré sur le plan x
	glBegin(GL_QUADS);
		glNormal3f(1, 0, 0);
		glTexCoord2f(0., 0.); glVertex3f(cx + l, cy - p, cz + h); 
		glTexCoord2f(1., 0.); glVertex3f(cx + l, cy - p, cz - h); 
		glTexCoord2f(1., 1.); glVertex3f(cx + l, cy + p, cz - h);
		glTexCoord2f(0., 1.); glVertex3f(cx + l, cy + p, cz + h);
	glEnd();
	
	//On dessine un carré sur le plan -x
	glBegin(GL_QUADS);
		glNormal3f(-1, 0, 0);
		glTexCoord2f(0., 0.); glVertex3f(cx - l, cy + p, cz + h); 
		glTexCoord2f(1., 0.); glVertex3f(cx - l, cy + p, cz - h); 
		glTexCoord2f(1., 1.); glVertex3f(cx - l, cy - p, cz - h);
		glTexCoord2f(0., 1.); glVertex3f(cx - l, cy - p, cz + h);
	glEnd();
	
	//On dessine un carré sur le plan y
	glBegin(GL_QUADS);
		glNormal3f(0, 1, 0);
		glTexCoord2f(0., 1.); glVertex3f(cx + l, cy + p, cz + h); 
		glTexCoord2f(1., 1.); glVertex3f(cx + l, cy + p, cz - h); 
		glTexCoord2f(1., 0.); glVertex3f(cx - l, cy + p, cz - h);
		glTexCoord2f(0., 0.); glVertex3f(cx - l, cy + p, cz + h);
	glEnd();
	
	//On dessine un carré sur le plan -y
	glBegin(GL_QUADS);
		glNormal3f(0, -1, 0);
		glTexCoord2f(0., 0.); glVertex3f(cx - l, cy - p, cz - h); 
		glTexCoord2f(0., 1.); glVertex3f(cx + l, cy - p, cz - h); 
		glTexCoord2f(1., 1.); glVertex3f(cx + l, cy - p, cz + h);
		glTexCoord2f(1., 0.); glVertex3f(cx - l, cy - p, cz + h);
	glEnd();                    
}
  
    
void creer_pave_with_texture (GLfloat centrex, GLfloat centrey, 
                            GLfloat centrez, GLfloat largeur,
                            GLfloat profondeur, GLfloat hauteur,
                           GLuint tex1, GLuint tex2, GLuint tex3, 
                           GLuint tex4, GLuint tex5, GLuint tex6) {
              
	GLfloat cx = centrex;
	GLfloat cy = centrey;
	GLfloat cz = centrez;
	GLfloat h = hauteur / 2;
	GLfloat l = largeur / 2;
	GLfloat p = profondeur / 2; 

	// On dessine un carré sur le plan -z
	glBindTexture(GL_TEXTURE_2D, tex1);
	glBegin(GL_QUADS);
		glNormal3f(0, 0, -1);
		glTexCoord2f(0., 1.); glVertex3f(cx - l, cy - p, cz - h); 
		glTexCoord2f(1., 1.); glVertex3f(cx - l, cy + p, cz - h); 
		glTexCoord2f(1., 0.); glVertex3f(cx + l, cy + p, cz - h);
		glTexCoord2f(0., 0.); glVertex3f(cx + l, cy - p, cz - h);
	glEnd();
	
	// On dessine un carré sur le plan z
	glBindTexture(GL_TEXTURE_2D, tex2);
	glBegin(GL_QUADS);
		glNormal3f(0, 0, 1);
		glTexCoord2f(0., 0.); glVertex3f(cx - l, cy - p, cz + h); 
		glTexCoord2f(0., 1.); glVertex3f(cx + l, cy - p, cz + h); 
		glTexCoord2f(1., 1.); glVertex3f(cx + l, cy + p, cz + h);
		glTexCoord2f(1., 0.); glVertex3f(cx - l, cy + p, cz + h);
	glEnd();
	
	//On dessine un carré sur le plan x
	glBindTexture(GL_TEXTURE_2D, tex4);
		glBegin(GL_QUADS);
		glNormal3f(1, 0, 0);
		glTexCoord2f(1., 0.); glVertex3f(cx + l, cy - p, cz + h); 
		glTexCoord2f(1., 1.); glVertex3f(cx + l, cy - p, cz - h); 
		glTexCoord2f(0., 1.); glVertex3f(cx + l, cy + p, cz - h);
		glTexCoord2f(0., 0.); glVertex3f(cx + l, cy + p, cz + h);
	glEnd();
	
	//On dessine un carré sur le plan -x
	glBindTexture(GL_TEXTURE_2D, tex3);
	glBegin(GL_QUADS);
		glNormal3f(-1, 0, 0);
		glTexCoord2f(1., 0.); glVertex3f(cx - l, cy + p, cz + h); 
		glTexCoord2f(1., 1.); glVertex3f(cx - l, cy + p, cz - h); 
		glTexCoord2f(0., 1.); glVertex3f(cx - l, cy - p, cz - h);
		glTexCoord2f(0., 0.); glVertex3f(cx - l, cy - p, cz + h);
	glEnd();
	
	//On dessine un carré sur le plan y
	glBindTexture(GL_TEXTURE_2D, tex6);
	glBegin(GL_QUADS);
		glNormal3f(0, 1, 0);
		glTexCoord2f(0., 0.); glVertex3f(cx + l, cy + p, cz + h); 
		glTexCoord2f(0., 1.); glVertex3f(cx + l, cy + p, cz - h); 
		glTexCoord2f(1., 1.); glVertex3f(cx - l, cy + p, cz - h);
		glTexCoord2f(1., 0.); glVertex3f(cx - l, cy + p, cz + h);
	glEnd();
	
	//On dessine un carré sur le plan -y
	glBindTexture(GL_TEXTURE_2D, tex5);
	glBegin(GL_QUADS);
		glNormal3f(0, -1, 0);
		glTexCoord2f(0., 1.); glVertex3f(cx - l, cy - p, cz - h); 
		glTexCoord2f(1., 1.); glVertex3f(cx + l, cy - p, cz - h); 
		glTexCoord2f(1., 0.); glVertex3f(cx + l, cy - p, cz + h);
		glTexCoord2f(0., 0.); glVertex3f(cx - l, cy - p, cz + h);
	glEnd();                                        
}
  
  
void creer_murs (GLfloat centrex, GLfloat centrey, GLfloat centrez, GLfloat largeur,
                    GLfloat profondeur, GLfloat hauteur) {
              
	GLfloat cx = centrex;
	GLfloat cy = centrey;
	GLfloat cz = centrez;
	GLfloat h = hauteur / 2;
	GLfloat l = largeur / 2;
	GLfloat p = profondeur / 2; 

	//On dessine un carré sur le plan x
	glBegin(GL_QUADS);
		glNormal3f(-1, 0, 0);
		glTexCoord2f(0., 0.); glVertex3f(cx + l, cy - p, cz + h);
		glTexCoord2f(0., 1.); glVertex3f(cx + l, cy + p, cz + h); 
		glTexCoord2f(1., 1.); glVertex3f(cx + l, cy + p, cz - h);
		glTexCoord2f(1., 0.); glVertex3f(cx + l, cy - p, cz - h);
	glEnd();
	
	//On dessine un carré sur le plan -x
	glBegin(GL_QUADS);
		glNormal3f(1, 0, 0);
		glTexCoord2f(0., 0.); glVertex3f(cx - l, cy + p, cz + h);
		glTexCoord2f(0., 1.); glVertex3f(cx - l, cy - p, cz + h); 
		glTexCoord2f(1., 1.); glVertex3f(cx - l, cy - p, cz - h);
		glTexCoord2f(1., 0.); glVertex3f(cx - l, cy + p, cz - h); 
	glEnd();
	
	//On dessine un carré sur le plan y
	glBegin(GL_QUADS);
		glNormal3f(0, -1, 0);
		glTexCoord2f(0., 1.); glVertex3f(cx + l, cy + p, cz + h); 
		glTexCoord2f(0., 0.); glVertex3f(cx - l, cy + p, cz + h);
		glTexCoord2f(1., 0.); glVertex3f(cx - l, cy + p, cz - h);
		glTexCoord2f(1., 1.); glVertex3f(cx + l, cy + p, cz - h);
	glEnd();
	
	//On dessine un carré sur le plan -y
	glBegin(GL_QUADS);
		glNormal3f(0, 1, 0);
		glTexCoord2f(0., 0.); glVertex3f(cx - l, cy - p, cz - h); 
		glTexCoord2f(1., 0.); glVertex3f(cx - l, cy - p, cz + h);
		glTexCoord2f(1., 1.); glVertex3f(cx + l, cy - p, cz + h);
		glTexCoord2f(0., 1.); glVertex3f(cx + l, cy - p, cz - h);
	glEnd();                                         
}
  
void creer_witness_stand() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matBrun);
	glBindTexture(GL_TEXTURE_2D, tex[1]);

	for (float c = 0.; c <= 1.1; c += 0.1) {
		float x = 100. * cos(3.14 * c);
		creer_pave_2(x, (sqrt(10000. - x * x) - 300.), 55., 10., 10., 110.);
	}

	for (int i = 110; i < 130; i++) {
		glPushMatrix();
			glTranslatef(0., -300., i);
			gluPartialDisk(quad, 90., 110., 20., 1., -93., 186.);   
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0., -300., i);
			glRotatef(180.,0.,1.,0.);
			gluPartialDisk(quad, 90., 110., 20., 1., -93., 186.);   
		glPopMatrix();
	}
}
  
void creer_phoenix() { // centre de pw 250 100 90
	creer_pave_with_texture(230., 90., 40., 10., 10., 80., tex[22], tex[20], tex[21], tex[21], tex[21], tex[21]); //jg
	creer_pave_with_texture(230., 110., 40., 10., 10., 80., tex[22], tex[20], tex[21], tex[21], tex[21], tex[21]); //jd
	creer_pave_with_texture(230., 100., 120., 10., 40., 80., tex[17], tex[16], tex[14], tex[13], tex[15], tex[15]); //corps
	creer_pave_with_texture(230., 100., 170., 20., 20.,20., tex[9], tex[10], tex[7], tex[8], tex[12], tex[11]); //tete

	glPushMatrix();
		glTranslatef(230., 125., 160. - langledubrasdephoenixwright / 20);
		glRotatef(deskslaming,0.,1.,0.);
		glRotatef(langledubrasdephoenixwright,-1.,1.,0.);
		creer_pave_with_texture(0., 0., -40., 10., 10., 80., tex[19], tex[20], tex[18], tex[18], tex[18], tex[18]); // bd
	glPopMatrix();

	glPushMatrix();
		glTranslatef(230., 75., 160.);

		glRotatef(deskslaming,0.,1.,0.);
		creer_pave_with_texture(0., 0., -40., 10., 10., 80., tex[19], tex[20], tex[18], tex[18], tex[18], tex[18]); // bg
	glPopMatrix();
}
void creer_mia() { // centre de pw 250 100 90
	creer_pave_with_texture(230., 190., 40., 10., 10., 80., tex[54], tex[52], tex[53], tex[53], tex[53], tex[53]); //jg
	creer_pave_with_texture(230., 210., 40., 10., 10., 80., tex[54], tex[52], tex[53], tex[53], tex[53], tex[53]); //jd
	creer_pave_with_texture(230., 200., 120., 10., 40., 80., tex[19], tex[48], tex[46], tex[45], tex[47], tex[47]); //corps
	creer_pave_with_texture(230., 200., 170., 20., 20.,20., tex[41], tex[42], tex[39], tex[40], tex[44], tex[43]); //tete
	creer_pave_with_texture(230., 225., 120., 10., 10., 80., tex[51], tex[52], tex[50], tex[50], tex[50], tex[50]); // bd
	creer_pave_with_texture(230., 175., 120., 10., 10., 80., tex[51], tex[52], tex[50], tex[50], tex[50], tex[50]);  //bg
}
void creer_winston() { // centre de pw 250 100 90
	creer_pave_with_texture(-230., 90., 40., 10., 10., 80., tex[38], tex[36], tex[37], tex[37], tex[37], tex[37]); //jg
	creer_pave_with_texture(-230., 110., 40., 10., 10., 80., tex[38], tex[36], tex[37], tex[37], tex[37], tex[37]); //jd
	creer_pave_with_texture(-230., 100., 120., 10., 40., 80., tex[33], tex[32], tex[29], tex[30], tex[31], tex[31]); //corps
	creer_pave_with_texture(-230., 100., 170., 20., 20.,20., tex[25], tex[26], tex[24], tex[23], tex[27], tex[28]); //tete
	creer_pave_with_texture(-230., 125., 120., 10., 10., 80., tex[35], tex[36], tex[34], tex[34], tex[34], tex[34]); // bd
	creer_pave_with_texture(-230., 75., 120., 10., 10., 80., tex[35], tex[36], tex[34], tex[34], tex[34], tex[34]);  //bg
}
void creer_public() { // centre de pw 250 100 90 
	for (int i = -200; i <= 300; i += 100) {
		creer_pave_with_texture(-377., i - 10, 140., 10., 10., 80., tex[118], tex[116], tex[117], tex[117], tex[117], tex[117]); //jg
		creer_pave_with_texture(-377., i + 10, 140., 10., 10., 80., tex[118], tex[116], tex[117], tex[117], tex[117], tex[117]); //jd
		creer_pave_with_texture(-377., i, 220., 10., 40., 80., tex[113], tex[112], tex[109], tex[110], tex[111], tex[111]); //corps

		glPushMatrix();
			glTranslatef(-377., i, 280.);
			glRotatef((i % 200 == 0) ? noding : -noding,0.,0.,1.);
			creer_pave_with_texture(0., 0., -10., 20., 20., 20., tex[105], tex[106], tex[104], tex[103], tex[107], tex[108]); // tete
		glPopMatrix();

		creer_pave_with_texture(-377., i+ 25, 220., 10., 10., 80., tex[115], tex[116], tex[114], tex[114], tex[114], tex[114]); // bd
		creer_pave_with_texture(-377., i - 25, 220., 10., 10., 80., tex[115], tex[116], tex[114], tex[114], tex[114], tex[114]);  //bg
	}
	for (int i = -200; i <= 300; i += 100) {
		creer_pave_with_texture(377., i - 10, 140., 10., 10., 80., tex[118], tex[116], tex[117], tex[117], tex[117], tex[117]); //jg
		creer_pave_with_texture(377., i + 10, 140., 10., 10., 80., tex[118], tex[116], tex[117], tex[117], tex[117], tex[117]); //jd
		creer_pave_with_texture(377., i, 220., 10., 40., 80., tex[113], tex[112], tex[110], tex[109], tex[111], tex[111]); //corps
		glPushMatrix();
			glTranslatef(377., i, 280.);
			glRotatef( (i % 200 == 0) ? -noding : noding , 0., 0., 1.);
			creer_pave_with_texture(0., 0., -10., 20., 20., 20., tex[105], tex[106], tex[103], tex[104], tex[108], tex[107]); // tete
		glPopMatrix();
		creer_pave_with_texture(377., i+ 25, 220., 10., 10., 80., tex[115], tex[116], tex[114], tex[114], tex[114], tex[114]); // bd
		creer_pave_with_texture(377., i - 25, 220., 10., 10., 80., tex[115], tex[116], tex[114], tex[114], tex[114], tex[114]);  //bg
	}
}


void creer_juge() { // centre de juge 0., 700., 100.
	creer_pave_with_texture(-10., 680., 240., 10., 10., 80., tex[70], tex[68], tex[69], tex[69], tex[69], tex[69]); //jg
	creer_pave_with_texture(10., 680., 240., 10., 10., 80., tex[70], tex[68], tex[69], tex[69], tex[69], tex[69]); //jd
	creer_pave_with_texture(0., 680., 320., 40., 10., 80., tex[65], tex[64], tex[63], tex[63], tex[62], tex[61]); //corps
	creer_pave_with_texture(0., 680., 370., 20., 20.,20., tex[57], tex[58], tex[59], tex[60], tex[55], tex[56]); //tete
	
	creer_pave_with_texture(25., 680., 320., 10., 10., 80., tex[67], tex[68], tex[66], tex[66], tex[66], tex[66]); // bg
	
	creer_pave_with_texture(-25., 680., 333.5 + mouvementmarteau / 2, 10., 10., 53. - + mouvementmarteau, tex[68], tex[68], tex[68], tex[68], tex[68], tex[68]);//bd
	glPushMatrix();
		glTranslatef(-25., 665., 312. + mouvementmarteau);
		creer_pave_with_texture(0, 0, 0, 10., 40., 10., tex[121], tex[121], tex[121], tex[121], tex[67], tex[68]);   //main
	glPopMatrix();
}

void creer_witness_1() { // centre de juge 0., 700., 100.
	creer_pave_with_texture(-10., -280., 40., 10., 10., 80., tex[86], tex[84], tex[85], tex[85], tex[85], tex[85]); //jg
	creer_pave_with_texture(10., -280., 40., 10., 10., 80., tex[86], tex[84], tex[85], tex[85], tex[85], tex[85]); //jd
	creer_pave_with_texture(0., -280., 120., 40., 10., 80., tex[81], tex[81], tex[79], tex[79], tex[77], tex[78]); //corps
	creer_pave_with_texture(0., -280., 170., 20., 20.,20., tex[73], tex[74], tex[75], tex[76], tex[72], tex[71]); //tete
	creer_pave_with_texture(25., -280., 120., 10., 10., 80., tex[83], tex[84], tex[82], tex[82], tex[82], tex[82]); // bd
	creer_pave_with_texture(-25., -280., 120., 10., 10., 80., tex[83], tex[84], tex[82], tex[82], tex[82], tex[82]);  //bg
}

void creer_witness_2() { // centre de juge 0., 700., 100.
	creer_pave_with_texture(-10., -280., 40., 10., 10., 80., tex[102], tex[100], tex[101], tex[101], tex[101], tex[101]); //jg
	creer_pave_with_texture(10., -280., 40., 10., 10., 80., tex[102], tex[100], tex[101], tex[101], tex[101], tex[101]); //jd
	creer_pave_with_texture(0., -280., 120., 40., 10., 80., tex[97], tex[96], tex[95], tex[95], tex[93], tex[94]); //corps
	creer_pave_with_texture(0., -280., 170., 20., 20.,20., tex[89], tex[90], tex[91], tex[92], tex[88], tex[87]); //tete
	creer_pave_with_texture(25., -280., 120., 10., 10., 80., tex[99], tex[100], tex[98], tex[98], tex[98], tex[98]); // bd
	creer_pave_with_texture(-25., -280., 120., 10., 10., 80., tex[99], tex[100], tex[98], tex[98], tex[98], tex[98]);  //bg
}

void creer_arcade() {
	glBindTexture(GL_TEXTURE_2D, tex[5]); 
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matBeigeClair);
	
	for (int y = -650; y < 750; y += 130) { 

		creer_pave_2(-500., y + 57.5, 250, 40., 42., 500.);
		creer_pave_2(-500., y - 57.5, 250, 40., 42., 500.);
		
		glPushMatrix();
			glTranslatef(-500., y - 25 ,525.);
			glRotatef(-45. , 1., 0., 0.);
		creer_pave_2(0., 0., 0., 40., 40., 110.);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(-500., y + 25 ,525.);
			glRotatef(45. , 1., 0., 0.);
		creer_pave_2(0., 0., 0., 40., 40., 110.);
		glPopMatrix();
	
	}
	for (int y = -650; y < 750; y += 130) { 

		creer_pave_2(500., y + 57.5, 250, 40., 42., 500.);
		creer_pave_2(500., y - 57.5, 250, 40., 42., 500.);
		
		glPushMatrix();
			glTranslatef(500., y - 25 ,525.);
			glRotatef(-45. , 1., 0., 0.);
		creer_pave_2(0., 0., 0., 40., 40., 110.);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(500., y + 25 ,525.);
			glRotatef(45. , 1., 0., 0.);
		creer_pave_2(0., 0., 0., 40., 40., 110.);
		glPopMatrix();
		
	}
	
	for (int x = -400; x < -200; x += 130) { 

		creer_pave_2(x + 57.5, -750 , 250, 42., 40., 500.);
		creer_pave_2(x - 57.5, -750 , 250, 42., 40., 500.);
		
		glPushMatrix();
			glTranslatef(x - 25, -750., 525.);
			glRotatef(45. , 0., 1., 0.);
		creer_pave_2(0., 0., 0., 40., 40., 110.);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(x + 25 , -750., 525.);
			glRotatef(-45. , 0., 1., 0.);
		creer_pave_2(0., 0., 0., 40., 40., 110.);
		glPopMatrix();
		
	}
	for (int x = 400; x > 200 ; x -= 130) { 

		creer_pave_2(x + 57.5, -750 , 250, 42., 40., 500.);
		creer_pave_2(x - 57.5, -750 , 250, 42., 40., 500.);
		
		glPushMatrix();
			glTranslatef(x - 25, -750., 525.);
			glRotatef(45. , 0., 1., 0.);
		creer_pave_2(0., 0., 0., 40., 40., 110.);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(x + 25 , -750., 525.);
			glRotatef(-45. , 0., 1., 0.);
		creer_pave_2(0., 0., 0., 40., 40., 110.);
		glPopMatrix();
		
	}
	for (int x = -400; x < -200; x += 130) { 

		creer_pave_2(x + 57.5, 750 , 250, 42., 40., 500.);
		creer_pave_2(x - 57.5, 750 , 250, 42., 40., 500.);
		
		glPushMatrix();
			glTranslatef(x - 25, 750., 525.);
			glRotatef(45. , 0., 1., 0.);
		creer_pave_2(0., 0., 0., 40., 40., 110.);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(x + 25 , 750., 525.);
			glRotatef(-45. , 0., 1., 0.);
		creer_pave_2(0., 0., 0., 40., 40., 110.);
		glPopMatrix();
	
	}
	for (int x = 400; x > 200 ; x -= 130) { 

		creer_pave_2(x + 57.5, 750 , 250, 42., 40., 500.);
		creer_pave_2(x - 57.5, 750 , 250, 42., 40., 500.);
		
		glPushMatrix();
			glTranslatef(x - 25, 750., 525.);
			glRotatef(45. , 0., 1., 0.);
		creer_pave_2(0., 0., 0., 40., 40., 110.);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(x + 25 , 750., 525.);
			glRotatef(-45. , 0., 1., 0.);
		creer_pave_2(0., 0., 0., 40., 40., 110.);
		glPopMatrix();
		
	}		
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matBrun);
	glBindTexture(GL_TEXTURE_2D, tex[119]); 
	creer_pave_2(100., -750,  200., 200., 20, 400.);
	glBindTexture(GL_TEXTURE_2D, tex[120]); 
	creer_pave_2(-100., -750,  200., 200., 20, 400.);

	
}

void creer_marteau() {
	glPushMatrix();
	glTranslatef(-25., 620., 302. + mouvementmarteau);
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, tex[1]); //manche
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matOr);
		glTranslatef(0., 30., 10.);
		glRotatef(90., 1., 0., 0.); 
		glRotatef(180., 1., 0., 0.); 
		gluDisk(quad, 0., 2., 20., 1.);  
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0., 30., 10.);
		glRotatef(90., 1., 0., 0.); 
	    glTranslatef(0., 0., 20.);
		gluDisk(quad, 0., 2., 20., 1.);   
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0., 30., 10.);
		glRotatef(90., 1., 0., 0.); 
		gluCylinder(quad,    2.,    2.,    20.,    20.,    1.); 
	glPopMatrix();	
	
	glPushMatrix(); // marteau
		glBindTexture(GL_TEXTURE_2D, tex[1]);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matOr);
		
		glRotatef(180., 1., 0., 0.); 
		gluDisk(quad, 0., 10., 20., 1.);  
	glPopMatrix();

	glPushMatrix();
	    glTranslatef(0., 0., 20.);
		gluDisk(quad, 0., 10., 20., 1.);   
	glPopMatrix();

	glPushMatrix();
		gluCylinder(quad,    10.,    10.,    20.,    20.,    1.); 
	glPopMatrix();	
	glPopMatrix();
	
	
}

void draw_support() {
	glPushMatrix();
	glTranslatef(-25., 620., 300.);
	glPushMatrix();// support
		glBindTexture(GL_TEXTURE_2D, tex[1]);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matOr);
		
		glRotatef(180., 1., 0., 0.); 
		gluDisk(quad, 0., 12., 20., 1.);  
	glPopMatrix();

	glPushMatrix();
	    glTranslatef(0., 0., 2.);
		gluDisk(quad, 0., 12., 20., 1.);   
	glPopMatrix();

	glPushMatrix();
		gluCylinder(quad,    12.,    12.,    2.,    20.,    1.); 
	glPopMatrix();	
	glPopMatrix();	
	
}


void anim_bras_pw(int sens) {
	if ((sens == -1 && langledubrasdephoenixwright > 0)
		|| (sens == 1 && langledubrasdephoenixwright < 90)) {
		for (int i = 0;  i < 90; i += 5) {
			langledubrasdephoenixwright += 5 * sens;
			display();
		}
	}
	
}
void desk_slaming_pw() {
    for (int i = 0;  i < 90; i += 5) {
        deskslaming += 5;
        display();
    }
	for (int i = 0;  i < 90; i += 5) {
        deskslaming -= 5;
        display();
    }
}
void public_noding() {
    for (int i = 0;  i < 90; i += 5) {
        noding += 5;
        display();
    }
	for (int i = 0;  i < 180; i += 5) {
        noding -= 5;
        display();
    }
	for (int i = 0;  i < 90; i += 5) {
        noding += 5;
        display();
    }

    
}
void anim_marteau() {
	for (int i = 0;  i < 90; i += 5) {
        mouvementmarteau += 1;
        display();
    }
	for (int i = 0;  i < 90; i += 5) {
        mouvementmarteau -= 1;
        display();
    }
}



void movecamera(GLfloat wtbx, GLfloat wtby, GLfloat wtbz, GLfloat wtlx, GLfloat wtly, GLfloat wtlz) {
    GLfloat locwiax = (wtbx - whereiamx) / 100.;
    GLfloat locwiay = (wtby - whereiamy) / 100.;
    GLfloat locwiaz = (wtbz - whereiamz) / 100.;
    GLfloat locwilx = (wtlx - whereilookx) / 100.;
    GLfloat locwily = (wtly - whereilooky) / 100.;
    GLfloat locwilz = (wtlz - whereilookz) / 100.;
    for (int i = 0; i < 100; i ++) {
        whereiamx += locwiax;
        whereiamy += locwiay;
        whereiamz += locwiaz;
        whereilookx += locwilx;
        whereilooky += locwily;
        whereilookz += locwilz;
        display();
    }
}

void lookfromjudge() {
    movecamera(0.000000, 720.000000, 400.000000, 0.000000, 110.000000, 180.000000);
}

void lookphoenix() {
    movecamera(-40.000000, 310.00, 160.00, 170.000000, 90.00, 220.000000);
}

void lookpayne() {
    movecamera(40.000000, 310.00, 160.00, -170.000000, 90.00, 220.000000);
}

void look_mia_from_phoenix() {
    movecamera(200.000000, 100.00, 170.00, 230.000000, 420.00, 170.000000);
}

void lookpublic() {
    movecamera(-0.000000, -760.000000, 690.000000, 0.000000, 100.000000, 180.000000);
}

void lookjudge() {
	movecamera(0.000000, 480.0, 320.000000, 0.000000, 1010.0, 350.000000);
}

void lookwitness() {
	movecamera(0.000000, -30.000000, 180.000000, 0.000000, -180.000000, 180.000000);
}

void quit_all() {
	GL_Quit();
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(fenetre);
	SDL_Quit();
} 
 
 

void GL_Quit() {
	gluDeleteQuadric(quad);
}

void *run() {
		
	struct evidence evidences;
	load_evidences(&evidences);

	FILE *fic = fopen(SCRIPT_PATH, "r");
	char buf[512];
	
	while (fgets(buf, 512, fic)) {
		remove_newline(buf);
		char *tmp = strdup(buf);
		if (buf[0] == '*') {
			extract_talking(tmp);
			printf("%s", talking);
			change_point_of_view();
			getchar();
		} else if(strstr(buf, "[QCM]") != NULL) {
			char* token = strtok(tmp, "->");
			token = strtok(NULL, "->");
			remove_newline(token);
			do_qcm(atoi(token));
		} else if(strstr(buf, "++") != NULL) {	
			
		} else if (strstr(buf, "[PUBLIC_TALK]") != NULL) {
			sdlevent.type = SDL_KEYDOWN;
			sdlevent.key.keysym.sym = SDLK_v;
			SDL_PushEvent(&sdlevent);
		} else if (strstr(buf, "[JUDGE_HAMMER]") != NULL) {
			talking = "Judge";
			change_point_of_view();
			strtok(tmp, "->");
			sdlevent.type = SDL_KEYDOWN;
			sdlevent.key.keysym.sym = SDLK_h;
			int n = atoi(strtok(NULL, "->"));
			for(int i = 0; i < n; i++) {
				SDL_PushEvent(&sdlevent);
			}
		} else if (strstr(buf, "[START_MUSIC_TRIAL]") != NULL) {
			sdlevent.key.keysym.sym = SDLK_l;
			SDL_PushEvent(&sdlevent);
		} else if (strstr(buf, "[STOP_MUSIC]") != NULL) {
			sdlevent.type = SDL_KEYDOWN;
			sdlevent.key.keysym.sym = SDLK_COLON;
			SDL_PushEvent(&sdlevent);
		} else if (strstr(buf, "[WITNESS]") != NULL) {
			strtok(tmp, "->");
			witness = atoi(strtok(NULL, "->"));
			sdlevent.type = SDL_KEYDOWN;
			sdlevent.key.keysym.sym = SDLK_COLON;
			SDL_PushEvent(&sdlevent);
			sdlevent.key.keysym.sym = SDLK_y;
			SDL_PushEvent(&sdlevent);
		} else if (strstr(buf, "[EVIDENCE]") != NULL) {
			strtok(tmp, "->");
			int evidence_nb = atoi(strtok(NULL, "->"));
			evidences.evidence_active[evidence_nb] = !evidences.evidence_active[evidence_nb];
		} else if (strstr(buf, "[TESTIMONY]") != NULL) {
			char* token = strtok(tmp, "->");
			token = strtok(NULL, "->");
			remove_newline(token);
			do_testimony(atoi(token));
		} else if (strstr(buf, "[CROSS_EXAM]") != NULL) {
			char* token = strtok(tmp, "->");
			token = strtok(NULL, "->");
			remove_newline(token);
			do_cross_exam(atoi(token), &evidences);
		} else if (strstr(buf, "[OBJECTION_MUSIC]") != NULL) {
			sdlevent.type = SDL_KEYDOWN;
			sdlevent.key.keysym.sym = SDLK_EXCLAIM;
			SDL_PushEvent(&sdlevent);
		} else if (strstr(buf, "[OBJECTION_STANCE]") != NULL) {
			sdlevent.type = SDL_KEYDOWN;
			sdlevent.key.keysym.sym = SDLK_w;
			SDL_PushEvent(&sdlevent);
		} else if (strstr(buf, "[END_OBJECTION_STANCE]") != NULL) {
			sdlevent.type = SDL_KEYDOWN;
			sdlevent.key.keysym.sym = SDLK_x;
			SDL_PushEvent(&sdlevent);
		} else if (strstr(buf, "[DESK_SLAM]") != NULL) {
			sdlevent.type = SDL_KEYDOWN;
			sdlevent.key.keysym.sym = SDLK_c;
			SDL_PushEvent(&sdlevent);
		} else if (strstr(buf, "[OBJECTION]") != NULL) {
			strtok(tmp, "->");
			objecting = strtok(NULL, "->");
			do_objection();
		} else if (strstr(buf, "[ALLEGRO]") != NULL) {
			allegro = 1;
		} else if (strstr(buf, "[CORNERED]") != NULL) {
			sdlevent.type = SDL_KEYDOWN;
			sdlevent.key.keysym.sym = SDLK_ASTERISK;
			SDL_PushEvent(&sdlevent);
		} else if (strstr(buf, "[PAUSE_MUSIC]") != NULL) {
			sdlevent.type = SDL_KEYDOWN;
			sdlevent.key.keysym.sym = SDLK_COMMA;
			SDL_PushEvent(&sdlevent);
		} else {
			printf("%s", buf);
			getchar();
		}
		memset(buf, 512, sizeof(char));
	}
	fclose(fic);
	
	return NULL;
}

void load_evidences(struct evidence *evidences) {
	FILE *fic = fopen(EVIDENCES_FILE, "r");
	char buf[512];
	
	int i = 0;
	while (fgets(buf, 512, fic)) {
		remove_newline(buf);
		char *tmp = strdup(buf);
		evidences->evidence_name[i] = strtok(tmp, ">");
		evidences->evidence_type[i] = strtok(NULL, ">");
		evidences->evidence_other[i] = strtok(NULL, ">");
		evidences->evidence_description[i] = strtok(NULL, ">");
		char *token = strtok(NULL, ">");
		evidences->evidence_active[i] = atoi(token);
		memset(buf, 512, sizeof(char));
		i++;
	}
	evidences->nb_evidence = i;
	fclose(fic);
}


void extract_talking(char *buf) {
	talking = buf + 1;
}

void change_point_of_view() {
	sdlevent.type = SDL_KEYDOWN;
	if(strcmp(talking, "Judge") == 0) {
		sdlevent.key.keysym.sym = SDLK_u;
	} else if(strcmp(talking, "Payne") == 0) {
		sdlevent.key.keysym.sym = SDLK_i;
	} else if (strcmp(talking, "Phoenix") == 0) {
		sdlevent.key.keysym.sym = SDLK_p;
	} else if (strcmp(talking, "Mia") == 0) {
		sdlevent.key.keysym.sym = SDLK_m;
	} else if (strcmp(talking, "Butz") == 0 || strcmp(talking, "Sahwit") == 0){
		sdlevent.key.keysym.sym = SDLK_y;
	}
	SDL_PushEvent(&sdlevent);
}

void do_qcm(int qcm_nb) {
	
	struct qcm_struct qcm;
	get_info_qcm(&qcm, qcm_nb);

	int choice;
	char choice2[10];
	int good_answer = 0;
	do {
		choice = do_question_menu(qcm.talking, qcm.question, qcm.proposition_case, qcm.nb_proposition);
		do_answer(qcm_nb, choice - 1, qcm.case_files);
		printf("\n");
		snprintf(choice2, strlen(qcm.answer[0]) + 1, "CASE_%d", choice);
		printf("\n");
		int i = 0;
		while(qcm.answer[i] != NULL) {
			if(strcmp(choice2, qcm.answer[i]) == 0) {
				good_answer = 1;
				break;
			}
			i++;
		}
	} while(good_answer == 0);
}

void get_info_qcm(struct qcm_struct *qcm, int qcm_nb) {
	char qcm_file[30];
	int nb_digits = floor(log10(abs(qcm_nb))) + 1;
	snprintf(qcm_file, strlen(QCM_PATH) + nb_digits + strlen("/qcm/") + nb_digits + strlen(".txt") + 1, "%s%d/qcm%d.txt", QCM_PATH, qcm_nb, qcm_nb);
	
	char last_string[50];
	FILE *fic = fopen(qcm_file, "r");

	char buf[512];
	int n = 0;
	while (fgets(buf, 512, fic)) {
		if(strstr(buf, "[TALKING]") != NULL) {
			snprintf(last_string, sizeof("[TALKING]"), "%s", buf);
		} else if(strstr(buf, "[QUESTION]") != NULL) {
			snprintf(last_string, sizeof("[QUESTION]"), "%s", buf);
		} else if(strstr(buf, "[ANSWER]") != NULL) {
			snprintf(last_string, sizeof("[ANSWER]"), "%s", buf);
		} else if(strstr(buf, "[PROPOSITION]") != NULL) {
			snprintf(last_string, sizeof("[PROPOSITION]"), "%s", buf);
		} else if(strstr(buf, "__") != NULL) {
			snprintf(last_string, 1, "0");
		}
		else {
			char *tmp = strdup(buf);
			remove_newline(tmp);
			if(strstr(last_string, "[TALKING]") != NULL) {
				qcm->talking = tmp;
				snprintf(last_string, 1, "0");
			} else if(strstr(last_string, "[QUESTION]") != NULL) {
				qcm->question = tmp;
				snprintf(last_string, 1, "0");
			} else if(strstr(last_string, "[ANSWER]") != NULL) {
				if(strstr(tmp, "&") != NULL) {
					int i = 0;
					char *token = strtok(tmp, "&");
					qcm->answer[i] = token;
					i++;
					while(token != NULL) {
						token = strtok(NULL, "&");
						qcm->answer[i] = token;
						i++;
					}
				} else {
					qcm->answer[0] = tmp;
				}
				snprintf(last_string, 1, "0");
			} else if(strstr(last_string, "[PROPOSITION]") != NULL) {
				qcm->proposition_case[n].key = strtok(tmp, "->");
				qcm->proposition_case[n].value = strtok(NULL, "->");
				char *file = strtok(NULL, "->");
				remove_newline(file);
				qcm->case_files[n] = file;
				n++;
			}
		}		
		memset(buf, 512, sizeof(char));
	}
	qcm->nb_proposition = n;
	fclose(fic);
	
}

int do_question_menu(char *talking, char *question, struct key_value *proposition_case, int nb_proposition) {
	printf("%s", talking + 1);
	getchar();
	if(strstr(question, "_") != NULL) {
		char *tmp = strdup(question);
		printf("%s", strtok(tmp, "_"));
		getchar();
		printf("%s\n", strtok(NULL, "_"));
	} else {
		printf("%s\n", question);
	}
	getchar();
	printf("=========================\n");
	for(int i = 0; i < nb_proposition; i++) {
		printf("%d) %s\n", i + 1, proposition_case[i].value);
	}
	printf("=========================\n");
	int choice;
	do {
		printf("Make your choice : ");
		fscanf(stdin, "%d", &choice);
	} while(choice < 1 || choice > nb_proposition);
	
	
	return choice;
}

void do_answer(int qcm_nb, int choice, char **case_files) {
	printf("\n");
	char case_path[40];
	int nb_digits = floor(log10(abs(qcm_nb))) + 1;
	snprintf(case_path, strlen(QCM_PATH) + nb_digits + strlen(case_files[choice]) + 2, "%s%d/%s", QCM_PATH, qcm_nb, case_files[choice]);
	FILE *fic = fopen(case_path, "r");

	char buf[512];
	while (fgets(buf, 512, fic)) {
		remove_newline(buf);
		char *tmp = strdup(buf);
		if(buf[0] == '*') {
			extract_talking(buf);
			change_point_of_view();
			printf("%s", talking);
		} else if(strstr(buf, "[CASE") != NULL){
			
		} else if(strstr(buf, "[DESK_SLAM]") != NULL){
			strtok(tmp, "->");
			slamming = strtok(NULL, "->");
			do_slam();
		} else if(strstr(buf, "[OBJECTION_STANCE]") != NULL){
			sdlevent.type = SDL_KEYDOWN;
			sdlevent.key.keysym.sym = SDLK_w;
			SDL_PushEvent(&sdlevent);
		} else if(strstr(buf, "[END_OBJECTION_STANCE]") != NULL){
			sdlevent.type = SDL_KEYDOWN;
			sdlevent.key.keysym.sym = SDLK_x;
			SDL_PushEvent(&sdlevent);
		} else if(strstr(buf, "[START_MUSIC_TRIAL]") != NULL) {
			sdlevent.type = SDL_KEYDOWN;
			sdlevent.key.keysym.sym = SDLK_l;
			SDL_PushEvent(&sdlevent);
		} else if(strstr(buf, "[PUBLIC_TALK]") != NULL) {
			sdlevent.type = SDL_KEYDOWN;
			sdlevent.key.keysym.sym = SDLK_v;
			SDL_PushEvent(&sdlevent);
		} else if(strstr(buf, "[OBJECTION]") != NULL) {
			strtok(tmp, "->");
			objecting = strtok(NULL, "->");
			do_objection();
		} else if (strstr(buf, "[JUDGE_HAMMER]") != NULL) {
			talking = "Judge";
			change_point_of_view();
			strtok(tmp, "->");
			sdlevent.type = SDL_KEYDOWN;
			sdlevent.key.keysym.sym = SDLK_h;
			int n = atoi(strtok(NULL, "->"));
			for(int i = 0; i < n; i++) {
				SDL_PushEvent(&sdlevent);
			}
		} else if(strstr(buf, "++") != NULL) {
		
		} else {
			printf("%s", buf);
		}
		getchar();
	}
	fclose(fic);
}

void do_slam() {
	sdlevent.type = SDL_KEYDOWN;
	if(strcmp(slamming, "Phoenix Wright") == 0) {
		sdlevent.key.keysym.sym = SDLK_c;
	}
	SDL_PushEvent(&sdlevent);
}

void do_objection() {
	sdlevent.type = SDL_KEYDOWN;
	if(strcmp(objecting, "Payne") == 0) {
		sdlevent.key.keysym.sym = SDLK_g;
	} else if (strcmp(objecting, "Phoenix") == 0) {
		sdlevent.key.keysym.sym = SDLK_n;
	}
	SDL_PushEvent(&sdlevent);
}

void do_testimony(int testimony_nb) {
	
	printf("\nWitness Testimony\n");
	char testimony_path[70];
	int nb_digits = floor(log10(abs(testimony_nb))) + 1;
	snprintf(testimony_path, strlen(TESTIMONY_PATH) + nb_digits + strlen(".txt") + 1, "%s%d.txt", TESTIMONY_PATH, testimony_nb);
	
	FILE *fic = fopen(testimony_path, "r");

	char buf[512];
	sdlevent.type = SDL_KEYDOWN;
	sdlevent.key.keysym.sym = SDLK_DOLLAR;
	SDL_PushEvent(&sdlevent);
	while (fgets(buf, 512, fic)) {
		remove_newline(buf);
		if(buf[0] == '*') {
			extract_talking(buf);
			change_point_of_view();
			printf("%s", talking);
		} else {
			printf("%s", buf);
		}
		getchar();
		if(Mix_PlayingMusic() == 0) {
			sdlevent.type = SDL_KEYDOWN;
			sdlevent.key.keysym.sym = SDLK_SEMICOLON;
			SDL_PushEvent(&sdlevent);
		}
	}
	fclose(fic);
	
}

void do_cross_exam(int cross_exam_nb, struct evidence *evidences) {
	printf("\n");
	
	struct cross_exam_struct cross_exam_infos;
	get_cross_exam_info(&cross_exam_infos, cross_exam_nb);
	
	good_objection = 0;
	cross_exam_infos.current_line = 0;
	char *line;
	char *token;
	int choice;
	printf("CROSS EXAMINATION\n-- %s --\n", cross_exam_infos.name);
	sdlevent.type = SDL_KEYDOWN;
	sdlevent.key.keysym.sym = SDLK_DOLLAR;
	SDL_PushEvent(&sdlevent);
	getchar();
	if(allegro) {
		sdlevent.key.keysym.sym = SDLK_t;
	} else {
		sdlevent.key.keysym.sym = SDLK_SEMICOLON;	
	}
	SDL_PushEvent(&sdlevent);

	do {
		line = cross_exam_infos.lines[cross_exam_infos.current_line];
		token = strdup(line);
		token = strtok(token, "_");
		talking = token + 1;
		getchar();
		printf("%s", talking);
		change_point_of_view();
		getchar();

		while(token != NULL) {
			token = strtok(NULL, "_");
			if (token != NULL)  {
				printf("%s", token);
			}
			getchar();
		}
		
		choice = do_cross_exam_menu(&cross_exam_infos);
		
		switch(cross_exam_infos.current_line) {
			case 0:
				switch(choice) {
					case 1:
						cross_exam_infos.current_line++;
						printf("\n");
					break;
					case 2:
						do_hold_it(cross_exam_infos.current_line + 1, cross_exam_nb);
						cross_exam_infos.current_line++;
						printf("\n");
					break;
					case 3:
						printf("\n");
						choice = do_present_menu(evidences);
						if(choice != 0) {
							good_objection = objection_try(choice - 1 , &cross_exam_infos);
							objecting = "Phoenix";
							do_objection();
						}
						printf("\n");
					break;
				}
			break;
			
			default:
				switch(choice) {
					case 1:
						cross_exam_infos.current_line--;
						printf("\n");
					break;
					case 2:
						cross_exam_infos.current_line++;
						if(cross_exam_infos.current_line + 1 > cross_exam_infos.nb_lines) {
							do_extras(&cross_exam_infos);
						}
						printf("\n");
					break;
					case 3:
						do_hold_it(cross_exam_infos.current_line + 1, cross_exam_nb);
						cross_exam_infos.current_line++;
						if(cross_exam_infos.current_line + 1 > cross_exam_infos.nb_lines) {
							do_extras(&cross_exam_infos);
						}
						printf("\n");
					break;
					case 4:
						printf("\n");
						choice = do_present_menu(evidences);
						if(choice != 0) {
							good_objection = objection_try(choice - 1, &cross_exam_infos);
							objecting = "Phoenix";
							do_objection();
						}
						printf("\n");
					break;
				}
			break;
		}
		
	} while(good_objection == 0);	
}

void get_cross_exam_info(struct cross_exam_struct *cross_exam_infos, int cross_exam_nb) {
	char cross_exam_path[70];
	int nb_digits = floor(log10(abs(cross_exam_nb))) + 1;
	snprintf(cross_exam_path, strlen(CROSS_EXAM_PATH) + nb_digits + strlen("/cross_exam/") + nb_digits + strlen(".txt") + 1, "%s%d/cross_exam%d.txt", CROSS_EXAM_PATH, cross_exam_nb, cross_exam_nb);
	
	FILE *fic = fopen(cross_exam_path, "r");

	char buf[512];
	int i = 0;
	while (fgets(buf, 512, fic)) {
		remove_newline(buf);
		char *tmp = strdup(buf);
		if (strstr(buf, "[NAME]") != NULL) {
			strtok(tmp, "->");
			cross_exam_infos->name = strtok(NULL, "->");
		} else if (strstr(buf, "[ANSWER]") != NULL) {
			if(strstr(tmp, "&") != NULL) {
					strtok(tmp, ">");
					int i = 0;
					char *token = strtok(NULL, "&");
					cross_exam_infos->answer_line[i] = token;
					i++;
					while(token != NULL) {
						token = strtok(NULL, "&");
						cross_exam_infos->answer_line[i] = token;
						i++;
					}
				} else {
					strtok(tmp, ">");
					cross_exam_infos->answer_line[0] = strtok(NULL, ">");
					cross_exam_infos->answer_line[1] = NULL;
				}
		} else if (strstr(buf, "[EVIDENCE]") != NULL) {
			strtok(tmp, "->");
			cross_exam_infos->evidence_to_show = atoi(strtok(NULL, "->"));
		} else if (strstr(buf, "[LINE") != NULL) {
			strtok(tmp, ">");
			cross_exam_infos->lines[i] = strtok(NULL, ">");
			i++;
		} else if (strstr(buf, "++") != NULL) {
			cross_exam_infos->nb_lines = i;
			i = 0;
		} else if (strstr(buf, "[EXTRA") != NULL) {
			strtok(tmp, ">");
			cross_exam_infos->extras[i] = strtok(NULL, ">");
			i++;
		} else if (strstr(buf, "__") != NULL) {
			cross_exam_infos->nb_extras = i;
			i = 0;
		}
	}
	fclose(fic);
}

int do_cross_exam_menu(struct cross_exam_struct *cross_exam_infos) {
	int nb_proposition;
	printf("=========================\n");
	switch(cross_exam_infos->current_line)  {
		case 0:
				nb_proposition = 3;
				printf("1) %s\n", "Next");
				printf("2) %s\n", "Press");
				printf("3) %s\n", "Present");
		break;
		default:
			nb_proposition = 4;
			printf("1) %s\n", "Previous");
			printf("2) %s\n", "Next");
			printf("3) %s\n", "Press");
			printf("4) %s\n", "Present");
		break;
	}
	
	printf("=========================\n");
	int choice;
	do {
		printf("Make your choice : ");
		fscanf(stdin, "%d", &choice);
	} while(choice < 1 || choice > nb_proposition);
	
	printf("\n");
	return choice;
}

void do_hold_it(int hold_it_nb, int cross_exam_nb) {
	sdlevent.type = SDL_KEYDOWN;
	sdlevent.key.keysym.sym = SDLK_r;
	SDL_PushEvent(&sdlevent);
	char hold_it_path[70];
	int nb_digits_1 = floor(log10(abs(hold_it_nb))) + 1;
	int nb_digits_2 = floor(log10(abs(cross_exam_nb))) + 1;
	snprintf(hold_it_path, strlen(CROSS_EXAM_PATH) + nb_digits_1 + strlen("/holdit/") + nb_digits_2 + strlen(".txt") + 1, "%s%d/holdit%d.txt", CROSS_EXAM_PATH, cross_exam_nb, hold_it_nb);
	FILE *fic = fopen(hold_it_path, "r");

	char buf[512];
	char *tmp;
	while (fgets(buf, 512, fic)) {
		remove_newline(buf);
		tmp = strdup(buf);
		if(tmp[0] == '*') {
			talking = tmp + 1;
			change_point_of_view();
			printf("%s", talking);
		} else if (strstr(tmp, "[HOLD_IT]") != NULL){
			printf("\n");
			printf("HOLD IT!");
		} 
		else if (strstr(tmp, "[DESK_SLAM]") != NULL){
			strtok(tmp, "->");
			slamming = strtok(NULL, "->");
			do_slam();
		} else if (strstr(tmp, "[OBJECTION]") != NULL) {
			strtok(tmp, "->");
			objecting = strtok(NULL, "->");
			do_objection();
		} else {
			printf("%s", tmp);
		}
		
		getchar();
	}
	fclose(fic);
}

void do_extras(struct cross_exam_struct *cross_exam_infos) {
	char *extra;
	char *token;
	for (int i = 0; i < cross_exam_infos->nb_extras; i++) {
		extra = cross_exam_infos->extras[i];
		token = strdup(extra);
		token = strtok(token, "_");
		talking = token + 1;
		getchar();
		printf("%s", talking);
		getchar();
		while(token != NULL) {
			token = strtok(NULL, "_");
			if (token != NULL)  {
				printf("%s", token);
			}
			getchar();
		}
	}
	cross_exam_infos->current_line = 0;
}

int do_present_menu(struct evidence *evidences) {
	printf("=========================\n");
	printf("0) Cancel\n");
	for(int i = 0; i < evidences->nb_evidence; i++) {
		printf("%d) %s\n", i + 1, evidences->evidence_name[i]);
	}
	printf("=========================\n");
	int choice;
	do {
		printf("Select evidence : ");
		fscanf(stdin, "%d", &choice);
	} while(choice < 1 || choice > evidences->nb_evidence);
	
	
	return choice;
}

int objection_try(int choice, struct cross_exam_struct *cross_exam_infos) {
	char try_answer[8];
	int nb_digits = floor(log10(abs(cross_exam_infos->current_line))) + 1;
	snprintf(try_answer, strlen("LINE_") + nb_digits + 1, "LINE_%d", cross_exam_infos->current_line + 1);
	int i = 0;
	while(cross_exam_infos->answer_line[i] != NULL) {
		printf("%s\t%s\n", try_answer, cross_exam_infos->answer_line[i]);
		if(strcmp(try_answer, cross_exam_infos->answer_line[i]) == 0 && choice == cross_exam_infos->evidence_to_show) {
			return 1;
		}
		i++;
	}
	return 0;
}

void remove_newline(char *line) {
	line[strcspn(line, "\r\n")] = 0;
}
