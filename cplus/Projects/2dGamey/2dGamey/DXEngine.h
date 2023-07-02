#pragma once
#include "Adapter.h"
#include "SyncedRenderer.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

class DXEngine
{
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pImmdiate;
	IDXGISwapChain* m_pSwapChain;
	ID3D11RenderTargetView* m_pRenderTargetView;
	ID3D10Blob* m_pBlob;
	
	D3D_DRIVER_TYPE m_DriverType;
	D3D_FEATURE_LEVEL m_FeatureLevel;
	UINT m_screenWidth;
	UINT m_screenHeight;
private:
protected:
	//Member Functions
	DXEngine() = default;
private:
	friend class VertexBuffer;
	friend class VertexShader;
	friend class PixelShader;
	friend class SyncedRenderer;
public:
	SyncedRenderer m_SyncedRenderer;
public:
	bool compileShader(const wchar_t* fileName, const char* shaderTarget, const char* entryPointName, void** shaderByteCode, size_t* byteCodeSize);
	void setScreenSize(UINT width, UINT height);
	void intialise(Adapter* adapter, HWND window, bool syncedRenderer = false);

	void clearRenderTarget(Vertex4 rgba = { 0.2f,0,0} );
	void setViewPort(UINT width = 0, UINT height = 0);
	void present(bool vsync);

	void setVertexBuffer(VertexBuffer* buffer);
	void setVertexShader(VertexShader* shader);
	void setPixelShader(PixelShader* shader);

	void drawTriangles(UINT vertexSize, UINT index);
	
	void release();
	void releaseCompileShader();

	Adapter* CreateAdpater();
	VertexBuffer* CreateVertexBuffer();
	VertexShader* CreateVertexShader(const void* shaderByteCode, SIZE_T ByteCodesize);
	PixelShader* CreatePixelShader(const void* shaderByteCode, SIZE_T ByteCodesize);
	
	static DXEngine* get();
	~DXEngine();
};

