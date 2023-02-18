#pragma once

namespace ImageLoader
{
	enum class ImageType
	{
		PNG
	,	JPEG
	,	BMP
	,	GIF
	};

	class Image 
	{
		int m_width, m_height;
		int m_components;
		unsigned char* m_pixels;
	public:
		Image(ImageType Type, int x, int y, int components);
		~Image() 
		{
			if (m_pixels)
			{
				delete[] m_pixels;
			}
		}
		ImageType m_type;

		bool load(std::string fileName, int channelsWanted = 0);

		int getWidth()
		{
			return m_width;
		}

		int getHeight()
		{
			return m_height;
		}

		int getPixelComponents()
		{
			return m_components;
		}

		const unsigned char * getPixels()
		{
			return m_pixels;
		}

	};

}
