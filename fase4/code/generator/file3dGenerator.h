#ifndef FILE3D_H
#define FILE3D_H
using namespace std;
#include <vector>
#include <string> 
#include <iostream>
#include <sstream>
#include <cstring>
#include <fstream>

char* generateChar(const string& str, const float* arr, int size);

void vectorTo3dFile(vector<float> pontos,vector<float> normais,vector<float> texture, char* filepath);

#endif