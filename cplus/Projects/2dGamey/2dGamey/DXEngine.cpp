#include "pch.h"
#include <d3dcompiler.h>
#include "DXEngine.h"


Adapter* DXEngine::CreateAdpater()
{
	return new Adapter;
}

VertexBuffer* DXEngine::CreateVertexBuffer()
{
	return new VertexBuffer;
}

VertexShader* DXEngine::CreateVertexShader(const void* shaderByteCode, SIZE_T ByteCodesize)
{
	VertexShader* vertexShader = new VertexShader;
	if(vertexShader->initialise(shaderByteCode, ByteCodesize))
		return vertexShader;
	vertexShader->release();
	return nullptr;
}

PixelShader* DXEngine::CreatePixelShader(const void* shaderByteCode, SIZE_T ByteCodesize)
{
	PixelShader* pixelShader = new PixelShader;
	if (pixelShader->initialise(shaderByteCode, ByteCodesize))
		return pixelShader;
	pixelShader->release();
	return nullptr;
}

void DXEngine::drawTriangles(UINT vertexSize, UINT index)
{
	m_pImmdiate->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pImmdiate->Draw(vertexSize, index);
}

DXEngine::~DXEngine()
{
	release();
}

bool DXEngine::compileShader(const wchar_t* fileName, const char* shaderTarget, const char* entryPointName, void** shaderByteCode, size_t* byteCodeSize)
{
	ID3D10Blob* errorBlob = nullptr;

	if (FAILED(D3DCompileFromFile(fileName, nullptr, nullptr, entryPointName, shaderTarget, 0, 0, &m_pBlob, &errorBlob)))
	{
		if (errorBlob) errorBlob->Release();
		return false;
	}

	*shaderByteCode = m_pBlob->GetBufferPointer();
	*byteCodeSize = m_pBlob->GetBufferSize();

	return true;
}

void DXEngine::releaseCompileShader()
{
	if (m_pBlob) m_pBlob->Release();
}

void DXEngine::setScreenSize(UINT width, UINT height)
{
	m_screenHeight = height;
	m_screenWidth = width;
}

void DXEngine::intialise(Adapter* adapter, HWND window, bool syncedRenderer)
{
	// initalising D3D11

	UINT createDeviceFlags = 0;

#ifdef _DEBUG 
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[]
	{		D3D_DRIVER_TYPE_HARDWARE
	    ,   D3D_DRIVER_TYPE_UNKNOWN
		,	D3D_DRIVER_TYPE_WARP
		,	D3D_DRIVER_TYPE_REFERENCE
	};

	UINT numDriverTypes = static_cast<UINT>(std::size(driverTypes));

	D3D_FEATURE_LEVEL featureLevels[]
	{
		 D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0
		,D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_10_1
		,D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_10_0
	};

	UINT numFeatureLevel = static_cast<UINT>(std::size(featureLevels));

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = m_screenWidth;
	swapChainDesc.BufferDesc.Height = m_screenHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = window;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT hResult = 0;

	for (size_t i = 0; i < numDriverTypes; i++)
	{
		hResult = D3D11CreateDeviceAndSwapChain(adapter ? adapter->m_pAdapterDXGI : nullptr , driverTypes[i], nullptr, createDeviceFlags,
			featureLevels, numFeatureLevel, D3D11_SDK_VERSION, &swapChainDesc, &m_pSwapChain, &m_pDevice, &m_FeatureLevel, &m_pImmdiate);

		if (SUCCEEDED(hResult))
		{
			m_DriverType = driverTypes[i];
			break;
		}
		else
		{
			std::string message = std::system_category().message(hResult);
			// logger failed to create device and swapchain
		}
	}

	if (syncedRenderer)
	{
		m_SyncedRenderer.initialise(adapter, m_pDevice, m_screenWidth,m_screenHeight);
	}

	ID3D11Texture2D* backBuffer = 0;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));

	hResult = m_pDevice->CreateRenderTargetView(backBuffer, nullptr, &m_pRenderTargetView);

	// grab the debug interface 

	if (FAILED(hResult))
	{
		// logger 
	}

	backBuffer->Release();
}

void DXEngine::release()
{
	m_pDevice->Release();
	m_pImmdiate->Release();
	m_pSwapChain->Release();
	m_pRenderTargetView->Release();
}

void DXEngine::clearRenderTarget(Vertex4 rgba)
{
	m_pImmdiate->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);

	FLOAT clearColour[] = { rgba.colour.x,rgba.colour.y,rgba.colour.z,rgba.colour.w };
	m_pImmdiate->ClearRenderTargetView(m_pRenderTargetView, clearColour);;

}

void DXEngine::present(bool sync)
{
	m_pSwapChain->Present(sync, 0);
}

DXEngine* DXEngine::get()
{
	static DXEngine engine;
	return &engine;
}

void DXEngine::setVertexBuffer(VertexBuffer* buffer)
{
	UINT offset = 0;
	m_pImmdiate->IASetVertexBuffers(0, 1, &buffer->m_pVertexBuffer, &buffer->m_size, &offset);
	m_pImmdiate->IASetInputLayout(buffer->m_pLayout);
}

void DXEngine::setVertexShader(VertexShader* shader)
{
	m_pImmdiate->VSSetShader(shader->m_pVertexShader, nullptr, 0);
}

void DXEngine::setPixelShader(PixelShader* shader)
{
	m_pImmdiate->PSSetShader(shader->m_pPixelShader, nullptr, 0);
}

void DXEngine::setViewPort(UINT width, UINT height)
{
	if (width > 0 && height > 0)
	{
		m_screenWidth = width;
		m_screenHeight = height;
	}
	// ViewPort 
	D3D11_VIEWPORT viewPort = {};
	viewPort.Width = static_cast<float>(m_screenWidth);
	viewPort.Height = static_cast<float>(m_screenHeight);
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;

// Bind viewPort
	m_pImmdiate->RSSetViewports(1, &viewPort);
}
