#include "pch.h"
#include "VertexBuffer.h"
#include "DXEngine.h"

bool VertexBuffer::load(void* list_vertices, UINT size, UINT length, void* shaderByteCode, SIZE_T ByteCodeSize)
{
	if (m_pVertexBuffer) m_pVertexBuffer->Release();
	if (m_pLayout) m_pLayout->Release();

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = size * length;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	m_size = size;
	m_length = length;

	D3D11_SUBRESOURCE_DATA vertexBufferData = {};
	ZeroMemory(&vertexBufferData, sizeof(D3D11_SUBRESOURCE_DATA));

	vertexBufferData.pSysMem = list_vertices;

	auto hResult = DXEngine::get()->m_pDevice->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &m_pVertexBuffer);

	if (FAILED(hResult))
	{
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		//SEMANTIC NAME, SEEMATIC INDEX, FORMAT, INPUT SLOT ,ALIGNED BYTE OFFSET ,SLOT CLASS, STEP RATE
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
	};

	UINT layoutSize = static_cast<UINT>(std::size(layout));

	DXEngine::get()->m_pDevice->CreateInputLayout(layout, layoutSize, shaderByteCode, ByteCodeSize, &m_pLayout);

	if (FAILED(hResult))
	{
		// failed creating input layout
		return false;
	}

    return true;
}

bool VertexBuffer::release()
{
    return false;
}

UINT VertexBuffer::size()
{
    return m_size;
}

UINT VertexBuffer::length()
{
    return m_length;
}
