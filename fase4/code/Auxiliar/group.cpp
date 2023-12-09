#include "group.h"


RGB set_RGB(int red, int green, int blue) {
	RGB newRGB;
	newRGB.Red = red;
	newRGB.Green = green;
	newRGB.Blue = blue;
	return newRGB;
}

Point set_Point(float x, float y, float z) {
	Point newPoint;
	newPoint.X = x;
	newPoint.Y = y;
	newPoint.Z = z;
	return newPoint;
}

Angle_Point set_Angle_Point(float x, float y, float z, float angle) {
	Angle_Point newPoint;
	newPoint.X = x;
	newPoint.Y = y;
	newPoint.Z = z;
	newPoint.angulo = angle;
	return newPoint;
}

Color set_Color(RGB dif, RGB amb, RGB spec, RGB emiss, int shini) {
	Color newColor;
	newColor.diffuse = dif;
	newColor.ambient = amb;
	newColor.specular = spec;
	newColor.emissive = emiss;
	newColor.shininess = shini;
	return newColor;
}

Light set_Light(Point pos, Point dir, Point spos, Point sdir, int spot) {
	Light newLight;
	newLight.point_pos = pos;
	newLight.direc_dir = dir;
	newLight.spot_pos = spos;
	newLight.spot_dir = sdir;
	newLight.spot_cutoff = spot;
	return newLight;
}
/*
void set_Translate(Group g, Point p) {
	g.translate.push_back(p);
}

void set_Rotate_Angle(Group g, Angle_Point p) {
	g.rotate_a.push_back(p);
}

void set_Rotate_Time(Group g, Angle_Point p) {
	g.rotate_t.push_back(p);
}

void set_Scale(Group g, Point p) {
	g.scale.push_back(p);
}

void set_Align(Group g, int align) {
	g.align = align;
}

void set_Matriz(Group g, Point p) {
	g.translate.push_back(p);
}
*/

