# TRV
# A multi-agent, genetic pathfinding algorithm


#Dependancies: gcc, c++11, libxml2, libxml++-2.6, glibmm-2.4


***********************************************************************************
********************************   HOW TO USE   ***********************************
***********************************************************************************
- Write an XML file describing your game rules in compliance with the DTD  
- Write a txt file describing the map (see an example in map.txt):  
 1. First line is two unsigned integers: map width and map height (origin is bottom left corner: 0,0)  
 2. Following lines each describe a tile that you want to be different from the default settings:  
    [x(unsigned int)] [y(unsigned int)] [terrain name(string without spaces)] [contrainte 1(string)]:[value 1(float)];[contrainte n]:[value n] [is obstacle(bool)]  
 3.Note the space between the fields. It means that if you do not want to specify any contrainte, but want to set a tile to be impassable, you must put THREE spaces after the terrain name and before the is_obstacle boolean: two for separations and one for empty field.  
- Include src/controller.h  
- Create a controller object and get its pointer: Controller* controller = Controller::create();  
- Initiate the xml rules with: controller->initiateRules("../regle.xml");  
- Initiate the map with: controller->initiateMap("../map.txt");  
- Create an instance of the pathfinding algorithm with: controller->create_algogen();  
- From now on all methods of Controller are available to you. Just ensure that you don't ask a path for an agent that you didn't create.  
- The most useful methods will be  
 1. controller->creer_agent(x,y,name,id)  
 2. controller->supprimer_agent(id)  
 3. controller->proch_case(id) ==> returns a pair of ints (x,y) that is the proposed next tile  
 4. controller->deplacement_agent(id,x,y) ==>actually moves the unit to the (x,y) tile  
           example:  controller->deplacement_agent(1,controller->proch_case(1).first,controller->proch_case(1).second);  
 5. tic(); starts the calculations.  
 6. toc(); interrupts the calculations. Note that coherent behavior is only guaranteed if you toc() before asking a proch_case() or a deplacement_agent()
 7. Controller::delete_controller();  

Authors: Théo Voillemin, Nicolas Roux, Corentin Talarmain
