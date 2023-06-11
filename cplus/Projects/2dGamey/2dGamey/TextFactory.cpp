#include "pch.h"
#include "TextFactory.h"

void TextFactory::intialise(ID2D1RenderTarget* RenderTarget, ID3D10Device1* device)
{
	auto hResult = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&m_pWriteFactory));

	if (SUCCEEDED(hResult))
	{
		hResult = m_pWriteFactory->CreateTextFormat(
			L"Arial",
			NULL,
			DWRITE_FONT_WEIGHT_REGULAR,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			72,
			L"en-gb",
			&m_pTextFormat
		);

		if (SUCCEEDED(hResult))
		{
			hResult = m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

			if (SUCCEEDED(hResult))
			{
				m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
			}
			else
			{
				// logger setting Paragraph Alignment failed
			}

		}
		else
		{
			// logger setting Text Aligment Failed
		}

	}
	else {
		// logger creating text format failed
	}

	hResult = RenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 0.0f, 1.0f), &m_pTextBrush);

	if (FAILED(hResult))
	{
		// failed creating text brush 
	}

	device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_POINTLIST);
}

bool TextFactory::release()
{
	return false;
}
