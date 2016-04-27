#include <iostream>
#include "controller.h"

using namespace std;

int main(int argc, char **argv) {
    cout << "TRV" << endl;
    Controller* controller = Controller::create();
    try{
      controller->initiateRules("../regle.xml");
      controller->initiateMap("../map.txt");
      controller->creer_agent(0,0,"Cavalier",0);
      controller->test();
      //controller->test();
     // controller->test();
//      cout << "Déplacement cavalerie Dijkstra : 4,1 jusqu'à : 12,8 " << endl;
//      controller->demande_chemin(0,99,88);
     cout << "Déplacement cavalerie A* : 4,1 jusqu'à : 5,2 " << endl;
     controller->demande_chemin_A_star(0,0,3);
	 controller->demande_chemin_algogen(0,50,50);
    } catch(str_exception& e){
    
      cout << "str_exception" << e.what() << endl;
    }
    catch(exception& e1)
    {
      cout << e1.what() << endl;
    }
    
   
    
    return 0;
}
