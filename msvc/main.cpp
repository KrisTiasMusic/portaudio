
#include <iostream>
#include <Mmdeviceapi.h>
#include <audiopolicy.h>
#include <Audioclient.h>
#include <functiondiscoverykeys_devpkey.h>
#include <audiosessiontypes.h>
#include <portaudio.h>
#include <pa_win_wasapi.h>
#include <pa_x86_plain_converters.h>

#define PA_WASAPI_MAX_CONST_DEVICE_COUNT = 32

int main()
{
    auto err = Pa_Initialize();

    IMMDevice* pDevice = NULL;
    std::cout << "Hello World!\n";

    // initialize the Windows Core Audio API
    HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(hr)) {
        std::cout << "Error: Failed to initialize Windows Core Audio API (" << hr << ")" << std::endl;
        return 1;
    }

    // create a new instance of the audio session manager
    IAudioSessionManager2* pSessionManager;
    hr = CoCreateInstance(__uuidof(pSessionManager), NULL, CLSCTX_ALL, __uuidof(IAudioSessionManager2), (void**)&pSessionManager);
    if (FAILED(hr)) {
        std::cout << "Error: Failed to create audio session manager (" << hr << ")" << std::endl;
        CoUninitialize();
        return 1;
    }

    // get the audio session control
    IAudioSessionControl* pSessionControl;
    hr = pSessionManager->GetAudioSessionControl(NULL, 0, &pSessionControl);
    if (FAILED(hr)) {
        std::cout << "Error: Failed to get audio session control (" << hr << ")" << std::endl;
        pSessionManager->Release();
        CoUninitialize();
        return 1;
    }

    // set the display name of the audio session control
    LPCWSTR displayName = L"My Audio Application";
    hr = pSessionControl->SetDisplayName(displayName, NULL);
    if (FAILED(hr)) {
        std::cout << "Error: Failed to set display name (" << hr << ")" << std::endl;
        pSessionControl->Release();
        pSessionManager->Release();
        CoUninitialize();
        return 1;
    }

    // get the session identifier of the audio session control
 /*   LPWSTR sessionId;
    hr = pSessionControl->GetSessionIdentifier(&sessionId);
    if (FAILED(hr)) {
        std::cout << "Error: Failed to get session identifier (" << hr << ")" << std::endl;
        pSessionControl->Release();
        pSessionManager->Release();
        CoUninitialize();
        return 1;
    }*/
    
    // register the audio session control with the Windows Audio Session API (WASAPI)
  /*  hr = RegisterAudioSession(sessionId, 0);
    if (FAILED(hr)) {
        std::cout << "Error: Failed to register audio session control with WASAPI (" << hr << ")" << std::endl;
    }*/

    // release resources
    //CoTaskMemFree(sessionId);
    pSessionControl->Release();
    pSessionManager->Release();
    CoUninitialize();
}
