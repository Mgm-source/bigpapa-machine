#pragma once
class TextFactory
{
	//DirectWrite
	IDWriteTextFormat* m_pTextFormat;
	IDWriteFactory* m_pWriteFactory;

	//Direct2D Attributes
	ID2D1SolidColorBrush* m_pTextBrush;

public:
	TextFactory()= default;
	void intialise(ID2D1RenderTarget* RenderTarget, ID3D10Device1* device);
	bool release();
};