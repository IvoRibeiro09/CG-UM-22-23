#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

float angulo = 35*M_PI/180;
float a2 = 40 * M_PI / 180;


void drawSphere(float radius, int slices, int stacks)
{
    const float deltaTheta = M_PI / stacks;
    const float deltaPhi = 2 * M_PI / slices;

    for (int i = 0; i < stacks; i++)
    {
        const float theta1 = i * deltaTheta;
        const float theta2 = (i + 1) * deltaTheta;

        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= slices; j++)
        {
            const float phi = j * deltaPhi;

            const float x1 = radius * sin(theta1) * cos(phi);
            const float y1 = radius * sin(theta1) * sin(phi);
            const float z1 = radius * cos(theta1);

            const float x2 = radius * sin(theta2) * cos(phi);
            const float y2 = radius * sin(theta2) * sin(phi);
            const float z2 = radius * cos(theta2);

            glVertex3f(x2, y2, z2);
            glVertex3f(x1, y1, z1);
        }
        glEnd();
    }
}



void drawCone(float radius, float height, int slices, int stacks) {
	for (int i = 0; i < slices; i++) {
		float angulo = 2 * M_PI * i / slices;
		float angulo2 = 2 * M_PI * (i + 1) / slices;

		glBegin(GL_TRIANGLES);

		//  base
		glVertex3f(0.0, -height / 2, 0.0);
		glVertex3f(radius * sin(angulo2), -height / 2, radius * cos(angulo2));
		glVertex3f(radius * sin(angulo), -height / 2, radius * cos(angulo));
		glEnd();

		//lados
		for (int j = 1; j <= stacks; j++) 
		{
			//tamanho da particao
			float part1 = (float)j / stacks;



			float part2 = (float)(j - 1) / stacks;



			float y1 = -height / 2 + part1 * height;
			float y2 = -height / 2 + part2 * height;
			float raio1 = radius * (1 - part1);
			float raio2 = radius * (1 - part2);

			glBegin(GL_TRIANGLES);

			//triangulo com a base em cima
			glVertex3f(raio1 * sin(angulo), y1, raio1 * cos(angulo));
			glVertex3f(raio2 * sin(angulo), y2, raio2 * cos(angulo));
			glVertex3f(raio2 * sin(angulo2), y2, raio2 * cos(angulo2));


			//triangulo com  a base em baixo
			glVertex3f(raio2 * sin(angulo2), y2, raio2 * cos(angulo2));
			glVertex3f(raio1 * sin(angulo2), y1, raio1 * cos(angulo2));
			glVertex3f(raio1 * sin(angulo), y1, raio1 * cos(angulo));
			glEnd();
		}
	}
}

void plane(float X1, float X2, float Y1, float Y2, float Z1, float Z2, int length) {
	glBegin(GL_TRIANGLES);
		glVertex3f(X1 * length, Y1 * length, Z1 * length);
		glVertex3f(X1 * length, Y2 * length, Z2 * length);
		glVertex3f(X2 * length, Y2 * length, Z1 * length);
		
		glVertex3f(X2 * length, Y2 * length, Z2 * length);
		glVertex3f(X2 * length, Y1 * length, Z1 * length);
		glVertex3f(X1 * length, Y1 * length, Z2 * length);
	glEnd();

}

