#pragma once
class VertexShader
{
	ID3D11VertexShader* m_pVertexShader;
private:

	bool initialise(const void* byteCode, SIZE_T byteCodeSize);
private:
	friend class DXEngine;
public:
	VertexShader() = default;
	void release();
};

