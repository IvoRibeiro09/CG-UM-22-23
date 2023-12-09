#include <cstdio>
#include <cstring>
#include <math.h>
#include <iostream>
#include <fstream>

int drawSphere(float radius, int slices, int stacks,char* filepath){

	std::ofstream file;
    file.open (filepath);
    if (!file.is_open()) {
        std::cout << "Erro ao abrir o arquivo." << std::endl;
        return -1;
    }

   
    const float deltaTheta = M_PI / stacks;
    const float deltaPhi = 2 * M_PI / slices;

    for (int i = 0; i < stacks; i++) {
        const float theta1 = i * deltaTheta;
        const float theta2 = (i + 1) * deltaTheta;

        for (int j = 0; j < slices; j++) {
            const float phi1 = j * deltaPhi;
            const float phi2 = (j + 1) * deltaPhi;

            const float x1 = radius * sin(theta1) * cos(phi1);
            const float y1 = radius * sin(theta1) * sin(phi1);
            const float z1 = radius * cos(theta1);

            const float x2 = radius * sin(theta2) * cos(phi1);
            const float y2 = radius * sin(theta2) * sin(phi1);
            const float z2 = radius * cos(theta2);

            const float x3 = radius * sin(theta2) * cos(phi2);
            const float y3 = radius * sin(theta2) * sin(phi2);
            const float z3 = radius * cos(theta2);

            const float x4 = radius * sin(theta1) * cos(phi2);
            const float y4 = radius * sin(theta1) * sin(phi2);
            const float z4 = radius * cos(theta1);

			file << x1 << " "<< y1 << " " << z1 <<std::endl;
			file << x2 << " "<< y2 << " " << z2 <<std::endl;
			file << x3 << " "<< y3 << " " << z3 <<std::endl;

			file << x1 << " "<< y1 << " " << z1 <<std::endl;
			file << x3 << " "<< y3 << " " << z3 <<std::endl;
			file << x4 << " "<< y4 << " " << z4 <<std::endl;
        }
    }

	file.close();
    return 0;
}


int drawBox(int length, int side,char*filepath) {

	std::ofstream file;
    file.open (filepath);


    if (!file.is_open()) 
	{
       std:: cout << "failed to open " << filepath << '\n';
       return -1;
    } 
    
	float imppar, w, limitesup, limiteinf;
	if (side % 2 != 0)
	{
		imppar = 0.5;
		w = (side / 2) + 0.5;
		limitesup = (side / 2) +1;
		limiteinf = -(side /2);
	} 
	else 
	{
		imppar = 1;
		w = (side / 2) ;
		limitesup = side/2;
		limiteinf = -(side / 2) + 1;
	}
	for (int j = limiteinf; j < limitesup; j++) 
    {
		for (int i = limiteinf; i < limitesup; i++) 
        {
				
			float X1=(imppar + i)* length , X2=(-imppar + i)* length ,Y1= -w* length ,Y2=-w* length , Z1=(-imppar + j)* length , Z2=(imppar + j)* length ;//baixo
				file << X1 << " "<< Y1 << " " << Z1 <<std::endl;
				file << X1 << " "<< Y2 << " " << Z2 << std::endl;
				file << X2 << " "<< Y2 << " " << Z1 << std::endl;
		
				file << X2 << " "<< Y2 << " " << Z2 << std::endl;
				file << X2 << " "<< Y1 << " " << Z1 << std::endl;
				file << X1 << " "<< Y1 << " " << Z2 << std::endl;
				
			X1=(imppar + i),X2= (-imppar + i), Y1=(imppar + j), Y2=(-imppar + j),Z1= -w,Z2= -w; //costas
				file <<  X1 * length << " "<< Y1 * length << " "<< Z1 * length <<std::endl;
				file <<  X1 * length << " "<< Y2 * length << " "<< Z2 * length << std::endl;
				file <<  X2 * length << " "<< Y2 * length << " "<< Z1 * length << std::endl;
		
				file <<  X2 * length << " "<< Y2 * length << " "<< Z2 * length << std::endl;
				file <<  X2 * length << " "<< Y1 * length << " "<< Z1 * length << std::endl;
				file <<  X1 * length << " "<< Y1 * length << " "<< Z2 * length << std::endl;
				
			X1=-w, X2=-w,Y1= (imppar + i),Y2= (-imppar + i),Z1= (imppar + j),Z2= (-imppar + j);//lado esquerdo
				file <<  X1 * length << " "<< Y1 * length << " "<< Z1 * length <<std::endl;
				file <<  X1 * length << " "<< Y2 * length << " "<< Z2 * length << std::endl;
				file <<  X2 * length << " "<< Y2 * length << " "<< Z1 * length << std::endl;
		
				file <<  X2 * length << " "<< Y2 * length << " "<< Z2 * length << std::endl;
				file <<  X2 * length << " "<< Y1 * length << " "<< Z1 * length << std::endl;
				file <<  X1 * length << " "<< Y1 * length << " "<< Z2 * length << std::endl;
				
			X1=(-imppar + i), X2=(imppar + i),Y1= w,Y2= w, Z1=(-imppar + j),Z2= (imppar + j);//cima
				file <<  X1 * length << " "<< Y1 * length << " "<< Z1 * length <<std::endl;
				file <<  X1 * length << " "<< Y2 * length << " "<< Z2 * length << std::endl;
				file <<  X2 * length << " "<< Y2 * length << " "<< Z1 * length << std::endl;
		
				file <<  X2 * length << " "<< Y2 * length << " "<< Z2 * length << std::endl;
				file <<  X2 * length << " "<< Y1 * length << " "<< Z1 * length << std::endl;
				file <<  X1 * length << " "<< Y1 * length << " "<< Z2 * length << std::endl;
				
			X1=(-imppar + i),X2= (imppar + i), Y1=(imppar + j),Y2= (-imppar + j),Z1= w,Z2= w; //frente
				file <<  X1 * length << " "<< Y1 * length << " "<< Z1 * length <<std::endl;
				file <<  X1 * length << " "<< Y2 * length << " "<< Z2 * length << std::endl;
				file <<  X2 * length << " "<< Y2 * length << " "<< Z1 * length << std::endl;
	
				file <<  X2 * length << " "<< Y2 * length << " "<< Z2 * length << std::endl;
				file <<  X2 * length << " "<< Y1 * length << " "<< Z1 * length << std::endl;
				file <<  X1 * length << " "<< Y1 * length << " "<< Z2 * length << std::endl;
				
			X1=w,X2=w,Y1=(-imppar + i),Y2= (imppar + i),Z1= (imppar + j),Z2= (-imppar + j); //lado direito
				file << X1 * length << " "<< Y1 * length << " "<< Z1 * length <<std::endl;
				file << X1 * length << " "<< Y2 * length << " "<< Z2 * length << std::endl;
				file << X2 * length << " "<< Y2 * length << " "<< Z1 * length << std::endl;
		
				file <<  X2 * length << " "<< Y2 * length << " "<< Z2 * length << std::endl;
				file <<  X2 * length << " "<< Y1 * length << " "<< Z1 * length << std::endl;
				file <<  X1 * length << " "<< Y1 * length << " "<< Z2 * length << std::endl;
		}
	}

    file.close();
    return 0;
}