void drawBox(int length, int side) {

	if (side % 2 != 0) {
		float w = (side / 2) + 0.5;
		for (int j = -(side / 2); j <= (side / 2); j++) {
			for (int i = -(side / 2); i <= (side / 2); i++) {
				glColor3f(1.0f, 1.0f, 1.0f); //branco
				plane((0.5 + i), (-0.5 + i), -w,-w, (-0.5 + j), (0.5 + j),length);//baixo
				glColor3f(1.0f, 1.0f, 0.0f);//amarelo
				plane((0.5 + i), (-0.5 + i), (0.5 + j), (-0.5 + j), -w, -w, length); //costas
				glColor3f(1.0f, 0.5f, 0.5f);//rosa
				plane(-w, -w, (0.5 + i), (-0.5 + i), (0.5 + j), (-0.5 + j), length);//lado esquerdo
				glColor3f(1.0f, 1.0f, 1.0f); //branco
				plane((-0.5 + i), (0.5 + i), w, w, (-0.5 + j), (0.5 + j), length);//cima
				glColor3f(0.5f, 0.5f, 0.5f);//amarelo
				plane((-0.5 + i), (0.5 + i), (0.5 + j), (-0.5 + j), w, w, length); //frente
				glColor3f(1.0f, 0.5f, 0.5f);//rosa
				plane(w,w,(-0.5 + i), (0.5 + i), (0.5 + j), (-0.5 + j), length); //lado direito
			}
		}
		
	}
	else if (side % 2 == 0) {
		float w = (side / 2) ;
		for (int j = -(side / 2) + 1; j < (side / 2); j++) {
			for (int i = -(side / 2) + 1 ; i < (side / 2); i++) {
				glColor3f(1.0f, 1.0f, 1.0f); //branco
				plane((1 + i), (-1 + i), -w, -w, (-1 + j), (1 + j), length);//baixo
				glColor3f(1.0f, 1.0f, 0.0f);//amarelo
				plane((1 + i), (-1 + i), (1 + j), (-1 + j), -w, -w, length); //costas
				glColor3f(1.0f, 0.5f, 0.5f);//rosa
				plane(-w, -w, (1 + i), (-1 + i), (1 + j), (-1 + j), length);//lado esquerdo
				glColor3f(1.0f, 1.0f, 1.0f); //branco
				plane((-1 + i), (1 + i), w, w, (-1 + j), (1 + j), length);//cima
				glColor3f(0.5f, 0.5f, 0.5f);//amarelo
				plane((-1 + i), (1 + i), (1 + j), (-1 + j), w, w, length); //frente
				glColor3f(1.0f, 0.5f, 0.5f);//rosa
				plane(w, w, (-1 + i), (1+ i), (1 + j), (-1 + j), length); //lado direito
			}
		}
	}
}






