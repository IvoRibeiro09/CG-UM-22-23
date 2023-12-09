#include "file3dGenerator.h"

char* generateChar(const string& str, const float* arr, int size) {
    ostringstream oss;
    oss << str;
    for (int i = 0; i < size; i++) {
        oss << "_" << arr[i];
    }
    oss << ".3d";

    string result = oss.str();
    char* charArray = new char[result.length() + 1];
    strcpy(charArray, result.c_str());
    return charArray;
}

void vectorTo3dFile(vector<float> pontos,vector<float> normais,vector<float> texture, char* filepath){
    
    ofstream file;
    file.open (filepath);
    int i=0, j=0;
	while(i < pontos.size()){
        file << pontos[i] << " " << pontos[i+1] << " " << pontos[i+2] << endl;
        file << texture[j] << " " << texture[j+1] << endl;
        file << normais[i] << " " << normais[i+1] << " " << normais[i+2] <<endl;		
        i+=3;
        j+=2;
    }
    file.close();
}
/*
void drawPlane(int length, int divisions,char*filepath)
{
	std::ofstream file;
    file.open (filepath);
	if (divisions % 2 != 0) 
	{
		for (int j = -(divisions / 2); j <= (divisions / 2); j++) 
		{
			for (int i = -(divisions / 2); i <= (divisions / 2); i++) 
			{
				file << (-0.5 + i) * length<< " "<< 0.0f<<" " <<(0.5 + j) * length <<std::endl;
				file << (0.5 + i) * length<< " "<< 0.0f<<" " <<(0.5 + j) * length <<std::endl;
				file << (0.5 + i) * length<< " "<< 0.0f<<" " <<(-0.5 + j) * length <<std::endl;

				file << (0.5 + i) * length<< " "<< 0.0f<<" " <<(-0.5 + j) * length <<std::endl;
				file << (-0.5 + i) * length<< " "<< 0.0f<<" " <<(-0.5 + j) * length <<std::endl;
				file << (-0.5 + i) * length<< " "<< 0.0f<<" " <<(0.5 + j) * length <<std::endl;
			}
		}
	}
	else if (divisions % 2 == 0) {
		for (int j = -(divisions / 2); j < (divisions / 2); j++) {
			for (int i = -(divisions / 2); i < (divisions / 2); i++) {

				file << (i)*length<< " "<< 0.0f<<" " <<(j + 1) * length <<std::endl;
				file << (1 + i) * length<< " "<< 0.0f<<" " <<(j + 1) * length <<std::endl;
				file << (1 + i) * length<< " "<< 0.0f<<" " <<(j)*length <<std::endl;

				file << (1 + i) * length<< " "<< 0.0f<<" " <<(j)*length <<std::endl;
				file << (i)*length<< " "<< 0.0f<<" " <<(j)*length <<std::endl;
				file << (i)*length<< " "<< 0.0f<<" " <<(j + 1) * length <<std::endl;
			}
		}
	}
	file.close();
}
*/