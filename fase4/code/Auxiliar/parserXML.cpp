#include "parserXML.h"

void parserFile(Group* p, const string& filepath, vector<file3d> *arr_file) {
	ifstream arquivo(filepath);
	string linha;

	bool found = false;
	for (int i = 0; i < arr_file->size();i++) {
		if (arr_file->at(i).filename == filepath) {
			found = true;
			p->file_PosOnArray = i;
		}
	}
	if (found == false) {
		if (arquivo.is_open()) {
			vector<float> pontos;
			vector<float> pontos_t;
			vector<float> normais;
			string palavra;
			while (getline(arquivo, linha)) {
				istringstream iss(linha);
				while (iss >> palavra) {
					pontos.push_back(stof(palavra));
				}
				getline(arquivo, linha);
				istringstream iss2(linha);
				while (iss2 >> palavra) {
					pontos_t.push_back(stof(palavra));
				}
				getline(arquivo, linha);
				istringstream iss3(linha);
				while (iss3 >> palavra) {
					normais.push_back(stof(palavra));
				}
			}
			file3d f;
			f.filename = filepath;
			f.pontos = move(pontos);
			f.pontos_t = move(pontos_t);
			f.normais = move(normais);
			arr_file->push_back(f);
			p->file_PosOnArray = arr_file->size() - 1;

			arquivo.close();
		}
		else {
			cout << "Erro ao abrir o arquivo." << endl;
		}
	}
}

