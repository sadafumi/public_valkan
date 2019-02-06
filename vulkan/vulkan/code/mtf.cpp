#include "mtf.h"
#include <Windows.h>

namespace mtf
{
	void Texture::LoadTexture(std::string Path)
	{
		FILE *fp = NULL;

		if ((fp = fopen(Path.data(), "rb")) == NULL)//�t�@�C�����J���邩����
		{
			MessageBox(NULL, "LOAD�t�@�C�����J���܂���ł���","���[�h�G���[", MB_OK);
			return;//�J���Ȃ�������A��
		}
		fread(&this->Height, sizeof(int), 1, fp);//������ǂݍ���
		fread(&this->Width, sizeof(int), 1, fp);//����ǂݍ���
		this->Data.resize(this->Height);//�����������ꎟ���ڂ̔z����L����
		for(int i = 0; i <  this->Height; i++)
		{
			this->Data[i].resize(this->Width);//���������ꎟ���ڂ̔z����L����
			for (int j = 0; j < this->Width; j++)
			{
				fread(&this->Data[i][j], sizeof(Color), 1, fp);//Color(Uchar4)��ǂݍ���
			}
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
				fwrite(&this->Data[i][j], sizeof(Color), 1, fp);//Color(Uchar4)����������
			}
		}
		fclose(fp);//�t�@�C�������
	}
}
