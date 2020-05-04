#ifndef REMOTING_HOST_DECODER_UTILITY_H_
#define REMOTING_HOST_DECODER_UTILITY_H_

#include <napi.h>
#include "decoder.h"

namespace remoting
{
class DecoderUtility : public Napi::ObjectWrap<DecoderUtility>
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    DecoderUtility(const Napi::CallbackInfo &info);
    ~DecoderUtility();

private:
    static Napi::FunctionReference constructor;

    void GetNextFrame(const Napi::CallbackInfo &info);
    void Init(const Napi::CallbackInfo &info);

    Decoder *_decoder;
};
} // namespace remoting

#endif // REMOTING_HOST_SCREEN_CAPTURE_UTILITY_H_