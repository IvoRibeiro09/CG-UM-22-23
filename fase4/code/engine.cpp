#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <crtdbg.h>
using namespace std;
#include "Auxiliar/group.h"
#include "Auxiliar/parserXML.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <IL/il.h>

int width, height;
float Yi[3] = { 0,1,0 }, color[3] = { 1,1,1 };

Camera camera;
vector<Group> group_vector = {};
vector<Light> light_vector = {};
vector<file3d> arr_file = {};

/*void drawModel(Model m) {

	// Set model material properties
	glMaterialfv(GL_FRONT, GL_AMBIENT, m.getAmbient());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m.getDiffuse());
	glMaterialfv(GL_FRONT, GL_SPECULAR, m.getSpecular());
	glMaterialfv(GL_FRONT, GL_EMISSION, m.getEmissive());
	glMaterialf(GL_FRONT, GL_SHININESS, m.getShininess());

	// Bind points VBO
	glBindBuffer(GL_ARRAY_BUFFER, m.getPVBOInd());
	glVertexPointer(3, GL_FLOAT, 0, 0);

	// If defined, bind normals VBO
	GLuint n_vbo_ind = m.getNVBOInd();
	if (n_vbo_ind != 0) {
		glBindBuffer(GL_ARRAY_BUFFER, n_vbo_ind);
		glNormalPointer(GL_FLOAT, 0, 0);
	}

	// If defined, bind textures VBO
	GLuint t_vbo_ind = m.getTVBOInd();
	if (t_vbo_ind != 0) {
		glBindBuffer(GL_ARRAY_BUFFER, t_vbo_ind);
		glTexCoordPointer(2, GL_FLOAT, 0, 0);
		glBindTexture(GL_TEXTURE_2D, m.getTextureID());
	}

	glDrawArrays(GL_TRIANGLES, 0, m.getVerticeCount());

	glBindTexture(GL_TEXTURE_2D, 0);
}


glBindTexture(GL_TEXTURE_2D, g[j].getTexID());
	glEnable(GL_LIGHTING);
	g[j].draw();
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, 0);
*/

void renderPlaneta(Group& p) {
	
	float white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);

	glBindTexture(GL_TEXTURE_2D, p.texID);
	glBindBuffer(GL_ARRAY_BUFFER, p.vbo[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, p.vbo[1]);
	glNormalPointer(GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, p.vbo[2]);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, arr_file[p.file_PosOnArray].pontos.size()/3);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
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
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void converte() {

	camera.posX = camera.raio * cos(camera.beta) * sin(camera.alfa);
	camera.posY = camera.raio * sin(camera.beta);
	camera.posZ = camera.raio * cos(camera.beta) * cos(camera.alfa);
}

void processKeys(int key, int xx, int yy)
{
	switch (key) {

	case GLUT_KEY_RIGHT:
		camera.alfa -= 0.1; break;

	case GLUT_KEY_LEFT:
		camera.alfa += 0.1; break;

	case GLUT_KEY_UP:
		camera.beta += 0.1f;
		if (camera.beta > 1.5f)
			camera.beta = 1.5f;
		break;

	case GLUT_KEY_DOWN:
		camera.beta -= 0.1f;
		if (camera.beta < -1.5f)
			camera.beta = -1.5f;
		break;

	case GLUT_KEY_PAGE_DOWN: camera.raio -= 0.1f;
		if (camera.raio < 0.1f)
			camera.raio = 0.1f;
		break;

	case GLUT_KEY_PAGE_UP: camera.raio += 0.1f; break;
	}
	converte();
}
/*
	void processSpecialKeys(int key, int xx, int yy)
	
	if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
		switch (key) {
		case GLUT_KEY_UP:
			camera.lookY += 0.2;
			break;
		case GLUT_KEY_DOWN:
			camera.lookY -= 0.2;
			break;
		case GLUT_KEY_LEFT:
			camera.lookX -= 0.2;
			break;
		case GLUT_KEY_RIGHT:
			camera.lookX += 0.2;
			break;
		}
		glutPostRedisplay();
	}
	else {
		float stepSize = 0.2;
		float dx = camera.lookX - camera.posX;
		float dy = camera.lookY - camera.posY;
		float dz = camera.lookZ - camera.posZ;
		float magnitude = sqrt(dx * dx + dy * dy + dz * dz);
		dx /= magnitude;
		dy /= magnitude;
		dz /= magnitude;

		switch (key) {
		case GLUT_KEY_LEFT:
			camera.posX -= stepSize;
			break;
		case GLUT_KEY_RIGHT:
			camera.posX += stepSize;
			break;
		case GLUT_KEY_UP:

			camera.posX += dx * stepSize;
			camera.posY += dy * stepSize;
			camera.posZ += dz * stepSize;
			break;

		case GLUT_KEY_DOWN:

			camera.posX -= dx * stepSize;
			camera.posY -= dy * stepSize;
			camera.posZ -= dz * stepSize;
			break;
		}
		glutPostRedisplay();
	}
*/

