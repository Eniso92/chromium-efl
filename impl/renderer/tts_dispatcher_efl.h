// Copyright (c) 2014 Samsung Electronics Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef RENDERER_TTS_DISPATCHER_H_
#define RENDERER_TTS_DISPATCHER_H_

#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/containers/hash_tables.h"
#include "content/public/renderer/render_process_observer.h"
#include "third_party/WebKit/public/platform/WebSpeechSynthesizer.h"
#include "third_party/WebKit/public/platform/WebSpeechSynthesizerClient.h"

namespace IPC {
class Message;
}

namespace content {

struct TtsVoice;

// TtsDispatcher is a delegate for methods used by Blink for speech synthesis
// APIs. It's the complement of TtsDispatcherHost (owned by RenderViewHost).
// Each TtsDispatcher is owned by the WebSpeechSynthesizerClient in Blink;
// it registers itself to listen to IPC upon construction and unregisters
// itself when deleted. There can be multiple TtsDispatchers alive at once,
// so each one routes IPC messages to its WebSpeechSynthesizerClient only if
// the utterance id (which is globally unique) matches.
class TtsDispatcherEfl
    : public blink::WebSpeechSynthesizer,
      public content::RenderProcessObserver {
 public:
  explicit TtsDispatcherEfl(blink::WebSpeechSynthesizerClient* client);

 private:
  virtual ~TtsDispatcherEfl();

  // RenderProcessObserver override.
  bool OnControlMessageReceived(const IPC::Message& message) override;

  // blink::WebSpeechSynthesizer implementation.
  void updateVoiceList() override;
  void speak(const blink::WebSpeechSynthesisUtterance& utterance)
      override;
  void pause() override;
  void resume() override;
  void cancel() override;

  blink::WebSpeechSynthesisUtterance FindUtterance(int utterance_id);

  void OnSetVoiceList(const std::vector<TtsVoice>& voices);
  void OnDidStartSpeaking(int utterance_id);
  void OnDidFinishSpeaking(int utterance_id);
  void OnDidPauseSpeaking(int utterance_id);
  void OnDidResumeSpeaking(int utterance_id);
  void OnWordBoundary(int utterance_id, int char_index);
  void OnSentenceBoundary(int utterance_id, int char_index);
  void OnMarkerEvent(int utterance_id, int char_index);
  void OnWasInterrupted(int utterance_id);
  void OnWasCancelled(int utterance_id);
  void OnSpeakingErrorOccurred(int utterance_id,
                               const std::string& error_message);

  // The WebKit client class that we use to send events back to the JS world.
  // Weak reference, this will be valid as long as this object exists.
  blink::WebSpeechSynthesizerClient* synthesizer_client_;

  // Next utterance id, used to map response IPCs to utterance objects.
  static int next_utterance_id_;

  // Map from id to utterance objects.
  base::hash_map<int, blink::WebSpeechSynthesisUtterance> utterance_id_map_;

  DISALLOW_COPY_AND_ASSIGN(TtsDispatcherEfl);
};

}  // namespace content

#endif  // RENDERER_TTS_DISPATCHER_H_
