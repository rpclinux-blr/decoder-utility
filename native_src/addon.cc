#include <napi.h>
#include "../headers/decoder_utility.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return remoting::DecoderUtility::Init(env, exports);
}

NODE_API_MODULE(addon, InitAll)