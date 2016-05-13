#include <iostream>
#include "controller.h"

int main(int argc, char **argv) {
    std::cout << "TRV" << std::endl;
    Controller* controller = Controller::create();
    try{
      
      controller->initiateRules("../regle.xml");
      controller->initiateMap("../map.txt");
      std::cout << "init map & règles OK" << std::endl;
      controller->creer_agent(2,95,"Cavalier",0);
      controller->creer_agent(4,4,"Cavalier",1);
      controller->creer_agent(30,30,"Artillerie",2);
      controller->creer_agent(90,6,"Infanterie",3);
      controller->creer_agent(10,15,"Cavalier",4);
      controller->creer_agent(20,20,"Cavalier",5);
      controller->creer_agent(0,24,"Cavalier",6);
      controller->creer_agent(10,35,"Cavalier",7);
      controller->creer_agent(85,30,"Artillerie",8);
      controller->creer_agent(70,40,"Infanterie",9);
      std::cout << "créations ok, 10 agents, 300 itérations" << std::endl;
//       controller->test();
      std::cout << "vachemins popsize mutationRatio popToMutate nbAjouts ratioSupprs ratioModifs ratioElitism cullRatio nbkids singlePoint" << std::endl;
      for(unsigned int i=0;i<5000;++i){
	controller->create_algogen();
// 	controller->deplacement_agent(0, 5, 5);
// 	controller->deplacement_agent(3, 5, 95);
      // controller->test();
  //      std::cout << "Déplacement cavalerie Dijkstra : 4,1 jusqu'à : 12,8 " << std::endl;
  //      controller->demande_chemin(0,99,88);
  //      controller->demande_chemin_A_star(0,450,450);
  //      std::cout << "astar ok" << std::endl;
	controller->demande_chemin_algogen(0,90,90);
	controller->demande_chemin_algogen(1,90,10);
	controller->demande_chemin_algogen(2,30,90);
	controller->demande_chemin_algogen(3,5,95);
	controller->demande_chemin_algogen(4,97,36);
	controller->demande_chemin_algogen(5,98,20);
	controller->demande_chemin_algogen(6,98,98);
	controller->demande_chemin_algogen(7,50,60);
	controller->demande_chemin_algogen(8,5,70);
	controller->demande_chemin_algogen(9,45,2);
	controller->iterate_algogen(300);
// 	std::cout << "fini d'iterate" << std::endl;
	controller->delete_algogen();
      }
    } catch(str_exception& e){
    
      std::cout << "str_exception" << e.what() << std::endl;
    }
    catch(std::exception& e1)
    {
      std::cout << e1.what() << std::endl;
    }
    Controller::delete_controller();
    return 0;
}