void multMatrixVector(float* m, float* v, float* res)
{

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}
}

void getCatmullRomPoint(float t, float* p0, float* p1, float* p2, float* p3, float* pos, float* deriv) {

	// catmull-rom matrix
	float m[4][4] = { {-0.5f,  1.5f, -1.5f,  0.5f},
						{ 1.0f, -2.5f,  2.0f, -0.5f},
						{-0.5f,  0.0f,  0.5f,  0.0f},
						{ 0.0f,  1.0f,  0.0f,  0.0f} };

	// Compute A = M * P
	for (int i = 0; i < 3; i++) {
		float p[4] = { p0[i],p1[i],p2[i],p3[i] };
		float a[4];

		float* mm = (float*)m;
		multMatrixVector(mm, p, a);

		// Compute pos = T * A
		pos[i] = t * t * t * a[0] + t * t * a[1] + t * a[2] + a[3];

		// compute deriv = T' * A
		deriv[i] = 3 * t * t * t * a[0] + 2 * t * a[1] + a[2];
	}
}

// given  global t, returns the point in the curve
void getGlobalCatmullRomPoint(vector<Point> matriz, float gt, float* pos, float* deriv) {

	float t = gt * matriz.size(); // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment

	// indices store the points
	int indices[4];
	indices[0] = (index + matriz.size() - 1) % matriz.size();
	indices[1] = (indices[0] + 1) % matriz.size();
	indices[2] = (indices[1] + 1) % matriz.size();
	indices[3] = (indices[2] + 1) % matriz.size();

	float p0[3] = { matriz[indices[0]].X, matriz[indices[0]].Y , matriz[indices[0]].Z };
	float p1[3] = { matriz[indices[1]].X, matriz[indices[1]].Y , matriz[indices[1]].Z };
	float p2[3] = { matriz[indices[2]].X, matriz[indices[2]].Y , matriz[indices[2]].Z };
	float p3[3] = { matriz[indices[3]].X, matriz[indices[3]].Y , matriz[indices[3]].Z };

	getCatmullRomPoint(t, p0, p1, p2, p3, pos, deriv);
}

void renderCatmullRomCurve(float time, vector<Point> matriz) {
	// draw curve using line segments with GL_LINE_LOOP
	//gt de 0 a 1
	float gt = 0;
	float pos[3], deriv[3];

	glColor3f(0.5f, 0.5f, 0.35f);
	glBegin(GL_LINE_LOOP);
	while (gt < 1) {
		getGlobalCatmullRomPoint(matriz, gt, pos, deriv);
		glVertex3f(pos[0], pos[1], pos[2]);
		gt += 1 / time;
	}
	glEnd();
}

float calcularAngulo(float tempo)
{
	float t = glutGet(GLUT_ELAPSED_TIME) / (tempo * 1000);

	return t * 360;
}

float calcularSalto(float tempo)
{
	float t = glutGet(GLUT_ELAPSED_TIME) / (tempo * 1000);

	return t;
}

void normalize(float* a){
	float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0] / l;
	a[1] = a[1] / l;
	a[2] = a[2] / l;
}

void buildRotMatrix(float* x, float* y, float* z, float* m) {
	m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
	m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
	m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
	m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}

void cross(float* a, float* b, float* res) {
	res[0] = a[1] * b[2] - a[2] * b[1];
	res[1] = a[2] * b[0] - a[0] * b[2];
	res[2] = a[0] * b[1] - a[1] * b[0];
}


