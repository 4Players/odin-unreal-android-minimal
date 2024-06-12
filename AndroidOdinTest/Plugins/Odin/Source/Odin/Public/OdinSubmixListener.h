/* Copyright (c) 2022-2024 4Players GmbH. All rights reserved. */

#pragma once

#include "Engine/GameEngine.h"
#include "Runtime/Launch/Resources/Version.h"
#include "odin_sdk.h"
#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 3
#include "ISubmixBufferListener.h"
#else
#include "AudioDevice.h"
#endif

class ODIN_API FOdinSubmixListener : public ISubmixBufferListener
{
  public:
    FOdinSubmixListener();
    virtual ~FOdinSubmixListener();

    void StartSubmixListener(TSharedPtr<FOdinSubmixListener> SubmixListenerPtr);
    void StopSubmixListener(TSharedPtr<FOdinSubmixListener> SubmixListenerPtr);
    void SetRoom(OdinRoomHandle handle);

  protected:
    int32 OdinSampleRate = 48000;
    int32 OdinChannels   = 2;

  private:
    FCriticalSection    submix_cs_;
    bool                bInitialized;
    OdinRoomHandle      current_room_handle;
    OdinResamplerHandle resampler_handle;

    void OnNewSubmixBuffer(const USoundSubmix* OwningSubmix, float* AudioData, int32 InNumSamples,
                           int32 InNumChannels, const int32 InSampleRate, double) override;
};
