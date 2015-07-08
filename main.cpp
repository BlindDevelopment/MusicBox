#include <iostream>

using namespace std;

int main()
{
    cout<<"Started!\n";

    data = (SoundData *)malloc(sizeof(SoundData));
    Pa_Initialize();
    InitPortAudio();

    cout << "Hello world!" << endl;
    return 0;
}



void PlaySound()
{
    if (data->go == false)
    {
        data->go = true;
        //alarmtimer->Start(1000,true);
        sf_seek(data->alarm,0,SEEK_SET);
        Pa_StartStream(data->stream);
    }
}

void StopSound()
{
    if (data->go)
    {
        data->go = false;
        alarmtimer->Stop();
        Pa_StopStream(data->stream);
    }
}

int CallbackStream(const void *input, void *output, unsigned long frames_per_buffer,const PaStreamCallbackTimeInfo *time_info,PaStreamCallbackFlags flags, void *usedata)
{
    SoundData* sdata = (SoundData *) usedata;
    short int *cursor = (short int *)output;

        for (int i=0;i<frames_per_buffer;i++)
        {
            if (sf_read_short(sdata->alarm,cursor,1) < 1)
            {
                sf_seek(sdata->alarm,0,SEEK_SET);

            }
            cursor++;
            sdata->position++;
        }

        //cursor = (short int*) output;


        return paContinue;
}

void InitPortAudio()
{
    PaError err;
    PaStreamParameters out_param;
    string filename = dir2+"Alarm.wav";
    data->alarminfo.format = 0;
    data->position = 0;
    data->alarm = sf_open(filename.c_str(),SFM_READ,&(data->alarminfo));

    if (!data->alarm)
    {
        cout<<"Portaudio file load error\n";
        return;
    }

    out_param.device = Pa_GetDefaultOutputDevice();
    out_param.channelCount = data->alarminfo.channels;
    out_param.sampleFormat = paInt16;
    out_param.suggestedLatency = 0.5;
    out_param.hostApiSpecificStreamInfo = NULL;
    err = Pa_OpenStream(&data->stream,NULL,&out_param,data->alarminfo.samplerate,
                        paFramesPerBufferUnspecified
                        ,paNoFlag,CallbackStream,data);

    if (err)
    {
        cout<<"Portaudio stream opening error.\n";
        return;
    }

    Pa_SetStreamFinishedCallback(data->stream,EndStream);
}
