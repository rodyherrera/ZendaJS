/***
 * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root 
 * for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * For related information - https://github.com/codewithrodi/ZendaJS/
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/

#include "infoware/cpu.hpp"
#include "infoware/system.hpp"

namespace Zenda::JavaScript::Objects::System{
    static inline void Threads(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void SourceCodeLocation(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void CommandOutput(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void Execute(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Platform(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void Arguments(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void CurrentWorkignDirectory(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Exit(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void GetPID(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void GetHeapStatistics(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void ChangeWorkingDirectory(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void SetEnvironmentVariable(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void UnsetEnvironmentVariable(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void GetV8Version(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void KillProcess(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void SetUID(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void GetUID(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void GetCPU(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void GetKernel(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void GetVersion(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static const char* ResolveCacheTypeName(iware::cpu::cache_type_t CacheType) noexcept;
    static const char* ResolveArchitectureName(iware::cpu::architecture_t Architecture) noexcept;
    static const char* ResolveEndiannessName(iware::cpu::endianness_t Endianness) noexcept;
    static const char* ResolveKernelVariantName(iware::system::kernel_t Variant) noexcept;
    static void GetDistribution(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Thread(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void RunThread(void *Argument);

    static void RunThread(void *Argument){
        int Counter = *((int *) Argument);
        while(Counter){
            Counter--;
            fprintf(stderr, ".\n");
            uv_sleep(100);
        }
        fprintf(stderr, "Tortoise done running!\n");
    }

    static inline void Thread(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        int64_t Counter = Arguments[0]->IntegerValue(
            Arguments.GetIsolate()->GetCurrentContext()).ToChecked();
        uv_thread_t TaskID;
        uv_thread_create(&TaskID, RunThread, &Counter);
    }
    
    static void GetDistribution(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        const auto Information = iware::system::OS_info();
        v8::Local<v8::Object> Object = v8::Object::New(Arguments.GetIsolate());
        Zenda::Shortcuts::Set(Object, "GetName", Information.name);
        Zenda::Shortcuts::Set(Object, "GetFullName", Information.full_name);
        Zenda::Shortcuts::Set(Object, "GetPatch", Information.patch);
        Zenda::Shortcuts::Set(Object, "GetBuildNumber", Information.build_number);
        Zenda::Shortcuts::Set(Object, "GetMinor", Information.minor);
        Zenda::Shortcuts::Set(Object, "GetMajor", Information.major);
        Arguments.GetReturnValue().Set(Object);
    }

    static const char* ResolveKernelVariantName(iware::system::kernel_t Variant) noexcept{
        switch(Variant){
            case iware::system::kernel_t::windows_nt:
                return "Windows NT";
            case iware::system::kernel_t::linux:
                return "Linux";
            case iware::system::kernel_t::darwin:
                return "Darwin";
            default:
                return "Unknown";
        }
    }

    static void GetKernel(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        const auto KernelInfo = iware::system::kernel_info();
        v8::Local<v8::Object> Object = v8::Object::New(Arguments.GetIsolate());
        Zenda::Shortcuts::Set(Object, "GetVariant", ResolveKernelVariantName(KernelInfo.variant));
        Zenda::Shortcuts::Set(Object, "GetBuildNumber", KernelInfo.build_number);
        Zenda::Shortcuts::Set(Object, "GetMajor", KernelInfo.major);
        Zenda::Shortcuts::Set(Object, "GetMinor", KernelInfo.minor);
        Zenda::Shortcuts::Set(Object, "GetPatch", KernelInfo.patch);
        Arguments.GetReturnValue().Set(Object);
    }

    static const char* ResolveEndiannessName(iware::cpu::endianness_t Endianness) noexcept{
        switch(Endianness){
            case iware::cpu::endianness_t::little:
                return "Little-Endian";
            case iware::cpu::endianness_t::big:
                return "Big-Endian";
            default:
                return "Unknown";
        }
    }

    static const char* ResolveArchitectureName(iware::cpu::architecture_t Architecture) noexcept{
        switch(Architecture){
            case iware::cpu::architecture_t::x64:
                return "x64";
            case iware::cpu::architecture_t::arm:
                return "ARM";
            case iware::cpu::architecture_t::itanium:
                return "Itanium";
            case iware::cpu::architecture_t::x86:
                return "x86";
            default:
                return "Unknown";
        }
    }

    static const char* ResolveCacheTypeName(iware::cpu::cache_type_t CacheType) noexcept{
        switch(CacheType){
            case iware::cpu::cache_type_t::unified:
                return "Unified";
            case iware::cpu::cache_type_t::instruction:
                return "Instruction";
            case iware::cpu::cache_type_t::data:
                return "Data";
            case iware::cpu::cache_type_t::trace:
                return "Trace";
            default:
                return "Unknown";
        }
    }

    static void GetCPU(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        const auto Quantities = iware::cpu::quantities();
        v8::Local<v8::Object> Data = v8::Object::New(Arguments.GetIsolate());
        Zenda::Shortcuts::Set(Data, "GetFrequency", iware::cpu::frequency());
        Zenda::Shortcuts::Set(Data, "GetModelName", iware::cpu::model_name());
        Zenda::Shortcuts::Set(Data, "GetVendorID", iware::cpu::vendor_id());
        Zenda::Shortcuts::Set(Data, "GetArchitecture", ResolveArchitectureName(iware::cpu::architecture()));
        Zenda::Shortcuts::Set(Data, "GetEndianness", ResolveEndiannessName(iware::cpu::endianness()));
        v8::Local<v8::Object> InstructionSetSupported = v8::Object::New(Arguments.GetIsolate());
        for(auto && Set : {std::make_pair("S3DNow", iware::cpu::instruction_set_t::s3d_now),
                            std::make_pair("S3DNowExtended", iware::cpu::instruction_set_t::s3d_now_extended),
                            std::make_pair("MMX", iware::cpu::instruction_set_t::mmx),
                            std::make_pair("MMXExtended", iware::cpu::instruction_set_t::mmx_extended),
                            std::make_pair("SSE", iware::cpu::instruction_set_t::sse),
                            std::make_pair("SSE2", iware::cpu::instruction_set_t::sse2),
                            std::make_pair("SSE3", iware::cpu::instruction_set_t::sse3),
                            std::make_pair("SSSE3", iware::cpu::instruction_set_t::ssse3),
                            std::make_pair("SSE4A", iware::cpu::instruction_set_t::sse4a),
                            std::make_pair("SSE41", iware::cpu::instruction_set_t::sse41),
                            std::make_pair("SSE42", iware::cpu::instruction_set_t::sse42),
                            std::make_pair("AES", iware::cpu::instruction_set_t::aes),
                            std::make_pair("AVX", iware::cpu::instruction_set_t::avx),
                            std::make_pair("AVX2", iware::cpu::instruction_set_t::avx2),
                            std::make_pair("AVX512", iware::cpu::instruction_set_t::avx_512),
                            std::make_pair("AVX512F", iware::cpu::instruction_set_t::avx_512_f),
                            std::make_pair("AVX512CD", iware::cpu::instruction_set_t::avx_512_cd),
                            std::make_pair("AVX512PF", iware::cpu::instruction_set_t::avx_512_pf),
                            std::make_pair("AVX512ER", iware::cpu::instruction_set_t::avx_512_er),
                            std::make_pair("AVX512VL", iware::cpu::instruction_set_t::avx_512_vl),
                            std::make_pair("AVX512BW", iware::cpu::instruction_set_t::avx_512_bw),
                            std::make_pair("AVX512BQ", iware::cpu::instruction_set_t::avx_512_bq),
                            std::make_pair("AVX512DQ", iware::cpu::instruction_set_t::avx_512_dq),
                            std::make_pair("AVX512Ifma", iware::cpu::instruction_set_t::avx_512_ifma),
                            std::make_pair("AVX512Vbmi", iware::cpu::instruction_set_t::avx_512_vbmi),
                            std::make_pair("HLE", iware::cpu::instruction_set_t::hle),
                            std::make_pair("BMI1", iware::cpu::instruction_set_t::bmi1),
                            std::make_pair("BMI2", iware::cpu::instruction_set_t::bmi2),
                            std::make_pair("ADX", iware::cpu::instruction_set_t::adx),
                            std::make_pair("MPX", iware::cpu::instruction_set_t::mpx),
                            std::make_pair("SHA", iware::cpu::instruction_set_t::sha),
                            std::make_pair("PreFetchWT1", iware::cpu::instruction_set_t::prefetch_wt1),
                            std::make_pair("FMA3", iware::cpu::instruction_set_t::fma3),
                            std::make_pair("FMA4", iware::cpu::instruction_set_t::fma4),
                            std::make_pair("XOP", iware::cpu::instruction_set_t::xop),
                            std::make_pair("RDRand", iware::cpu::instruction_set_t::rd_rand),
                            std::make_pair("x64", iware::cpu::instruction_set_t::x64),
                            std::make_pair("x87FPU", iware::cpu::instruction_set_t::x87_fpu)}){
            v8::Maybe<bool> IsSupportedInstruction = InstructionSetSupported->Set(
                Arguments.GetIsolate()->GetCurrentContext(), 
                Zenda::Shortcuts::V8String(Arguments.GetIsolate(), Set.first), 
                v8::Boolean::New(Arguments.GetIsolate(), 
                (iware::cpu::instruction_set_supported(Set.second)) ? (true) : (false)));
        }
        Zenda::Shortcuts::Set(Data, "InstructionSetSupported", InstructionSetSupported);
        v8::Local<v8::Object> Cores = v8::Object::New(Arguments.GetIsolate());
        Zenda::Shortcuts::Set(Cores, "GetLogicals", Quantities.logical);
        Zenda::Shortcuts::Set(Cores, "GetPhysicals", Quantities.physical);
        Zenda::Shortcuts::Set(Cores, "GetPackages", Quantities.packages);
        Zenda::Shortcuts::Set(Data, "Cores", Cores);
        v8::Local<v8::Array> Caches = v8::Array::New(Arguments.GetIsolate());
        for(unsigned short int Iterator = 1u; Iterator <= 3; ++Iterator){
            const auto Cache = iware::cpu::cache(Iterator);
            v8::Local<v8::Object> CacheData = v8::Object::New(Arguments.GetIsolate());
            Zenda::Shortcuts::Set(CacheData, "GetSize", Cache.size);
            Zenda::Shortcuts::Set(CacheData, "GetLineSize", Cache.line_size);
            Zenda::Shortcuts::Set(CacheData, "GetAssociativity", static_cast<unsigned int>(Cache.associativity));
            Zenda::Shortcuts::Set(CacheData, "Type", ResolveCacheTypeName(Cache.type));
            v8::Maybe<bool> RecollectedCacheData = 
                Caches->Set(Arguments.GetIsolate()->GetCurrentContext(), Iterator - 1, CacheData);
        }
        Zenda::Shortcuts::Set(Data, "Caches", Caches);
        Arguments.GetReturnValue().Set(Data);
    }

    static inline void GetUID(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8Integer(Arguments.GetIsolate(), getuid()));
    }

    static inline void SetUID(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "To set a new UID you must send it as a parameter.");
        else
            Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8Integer(
                Arguments.GetIsolate(), setuid(v8::Local<v8::Integer>::Cast(Arguments[0])->Value())));
    }

    static inline void KillProcess(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "To kill the process you must send its PID as a parameter.");
        else{
            pid_t PID = v8::Local<v8::Integer>::Cast(Arguments[0])->Value();
            Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8Integer(Arguments.GetIsolate(), kill(PID, SIGKILL)));
        }
    }

    static inline void GetV8Version(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8String(
                Arguments.GetIsolate(), std::string(v8::V8::GetVersion())));
    }

    static inline void UnsetEnvironmentVariable(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined()){
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You must indicate the name of the variable that you want to remove from the environment variable of the operating system <PATH>.");
        }else{
            v8::String::Utf8Value Variable(Arguments.GetIsolate(), Arguments[0]);
            unsetenv(*Variable);
        }
    }

    static inline void SetEnvironmentVariable(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined() || Arguments[1]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You must indicate the name of the variable next to its value to be able to add them to the variable environment of your operating system <PATH>.");
        else{
            v8::String::Utf8Value Variable(Arguments.GetIsolate(), Arguments[0]);
            v8::String::Utf8Value Value(Arguments.GetIsolate(), Arguments[1]);
            setenv(*Variable, *Value, 1);
        }
    }

    static inline void ChangeWorkingDirectory(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "To be able to change directory, you must send the new working directory as a parameter.");
        else{
            v8::String::Utf8Value Path(Arguments.GetIsolate(), Arguments[0]);
            Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8Integer(Arguments.GetIsolate(), chdir(*Path)));
        }
    }

    static inline void GetHeapStatistics(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::Isolate* Isolate = Arguments.GetIsolate();
        v8::Local<v8::Context> Context = Isolate->GetCurrentContext();
        v8::HandleScope Scope(Isolate);
        v8::HeapStatistics HeapStatistics;
        Isolate->GetHeapStatistics(&HeapStatistics);
        v8::Local<v8::Object> Data = v8::Object::New(Isolate);
        Zenda::Shortcuts::Set(Data, "TotalHeapSize", HeapStatistics.total_heap_size());
        Zenda::Shortcuts::Set(Data, "UsedHeapSize", HeapStatistics.used_heap_size());
        Zenda::Shortcuts::Set(Data, "ExternalMemory", HeapStatistics.external_memory());
        Zenda::Shortcuts::Set(Data, "DoesZapGarbage", HeapStatistics.does_zap_garbage());
        Zenda::Shortcuts::Set(Data, "HeapSizeLimit", HeapStatistics.heap_size_limit());
        Zenda::Shortcuts::Set(Data, "MallocedMemory", HeapStatistics.malloced_memory());
        Zenda::Shortcuts::Set(Data, "NumberOfDetachedContexts", HeapStatistics.number_of_detached_contexts());
        Zenda::Shortcuts::Set(Data, "NumberOfNativeContexts", HeapStatistics.number_of_native_contexts());
        Zenda::Shortcuts::Set(Data, "PeakMallocedMemory", HeapStatistics.peak_malloced_memory());
        Zenda::Shortcuts::Set(Data, "TotalAvailableSize", HeapStatistics.total_available_size());
        Zenda::Shortcuts::Set(Data, "TotalHeapSizeExecutable", HeapStatistics.total_heap_size_executable());
        Arguments.GetReturnValue().Set(Data);
    }

    static inline void GetPID(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8Integer(Arguments.GetIsolate(), getpid()));
    }

    static inline void Threads(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        Arguments.GetReturnValue().Set(
            Zenda::Shortcuts::V8Number(Arguments.GetIsolate(), std::thread::hardware_concurrency()));
    }

    static inline void SourceCodeLocation(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8String(Arguments.GetIsolate(), Zenda::Algorithms::SourceCodeLocation()));
    }

    static void CommandOutput(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8String(Arguments.GetIsolate(), "You need enter a command for get their output.");
        else{
            v8::String::Utf8Value Command(Arguments.GetIsolate(), Arguments[0]);
            Arguments.GetReturnValue().Set(
                Zenda::Shortcuts::V8String(Arguments.GetIsolate(), Zenda::Algorithms::GetOutputOfCommand(
                    std::string(*Command))));
        }
    }

    static void Execute(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "You need to enter one or more commands to the Execute method so that you can execute them in the operating .");
        else
            for(unsigned short int Iterator = 0; Iterator < Arguments.Length(); Iterator++){
                v8::HandleScope Scope(Arguments.GetIsolate());
                v8::String::Utf8Value Command(Arguments.GetIsolate(), Arguments[Iterator]);
                system(*Command);
            }
    }

    static inline void Platform(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8String(Arguments.GetIsolate(), Zenda::Shared::OperativeSystem()));
    }

    static void Arguments(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        v8::Local<v8::Context> ArgumentsContext = v8::Context::New(Zenda::Definitions::Isolate);
        v8::Local<v8::Array> ArgumentList = v8::Array::New(Zenda::Definitions::Isolate, Zenda::Definitions::CallArguments.size());
        for(unsigned short int Iterator = 0; Iterator < Zenda::Definitions::CallArguments.size(); Iterator++){
            v8::Local<v8::String> SomeArgument = v8::String::NewFromUtf8(
                Zenda::Definitions::Isolate, Zenda::Definitions::CallArguments.at(Iterator).c_str()).ToLocalChecked();
            v8::Maybe<bool> ArgumentAdded = ArgumentList->Set(ArgumentsContext, Iterator, SomeArgument);
        }
        Arguments.GetReturnValue().Set(ArgumentList);
    }

    static inline void CurrentWorkignDirectory(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        Arguments.GetReturnValue().Set(Zenda::Shortcuts::V8String(Arguments.GetIsolate(), Zenda::Definitions::WorkingDirectory));
    }

    static inline void Exit(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "In order to exit with a status code you must send it as a parameter.");
        else
            exit(v8::Local<v8::Integer>::Cast(Arguments[0])->Value());
    }
};
