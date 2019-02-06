#include "mtfv.h"
#include <Windows.h>

namespace mtfv
{
	void Texture::LoadTexture(std::string Path, unsigned char* data, unsigned int rowPitch)
	{
		FILE *fp = NULL;

		if ((fp = fopen(Path.data(), "rb")) == NULL)//�t�@�C�����J���邩����
		{
			MessageBox(NULL, "LOAD�t�@�C�����J���܂���ł���", "���[�h�G���[", MB_OK);
			return;//�J���Ȃ�������A��
		}
		fread(&this->Height, sizeof(int), 1, fp);//������ǂݍ���
		fread(&this->Width, sizeof(int), 1, fp);//����ǂݍ���
		if (data == NULL)
		{
			fclose(fp);
			return;
		}
		this->Data.resize(this->Height);//�����������ꎟ���ڂ̔z����L����
		for (int i = 0; i < this->Height; i++)
		{
			this->Data[i].resize(this->Width);//���������ꎟ���ڂ̔z����L����
			unsigned char *rowPtr = data;
			for (int j = 0; j < this->Width; j++)
			{
				unsigned char in[4];
				fwrite(&in, sizeof(unsigned char), 4, fp);//Color(Uchar4)����������
				rowPtr = in;
				rowPtr += 4;
			}
			data += rowPitch;
		}
		fclose(fp);//�t�@�C�������
	}
	void Texture::SaveTexture(std::string Path)
	{
		FILE *fp = NULL;

		if ((fp = fopen(Path.data(), "wb")) == NULL)//�t�@�C�����J���邩����
		{
			MessageBox(NULL, "SAVE�t�@�C�����J���܂���ł���", "���[�h�G���[", MB_OK);
			return;//�J���Ȃ�������A��
		}
		fwrite(&this->Height, sizeof(int), 1, fp);//��������������
		fwrite(&this->Width, sizeof(int), 1, fp);//������������
		for (int i = 0; i < this->Height; i++)
		{
			for (int j = 0; j < this->Width; j++)
			{
				unsigned char rowPtr[4];
				rowPtr[0] = this->Data[i][j].R;
				rowPtr[1] = this->Data[i][j].G;
				rowPtr[2] = this->Data[i][j].B;
				rowPtr[3] = this->Data[i][j].A;
				fwrite(&rowPtr, sizeof(unsigned char), 4, fp);//Color(Uchar4)����������
			}
		}
		fclose(fp);//�t�@�C�������
	}
}

