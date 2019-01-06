#include "soundmanager.h"

namespace ps
{
namespace managers
{
SoundManager::SoundManager()
    : soundEngine_(irrklang::createIrrKlangDevice())
{
}

SoundManager& SoundManager::Get()
{
    static SoundManager manager;
    return manager;
}

void SoundManager::loadSound(const std::string& name, const std::string& path)
{
    if(soundMap_.find(name) == soundMap_.end())
    {
        soundMap_[name] = path;
    }
}
void SoundManager::playSound(const std::string& name)
{
    if(soundMap_.find(name) != soundMap_.end())
    {
        stopSound(name);
        activeSoundMap_[name] = soundEngine_->play2D(soundMap_[name].c_str(), false, false, true);
    }
}

void SoundManager::stopSound(const std::string& name)
{
    if(activeSoundMap_.find(name) != activeSoundMap_.end())
    {
        activeSoundMap_[name]->stop();
        activeSoundMap_[name]->drop();
        activeSoundMap_.erase(name);
    }
}
}
}
