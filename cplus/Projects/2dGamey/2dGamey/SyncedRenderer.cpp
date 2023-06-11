#include "pch.h"
#include "SyncedRenderer.h"
#include "DXEngine.h"

bool SyncedRenderer::initialise(Adapter* adpater, ID3D11Device* Device, UINT Width, UINT Height)
{
	auto hResult = D3D10CreateDevice1(adpater->m_pAdapterDXGI, D3D10_DRIVER_TYPE_HARDWARE, NULL, D3D10_CREATE_DEVICE_DEBUG | D3D10_CREATE_DEVICE_BGRA_SUPPORT,
		D3D10_FEATURE_LEVEL_9_3, D3D10_1_SDK_VERSION, &m_pDevice1);

	D3D11_TEXTURE2D_DESC sharedTexDesc;

	ZeroMemory(&sharedTexDesc, sizeof(sharedTexDesc));

	sharedTexDesc.Width = Width;
	sharedTexDesc.Height = Height;
	sharedTexDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sharedTexDesc.MipLevels = 1;
	sharedTexDesc.ArraySize = 1;
	sharedTexDesc.SampleDesc.Count = 1;
	sharedTexDesc.Usage = D3D11_USAGE_DEFAULT;
	sharedTexDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	sharedTexDesc.MiscFlags = D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX;

	if (SUCCEEDED(hResult))
	{
		hResult = Device->CreateTexture2D(&sharedTexDesc, NULL, (ID3D11Texture2D**)&m_pSharedTex11);
	}
	else
	{
		// failed to create d3d10Device
	}

	if (FAILED(hResult))
	{
		// failed creating d2d texture
	}

	hResult = m_pSharedTex11->QueryInterface(__uuidof(IDXGIKeyedMutex), (void**)&m_pKeyedMutex11);

	if (FAILED(hResult))
	{
		// failed querying Interface
	}

	hResult = m_pSharedTex11->QueryInterface(__uuidof(IDXGIResource), (void**)&m_pSharedResource);

	if (FAILED(hResult))
	{
		// failed querying Interface
	}

	HANDLE sharedHandle;

	hResult = m_pSharedResource->GetSharedHandle(&sharedHandle);

	if (FAILED(hResult))
	{
		// failed retrieving shared handle
	}

	hResult = m_pDevice1->OpenSharedResource(sharedHandle, __uuidof(IDXGISurface1), (void**)(&m_pSharedSurface));

	if (FAILED(hResult))
	{
		// failed opening Shared Resource
	}

	hResult = m_pSharedSurface->QueryInterface(__uuidof(IDXGIKeyedMutex), (void**)&m_pKeyedMutex10);

	if (FAILED(hResult))
	{
		// failed querying Interface
	}

	hResult = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), (void**)&m_pD2DFactory);

	if (FAILED(hResult))
	{
		// failed create D2d factory
	}

	D2D1_RENDER_TARGET_PROPERTIES renderTargetProperties;

	ZeroMemory(&renderTargetProperties, sizeof(renderTargetProperties));

	renderTargetProperties.type = D2D1_RENDER_TARGET_TYPE_HARDWARE;
	renderTargetProperties.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED);

	hResult = m_pD2DFactory->CreateDxgiSurfaceRenderTarget(m_pSharedSurface, &renderTargetProperties, &m_pD2DRenderTarget);

	if (FAILED(hResult))
	{
		// failed creating Dxgi surfaceRender Target 
	}

	return true;

	m_pTextFactory.intialise(m_pD2DRenderTarget, m_pDevice1);
}

void SyncedRenderer::release()
{
}
