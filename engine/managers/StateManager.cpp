#include "StateManager.h"

#include <iostream>
#include <string>

#include "WindowManager.h"

StateManager::StateManager()
    : m_nextId(0)
{
}

StateManager::~StateManager()
{
    for(auto& state : m_states)
    {
        delete state.second;    
    }
}

bool StateManager::setState(const int& id)
{
    if(m_states.find(id) != m_states.end())
    {
        WindowManager::instance().setState(m_states[id]);
        return true;
    }
    return false;
}

bool StateManager::addState(int& id, State* state)
{
    if(m_states.find(id) != m_states.end())
    {
        return false;
    }
    
    m_states.insert(std::make_pair(0, state));
    return true;
}

bool StateManager::removeState(const int& id)
{
    auto state = m_states.find(id);
    if(state != m_states.end() && state->second != WindowManager::instance().getState())
    {
        delete state->second;
        m_states.erase(state);
        return true;
    }
    return false;
}

