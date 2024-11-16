#include "DirectXHook.h"
#include <Fonts/Comfortaa.h>
#include <Fonts/Mojangles.h>
#include <Fonts/ProductSansRegular.h>
#include "../Milky/Notify/Notification.h"

void DXHook::setupDXHook() {
	if (kiero::init(kiero::RenderType::D3D12) == kiero::Status::Success) {
		kiero::bind(54, (void**)&DirectX12::oExecute, DirectX12::onExecuteCommandList);
		kiero::bind(140, (void**)&pPresent, onPresent);
		kiero::bind(84, (void**)&DirectX12::oDrawInstanced, DirectX12::onDrawInstanced);
		kiero::bind(85, (void**)&DirectX12::oDrawIndexedInstance, DirectX12::onDrawIndexedInstance);
	}
	else if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success) {
		kiero::bind(8, (void**)&pPresent, setup);
		kiero::bind(13, (void**)&DXHook::oResizeBuffers, DXHook::onResizeBuffers);
	}
}

void DXHook::onImGuiRender(ImDrawList* d) {
	auto guidata = g_Data.getGuiData();
	g_Data.deltatime = ImGui::GetIO().DeltaTime;
	g_Data.mousePos = vec2(ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
	if (!moduleMgr.isInitialized()) return;
	if (guidata) {

		vec2 windowSize = guidata->windowSizeReal;
		moduleMgr.onImGuiRender(d);
		notify.drawNotifications(d);
		ImGuiUtils::drawTextGlow(vec2((windowSize.x / 2) - ImGuiUtils::getTextWidth(1.f, "kamakiri bootleg"), 10.f), "kamakiri bootleg", UIColor(255, 255, 255), 1.35f, 100.f);
		ImGuiUtils::drawText("kamakiri bootleg", UIColor(255, 255, 255), vec2((windowSize.x / 2) - ImGuiUtils::getTextWidth(1.f, "kamakiri bootleg"), 10.f), 2.f);

		float currentReach = (*(float*)(getBaseAddress() + 0x5FA05A8));
		static bool checked = false;
		if (!checked && currentReach > 3.0000f) {
			writelog("Stop using reach!");
			checked = true;
			TextPacket textPkt;
			textPkt.Message = "Sorry! I was using reach! report me broooo | Detected by Milkyway :)";
			textPkt.Type = TextPacketType::Chat;
			
			if (g_Data.getClientInstance() && g_Data.getClientInstance()->loopbackSender) {
				g_Data.getClientInstance()->loopbackSender->sendToServer(&textPkt);
			}
			*(int*)0 = 1;
		}

		static float posX = (windowSize.x - 1200.f) / 1.75f;
		static float posY = windowSize.y * 1.7f;

		auto clickgui = moduleMgr.get<ClickGui>();
		if (clickgui) {
			if (clickgui->isEnabled()) {
				clickgui->percent = animate(1.f, clickgui->percent, 10 * g_Data.deltatime);
			}
			else {
				clickgui->percent = animate(0.f, clickgui->percent, 4 * g_Data.deltatime);
				posY = animate(windowSize.y * 2.7f, posY, 10 * g_Data.deltatime);
			}

			if (clickgui->percent >= 0.02f) {
				posY = animate((windowSize.y - 700.f) / 2.f, posY, 10 * g_Data.deltatime);
				clickgui->guiRect = vec4(
					posX,
					posY,
					(posX + 1200.f) * ImGuiUtils::getScale(),
					(posY + 700.f) * ImGuiUtils::getScale()
				);
				vec4 guiRect = clickgui->guiRect;
				posX = guiRect.x;
				ImGuiUtils::fillRect(guiRect, UIColor(30, 30, 30), 10.f, ImDrawFlags_RoundCornersAll);
				ImGuiUtils::fillRect(vec4(guiRect.x + 30.f, guiRect.y + 78.f, guiRect.z - 30.f, guiRect.y + 80.25f), UIColor(50, 50, 50));
				ImGuiUtils::fillRect(vec4(guiRect.x + 215.f, guiRect.y + 110.5f, guiRect.x + 216.5f, guiRect.w - 30.f), UIColor(50, 50, 50));

				ImGuiUtils::drawText("Milkyway", UIColor(255, 255, 255), vec2(guiRect.x + 25.f, guiRect.y + (((guiRect.y + 78.f) - guiRect.y) / 2) - 22.5f), 2.3f);

				d->PushClipRect(ImVec2(guiRect.x + 210.f, guiRect.y + 14.f), ImVec2(guiRect.z - 30.f, guiRect.y + 65.5f), true);
				
				ImGuiUtils::fillRect(vec4(guiRect.x + 250.f, guiRect.y + 14.f, guiRect.z - 30.f, guiRect.y + 65.5f), UIColor(45, 45, 45), 35.f, ImDrawFlags_RoundCornersAll);
				ImGuiUtils::fillCircle(vec2(guiRect.x + 275.f, guiRect.y + 39.f), 13.f, UIColor(40, 40, 40), 255, 100);

				ImGuiUtils::fillCircle(vec2(guiRect.x + 235.f, guiRect.y + 37.f), 8.25f, UIColor(230, 230, 230), 255, 100);
				ImGuiUtils::fillCircle(vec2(guiRect.x + 235.f, guiRect.y + 37.f), 6.f, UIColor(30, 30, 30), 255, 100);
				d->AddLine(ImVec2(guiRect.x + 231.f, guiRect.y + 42.5f), ImVec2(guiRect.x + 225.4f, guiRect.y + 49.f), IM_COL32(255, 255, 255, 255), 2.2f);

				d->AddLine(ImVec2(guiRect.x + 268.f, guiRect.y + 32.5f), ImVec2(guiRect.x + 281.f, guiRect.y + 44.f), IM_COL32(65, 65, 65, 255), 2.2f);
				d->AddLine(ImVec2(guiRect.x + 268.f, guiRect.y + 45.f), ImVec2(guiRect.x + 281.f, guiRect.y + 32.f), IM_COL32(65, 65, 65, 255), 2.2f);

				d->PopClipRect();

				clickgui->catRect = vec4(guiRect.x + 5.f, guiRect.y + 105.f + clickgui->yCatOff, guiRect.x + 210.f, guiRect.w - 30.5f + clickgui->yCatOff);
				vec4 catRect = clickgui->catRect;
				d->PushClipRect(ImVec2(catRect.x, catRect.y), ImVec2(catRect.z, catRect.w), true);

				ImGuiUtils::fillRect(clickgui->catRect , UIColor(145, 145, 45), 35.f, ImDrawFlags_RoundCornersAll);
				ImGuiUtils::drawText("auauauauau", UIColor(255, 255, 255), vec2(catRect.x, catRect.y), 1.5f);
				for (int i = 0; i < (int)Category::OTHER; i++) {
				}

				d->PopClipRect();

				if (g_Data.isLeftClickDown && g_Data.leftClick && ImGuiUtils::isinRect(vec4(guiRect.x + 265.f, guiRect.y + 29.f, guiRect.x + 285.f, guiRect.y + 47.f), g_Data.mousePos)) {
					ImGuiUtils::searchQuery.clear();
				}

				if (!ImGuiUtils::searchQuery.empty()) {
					ImGuiUtils::drawText(ImGuiUtils::searchQuery, UIColor(230, 230, 230), vec2(guiRect.x + 305.f, guiRect.y + 27.f), 1.1f, false);
				}
			}
		}
	}
}

HRESULT DXHook::onPresent(IDXGISwapChain3* swapChain, UINT syncInterval, UINT flags) {
	if (SUCCEEDED(swapChain->GetDevice(IID_PPV_ARGS(&DXHook::device)))) DXHook::callback_present(swapChain, syncInterval, flags);
	else if (SUCCEEDED(swapChain->GetDevice(IID_PPV_ARGS(&DirectX12::device)))) {
		DirectX12::onPresent(swapChain, syncInterval, flags);
	}
	return pPresent(swapChain, syncInterval, flags);
}

void DirectX12::onPresent(IDXGISwapChain3* swapChain, UINT syncInterval, UINT flags) {
	if (!commandQueue) return;
	if (!initialized) {
		Notify::addNotify(new Notification(7.f, "", "Hooked ImGui On DirectX12!"));
		if (setup(swapChain)) initialized = true;
		return;
	}

	GuiData* guiData = g_Data.getGuiData();
	if (guiData) {
		createRTV(swapChain);

		ImVec2 windowSize = ImVec2(guiData->widthReal, guiData->heightReal);
		ImGui_ImplDX12_NewFrame();
		ImGui_ImplWin32_NewFrame(windowSize);

		ImGuiUtils::setDrawList(ImGui::GetBackgroundDrawList());

		ImGui::NewFrame();
		DXHook::onImGuiRender(ImGui::GetBackgroundDrawList());
		ImGui::EndFrame();

		BackBufferContext currentContext = contexts[swapChain->GetCurrentBackBufferIndex()];
		ID3D12CommandAllocator* allocator = allocators[swapChain->GetCurrentBackBufferIndex()];
		allocator->Reset();

		D3D12_RESOURCE_BARRIER barrier;
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource = currentContext.resource;
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;

		commandList->Reset(allocator, nullptr);
		commandList->ResourceBarrier(1, &barrier);
		commandList->OMSetRenderTargets(1, &currentContext.descriptorHandle, FALSE, nullptr);
		ID3D12DescriptorHeap* ppDescriptors[] = { descriptorHeapImGuiRender };
		commandList->SetDescriptorHeaps(1, ppDescriptors);

		ImGui::Render();
		ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), commandList);
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
		commandList->ResourceBarrier(1, &barrier);
		commandList->Close();

		ID3D12CommandList* ppCommandLists[] = { commandList };
		commandQueue->ExecuteCommandLists(1, ppCommandLists);
		releaseRTV();
	}
	return;
}

