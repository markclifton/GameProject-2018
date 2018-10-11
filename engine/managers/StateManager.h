#pragma once

#include <map>
#include <memory>

#include "../states/State.h"

class StateManager
{
public:
    static StateManager& instance()
    {
        static StateManager instance;
        return instance;
    }

    ~StateManager();
    
    bool setState(const int& id);
    bool addState(int& id, State* state);
    bool removeState(const int& id);

private:
    StateManager();
    
    int m_nextId; 
    std::map<int, State*> m_states;
};
