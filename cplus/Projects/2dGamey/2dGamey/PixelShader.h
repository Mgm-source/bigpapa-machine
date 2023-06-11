#pragma once
class PixelShader
{
	ID3D11PixelShader* m_pPixelShader;
private:
	friend class DXEngine;
private:	
	bool initialise(const void* ShaderByteCode, SIZE_T ShaderSize);
public:
	PixelShader() = default;
	void release();
};

