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
			if ((fp = fopen(Path.data(), "rb")) == NULL)//�t�@�C�����J���邩����
			{
				std::string out(Path + "�t�@�C�����J���܂���ł���\n");
				std::cout << out.data() << "���[�h�G���[" <<  std::endl;
				return;//�J���Ȃ�������A��
			}
			fread(&this->Height, sizeof(int), 1, fp);//������ǂݍ���
			fread(&this->Width, sizeof(int), 1, fp);//����ǂݍ���
			this->Data.resize(this->Height * this->Width * 4);//�����������ꎟ���ڂ̔z����L����
			fread(this->Data.data(), sizeof(unsigned char), this->Height * this->Width * 4, fp);//Color(Uchar4)����������
			fclose(fp);//�t�@�C�������
		};
		void LoadSize(std::string Path) 
		{
			FILE* fp = NULL;

			if ((fp = fopen(Path.data(), "rb")) == NULL)//�t�@�C�����J���邩����
			{
				printf("�t�@�C��(%s)���J���܂���ł���\n", Path.data());
				return;//�J���Ȃ�������A��
			}
			fread(&this->Height, sizeof(int), 1, fp);//������ǂݍ���
			fread(&this->Width, sizeof(int), 1, fp);//����ǂݍ���
			fclose(fp);//�t�@�C�������
		};
		void LoadData(std::string Path, unsigned char* data, unsigned int rowPitch) 
		{
			FILE* fp = NULL;

			if ((fp = fopen(Path.data(), "rb")) == NULL)//�t�@�C�����J���邩����
			{
				printf("�t�@�C��(%s)���J���܂���ł���\n", Path.data());
				return;//�J���Ȃ�������A��
			}
			if (data == NULL || this->Height == 0 || this->Width == 0)
			{
				fclose(fp);
				return;
			}
			fread(&this->Height, sizeof(int), 1, fp);//������ǂݍ���
			fread(&this->Width, sizeof(int), 1, fp);//����ǂݍ���
			for (int i = 0; i < this->Height; i++)
			{
				unsigned char* rowPtr = data;
				fread(rowPtr, 1, this->Width * 4, fp);
				data += rowPitch;
			}
			fclose(fp);//�t�@�C�������
		};
		void SaveTexture(std::string Path) 
		{
			FILE* fp = NULL;
			if ((fp = fopen(Path.data(), "wb")) == NULL)//�t�@�C�����J���邩����
			{
				std::string out(Path + "�t�@�C�����J���܂���ł���\n");
				std::cout << out.data() << "���[�h�G���[" << std::endl;
				return;//�J���Ȃ�������A��
			}
			fwrite(&this->Height, sizeof(int), 1, fp);//��������������
			fwrite(&this->Width, sizeof(int), 1, fp);//������������
			fwrite(this->Data.data(), sizeof(unsigned char), this->Height * this->Width * 4, fp);//Color(Uchar4)����������
			fclose(fp);//�t�@�C�������
		};
	};
}


#endif
