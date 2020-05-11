#include "../headers/decoder_utility.h"
#include <iostream>
using namespace remoting;
Napi::FunctionReference DecoderUtility::constructor;

Napi::Object DecoderUtility::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "DecoderUtility", {
        InstanceMethod("init", &DecoderUtility::Init), 
        InstanceMethod("decodeFrame", &DecoderUtility::GetNextFrame),
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
}

void DecoderUtility::Init(const Napi::CallbackInfo &info)
{
    try
    {
        this->_decoder = new Decoder();
    }
    catch (const char *message)
    {
        Napi::Error::New(info.Env(), message).ThrowAsJavaScriptException();
        return;
    }
    catch (std::string message)
    {
        Napi::Error::New(info.Env(), message).ThrowAsJavaScriptException();
        return;
    }
}

void DecoderUtility::GetNextFrame(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return;
    }
    if (!info[0].IsArrayBuffer() || !info[1].IsFunction())
    {
        Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
        return;
    }
    
    Napi::Function cb = info[0].As<Napi::Function>();
    AVFrame* frame = this->_decoder->decode((uint8_t*) info[0].As<Napi::ArrayBuffer>().Data(), info[0].As<Napi::ArrayBuffer>().ByteLength());

    Napi::Object decodedFrame = Napi::Object::New(env);
    decodedFrame.Set(Napi::String::New(env, "height"), Napi::Number::New(env, frame->height));
    decodedFrame.Set(Napi::String::New(env, "width"), Napi::Number::New(env, frame->width));
    decodedFrame.Set(Napi::String::New(env, "yData"), Napi::ArrayBuffer::New(env, frame->data[0], frame->linesize[0] * frame->height));
    decodedFrame.Set(Napi::String::New(env, "uData"), Napi::ArrayBuffer::New(env, frame->data[1], frame->linesize[1] * frame->height / 2));
    decodedFrame.Set(Napi::String::New(env, "vData"), Napi::ArrayBuffer::New(env, frame->data[2], frame->linesize[2] * frame->height / 2));

    cb.Call(env.Global(), {decodedFrame});
}

DecoderUtility::~DecoderUtility()
{
    delete this->_decoder;
}