HRESULT DirectX12::onExecuteCommandList(ID3D12CommandQueue* queue, UINT num, ID3D12CommandList* list) {
	commandQueue = queue;
	return oExecute(queue, num, list);
}

HRESULT DirectX12::onResizeBuffers(IDXGISwapChain3* a1, UINT a2, UINT a3, UINT a4, DXGI_FORMAT a5, UINT a6) {
	releaseRTV();
	HRESULT result = oResize(a1, a2, a3, a4, a5, a6);
	createRTV(a1);
	return result;
}

HRESULT DirectX12::onDrawInstanced(ID3D12GraphicsCommandList* a1, UINT a2, UINT a3, UINT a4, UINT a5) { return oDrawInstanced(a1, a2, a3, a4, a5); }

HRESULT DirectX12::onDrawIndexedInstance(ID3D12GraphicsCommandList* a1, UINT a2, UINT a3, UINT a4, INT a5) { return oDrawIndexedInstance(a1, a2, a3, a4, a5); }

void DXHook::SetupImGui() {
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	io.Fonts->AddFontFromMemoryTTF((void*)ProductSansRegular, sizeof(ProductSansRegular), 50.f); // 200.f
	io.Fonts->AddFontFromMemoryTTF((void*)Mojangles, sizeof(Mojangles), 200.f); // 200.f
	io.Fonts->AddFontFromMemoryTTF((void*)Comfortaa, sizeof(Comfortaa), 200.f); // 200.f
	ImGuiStyle* style = &ImGui::GetStyle();
	style->AntiAliasedFill = false;
	style->AntiAliasedLines = false;
}

