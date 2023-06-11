#include "pch.h"
#include "VertexShader.h"
#include "DXEngine.h"

bool VertexShader::initialise(const void* byteCode, SIZE_T byteCodeSize)
{
	if(FAILED(DXEngine::get()->m_pDevice->CreateVertexShader(byteCode, byteCodeSize, nullptr, &m_pVertexShader)))
	{
		return false;
	}
	return true;
}

void VertexShader::release()
{
}
