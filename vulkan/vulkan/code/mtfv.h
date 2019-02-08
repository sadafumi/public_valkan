//========================================================================
//	maked by sadafumi 
//	2019/2/7
//========================================================================
#pragma once
#ifndef __MTFV_H__
#define __MTFV_H__

#include <vector>
#include <string>

namespace mtfv 
{
	struct Color
	{
		unsigned char R;
		unsigned char G;
		unsigned char B;
		unsigned char A;
	};
	class Texture
	{
	public:
		int Width;
		int Height;
		std::vector<std::vector<Color>> Data;
		void LoadTexture(std::string Path, unsigned char* data, unsigned int rowPitch);
		void SaveTexture(std::string Path);
	};
}

#endif