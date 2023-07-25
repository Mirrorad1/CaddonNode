#include <node.h>

namespace calculate {

    using v8::FunctionCallbackInfo;
    using v8::Isolate;
    using v8::Local;
    using v8::Object;
    using v8::Function;
    using v8::Value;

    void Method(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();

        if (!args[0]->IsFunction()) {
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, "Argument must be a function").ToLocalChecked()));
            return;
        }

        Local<Function> func = Local<Function>::Cast(args[0]);
        Local<Value> result = func->Call(isolate->GetCurrentContext(), Null(isolate), 0, nullptr).ToLocalChecked();
        args.GetReturnValue().Set(result);
    }

    void Initialize(Local<Object> exports) {
        NODE_SET_METHOD(exports, "calc", Method);
    }

    NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize);
}
