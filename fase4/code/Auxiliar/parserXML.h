#ifndef PARSERXML_H
#define PARSERXML_H

#include "group.h"
#include "../../tinyxml/tinystr.h"
#include "../../tinyxml/tinyxml.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;


int LoadXML(const char* file,int* widht,int* height,Camera* cam, vector<Group>* group_vector, vector<Light>* light_vector, vector<file3d>* arr_file);

#endif
