#include "mtfv.h"
#include <Windows.h>

namespace mtfv
{
	void Texture::LoadTexture(std::string Path, unsigned char* data, unsigned int rowPitch)
	{
		FILE *fp = NULL;

		if ((fp = fopen(Path.data(), "rb")) == NULL)//ファイルが開けるか検証
		{
			MessageBox(NULL, "LOADファイルを開けませんでした", "ロードエラー", MB_OK);
			return;//開けなかったら帰る
		}
		fread(&this->Height, sizeof(int), 1, fp);//高さを読み込み
		fread(&this->Width, sizeof(int), 1, fp);//幅を読み込み
		if (data == NULL)
		{
			fclose(fp);
			return;
		}
		this->Data.resize(this->Height);//高さ分だけ一次元目の配列を広げる
		for (int i = 0; i < this->Height; i++)
		{
			this->Data[i].resize(this->Width);//幅分だけ一次元目の配列を広げる
			unsigned char *rowPtr = data;
			for (int j = 0; j < this->Width; j++)
			{
				unsigned char in[4];
				fwrite(&in, sizeof(unsigned char), 4, fp);//Color(Uchar4)を書き込む
				rowPtr = in;
				rowPtr += 4;
			}
			data += rowPitch;
		}
		fclose(fp);//ファイルを閉じる
	}
	void Texture::SaveTexture(std::string Path)
	{
		FILE *fp = NULL;

		if ((fp = fopen(Path.data(), "wb")) == NULL)//ファイルが開けるか検証
		{
			MessageBox(NULL, "SAVEファイルを開けませんでした", "ロードエラー", MB_OK);
			return;//開けなかったら帰る
		}
		fwrite(&this->Height, sizeof(int), 1, fp);//高さを書き込む
		fwrite(&this->Width, sizeof(int), 1, fp);//幅を書き込む
		for (int i = 0; i < this->Height; i++)
		{
			for (int j = 0; j < this->Width; j++)
			{
				unsigned char rowPtr[4];
				rowPtr[0] = this->Data[i][j].R;
				rowPtr[1] = this->Data[i][j].G;
				rowPtr[2] = this->Data[i][j].B;
				rowPtr[3] = this->Data[i][j].A;
				fwrite(&rowPtr, sizeof(unsigned char), 4, fp);//Color(Uchar4)を書き込む
			}
		}
		fclose(fp);//ファイルを閉じる
	}
}

