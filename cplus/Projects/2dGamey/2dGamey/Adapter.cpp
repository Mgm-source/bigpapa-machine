#include "pch.h"
#include "Adapter.h"

void Adapter::initalise()
{
	IDXGIAdapter1* Adapter = nullptr;
	auto hResult = CreateDXGIFactory1(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&m_pDXGIFactory));

	if (SUCCEEDED(hResult))
	{
		m_pDXGIFactory->EnumAdapters1(0, &m_pAdapterDXGI);;

		if (FAILED(hResult))
		{
			// logger failed to create enumarate adapters
		}
	}
	else
	{
	}
}

void Adapter::release()
{
}
