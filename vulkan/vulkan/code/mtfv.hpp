#pragma once
#ifndef __MTFV_H__
#define __MTFV_H__

#include <vector>
#include <string>

namespace mtf
{
	class Texture
	{
	public:
		int Width;
		int Height;
		std::vector<unsigned char> Data;
		void LoadTexture(std::string Path) 
		{
			FILE* fp = NULL;
			if ((fp = fopen(Path.data(), "rb")) == NULL)//ファイルが開けるか検証
			{
				std::string out(Path + "ファイルを開けませんでした\n");
				std::cout << out.data() << "ロードエラー" <<  std::endl;
				return;//開けなかったら帰る
			}
			fread(&this->Height, sizeof(int), 1, fp);//高さを読み込み
			fread(&this->Width, sizeof(int), 1, fp);//幅を読み込み
			this->Data.resize(this->Height * this->Width * 4);//高さ分だけ一次元目の配列を広げる
			fread(this->Data.data(), sizeof(unsigned char), this->Height * this->Width * 4, fp);//Color(Uchar4)を書き込む
			fclose(fp);//ファイルを閉じる
		};
		void LoadSize(std::string Path) 
		{
			FILE* fp = NULL;

			if ((fp = fopen(Path.data(), "rb")) == NULL)//ファイルが開けるか検証
			{
				printf("ファイル(%s)が開けませんでした\n", Path.data());
				return;//開けなかったら帰る
			}
			fread(&this->Height, sizeof(int), 1, fp);//高さを読み込み
			fread(&this->Width, sizeof(int), 1, fp);//幅を読み込み
			fclose(fp);//ファイルを閉じる
		};
		void LoadData(std::string Path, unsigned char* data, unsigned int rowPitch) 
		{
			FILE* fp = NULL;

			if ((fp = fopen(Path.data(), "rb")) == NULL)//ファイルが開けるか検証
			{
				printf("ファイル(%s)が開けませんでした\n", Path.data());
				return;//開けなかったら帰る
			}
			if (data == NULL || this->Height == 0 || this->Width == 0)
			{
				fclose(fp);
				return;
			}
			fread(&this->Height, sizeof(int), 1, fp);//高さを読み込み
			fread(&this->Width, sizeof(int), 1, fp);//幅を読み込み
			for (int i = 0; i < this->Height; i++)
			{
				unsigned char* rowPtr = data;
				fread(rowPtr, 1, this->Width * 4, fp);
				data += rowPitch;
			}
			fclose(fp);//ファイルを閉じる
		};
		void SaveTexture(std::string Path) 
		{
			FILE* fp = NULL;
			if ((fp = fopen(Path.data(), "wb")) == NULL)//ファイルが開けるか検証
			{
				std::string out(Path + "ファイルを開けませんでした\n");
				std::cout << out.data() << "ロードエラー" << std::endl;
				return;//開けなかったら帰る
			}
			fwrite(&this->Height, sizeof(int), 1, fp);//高さを書き込む
			fwrite(&this->Width, sizeof(int), 1, fp);//幅を書き込む
			fwrite(this->Data.data(), sizeof(unsigned char), this->Height * this->Width * 4, fp);//Color(Uchar4)を書き込む
			fclose(fp);//ファイルを閉じる
		};
	};
}


#endif
