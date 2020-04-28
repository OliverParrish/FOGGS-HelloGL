#include "MeshLoader.h"
#include <iostream>
#include <fstream>

using namespace std;

namespace MeshLoader
{
	void LoadVertices(ifstream& inFile, Mesh& mesh);
	//void LoadColours(ifstream& inFile, Mesh& mesh);
	void LoadUVs(ifstream& inFile, Mesh& mesh);
	void LoadNormals(ifstream& inFile, Mesh& mesh);
	void LoadIndices(ifstream& inFile, Mesh& mesh);

	void LoadVertices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.VertexCount;

		if (mesh.VertexCount > 0)
		{
			mesh.Vertices = new Vertex[mesh.VertexCount];

			for (int i = 0; i < mesh.VertexCount; i++)
			{
				inFile >> mesh.Vertices[i].x;
				inFile >> mesh.Vertices[i].y;
				inFile >> mesh.Vertices[i].z;
			}
		}
	}

	void LoadUVs(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.TexCoordsCount;

		if (mesh.TexCoordsCount > 0)
		{
			mesh.TexCoords = new TexCoord[mesh.TexCoordsCount];

			for (int i = 0; i < mesh.TexCoordsCount; i++)
			{
				inFile >> mesh.TexCoords[i].u;
				inFile >> mesh.TexCoords[i].v;
			}
		}
	}

	void LoadNormals(ifstream& inFile, Mesh& mesh)
	{
		//LOAD NORMALS
		inFile >> mesh.NormalCount;

		if (mesh.NormalCount > 0)
		{
			mesh.Normals = new Vector3[mesh.NormalCount];

			for (int i = 0; i < mesh.NormalCount; i++)
			{
				inFile >> mesh.Normals[i].x;
				inFile >> mesh.Normals[i].y;
				inFile >> mesh.Normals[i].z;
			}
		}
	}

	/*void LoadColours(ifstream& inFile, Mesh& mesh)
	{
		LOAD COLOURS
		inFile >> mesh.ColorCount;

		if (mesh.ColorCount > 0)
		{
			mesh.Colors = new Color[mesh.ColorCount];

			for (int i = 0; i < mesh.ColorCount; i++)
			{
				inFile >> mesh.Colors[i].r;
				inFile >> mesh.Colors[i].g;
				inFile >> mesh.Colors[i].b;
			}
		}
	}*/

	void LoadIndices(ifstream& inFile, Mesh& mesh)
	{
		//Load Indices
		inFile >> mesh.IndexCount;

		if (mesh.IndexCount > 0)
		{
			mesh.Indices = new GLushort[mesh.IndexCount];

			for (int i = 0; i < mesh.IndexCount; i++)
			{
				inFile >> mesh.Indices[i];
			}
		}
	}


	Mesh* LoadTextured(char* path)
	{
		Mesh* mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())
		{
			cerr << "Can't open texture file " << path << endl;
			return nullptr;
		}

		//LOAD DATA USING METHODS ABOVE
		LoadVertices(inFile, *mesh);
		LoadUVs(inFile, *mesh);
		LoadNormals(inFile, *mesh);
		LoadIndices(inFile, *mesh);

		return mesh;
	}


	Mesh* MeshLoader::Load(char* path)
	{
		Mesh* mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())  
		{
			cerr  << "Can't open texture file " << path << endl;
			return nullptr;
		}

		//LOAD DATA USING METHODS ABOVE
		LoadVertices(inFile, *mesh);
	
		LoadNormals(inFile, *mesh);

		LoadUVs(inFile, *mesh);

		LoadIndices(inFile, *mesh);

		return mesh;
	}

}