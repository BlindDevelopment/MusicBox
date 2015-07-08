#include <portaudio.h>
#include <sndfile.h>
#include <sstream>
#include <string>

using namespace std;

struct SoundData {
    SNDFILE *alarm;
    SF_INFO alarminfo;
    int position;
    bool go;
    PaStream *stream;
};

void PlaySound();
void StopSound();
void InitPortAudio();
