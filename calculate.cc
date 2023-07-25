// calculate.cc
#include <node.h>
#include <thread>
#include <future>

namespace calculate {

    using v8::FunctionCallbackInfo;
    using v8::Isolate;
    using v8::Local;
    using v8::Object;
    using v8::Number;
    using v8::Value;

    // Result class definition
    template<typename T>
    class Result {
    public:
        Result(T val) : value(val) {}

        T getValue() const {
            return value;
        }

    private:
        T value;
    };

    // Function that performs the first calculation
    Result<double> calc1() {
        double x = 100.32462344, y = 200.333456533452;
        for (int i = 0; i < 100; i++) {
            x += y;
        }
        return Result<double>(x);
    }

    // Function that performs the second calculation
    Result<double> calc2() {
        int result = 0;
        for (int i = 0; i < 100; i++) {
            result += i;
        }
        return Result<double>(result);
    }

    // Function that performs the third calculation
    Result<std::string> calc3() {
        return Result<std::string>("Hello, world!");
    }

    // Function that runs a calculation in a thread and returns the result via promise
    template<typename T>
    void threadedCalc(std::promise<Result<T>>& resultPromise, Result<T> (*calcFunc)()) {
        Result<T> result = calcFunc();
        resultPromise.set_value(result);
    }

    void Method(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();

        // Create promises to store the results
        std::promise<Result<double>> resultPromise1, resultPromise2;
        std::promise<Result<std::string>> resultPromise3;
        std::future<Result<double>> resultFuture1 = resultPromise1.get_future();
        std::future<Result<double>> resultFuture2 = resultPromise2.get_future();
        std::future<Result<std::string>> resultFuture3 = resultPromise3.get_future();

        // Create threads to run the calculations concurrently
        std::thread thread1(threadedCalc<double>, std::ref(resultPromise1), calc1);
        std::thread thread2(threadedCalc<double>, std::ref(resultPromise2), calc2);
        std::thread thread3(threadedCalc<std::string>, std::ref(resultPromise3), calc3);

        // Wait for the threads to finish
        thread1.join();
        thread2.join();
        thread3.join();

        // Get the results from the promises
        Result<double> result1 = resultFuture1.get();
        Result<double> result2 = resultFuture2.get();
        Result<std::string> result3 = resultFuture3.get();

        // Convert the Result instances to V8 Numbers and store them in the results object
        auto total1 = Number::New(isolate, result1.getValue());
        auto total2 = Number::New(isolate, result2.getValue());
        auto total3 = v8::String::NewFromUtf8(isolate, result3.getValue().c_str()).ToLocalChecked();

        Local<Object> resultsObj = Object::New(isolate);
        resultsObj->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "calc1").ToLocalChecked(), total1).Check();
        resultsObj->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "calc2").ToLocalChecked(), total2).Check();
        resultsObj->Set(isolate->GetCurrentContext(), v8::String::NewFromUtf8(isolate, "calc3").ToLocalChecked(), total3).Check();

        args.GetReturnValue().Set(resultsObj);
    }

    void Initialize(Local<Object> exports) {
        NODE_SET_METHOD(exports, "calc", Method);
    }

    NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize);
}