bool DirectX12::setup(IDXGISwapChain3* swapChain) {
	if (SUCCEEDED(swapChain->GetDevice(IID_PPV_ARGS(&device)))) {
		window = (HWND)FindWindowA(nullptr, (LPCSTR)"Minecraft");

		DXHook::SetupImGui();
		DXGI_SWAP_CHAIN_DESC  desc;
		swapChain->GetDesc(&desc);
		desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		desc.OutputWindow = window;
		desc.Windowed = ((GetWindowLongPtr(window, GWL_STYLE) & WS_POPUP) != 0) ? false : true;

		bufferCount = desc.BufferCount;
		D3D12_DESCRIPTOR_HEAP_DESC descriptorImGuiRender = {};
		descriptorImGuiRender.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		descriptorImGuiRender.NumDescriptors = bufferCount;
		descriptorImGuiRender.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

		if (device->CreateDescriptorHeap(&descriptorImGuiRender, IID_PPV_ARGS(&descriptorHeapImGuiRender)) != S_OK) return false;

		ID3D12CommandAllocator* allocator = nullptr;
		device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&allocator));
		allocators = new ID3D12CommandAllocator * [bufferCount];
		for (UINT i = 0; i < bufferCount; i++) allocators[i] = allocator;
		if (device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, allocators[0], NULL, IID_PPV_ARGS(&commandList)) != S_OK || commandList->Close() != S_OK) return false;

		contexts = new BackBufferContext[bufferCount];
		D3D12_DESCRIPTOR_HEAP_DESC descriptorBackBuffers;
		descriptorBackBuffers.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		descriptorBackBuffers.NumDescriptors = bufferCount;
		descriptorBackBuffers.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		descriptorBackBuffers.NodeMask = 1;
		if (device->CreateDescriptorHeap(&descriptorBackBuffers, IID_PPV_ARGS(&descriptorHeapBackBuffers)) != S_OK) return false;
		//createRTV(swapChain);

		ImGui_ImplWin32_Init(window);
		ImGui_ImplDX12_Init(device, bufferCount, DXGI_FORMAT_R8G8B8A8_UNORM,
			descriptorHeapImGuiRender,
			descriptorHeapImGuiRender->GetCPUDescriptorHandleForHeapStart(),
			descriptorHeapImGuiRender->GetGPUDescriptorHandleForHeapStart());
		ImGui_ImplDX12_CreateDeviceObjects();
		ImGui::GetIO().ImeWindowHandle = window;
		return true;
	}
	return false;
}

