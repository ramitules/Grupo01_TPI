#include <iostream>
#include "include/utils/rlutil.h"
#include "include/menu/MenuPrincipal.h"


int main(){
    MenuPrincipal menu;
    menu.buclePrincipal();
    rlutil::getkey();
    return 0;
}
