#pragma once

#ifdef _WIN32
#pragma comment(lib, "irrKlang.lib")
#endif
#include "irrKlang/irrKlang.h"

#include <map>
#include <memory>
#include <string>

namespace ps
{

//TODO: This class is basic and will need further development
namespace managers
{
class SoundManager
{
    struct irrKlangDeleter
    {
        void operator()(irrklang::ISoundEngine* ptr){
            ptr->drop();
        }
    };
public:
    static SoundManager& Get();

    //TODO: Load sounds into a common file...
    //TODO: This doesn't really load the file into memory yet...
    void loadSound(const std::string& name, const std::string& path);
    void playSound(const std::string& name);
    void stopSound(const std::string& name);

private:
    SoundManager();
    SoundManager(SoundManager const&) = delete;
    void operator=(SoundManager const&) = delete;

    std::unique_ptr<irrklang::ISoundEngine, irrKlangDeleter> soundEngine_;
    std::map<std::string, std::string> soundMap_;
    std::map<std::string, irrklang::ISound*> activeSoundMap_;
};
}
}