void processNode(Group* planeta, TiXmlNode* pParent,vector<file3d> *arr_file) {
	if (!pParent) return;

	TiXmlNode* pChild = pParent->FirstChild();
	pChild = pParent->FirstChild("transform");
	if (pChild) {
		TiXmlNode* ptranslate = pChild->FirstChild("translate");
		while (ptranslate){
			float x, y, z, time;
			string align;
			if (ptranslate->ToElement()->QueryFloatAttribute("x", &x) == TIXML_SUCCESS &&
				ptranslate->ToElement()->QueryFloatAttribute("y", &y) == TIXML_SUCCESS &&
				ptranslate->ToElement()->QueryFloatAttribute("z", &z) == TIXML_SUCCESS){
				//std::cout << "Transformação encontrada: (" << x << ", " << y << ", " << z << ")" << std::endl;
				planeta->translate.push_back(set_Point(x,y,z));
			}
			else {
				ptranslate->ToElement()->QueryFloatAttribute("time", &time);
				bool align = false;
				const char* alignStr = ptranslate->ToElement()->Attribute("align");
				TiXmlNode* pPoint = ptranslate->FirstChild("point");
				planeta->time_translate = time;
				if (alignStr){
					align = strcmp(alignStr, "True") == 0;
				}
				planeta->align = align;

				while (pPoint) {
					float x, y, z;
					pPoint->ToElement()->QueryFloatAttribute("x", &x);
					pPoint->ToElement()->QueryFloatAttribute("y", &y);
					pPoint->ToElement()->QueryFloatAttribute("z", &z);
					//std::cout << "Point encontrado: (" << x << ", " << y << ", " << z << ")" << std::endl;
					
					planeta->matriz.push_back(set_Point(x, y, z));
					pPoint = pPoint->NextSibling("point");
				}
			}
			ptranslate = ptranslate->NextSibling("translate");
		}
		TiXmlNode* protate = pChild->FirstChild("rotate");
		while (protate) {
			float angle, time, x, y, z;
			if (protate->ToElement()->QueryFloatAttribute("angle", &angle) == TIXML_SUCCESS
				&& protate->ToElement()->QueryFloatAttribute("x", &x) == TIXML_SUCCESS
				&& protate->ToElement()->QueryFloatAttribute("y", &y) == TIXML_SUCCESS
				&& protate->ToElement()->QueryFloatAttribute("z", &z) == TIXML_SUCCESS) {
				planeta->rotate_a.push_back(set_Angle_Point(x,y,z,angle));
			}
			else {
				protate->ToElement()->QueryFloatAttribute("time", &time);
				protate->ToElement()->QueryFloatAttribute("x", &x);
				protate->ToElement()->QueryFloatAttribute("y", &y);
				protate->ToElement()->QueryFloatAttribute("z", &z);
				planeta->rotate_t.push_back(set_Angle_Point(x, y, z, time));
			}
			protate = protate->NextSibling("rotate");
		}
		TiXmlNode* pscale = pChild->FirstChild("scale");
		while (pscale) {
			float x, y, z;
			pscale->ToElement()->QueryFloatAttribute("x", &x);
			pscale->ToElement()->QueryFloatAttribute("y", &y);
			pscale->ToElement()->QueryFloatAttribute("z", &z);
			//std::cout << "Escala encontrada: (" << x << ", " << y << ", " << z << ")" << std::endl;
			planeta->scale.push_back(set_Point(x,y,z));

			pscale = pscale->NextSibling("scale");
		}
	}

	pChild = pParent->FirstChild("models");
	if (pChild) {
		TiXmlNode* pModel = pChild->FirstChild("model");
		while (pModel) {
			std::cout << "Modelo encontrado: " << pModel->ToElement()->Attribute("file") << std::endl;

			parserFile(planeta, pModel->ToElement()->Attribute("file"), arr_file);

			TiXmlNode* pTexture = pModel->FirstChild("texture");
			if (pTexture) {
				std::cout << "Textura encontrada: " << pTexture->ToElement()->Attribute("file") << std::endl;
				planeta->textura_str = pTexture->ToElement()->Attribute("file");

			}
			TiXmlNode* pColor = pModel->FirstChild("color");
			if (pColor) {
				int r, b, g;
				TiXmlNode* diffuse = pColor->FirstChild("diffuse");
				diffuse->ToElement()->QueryIntAttribute("R", &r);
				diffuse->ToElement()->QueryIntAttribute("G", &g);
				diffuse->ToElement()->QueryIntAttribute("B", &b);
				//std::cout << r << " " << g << " " << b << " " << std::endl;
				RGB dif = set_RGB(r, g, b);

				TiXmlNode* ambiente = pColor->FirstChild("ambient");
				ambiente->ToElement()->QueryIntAttribute("R", &r);
				ambiente->ToElement()->QueryIntAttribute("G", &g);
				ambiente->ToElement()->QueryIntAttribute("B", &b);
				//std::cout << r << " " << g << " " << b << " " << std::endl;
				RGB amb = set_RGB(r, g, b);

				TiXmlNode* specular = pColor->FirstChild("specular");
				specular->ToElement()->QueryIntAttribute("R", &r);
				specular->ToElement()->QueryIntAttribute("G", &g);
				specular->ToElement()->QueryIntAttribute("B", &b);
				//std::cout << r << " " << g << " " << b << " " << std::endl;
				RGB spec = set_RGB(r, g, b);

				TiXmlNode* emissive = pColor->FirstChild("emissive");
				emissive->ToElement()->QueryIntAttribute("R", &r);
				emissive->ToElement()->QueryIntAttribute("G", &g);
				emissive->ToElement()->QueryIntAttribute("B", &b);
				//std::cout << r << " " << g << " " << b << " " << std::endl;
				RGB emiss = set_RGB(r, g, b);

				int shininess = pColor->FirstChild("shininess")->ToElement()->QueryIntAttribute("value", &shininess);
				//std::cout << shininess << std::endl;
				planeta->color = set_Color(dif, amb, spec, emiss, shininess);
			}
			pModel = pModel->NextSibling("model");
		}

	}
	for (TiXmlNode* group = pParent->FirstChild("group"); group != nullptr; group = group->NextSibling("group")) {
		Group p;
		processNode(&p, group, arr_file);
		planeta->sub_group.push_back(p);
	}
}

