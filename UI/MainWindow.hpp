#pragma once
#if defined(AuroraWindows)
#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#endif
#include <Core\Exception.hpp>

namespace Aurora
{
    namespace UI
    {
        namespace MainWindow
        {
            #if defined(AuroraWindows)
            class AuroraCPUDescriptorHandle : public D3D12_CPU_DESCRIPTOR_HANDLE
            {
            public:
                inline  AuroraCPUDescriptorHandle() = default;

                inline explicit AuroraCPUDescriptorHandle(const D3D12_CPU_DESCRIPTOR_HANDLE &o) noexcept : D3D12_CPU_DESCRIPTOR_HANDLE(o){}

                inline AuroraCPUDescriptorHandle(_In_ const D3D12_CPU_DESCRIPTOR_HANDLE &other, INT offsetInDescriptors, UINT descriptorIncrementSize) noexcept
                {
                    this->ptr = SIZE_T(INT64(other.ptr) + INT64(offsetInDescriptors) * INT64(descriptorIncrementSize));
                }

                inline AuroraCPUDescriptorHandle& Offset(INT offsetScaledByIncrementSize) noexcept
                {
                    ptr = SIZE_T(INT64(ptr) + INT64(offsetScaledByIncrementSize));
                    return *this;
                }
            };

            class AuroraResourceBarrier : public D3D12_RESOURCE_BARRIER
            {
            public:
                static inline AuroraResourceBarrier Transition(_In_ ID3D12Resource* pResource, D3D12_RESOURCE_STATES stateBefore, D3D12_RESOURCE_STATES stateAfter, UINT subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES, D3D12_RESOURCE_BARRIER_FLAGS flags = D3D12_RESOURCE_BARRIER_FLAG_NONE) noexcept
                {
                    AuroraResourceBarrier result = {};
                    D3D12_RESOURCE_BARRIER &barrier = result;
                    result.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
                    result.Flags = flags;
                    barrier.Transition.pResource = pResource;
                    barrier.Transition.StateBefore = stateBefore;
                    barrier.Transition.StateAfter = stateAfter;
                    barrier.Transition.Subresource = subresource;
                    return result;
                }
            };

            HINSTANCE AppInstance;

            ID3D12Device8* device;

            bool Tearing = true;

            ID3D12CommandQueue* queue;

            IDXGISwapChain4* chain;

            u32 BackBufferIndex;

            ID3D12DescriptorHeap* heap;

            u32 DescriptorSize;

            ID3D12Resource* backbuffers[3];

            ID3D12CommandAllocator* coallocators[3];

            ID3D12GraphicsCommandList2* colist;

            ID3D12Fence* fence;

            u64 fencevalue = 0u;
            
            u64 framefencevalues[3] = {};

            HANDLE fenceevent;

            HWND Handler;
            #endif
            u16 X = 0u, Y = 0u, Width = 300u, Height = 200u;

            bool Exit = false;

            inline void Relocate(u16 NewX, u16 NewY, Exception& e = GlobalException) noexcept
            {
                #if defined(AuroraWindows)
                if(!SetWindowPos(Handler, 0, NewX, NewY, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER))
                    e = Exception::MainWindowRelocate;
                else
                {
                    X = NewX;
                    Y = NewY;
                }
                #endif
            }

            void Resize(u16 NewWidth, u16 NewHeight, Exception& e = GlobalException) noexcept
            {
                #if defined(AuroraWindows)
                ++fencevalue;
                if(queue->Signal(fence, fencevalue) == S_OK)
                {
                    if(fence->GetCompletedValue() < fencevalue)
                    {
                        if(fence->SetEventOnCompletion(fencevalue, fenceevent) == S_OK)
                            WaitForSingleObject(fenceevent, 1000u);
                        else
                        {
                            e = Exception::MainWindowResize;
                            return;
                        }
                    }
                    backbuffers[0]->Release();
                    framefencevalues[0] = framefencevalues[BackBufferIndex];
                    backbuffers[1]->Release();
                    framefencevalues[1] = framefencevalues[BackBufferIndex];
                    backbuffers[2]->Release();
                    framefencevalues[2] = framefencevalues[BackBufferIndex];
                    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
                    if(chain->GetDesc(&swapChainDesc) == S_OK)
                        if(chain->ResizeBuffers(3u, NewWidth, NewHeight, swapChainDesc.BufferDesc.Format, swapChainDesc.Flags) == S_OK)
                        {
                            BackBufferIndex = chain->GetCurrentBackBufferIndex();
                            auto rtvDescriptorSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
                            AuroraCPUDescriptorHandle rtvHandle(heap->GetCPUDescriptorHandleForHeapStart());
                            ID3D12Resource* backBuffer;
                            if(chain->GetBuffer(0, IID_PPV_ARGS(&backBuffer)) == S_OK)
                            {
                                device->CreateRenderTargetView(backBuffer, 0, rtvHandle);
                                backbuffers[0] = backBuffer;
                                backBuffer->Release();
                                rtvHandle.Offset(rtvDescriptorSize);
                                if(chain->GetBuffer(1, IID_PPV_ARGS(&backBuffer)) == S_OK)
                                {
                                    device->CreateRenderTargetView(backBuffer, 0, rtvHandle);
                                    backbuffers[1] = backBuffer;
                                    backBuffer->Release();
                                    rtvHandle.Offset(rtvDescriptorSize);
                                    if(chain->GetBuffer(2, IID_PPV_ARGS(&backBuffer)) == S_OK)
                                    {
                                        device->CreateRenderTargetView(backBuffer, 0, rtvHandle);
                                        backbuffers[2] = backBuffer;
                                        backBuffer->Release();
                                        rtvHandle.Offset(rtvDescriptorSize);
                                        if(SetWindowPos(Handler, 0, 0, 0, NewWidth, NewHeight, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER))
                                        {
                                            Width = NewWidth;
                                            Height = NewHeight;
                                            return;
                                        }
                                    }
                                }
                            }
                        }
                }
                e = Exception::MainWindowResize;
                #endif
            }
        }
    }
}