#pragma once
class VertexBuffer
{
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11InputLayout* m_pLayout;

	UINT m_size;
	UINT m_length;
private:
	friend class DXEngine;
public:
	VertexBuffer() : m_pVertexBuffer{ 0 }, m_pLayout{ 0 }, m_size{}, m_length{} {};
	bool load(void* list_vertices, UINT size, UINT length, void* shaderByteCode, SIZE_T ByteCodeSize);
	bool release();
	UINT size();
	UINT length();
};