int LoadXML(const char* file, int* width, int* height, Camera* cam, vector<Group>* group_vector, vector<Light>* light_vector, vector<file3d>* arr_file){

	TiXmlDocument doc(file);
	if (!doc.LoadFile()) {
		std::cout << "Documento invalido!!!!!!!!!!!!!!" << std::endl;
		return 0;
	}

	//window
	TiXmlElement* windowElement = doc.FirstChildElement("world")->FirstChildElement("window");
	//camera
	TiXmlElement* positionElement = doc.FirstChildElement("world")->FirstChildElement("camera")->FirstChildElement("position");
	TiXmlElement* lookAtElement = doc.FirstChildElement("world")->FirstChildElement("camera")->FirstChildElement("lookAt");
	TiXmlElement* upElement = doc.FirstChildElement("world")->FirstChildElement("camera")->FirstChildElement("up");
	TiXmlElement* projectionElement = doc.FirstChildElement("world")->FirstChildElement("camera")->FirstChildElement("projection");
	//light
	TiXmlNode* lights = doc.FirstChildElement("world")->FirstChildElement("lights")->FirstChildElement("light");
	//modelos
	TiXmlElement* groupElement = doc.FirstChildElement("world")->FirstChildElement("group");

	
	if (windowElement) {
		if (windowElement->QueryIntAttribute("width", width) == TIXML_SUCCESS &&
			windowElement->QueryIntAttribute("height", height) == TIXML_SUCCESS);
	}

	if (positionElement) {
		if (positionElement->QueryFloatAttribute("x", &cam->posX) == TIXML_SUCCESS &&
			positionElement->QueryFloatAttribute("y", &cam->posY) == TIXML_SUCCESS &&
			positionElement->QueryFloatAttribute("z", &cam->posZ) == TIXML_SUCCESS);
	}

	if (lookAtElement) {
		if (lookAtElement->QueryFloatAttribute("x", &cam->lookX) == TIXML_SUCCESS &&
			lookAtElement->QueryFloatAttribute("y", &cam->lookY) == TIXML_SUCCESS &&
			lookAtElement->QueryFloatAttribute("z", &cam->lookZ) == TIXML_SUCCESS);
	}

	if (upElement) {
		if (upElement->QueryFloatAttribute("x", &cam->camX) == TIXML_SUCCESS &&
			upElement->QueryFloatAttribute("y", &cam->camY) == TIXML_SUCCESS &&
			upElement->QueryFloatAttribute("z", &cam->camZ) == TIXML_SUCCESS);
	}

	if (projectionElement)
	{
		if (projectionElement->QueryFloatAttribute("fov", &cam->fov) == TIXML_SUCCESS &&
			projectionElement->QueryFloatAttribute("near", &cam->near) == TIXML_SUCCESS &&
			projectionElement->QueryFloatAttribute("far", &cam->far) == TIXML_SUCCESS);
	}
	
	while (lights) {
		const char* typeAttribute = lights->ToElement()->Attribute("type");
		Light luz;
		if (typeAttribute != nullptr && strcmp(typeAttribute, "point") == 0) {

			lights->ToElement()->QueryFloatAttribute("posX", &luz.point_pos.X);
			lights->ToElement()->QueryFloatAttribute("posY", &luz.point_pos.Y);
			lights->ToElement()->QueryFloatAttribute("posZ", &luz.point_pos.Z);

			//std::cout << luz.point_pos.X << " " << luz.point_pos.Y << " " << luz.point_pos.Z << " " << std::endl;
		}
		if (typeAttribute != nullptr && strcmp(typeAttribute, "directional") == 0) {

			lights->ToElement()->QueryFloatAttribute("dirX", &luz.direc_dir.X);
			lights->ToElement()->QueryFloatAttribute("dirY", &luz.direc_dir.Y);
			lights->ToElement()->QueryFloatAttribute("dirZ", &luz.direc_dir.Z);

			//std::cout << luz.direc_dir.X << " " << luz.direc_dir.Y << " " << luz.direc_dir.Z << " " << std::endl;
		}
		if (typeAttribute != nullptr && strcmp(typeAttribute, "spotlight") == 0) {

			lights->ToElement()->QueryFloatAttribute("posX", &luz.spot_pos.X);
			lights->ToElement()->QueryFloatAttribute("posY", &luz.spot_pos.Y);
			lights->ToElement()->QueryFloatAttribute("posZ", &luz.spot_pos.Z);

			lights->ToElement()->QueryFloatAttribute("dirX", &luz.spot_dir.X);
			lights->ToElement()->QueryFloatAttribute("dirY", &luz.spot_dir.Y);
			lights->ToElement()->QueryFloatAttribute("dirZ", &luz.spot_dir.Z);

			lights->ToElement()->QueryIntAttribute("cutoff", &luz.spot_cutoff);

			//std::cout << luz.spot_pos.X << " " << luz.spot_pos.Y << " " << luz.spot_pos.Z << " " << std::endl;
			//std::cout << luz.spot_dir.X << " " << luz.spot_dir.Y << " " << luz.spot_dir.Z << " " << std::endl;
			//std::cout << luz.spot_cutoff << std::endl;
		}
		light_vector->push_back(luz);
		lights = lights->NextSibling("light");
	}

	for (TiXmlNode* group = doc.FirstChildElement("world")->FirstChild("group"); group != nullptr; group = group->NextSibling("group")) {
		Group g;
		processNode(&g, group, arr_file);
		group_vector->push_back(g);
	}

	return 1;
}


