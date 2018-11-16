#pragma once

#ifdef _WIN32
#pragma comment(lib, "irrKlang.lib")
#endif
#include "irrKlang/irrKlang.h"

#include <map>
#include <memory>
#include <string>

struct irrKlangDeleter
{
    void operator()(irrklang::ISoundEngine* ptr){
        ptr->drop();
    }
};

//TODO: This class is basic and will need further development
namespace managers
{
class SoundManager
{
public:
    SoundManager()
        : soundEngine_(irrklang::createIrrKlangDevice())
    {
    }

    //TODO: Load sounds into a common file...
    //TODO: This doesn't really load the file into memory yet...
    void loadSound(const std::string& name, const std::string& path)
    {
        if(soundMap_.find(name) == soundMap_.end())
        {
            soundMap_[name] = path;
        }
    }
    void playSound(const std::string& name)
    {
        if(soundMap_.find(name) != soundMap_.end())
        {
            stopSound(name);
            activeSoundMap_[name] = soundEngine_->play2D(soundMap_[name].c_str(), false, false, true);
        }
    }

    void stopSound(const std::string& name)
    {
        if(activeSoundMap_.find(name) != activeSoundMap_.end())
        {
            activeSoundMap_[name]->stop();
            activeSoundMap_[name]->drop();
            activeSoundMap_.erase(name);
        }
    }

private:
    std::unique_ptr<irrklang::ISoundEngine, irrKlangDeleter> soundEngine_;
    std::map<std::string, std::string> soundMap_;
    std::map<std::string, irrklang::ISound*> activeSoundMap_;
};
}
