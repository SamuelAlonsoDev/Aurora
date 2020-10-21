#if defined(AuroraConsole)
#include <iostream>

int main()
{
    std::cout << "Hello Aurora!";
    return 0;
}
#elif defined(AuroraWindows)
#include <UI\MainWindow.hpp>
#include <Engine\Behaviour.hpp>

LRESULT CALLBACK WndProc(HWND h, UINT u, WPARAM w, LPARAM l)
{
    ID3D12CommandAllocator* coallocator;
    ID3D12Resource* backbuffer;
    Aurora::UI::MainWindow::AuroraResourceBarrier barrier;
    Aurora::UI::MainWindow::AuroraCPUDescriptorHandle rtv;
    ID3D12CommandList* commandLists[1];
    UINT presentFlags = Aurora::UI::MainWindow::Tearing ? DXGI_PRESENT_ALLOW_TEARING : 0;
    const FLOAT BackColor[] = {0.f, 0.f, 0.f, 1.0f};
    switch(u)
    {
        case WM_PAINT:
            coallocator = Aurora::UI::MainWindow::coallocators[Aurora::UI::MainWindow::BackBufferIndex];
            backbuffer = Aurora::UI::MainWindow::backbuffers[Aurora::UI::MainWindow::BackBufferIndex];
            coallocator->Reset();
            Aurora::UI::MainWindow::colist->Reset(coallocator, 0);
            barrier = Aurora::UI::MainWindow::AuroraResourceBarrier::Transition(backbuffer, D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
            Aurora::UI::MainWindow::colist->ResourceBarrier(1, &barrier);
            rtv = Aurora::UI::MainWindow::AuroraCPUDescriptorHandle(Aurora::UI::MainWindow::heap->GetCPUDescriptorHandleForHeapStart(), Aurora::UI::MainWindow::BackBufferIndex, Aurora::UI::MainWindow::DescriptorSize);
            Aurora::UI::MainWindow::colist->ClearRenderTargetView(rtv, BackColor, 0, nullptr);
            if(Aurora::UI::MainWindow::colist->Close() != S_OK)
                Aurora::UI::MainWindow::Exit = true;
            else
            {
                commandLists[0] = Aurora::UI::MainWindow::colist;
                Aurora::UI::MainWindow::queue->ExecuteCommandLists(1u, commandLists);
                if(Aurora::UI::MainWindow::chain->Present(0u, presentFlags) != S_OK)
                    Aurora::UI::MainWindow::Exit = true;
                else
                {
                    ++Aurora::UI::MainWindow::fencevalue;
                    if(Aurora::UI::MainWindow::queue->Signal(Aurora::UI::MainWindow::fence, Aurora::UI::MainWindow::fencevalue) != S_OK)
                        Aurora::UI::MainWindow::Exit = true;
                    else
                    {
                        Aurora::UI::MainWindow::framefencevalues[Aurora::UI::MainWindow::BackBufferIndex] = Aurora::UI::MainWindow::fencevalue;
                        Aurora::UI::MainWindow::BackBufferIndex = Aurora::UI::MainWindow::chain->GetCurrentBackBufferIndex();
                        if(Aurora::UI::MainWindow::fence->GetCompletedValue() < Aurora::UI::MainWindow::framefencevalues[Aurora::UI::MainWindow::BackBufferIndex])
                        {
                            if(Aurora::UI::MainWindow::fence->SetEventOnCompletion(Aurora::UI::MainWindow::framefencevalues[Aurora::UI::MainWindow::BackBufferIndex], Aurora::UI::MainWindow::fenceevent) != S_OK)
                                Aurora::UI::MainWindow::Exit = true;
                            else
                                WaitForSingleObject(Aurora::UI::MainWindow::fenceevent, 1000u);
                        }
                        if(!Aurora::UI::MainWindow::Exit)
                            Aurora::Engine::Behaviour::Update();
                    }
                }
            }
            break;
        case WM_KEYDOWN:
            if(w == 0x08)
                Aurora::UI::MainWindow::Exit = true;
        break;
        default:
            return DefWindowProcW(h, u, w, l);
        break;
    }
    return 0;
}

int CALLBACK WinMain(HINSTANCE hInst, [[maybe_unused]] HINSTANCE hPrevInstance, [[maybe_unused]] LPSTR lpCmdLine, [[maybe_unused]] int nCmdShow)
{
    Aurora::UI::MainWindow::AppInstance = hInst;
    WNDCLASSEXW windowClass = {};
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = (WNDPROC)WndProc;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = hInst;
    windowClass.hIcon = ::LoadIcon(hInst, NULL);
    windowClass.hCursor = ::LoadCursor(NULL, IDC_ARROW);
    windowClass.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
    windowClass.lpszMenuName = NULL;
    windowClass.lpszClassName = L"AuroraMainWindow";
    windowClass.hIconSm = ::LoadIcon(hInst, NULL);
    if(RegisterClassExW(&windowClass))
    {
        HWND h = CreateWindowExW(WS_EX_APPWINDOW, L"AuroraMainWindow", 0, WS_POPUP|WS_VISIBLE|WS_SYSMENU, Aurora::UI::MainWindow::X, Aurora::UI::MainWindow::Y, Aurora::UI::MainWindow::Width, Aurora::UI::MainWindow::Height, 0, 0, hInst, 0);
        if(h)
        {
            Aurora::UI::MainWindow::Handler = h;
            ShowWindow(h, SW_SHOW);
            if(D3D12CreateDevice(0, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&Aurora::UI::MainWindow::device)) == S_OK)
            {
                D3D12_COMMAND_QUEUE_DESC desc = {};
                desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
                desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
                desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
                desc.NodeMask = 0u;
                if(Aurora::UI::MainWindow::device->CreateCommandQueue(&desc, IID_PPV_ARGS(&Aurora::UI::MainWindow::queue)) == S_OK)
                {
                    IDXGIFactory7* factory;
                    if(CreateDXGIFactory2(0u, IID_PPV_ARGS(&factory)) == S_OK)
                    {
                        if(factory->CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING, &Aurora::UI::MainWindow::Tearing, sizeof(bool)) != S_OK)
                            Aurora::UI::MainWindow::Tearing = false;
                        DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
                        swapChainDesc.Width = Aurora::UI::MainWindow::Width;
                        swapChainDesc.Height = Aurora::UI::MainWindow::Height;
                        swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                        swapChainDesc.Stereo = FALSE;
                        swapChainDesc.SampleDesc = { 1, 0 };
                        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
                        swapChainDesc.BufferCount = 3u;
                        swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
                        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
                        swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
                        swapChainDesc.Flags = Aurora::UI::MainWindow::Tearing ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0;
                        IDXGISwapChain1* chain1;
                        if(factory->CreateSwapChainForHwnd(Aurora::UI::MainWindow::queue, h, &swapChainDesc, 0, 0, &chain1) == S_OK)
                        {
                            if(factory->MakeWindowAssociation(h, DXGI_MWA_NO_ALT_ENTER) == S_OK)
                            {
                                if(chain1->QueryInterface(IID_PPV_ARGS(&Aurora::UI::MainWindow::chain)) == S_OK)
                                {
                                    chain1->Release();
                                    factory->Release();
                                    Aurora::UI::MainWindow::BackBufferIndex = Aurora::UI::MainWindow::chain->GetCurrentBackBufferIndex();
                                    D3D12_DESCRIPTOR_HEAP_DESC desch = {0};
                                    desch.NumDescriptors = 3u;
                                    desch.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
                                    if(Aurora::UI::MainWindow::device->CreateDescriptorHeap(&desch, IID_PPV_ARGS(&Aurora::UI::MainWindow::heap)) == S_OK)
                                    {
                                        Aurora::UI::MainWindow::DescriptorSize = Aurora::UI::MainWindow::device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
                                        const Aurora::u32 descriptorsize = Aurora::UI::MainWindow::device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
                                        Aurora::UI::MainWindow::AuroraCPUDescriptorHandle cdh(Aurora::UI::MainWindow::heap->GetCPUDescriptorHandleForHeapStart());
                                        ID3D12Resource* tr;
                                        if(Aurora::UI::MainWindow::chain->GetBuffer(0, IID_PPV_ARGS(&tr)) == S_OK)
                                        {
                                            Aurora::UI::MainWindow::device->CreateRenderTargetView(tr, 0, cdh);
                                            Aurora::UI::MainWindow::backbuffers[0] = tr;
                                            tr->Release();
                                            cdh.Offset(descriptorsize);
                                            if(Aurora::UI::MainWindow::chain->GetBuffer(1, IID_PPV_ARGS(&tr)) == S_OK)
                                            {
                                                Aurora::UI::MainWindow::device->CreateRenderTargetView(tr, 0, cdh);
                                                Aurora::UI::MainWindow::backbuffers[1] = tr;
                                                tr->Release();
                                                cdh.Offset(descriptorsize);
                                                if(Aurora::UI::MainWindow::chain->GetBuffer(2, IID_PPV_ARGS(&tr)) == S_OK)
                                                {
                                                    Aurora::UI::MainWindow::device->CreateRenderTargetView(tr, 0, cdh);
                                                    Aurora::UI::MainWindow::backbuffers[2] = tr;
                                                    tr->Release();
                                                    cdh.Offset(descriptorsize);
                                                    if(Aurora::UI::MainWindow::device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&Aurora::UI::MainWindow::coallocators[0])) == S_OK)
                                                    {
                                                        if(Aurora::UI::MainWindow::device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&Aurora::UI::MainWindow::coallocators[1])) == S_OK)
                                                        {
                                                            if(Aurora::UI::MainWindow::device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&Aurora::UI::MainWindow::coallocators[2])) == S_OK)
                                                            {
                                                                if(Aurora::UI::MainWindow::device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, Aurora::UI::MainWindow::coallocators[Aurora::UI::MainWindow::BackBufferIndex], 0, IID_PPV_ARGS(&Aurora::UI::MainWindow::colist)) == S_OK)
                                                                {
                                                                    if(Aurora::UI::MainWindow::colist->Close() == S_OK)
                                                                    {
                                                                        if(Aurora::UI::MainWindow::device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&Aurora::UI::MainWindow::fence)) == S_OK)
                                                                        {
                                                                            Aurora::UI::MainWindow::fenceevent = CreateEvent(0, 0, 0, 0);
                                                                            if(Aurora::UI::MainWindow::fenceevent)
                                                                            {
                                                                                Aurora::Engine::Behaviour::Start();
                                                                                MSG message = {};
                                                                                while (!Aurora::UI::MainWindow::Exit)
                                                                                {
                                                                                    if(GetMessageW(&message, 0, 0, 0) == -1)
                                                                                        Aurora::UI::MainWindow::Exit = true;
                                                                                    else
                                                                                    {
                                                                                        TranslateMessage(&message);
                                                                                        DispatchMessage(&message);
                                                                                    }
                                                                                }
                                                                                Aurora::Engine::Behaviour::Finish();
                                                                                ++Aurora::UI::MainWindow::fencevalue;
                                                                                if(Aurora::UI::MainWindow::queue->Signal(Aurora::UI::MainWindow::fence, Aurora::UI::MainWindow::fencevalue) == S_OK)
                                                                                    if(Aurora::UI::MainWindow::fence->GetCompletedValue() < Aurora::UI::MainWindow::fencevalue)
                                                                                        if(Aurora::UI::MainWindow::fence->SetEventOnCompletion(Aurora::UI::MainWindow::fencevalue, Aurora::UI::MainWindow::fenceevent) == S_OK)
                                                                                            WaitForSingleObject(Aurora::UI::MainWindow::fenceevent, 1000u);
                                                                                CloseHandle(Aurora::UI::MainWindow::fenceevent);
                                                                            }
                                                                            Aurora::UI::MainWindow::fence->Release();
                                                                        }
                                                                    }
                                                                    Aurora::UI::MainWindow::colist->Release();
                                                                }
                                                                Aurora::UI::MainWindow::coallocators[2]->Release();
                                                            }
                                                            Aurora::UI::MainWindow::coallocators[1]->Release();
                                                        }
                                                        Aurora::UI::MainWindow::coallocators[0]->Release();
                                                    }
                                                    Aurora::UI::MainWindow::backbuffers[2]->Release();
                                                }
                                                Aurora::UI::MainWindow::backbuffers[1]->Release();
                                            }
                                            Aurora::UI::MainWindow::backbuffers[0]->Release();
                                        }
                                        Aurora::UI::MainWindow::heap->Release();
                                    }
                                    Aurora::UI::MainWindow::chain->Release();
                                }
                                else
                                {
                                    chain1->Release();
                                    factory->Release();
                                }
                            }
                            else
                            {
                                chain1->Release();
                                factory->Release();
                            }
                        }
                        else
                            factory->Release();
                    }
                    Aurora::UI::MainWindow::queue->Release();
                }
                Aurora::UI::MainWindow::device->Release();
            }
            DestroyWindow(h);
        }
        UnregisterClassW(L"AuroraMainWindow", hInst);
    }
    return 0;
}
#endif