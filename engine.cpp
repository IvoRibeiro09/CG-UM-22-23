#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include "tinyxml.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


float angulo = 35 * M_PI/180;
float a2 = 40 * M_PI / 180;
float posX = 0,posY = 0,posZ = 0,lookX = 0,lookY = 0,lookZ = 0,camX = 0,camY = 0,camZ = 0,fov=0,near=0,far=0;
float oldX = 5, oldZ = 5, atualX = 5, atualZ = 5, raio = 15;
std::vector<float> valores;

void draw() {
    for(int i = 0;i < valores.size() ; i+=9){
        glBegin(GL_TRIANGLES);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(valores[i], valores[i+1], valores[i+2]);
            glVertex3f(valores[i+3], valores[i+4], valores[i+5]);
            glVertex3f(valores[i+6], valores[i+7], valores[i+8]);
        glEnd();
    }
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void mouse_camera(int x, int y) {

	if (oldX < x) {
		atualX += 0.3;
	}
	else {
		atualX -= 0.3;
	}

	if (oldZ < y) {
		atualZ += 0.3;
	}
	else {
		atualZ -= 0.3;
	}

	posX = sin(atualX / 40) * cos(atualZ / 40) * raio;
	posY = sin(atualZ / 40) * raio;
	posZ = cos(atualX / 40) * cos(atualZ / 40) * raio;


	oldX = x;
	oldZ = y;
	// Force a redraw of the window
	glutPostRedisplay();
}

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();

	gluLookAt(posX, posY, posZ,
		      lookX, lookY, lookZ,
			  camX,camY,camZ);

	// clear buffers
	glBegin(GL_LINES);
	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(
		-100.0f, 0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);
	// Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -100.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);
	// Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -100.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();

	draw();
	glutMotionFunc(mouse_camera);
    
	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

}

void processSpecialKeys(int key, int xx, int yy) {

	switch (key)
    {
	case GLUT_KEY_UP:
		posY += 0.2;
		break;
	case GLUT_KEY_DOWN:
		posY -= 0.2;
		break;
	case GLUT_KEY_LEFT:
		posX -= 0.2;
		break;
	case GLUT_KEY_RIGHT:
		posX += 0.2;
		break;

	}
	glutPostRedisplay();

}

void parserFunc(std::string filepath){

    std::ifstream arquivo(filepath);
    std::string linha;
   
    if (arquivo.is_open()) 
    {
        while (getline(arquivo, linha)) 
        {
            std::stringstream ss(linha);
            std::string palavra;
                
            while (ss >> palavra)
            {
                float valor = std::stof(palavra);
                valores.push_back(valor); 
            }
        }
    
        arquivo.close();
    } else 
    {
        std::cout << "Erro ao abrir o arquivo." << std::endl;
    }
}

int main(int argc, char **argv) 
{
	TiXmlDocument doc(argv[1]);
	if (!doc.LoadFile()) 
	{
		std::cerr << "Erro ao carregar o arquivo XML.\n";
		return 1;
	}
	
	//window
	TiXmlElement* windowElement = doc.FirstChildElement("world")->FirstChildElement("window");
	//camera
	TiXmlElement* positionElement = doc.FirstChildElement("world")->FirstChildElement("camera")->FirstChildElement("position");
	TiXmlElement* lookAtElement = doc.FirstChildElement("world")->FirstChildElement("camera")->FirstChildElement("lookAt");
	TiXmlElement* upElement = doc.FirstChildElement("world")->FirstChildElement("camera")->FirstChildElement("up");
	TiXmlElement* projectionElement = doc.FirstChildElement("world")->FirstChildElement("camera")->FirstChildElement("projection");
	//modelos
	TiXmlElement* modelElement = doc.FirstChildElement("world")->FirstChildElement("group")->FirstChildElement("models")->FirstChildElement("model");

 	int width, height;
	if (windowElement) 
	{
		if (windowElement->QueryIntAttribute("width", &width) == TIXML_SUCCESS); 
		if (windowElement->QueryIntAttribute("height", &height) == TIXML_SUCCESS); 
	}

	if (positionElement) 
	{
		if (positionElement->QueryFloatAttribute("x", &posX) == TIXML_SUCCESS);
		if (positionElement->QueryFloatAttribute("y", &posY) == TIXML_SUCCESS) ;
		if (positionElement->QueryFloatAttribute("z", &posZ) == TIXML_SUCCESS);
	}

	if (lookAtElement) 
	{
        if (lookAtElement->QueryFloatAttribute("x", &lookX) == TIXML_SUCCESS);
        if (lookAtElement->QueryFloatAttribute("y", &lookY) == TIXML_SUCCESS);
        if (lookAtElement->QueryFloatAttribute("z", &lookZ) == TIXML_SUCCESS);
    }

    if (upElement) 
	{
        if (upElement->QueryFloatAttribute("x", &camX) == TIXML_SUCCESS);
        if (upElement->QueryFloatAttribute("y", &camY) == TIXML_SUCCESS);
        if (upElement->QueryFloatAttribute("z", &camZ) == TIXML_SUCCESS);
    }

	if (projectionElement) 
	{
        if (projectionElement->QueryFloatAttribute("fov", &fov) == TIXML_SUCCESS);
        if (projectionElement->QueryFloatAttribute("near", &near) == TIXML_SUCCESS);
        if (projectionElement->QueryFloatAttribute("far", &far) == TIXML_SUCCESS);
    }

	while (modelElement != nullptr) 
	{
		std::string pathname;
		if (modelElement->QueryStringAttribute("file", &pathname) == TIXML_SUCCESS);
		parserFunc(pathname);

    // iterar o proximo model
    modelElement = modelElement->NextSiblingElement("model");
	}


// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(width, height);
	glutCreateWindow("Trabalho_prático_grupo_28_CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT, GL_LINE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}