#include <iostream>
#include <memory>
#include <string>

#include "engine/managers/StateManager.h"
#include "engine/managers/WindowManager.h"

int main()
{
    int stateId = 0;
    if(!StateManager::instance().addState(stateId, new State()))
        std::cerr << "Failed to add state\n";    

    if(!StateManager::instance().setState(stateId))
        std::cerr << "Failed to set state\n";

    WindowManager::instance().setTitle("New Title");

    WindowManager::instance().run();
    
	return 0;
}
