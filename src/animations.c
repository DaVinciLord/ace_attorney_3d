#include "animations.h"

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
