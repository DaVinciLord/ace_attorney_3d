#include "draw_functions.h"

// DRAW FUNCTIONS
void display() {
	
	const GLfloat matSpeculaire[4] = {1., 1., 1., 1.};
	const GLfloat matShininess = 50.;
	const GLfloat matBeige[4] = {197./255.,167./255., 147./255., 1.};
	const GLfloat matBrun[4] = {124./255., 64./255., 0., 1.};
	const GLfloat matBrunClair[4] = {240./255., 140./255., 70./255., 1.};
	const GLfloat matArgent[4] = {206./255., 206./255., 206./255., 1.};
	const GLfloat matOr[4] = {1., 215./255., 0., 1.};
	const GLfloat matBeigeClair[4] = {245./255., 245./255., 220/255., 1.};
	
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
	creer_arcade(matBrun, matBeigeClair);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matOr);
	glBindTexture(GL_TEXTURE_2D, tex[4]);  
	creer_pave_2(-125.,725.,350.,50.,50.,300.);  //montants derriere le juge
	creer_pave_2(125.,725.,350.,50.,50.,300.);
	creer_pave_2(0., 718., 475., 200., 20., 50.); //revetement derriere le juge 

	creer_witness_stand(matBrun);

    creer_marteau(matOr);
	draw_support(matOr);


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
  
void creer_witness_stand(const GLfloat matBrun[]) {
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

void creer_arcade(const GLfloat matBrun[], const GLfloat matBeigeClair[]) {
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

void creer_marteau(const GLfloat matOr[]) {
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

void draw_support(const GLfloat matOr[]) {
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
