//========================================================================
//	maked by sadafumi 
//	2019/2/7
//========================================================================
#ifndef __MFM_H__
#define __MFM_H__

#include <Windows.h>
#include <stdio.h>
#include <vector>

#define BONE_MAX (4)

namespace mfmlib
{
	struct Float3
	{
		float x;
		float y;
		float z;
	};

	struct Float2
	{
		float U;
		float V;
	};

	struct COLOR
	{
		Float3 Ambient;
		Float3 Diffuse;
		Float3 Emissive;
		Float3 Specular;
		Float3 Bump;
		float  Transparency;
		float  Shininess;
		float  Reflectivity;
	};

	struct MATRIX4D
	{
	public:
		void Set(int r, int c, float in) { Element[r][c] = in; };
		float Get(int r, int c) { return Element[r][c]; };
	private:
		float Element[4][4];
	};

	struct Weight
	{
	public:
		float weight[BONE_MAX];
		int index[BONE_MAX];//directx�ł����Ƃ���unsigned�����ǐ��̐������͂���񂩂炽�Ԃ���v
	};
	struct Material
	{
		COLOR Color;
		TCHAR pTexName[MAX_PATH];
	};


	class MATRIX
	{
	public:
		int Num;
		std::vector<MATRIX4D> Data;
	};

	class FloatData
	{
	public:
		void SetNum(float in) { Num = in; };
		float GetNum() { return Num; };
	private:
		float Num;
	};

	class Float3pData
	{
	public:
		int Num;
		std::vector<Float3> Data;
	};

	class Float2pData
	{
	public:
		int Num;
		std::vector<Float2> Data;
	};

	class Float1pData
	{
	public:
		FloatData Num;
		std::vector<float> Data;
	};

	class IntpData
	{
	public:
		int Num;
		std::vector<int> Data;
	};

	class VertexBoneWeight
	{
	public:
		int Num;
		std::vector<Weight> Data;
	};

	class BoneAnim
	{
	public:
		MATRIX4D init;
		MATRIX perFrame;
	private:
	};
	class BoneMesh
	{
	public:
		int BoneNum;
		std::vector<BoneAnim> Data;
		VertexBoneWeight VertexData;
	};

	class Mesh
	{
	public:
		//�f�[�^���o�����ꂷ��N���X�Q
		Float3pData Vertex;
		Float3pData Normals;
		Float2pData TexUV;
		IntpData Index;
		int MaterialIndex;
		int PrimitiveIndex;
	private:
	};


	class Model
	{
	public:
		int						materialNum;	//�}�e���A����
		int						MeshNum;		//���b�V����
		int						FrameNum;		//�A�j���[�V�����̃t���[����
		std::vector<Mesh>		MeshData;		//���b�V���̎��f�[�^
		std::vector<Material>	MaterialData;	//�}�e���A���̎��f�[�^
		std::vector<BoneMesh>	BoneData;

		//�f�[�^���t�@�C������o�����ꂷ��֐�
		void SetFileName(TCHAR* Filename);
		bool FileSaveMeshData();
		bool FileLoadMeshData(TCHAR* Filename);
		bool FileSaveFullData();
		bool FileLoadFullData(TCHAR* Filename);
	private:
		std::string Filename;
	};
}


#endif //__MFM_H__
