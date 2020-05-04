#include "../headers/decoder_utility.h"
#include <iostream>
using namespace remoting;
Napi::FunctionReference DecoderUtility::constructor;

Napi::Object DecoderUtility::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DecoderUtility", {
        InstanceMethod("init", &DecoderUtility::Init), 
        InstanceMethod("getNextFrame", &DecoderUtility::GetNextFrame),
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("DecoderUtility", func);
    return exports;
}

DecoderUtility::DecoderUtility(const Napi::CallbackInfo &info) : Napi::ObjectWrap<DecoderUtility>(info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    this->_decoder = new Decoder();
}

void DecoderUtility::Init(const Napi::CallbackInfo &info)
{
    //
}

void DecoderUtility::GetNextFrame(const Napi::CallbackInfo &info)
{
    //
}

DecoderUtility::~DecoderUtility()
{
    delete this->_decoder;
}
