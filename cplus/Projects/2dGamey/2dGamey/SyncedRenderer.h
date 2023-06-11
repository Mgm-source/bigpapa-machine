#pragma once
#include "TextFactory.h"
class Adapter;
class SyncedRenderer
{
	ID3D10Device1* m_pDevice1;
	IDXGIKeyedMutex* m_pKeyedMutex10;
	IDXGIKeyedMutex* m_pKeyedMutex11;
	TextFactory m_pTextFactory;
	ID2D1RenderTarget* m_pD2DRenderTarget;
	ID3D11Texture2D* m_pSharedTex11;
	IDXGISurface1* m_pSharedSurface;
	ID2D1Factory* m_pD2DFactory;
	IDXGIResource* m_pSharedResource;
public:
	SyncedRenderer() = default;
	bool initialise(Adapter* adapter, ID3D11Device* m_pDevice, UINT m_screenWidth, UINT m_screenHeight);
	void release();
	
};