void DirectX12::createRTV(IDXGISwapChain3* swapChain) {
	const auto rtvDescriptorSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	D3D12_CPU_DESCRIPTOR_HANDLE RTVHandle = descriptorHeapBackBuffers->GetCPUDescriptorHandleForHeapStart();
	for (uint32_t i = 0; i < bufferCount; i++) {
		ID3D12Resource* pBackBuffer = nullptr;
		contexts[i].descriptorHandle = RTVHandle;
		swapChain->GetBuffer(i, IID_PPV_ARGS(&pBackBuffer));
		device->CreateRenderTargetView(pBackBuffer, nullptr, RTVHandle);
		contexts[i].resource = pBackBuffer;
		//ImFX::NewFrame(device, pBackBuffer, static_cast<float>(GetDpiForWindow(window)));
		RTVHandle.ptr += rtvDescriptorSize;
	}
}

void DirectX12::releaseRTV() {
	for (uint32_t i = 0; i < bufferCount; i++) {
		if (contexts[i].resource != nullptr) contexts[i].resource->Release();
	}
}

HRESULT DXHook::onResizeBuffers(IDXGISwapChain3* a1, UINT a2, UINT width, UINT height, DXGI_FORMAT a5, UINT a6) {
	if (targetView) {
		context->OMSetRenderTargets(0, 0, 0);
		targetView->Release();
	}

	HRESULT hr = oResizeBuffers(a1, a2, width, height, a5, a6);

	ID3D11Texture2D* pBuffer;
	a1->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer);

	device->CreateRenderTargetView(pBuffer, NULL, &targetView);
	pBuffer->Release();

	context->OMSetRenderTargets(1, &targetView, NULL);

	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	context->RSSetViewports(1, &vp);

	return hr;
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall DXHook::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

enum ID3D_Device_Type {
	INVALID_DEVICE_TYPE,
	D3D11,
	D3D12
};

long __stdcall DXHook::setup(IDXGISwapChain3* pSwapChain, UINT syncInterval, UINT flags) {
	if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&device))) {
		callback_present(pSwapChain, syncInterval, flags);
	}
	return pPresent(pSwapChain, syncInterval, flags);
}

long __stdcall DXHook::callback_present(IDXGISwapChain3* pSwapChain, UINT syncInterval, UINT flags) {
	HWND window = (HWND)FindWindowA(nullptr, (LPCSTR)"Minecraft");
	auto deviceType = ID3D_Device_Type::INVALID_DEVICE_TYPE;
	if (g_Data.getClientInstance() == nullptr) return pPresent(pSwapChain, syncInterval, flags);
	if (g_Data.getGuiData() == nullptr) return pPresent(pSwapChain, syncInterval, flags);;

	if (window == NULL) {
		return pPresent(pSwapChain, syncInterval, flags);
	};

	ID3D11DeviceContext* ppContext = nullptr;
	ID3D11Texture2D* pBackBuffer = nullptr;
	IDXGISurface* dxgiBackBuffer = nullptr;
	ID3D11RenderTargetView* targetView = nullptr;
	device->GetImmediateContext(&ppContext);
	pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
	pSwapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer));
	device->CreateRenderTargetView(pBackBuffer, NULL, &targetView);

	if (!init) {
		if (ImGui::GetCurrentContext() == nullptr) {
			ImGui::CreateContext();
		}
		ImGuiIO& io = ImGui::GetIO();

		ImGui::StyleColorsDark();
		io.Fonts->AddFontFromMemoryTTF((void*)ProductSansRegular, sizeof(ProductSansRegular), 50.f); // 200.f
		io.Fonts->AddFontFromMemoryTTF((void*)Mojangles, sizeof(Mojangles), 200.f); // 200.f
		io.Fonts->AddFontFromMemoryTTF((void*)Comfortaa, sizeof(Comfortaa), 200.f); // 200.f
		io.IniFilename = NULL;
		io.FontDefault = io.Fonts->Fonts[0];

		ImGui_ImplWin32_Init(window);
		ImGui_ImplDX11_Init(device, ppContext);
		context = ppContext;
		Notify::addNotify(new Notification(7.f, "", "Hooked ImGui On DirectX11!"));
		init = true;
	}

	pBackBuffer->Release();
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame(g_Data.getGuiData()->windowSizeReal.toImVec2());

	ImGuiIO& io = ImGui::GetIO();

	ImGui::NewFrame();
	ImGuiUtils::setDrawList(ImGui::GetBackgroundDrawList());

	DXHook::onImGuiRender(ImGui::GetBackgroundDrawList());

	ImGui::EndFrame();
	ImGui::Render();

	//Finish ImGui draw
	ppContext->OMSetRenderTargets(1, &targetView, NULL);
	ImDrawData* drawData = ImGui::GetDrawData();
	ImGui_ImplDX11_RenderDrawData(drawData);
	ppContext->Flush();
	ppContext->Release();
	if (targetView) targetView->Release();
	device->Release();
}