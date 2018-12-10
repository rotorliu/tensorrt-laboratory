/* Copyright (c) 2018, NVIDIA CORPORATION. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of NVIDIA CORPORATION nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <benchmark/benchmark.h>
#include "tensorrt/playground/core/allocator.h"
#include "tensorrt/playground/core/memory.h"

using namespace yais;

static void BM_Memory_SystemMalloc(benchmark::State &state)
{
    for (auto _ : state)
    {
        auto unique = std::make_unique<Allocator<SystemMallocMemory>>(1024*1024);
        auto shared = std::make_shared<Allocator<SystemMallocMemory>>(1024*1024);
        Allocator<SystemMallocMemory> memory(1024*1024);
    }
}

static void BM_Memory_SystemMalloc_ctor(benchmark::State &state)
{
    for (auto _ : state)
    {
        Allocator<SystemMallocMemory> memory(1024*1024);
        Allocator<SystemMallocMemory> memory1(1024*1024);
        Allocator<SystemMallocMemory> memory2(1024*1024);
    }
}

static void BM_Memory_SystemMalloc_shared(benchmark::State &state)
{
    for (auto _ : state)
    {
        auto shared = std::make_shared<Allocator<SystemMallocMemory>>(1024*1024);
    }
}


/*
static void BM_Memory_UnsafeWrapRawPointer(benchmark::State &state)
{
    auto memory = std::make_shared<Allocator<SystemMallocMemory>>(1024*1024);
    for (auto _ : state)
    {
        auto base = memory->UnsafeWrapRawPointer(memory->Data(), memory->Size(), [memory](HostMemory *ptr) mutable {});
    }
}
*/

BENCHMARK(BM_Memory_SystemMalloc);
BENCHMARK(BM_Memory_SystemMalloc_ctor);
BENCHMARK(BM_Memory_SystemMalloc_shared);
// BENCHMARK(BM_Memory_UnsafeWrapRawPointer);