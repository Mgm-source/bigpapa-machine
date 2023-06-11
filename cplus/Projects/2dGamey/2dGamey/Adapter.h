#pragma once
class Adapter
{
	IDXGIFactory1* m_pDXGIFactory;
	IDXGIAdapter1* m_pAdapterDXGI;
private:
	friend class DXEngine;
	friend class SyncedRenderer;
public:
	Adapter() = default;
	~Adapter() = default;

	void initalise();
	void release();
};

