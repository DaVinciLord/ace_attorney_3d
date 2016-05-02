#include "camera.h"

void movecamera(GLfloat wtbx, GLfloat wtby, GLfloat wtbz, GLfloat wtlx, GLfloat wtly, GLfloat wtlz) {
	if (whereiamx == wtbx && whereiamy == wtby && whereiamz == wtbz 
	 && whereilookx == wtlx && whereilooky == wtly && whereilookz == wtlz) { 
		 return;
	 }
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
        whereiamx = wtbx;
        whereiamy = wtby;
        whereiamz = wtbz;
        whereilookx = wtlx;
        whereilooky = wtly;
        whereilookz = wtlz;
    
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
