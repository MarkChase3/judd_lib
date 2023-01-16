#define COBJMACROS
#define INITGUID
#include <windows.h>
#include <initguid.h>
#include <mmdeviceapi.h>
#include <audioclient.h>
#include <stdio.h>
#include <string.h>
/* Thanks to GPT-3 for some help here*/
typedef struct {
    IAudioClient* client;
    IAudioRenderClient* render;
} judd_audio_t;
void judd_create_audio(judd_audio_t* audio, unsigned char* data, int data_size) {
    CoInitializeEx(NULL, COINIT_MULTITHREADED);
    printf("Mlk\n");
    IMMDeviceEnumerator* enumerator;
    CoCreateInstance(&CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL, &IID_IMMDeviceEnumerator, (void**)&enumerator);
    IMMDevice* device;
    enumerator->lpVtbl->GetDefaultAudioEndpoint(enumerator, eRender, eConsole, &device);
    device->lpVtbl->Activate(device, &IID_IAudioClient, CLSCTX_ALL, NULL, (void**)&audio->client);
    WAVEFORMATEX* format;
    printf("gyfjkasdklhsdkjd\n");
    int a = audio->client->lpVtbl->GetMixFormat(audio->client, &format);
    printf("sdfkjnsdkhndfndfljhfkhfdhsdoh.%x\n", a);
    printf("novdkjvdbkdjbd.");
    a = audio->client->lpVtbl->Initialize(audio->client, AUDCLNT_SHAREMODE_SHARED, 0, 100, 0, format, NULL);
    printf("sdfkjnsdkhndfndfljhfkhfdhsdoh.%x\n", a);
    a = audio->client->lpVtbl->GetService(audio->client, &IID_IAudioRenderClient, (void **)&audio->render);
    printf("novdkjvdbkdjbdcxsdfsdgdgbdfhghm.%x\n", FAILED(a));
    audio->render->lpVtbl->GetBuffer(audio->render, data_size, &data);
    printf("novksdggsdkjgfbspjsdfkjsdjsbfdvhskgjbvlvsdkjhghkgcvhsvfhkshvsfhjgvkjsgvkjbsjksdkhbgkjasbgsd,kjgbkjgsd.fhhsdkgfsjkvfdjjbsvdvhkjfvdkjvdbkdjbdffgdfggggtgtggbhgxgg.\n");
    audio->render->lpVtbl->ReleaseBuffer(audio->render, data_size, 0);
    printf("novdkjvdbkdjbdffgdfggggtgtggbhgxgg.\n");
}


void judd_play_audio(judd_audio_t* audio) {
    audio->client->lpVtbl->Start(audio->client);
}

void judd_stop_audio(judd_audio_t* audio) {
    audio->client->lpVtbl->Stop(audio->client);
}

void judd_destroy_audio(judd_audio_t* audio) {
    audio->render->lpVtbl->Release(audio->render);
    audio->client->lpVtbl->Release(audio->client);
    CoUninitialize();
}
