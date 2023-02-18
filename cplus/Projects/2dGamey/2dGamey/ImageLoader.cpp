#include "pch.h"
#include "ImageLoader.h"

 #define STB_IMAGE_IMPLEMENTATION
 #include "stb_image.h"


ImageLoader::Image::Image(ImageType Type, int x, int y, int components) : m_type{ Type }, m_width{ x }, m_height{ y }, m_components{ components }, m_pixels{ nullptr }
{
}

bool ImageLoader::Image::load(std::string fileName, int channelsWanted)
{
	m_pixels = stbi_load(fileName.c_str(), &m_width, &m_height,&m_components, channelsWanted);
	if (m_pixels) return true;
	return false;
}