void drawPlane(int length, int divisions) {

	if (divisions % 2 != 0) {
		for (int j = -(divisions / 2); j <= (divisions / 2); j++) {
			for (int i = -(divisions / 2); i <= (divisions / 2); i++) {
				glBegin(GL_TRIANGLES);
				glColor3f(1.0f, 1.0f, 0.0f);//amarelo
				glVertex3f((-0.5 + i) * length, 0.0f, (0.5 + j) * length);
				glVertex3f((0.5 + i) * length, 0.0f, (0.5 + j) * length);
				glVertex3f((0.5 + i) * length, 0.0f, (-0.5 + j) * length);

				glColor3f(1.0f, 1.0f, 1.0f); //branco
				glVertex3f((0.5 + i) * length, 0.0f, (-0.5 + j) * length);
				glVertex3f((-0.5 + i) * length, 0.0f, (-0.5 + j) * length);
				glVertex3f((-0.5 + i) * length, 0.0f, (0.5 + j) * length);

				glEnd();
			}
		}
	}
	else if (divisions % 2 == 0) {
		for (int j = -(divisions / 2); j < (divisions / 2); j++) {
			for (int i = -(divisions / 2); i < (divisions / 2); i++) {
				glBegin(GL_TRIANGLES);
				glColor3f(1.0f, 1.0f, 0.0f);//amarelo
				glVertex3f((i)*length, 0.0f, (j + 1) * length);
				glVertex3f((1 + i) * length, 0.0f, (j + 1) * length);
				glVertex3f((1 + i) * length, 0.0f, (j)*length);

				glColor3f(1.0f, 1.0f, 1.0f); //branco
				glVertex3f((1 + i) * length, 0.0f, (j)*length);
				glVertex3f((i)*length, 0.0f, (j)*length);
				glVertex3f((i)*length, 0.0f, (j + 1) * length);

				glEnd();
			}
		}
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


void drawCylinder(float radius, float height, int slices) {

// put code to draw cylinder in here
	
	
	for (int i = 0;i < slices;i++) {
		float ang = i * 2 * M_PI / slices;
		float aux = (i+1) * 2 * M_PI / slices;
		
		
		glBegin(GL_TRIANGLES);
		// X axis in red
		glColor3f(1.0f, 0.0f, 0.0f);

		//face de cima
		glVertex3f(0.0f, height/2, 0.0f);
		glVertex3f(radius*sin(ang), height/2, radius*cos(ang));
		glVertex3f(radius * sin(aux), height/2, radius * cos(aux));
		glEnd();
		 

		glColor3f(1.0f, 1.0f, 1.0f);
		
		//um triangulo da face lateral
		glBegin(GL_TRIANGLES);
		glVertex3f(radius * sin(ang), -height / 2, radius * cos(ang));
		glVertex3f(radius * sin(aux),- height / 2, radius * cos(aux));
		glVertex3f(radius * sin(aux), height / 2, radius * cos(aux));
		glEnd();

		//um triangulo da face lateral
		glBegin(GL_TRIANGLES);
		glVertex3f(radius * sin(aux), height / 2, radius * cos(aux));
		glVertex3f(radius * sin(ang), height / 2, radius * cos(ang));
		glVertex3f(radius * sin(ang), -height / 2, radius * cos(ang));
		
		glEnd();

		



		//face de baixo 
		glBegin(GL_TRIANGLES);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, -height/2, 0.0f);
		glVertex3f(radius * sin(aux), -height/2, radius * cos(aux));
		glVertex3f(radius * sin(ang), -height/2, radius * cos(ang));
		glEnd();


	}
}


void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(10 * cos(angulo) * sin(a2), 10 * sin(angulo), 10 * cos(angulo) * cos(a2),
		      0.0f, 0.0f, 0.0f,
			  0.0f,1.0f,0.0f);

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



	//drawPlane(10, 10);
	//drawCylinder(1,2,50);
	//drawBox(1, 5);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawCone(1, 2, 4, 3);
	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

}


void processSpecialKeys(int key, int xx, int yy) {

	switch (key) {
	case GLUT_KEY_UP:
		if (angulo < M_PI/2){
			angulo += 0.1;
		}
		break;
	case GLUT_KEY_DOWN:
		if (angulo > -M_PI / 2) {
			angulo -= 0.1;
		}
		break;
	case GLUT_KEY_LEFT:
		a2 -= 0.1;
		break;
	case GLUT_KEY_RIGHT:
		a2 += 0.1;
		break;

	}
	glutPostRedisplay();

}


int main(int argc, char **argv) {
	/*
	if (argc <= 3)
		{
			printf( "Not enough arguments provided");
			
		}
		if (strcmp("box", argv[1]) == 0)
		{
			float size = atof(argv[2]);
			float divisions = atof(argv[3]);
		
		
		}
		else if (strcmp("plane", argv[1]) == 0)
		{
			float size = atof(argv[2]);
			float divisions = atof(argv[3]);
		}

		else if (strcmp("sphere", argv[1]) == 0)
		{
			if (argc == 4)
			{
				printf("Not enough arguments for the sphere");
				return -1;
			}
			float radius = atof(argv[2]);
			int slices = atoi(argv[3]);
			int stacks = atoi(argv[4]);
		
			
		}

		else if (strcmp("cone", argv[1]) == 0)
		{
			printf("cone");
			float radius = atof(argv[2]);
			float height = atof(argv[3]);
			int slices = atoi(argv[4]);
			int stacks = atoi(argv[5]);

	
		}
		else
		{	
			printf("Shape does not exist!\n");
		}
	
	*/


// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
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
