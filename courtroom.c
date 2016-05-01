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
	sdlevent.type = SDL_KEYDOWN;
	
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


	
}


void init_GL(void) {
	glClearColor(1., 1., 1., 0.);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat intensite[] = {0.2,0.2,0.2, 1.};

	glLightfv(GL_LIGHT0, GL_AMBIENT, intensite);

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
		continuer = keyboard(&event);
		display();
	}
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