void drawCone(float radius, float height, int slices, int stacks,char*filepath) {
	
    std::ofstream file;
    file.open (filepath);
    
    
    for (int i = 0; i < slices; i++) {
		float angulo = 2 * M_PI * i / slices;
		float angulo2 = 2 * M_PI * (i + 1) / slices;


		//  base
        file << 0.0<< " "<< -height / 2 <<" " <<0.0  <<std::endl;
        file << radius * sin(angulo2)<< " "<< -height / 2 <<" " <<radius * cos(angulo2) <<std::endl;
        file << radius * sin(angulo)<< " "<< -height / 2 <<" " <<radius * cos(angulo)  <<std::endl;
		

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

			//triangulo com a base em cima

            file << raio1 * sin(angulo)<< " "<< y1<<" " <<raio1 * cos(angulo)  <<std::endl;
            file << raio2 * sin(angulo)<< " "<< y2<<" " <<raio2 * cos(angulo)<<std::endl;
            file << raio2 * sin(angulo2)<< " "<< y2<<" " <<raio2 * cos(angulo2) <<std::endl;


            file << raio2 * sin(angulo2)<< " "<< y2<<" " <<raio2 * cos(angulo2)  <<std::endl;
            file << raio1 * sin(angulo2)<< " "<< y1<<" " <<raio1 * cos(angulo2)<<std::endl;
            file << raio1 * sin(angulo)<< " "<< y1<<" " <<raio1 * cos(angulo)<<std::endl;

		
		}
	}
    file.close();
}


void drawPlane(int length, int divisions,char*filepath) {
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


int main(int argc,char**argv){

    if ((strcmp(argv[1],"sphere")==0 ) && argc==6)
    {
        char *ficheiro = argv[5];
        
        float radius= atof(argv[2]);
        int slices=atoi(argv[3]) ;
        int stacks =atof(argv[4]);
        drawSphere(radius,slices,stacks,ficheiro);

        printf("esfera valida\n");
    }
    else if ((strcmp(argv[1],"box")==0 && argc==5))
    {
        char *ficheiro = argv[4];
        int length = atoi(argv[2]);
        int size =atoi(argv[3]);

        drawBox(length,size,ficheiro);
        printf("caixa\n");
    }
    else if ((strcmp(argv[1],"cone")==0)&& argc==7)
    {
        char *ficheiro=argv[6];
        float radius= atof(argv[2]);
        float height=atof(argv[3]);
        int slices =atoi(argv[4]);
        int stacks = atoi(argv[5]);

        drawCone(radius,height,slices,stacks,ficheiro);
        printf("cone\n");
    }
    else if ((strcmp(argv[1],"plane")==0)&& argc==5)
    {
        char *ficheiro=argv[4];
        
        int length=atoi(argv[2]);
        int  divisions=atoi(argv[3]);
       
	    drawPlane(length,divisions,ficheiro);
        printf("plano\n");
    }
}