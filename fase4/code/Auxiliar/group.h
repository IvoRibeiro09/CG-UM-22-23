#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include <string>
#include <GL/glew.h>
#include <IL/il.h>
using namespace std;

struct file3d {
	string filename;
	vector<float> pontos;
	vector<float> normais;
	vector<float> pontos_t;
};

struct Camera {
	float posX, posY, posZ;
	float lookX, lookY, lookZ;
	float camX, camY, camZ;
	float fov, near, far;
	float oldX = 5, oldZ = 5, atualX = 5, atualZ = 5, raio = 5.0f;
	float alfa = 0.0f, beta = 0.0f;
};

struct RGB {
	int Red;
	int Green;
	int Blue;
};

struct Color {
	RGB diffuse;
	RGB ambient;
	RGB specular;
	RGB emissive;
	int shininess;
};

struct Point {
	float X;
	float Y;
	float Z;
};

struct Angle_Point {
	float angulo;
	float X;
	float Y;
	float Z;
};

struct Light {
	Point point_pos;
	Point direc_dir;
	Point spot_pos;
	Point spot_dir;
	int spot_cutoff;
};

struct Group {
	std::vector<Point> translate;
	std::vector<Angle_Point> rotate_a;
	std::vector<Angle_Point> rotate_t;
	std::vector<Point> scale;
	int align;
	std::vector<Point> matriz;
	float time_translate;
	Color color;
	int file_PosOnArray;
	GLuint vbo[3];
	GLsizei nvertices;
	std::string textura_str;
	unsigned int ti, width, height;
	ILuint texID;
	std::vector<Group> sub_group;
};

Point set_Point(float x, float y, float z);

Angle_Point set_Angle_Point(float x, float y, float z, float angle);

RGB set_RGB(int red, int green, int blue);

Color set_Color(RGB dif, RGB amb, RGB spec, RGB emiss, int shini);

#endif // GROUP_H