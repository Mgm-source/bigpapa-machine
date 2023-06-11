#include "pch.h"
#include "PixelShader.h"
#include "DXEngine.h"

bool PixelShader::initialise(const void* ShaderByteCode, SIZE_T ShaderSize)
{
	if (FAILED(DXEngine::get()->m_pDevice->CreatePixelShader(ShaderByteCode, ShaderSize, nullptr, &m_pPixelShader)))
	{
		return false;
	}
	return true;
}

void PixelShader::release()
{
}