void percorrerPlanetas(Group& p)
{
	
	for (int i = 0;i < p.translate.size(); i++)
	{
		glTranslatef(p.translate[i].X, p.translate[i].Y, p.translate[i].Z);
	}
	for (int i = 0;i < p.rotate_a.size(); i++){
		glRotatef(p.rotate_a[i].angulo, p.rotate_a[i].X, p.rotate_a[i].Y, p.rotate_a[i].Z);
	}
	if (p.matriz.size() > 0){
		float pos[3], deriv[3];
		float vez = calcularSalto(p.time_translate);
		getGlobalCatmullRomPoint(p.matriz, vez, pos, deriv);
		renderCatmullRomCurve(100.0, p.matriz);
		glTranslatef(pos[0], pos[1], pos[2]);
		if (p.align == true)
		{
			glPushMatrix();
			float* Xi = deriv;
			float Zi[3];

			normalize(Xi);
			normalize(Yi);
			cross(Xi, Yi, Zi);
			cross(Zi, Xi, Yi);
			normalize(Xi);
			normalize(Yi);
			normalize(Zi);

			float m[16];

			buildRotMatrix(Xi, Yi, Zi, m);

			glMultMatrixf(m);
		}
	}
	for (int i = 0; i < p.rotate_t.size(); i++)
	{
		glRotatef(calcularAngulo(p.rotate_t[i].angulo), p.rotate_t[i].X, p.rotate_t[i].Y, p.rotate_t[i].Z);

	}
	for (int i = 0; i < p.scale.size(); i++) {
		glScalef(p.scale[i].X, p.scale[i].Y, p.scale[i].Z);
	}
	
	glColor3f(1.5, 0, 0);

	renderPlaneta(p);
	
	if (p.align == true) glPopMatrix();
	for (int i = 0; i < p.scale.size(); i++){
		glScalef(1 / p.scale[i].X, 1 / p.scale[i].Y, 1 / p.scale[i].Z);
	}
	for (auto s : p.sub_group) {
		glPushMatrix();
		percorrerPlanetas(s);
		glPopMatrix();
	}
}
/*
void mouse_camera(int x, int y) {
	static int lastX = x;
	static int lastY = y;

	int deltaX = x - lastX;
	int deltaY = y - lastY;

	float sensitivity = 0.1f;  // Sensibilidade do movimento do mouse

	// Atualizar a posição da câmera com base no movimento do mouse
	// Aqui, atualizamos as variáveis lookX e lookY de acordo com o movimento do mouse
	camera.lookX += deltaX * sensitivity;
	camera.lookY += deltaY * sensitivity;

	// Atualizar a posição do último mouse
	lastX = x;
	lastY = y;

	glutPostRedisplay();  // Redesenha a cena
}

void mouse_wheel(int button, int dir, int x, int y) {
	if (dir > 0) {
		// Aproximar do ponto onde o cursor do mouse está
		camera.posZ -= 1.0f;  // Diminuir o valor para aproximar mais rapidamente
	}
	else {
		// Afastar do ponto onde o cursor do mouse está
		camera.posZ += 1.0f;  // Aumentar o valor para afastar mais rapidamente
	}

	glutPostRedisplay();  // Redesenha a cena
}
*/

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(camera.posX, camera.posY, camera.posZ,
		camera.lookX, camera.lookY, camera.lookZ,
		camera.camX, camera.camY, camera.camZ);

	//glutMotionFunc(mouse_camera);

	for (auto s : group_vector) {
		glPushMatrix();
		percorrerPlanetas(s);
		glPopMatrix();
	}
	
	glutSwapBuffers();
}


void loadTextura(Group& p) {
	unsigned char* data;
	string path = p.textura_str;
	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	ilGenImages(1, &(p.ti));
	ilBindImage(p.ti);
	ILboolean success = ilLoadImage((ILstring)path.c_str());
	if (!success) {
		std::cout << "textura invalido!!!!!!!!!!!!!!" << std::endl;
		return;
	}
	p.width = ilGetInteger(IL_IMAGE_WIDTH);
	p.height = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	data = ilGetData();

	glGenTextures(1, &(p.texID));
	glBindTexture(GL_TEXTURE_2D, p.texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, p.width, p.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

void RenderVBO(Group& p) {
	
	glGenBuffers(1, &p.vbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, p.vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, arr_file[p.file_PosOnArray].pontos.size() * sizeof(float), arr_file[p.file_PosOnArray].pontos.data(), GL_STATIC_DRAW);
	glGenBuffers(1, &p.vbo[1]);
	glBindBuffer(GL_ARRAY_BUFFER, p.vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, arr_file[p.file_PosOnArray].normais.size() * sizeof(float), arr_file[p.file_PosOnArray].normais.data(), GL_STATIC_DRAW);
	glGenBuffers(1, &p.vbo[2]);
	glBindBuffer(GL_ARRAY_BUFFER, p.vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, arr_file[p.file_PosOnArray].pontos_t.size() * sizeof(float), arr_file[p.file_PosOnArray].pontos_t.data(), GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	loadTextura(p);

	for (auto& s : p.sub_group) {
		RenderVBO(s);
	}
}

void RenderVBOS() {
	for (auto& s : group_vector) {
		RenderVBO(s);
	}
}

void init() {
	ilInit();

	RenderVBOS();

	glEnable(GL_TEXTURE_2D);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

char* getCharPointer(const std::string& input) {
	char* cstr = new char[input.length() + 1];
	std::strcpy(cstr, input.c_str());
	return cstr;
}

int main(int argc, char** argv) {

	if (argc < 2 ) {
		std::cerr << "Argumentos em falta.\n";
		return -1;
	}
	string userInput;
	cout << "Enter a file name: ";
	getline(std::cin, userInput);
	char* charPtr = getCharPointer(userInput);

	if (LoadXML(charPtr, &width, &height, &camera, &group_vector, &light_vector, &arr_file) < 0) {
		std::cerr << "Erro ao ler o ficheiro XML.\n";
		return -1;
	}
	printf("grupos->%d\nficheiros3d->%d\n", group_vector.size(), arr_file.size());
	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	glutCreateWindow("Trabalho_prático_grupo_28_CG@DI-UM");

	//Required callback registry 
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

	//Callback registration for keyboard processing
;
	glutSpecialFunc(processKeys);

	//OpenGL settings
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//glPolygonMode(GL_FRONT, GL_LINE);
	glEnableClientState(GL_VERTEX_ARRAY);

	init();
	converte();

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}