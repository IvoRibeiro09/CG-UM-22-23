#include <cstdio>
#include <cstring>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <fstream>




struct Point 
{
    float x, y, z;
};

Point sum_p(Point p1, Point p2)
{
    Point res;
    res.x = p1.x+p2.x;
    res.y = p1.y+p2.y;
    res.z = p1.z+p2.z;

    return res;
}

Point multi_p(Point p1,float aux)
{
    Point res;
    res.x = p1.x * aux;
    res.y = p1.y * aux;
    res.z = p1.z * aux;

    return res;
}


Point getPointBezierCurve(std::vector<Point> control_p, float t)
{
    Point p1 = control_p[0];
    Point p2 = control_p[1];
    Point p3 = control_p[2];
    Point p4 = control_p[3];
    
    Point aux1 = multi_p(p1,pow(1-t,3));
    Point aux2 = multi_p(p2,(pow(1-t,2))*3*t);
    Point aux3 = multi_p(p3,(1-t)*3*pow(t,2));
    Point aux4 = multi_p(p4,pow(t,3));

    return sum_p(aux1,sum_p(aux2,sum_p(aux3,aux4)));
}


Point getPointBezierSuperficie(std::vector<Point>control_points, float t, float u)
{
    std:: vector<Point> p_internos;

    std:: vector<Point> aux;
    for(int i = 0; i< 16 ; i+=4)
    {
        aux.clear();
        aux.push_back(control_points[i]);
        aux.push_back(control_points[i+1]);
        aux.push_back(control_points[i+2]);
        aux.push_back(control_points[i+3]);

        p_internos.push_back(getPointBezierCurve(aux,t));
    }

    return (getPointBezierCurve(p_internos,u));
}


Point ** grelha (std::vector<Point>control_points,int tesse_level)
{
    float factor = (float)1/(float)tesse_level;

    Point ** res = (Point **) malloc(sizeof(Point *)*(tesse_level+1));

    int index=0;
    float t=0,u=0;

    /*
    for(int k=0;k<control_points.size();k++)
    {
        printf("%f -- %f -- %f\n",control_points[k].x,control_points[k].y,control_points[k].z);
    }
    */

    for(int i = 0; i<= tesse_level ; i++)
    {
        u=0;
        res[index++] = (Point *) malloc(sizeof(Point )*(tesse_level+1));
        for(int j = 0; j<= tesse_level ; j++)
        {
            //printf("t%f\n",t);
            //printf("u%f\n",u);
            res[i][j] = getPointBezierSuperficie(control_points,t,u);
            //printf("%f -- %f -- %f\n",res[i][j].x,res[i][j].y,res[i][j].z);
            u+=factor;
        }
        t+= factor;
    }

    return res;
}

void to_output(std::vector<Point> control_points, int tesse_level, const char* filepath)
{
    Point** gr = grelha(control_points, tesse_level);

    std::ofstream output(filepath, std::ios::app);
    for (int i = 0; i < tesse_level; i++) {  
        for (int j = 0; j < tesse_level; j++) {
            Point PA = gr[i][j];
            Point PB = gr[i][j + 1];
            Point PC = gr[i + 1][j];
            Point PD = gr[i + 1][j + 1];

            output << PA.x << " " << PA.y << " " << PA.z << std::endl;

            output << PC.x << " " << PC.y << " " << PC.z << std::endl;

            output << PD.x << " " << PD.y << " " << PD.z << std::endl;

            output << PB.x << " " << PB.y << " " << PB.z << std::endl;

            output << PC.x << " " << PC.y << " " << PC.z << std::endl;

            output << PD.x << " " << PD.y << " " << PD.z << std::endl;
        }
    }

    output.close();
}




void generate_bezier(const char* fp_points, int tessellation_value, const char* filepath) 
{
    std::ifstream input(fp_points);

    int nr_patches;
    std::vector<std::vector<int>> patches;

    int nr_control_p;
    std::vector<Point> points;
    std::string line;

    //ler o numero de patches
    std::getline(input, line);
    nr_patches = std::stoi(line);
    std::cout<<"Nr de patches: "<<nr_patches<< std::endl;

    // inicializar o vetor de patches com nr_patches elementos vazios
    patches.resize(nr_patches);

    // ler os patches do arquivo de entrada e armazená-los num vetor
    for (int i = 0; i < nr_patches; i++) 
    {
        std::getline(input, line);

        std::stringstream ss(line);
        std::string token;
        while (std::getline(ss, token, ','))
        {
            patches[i].push_back(std::stoi(token));
            std::cout<<"token patch: "<<token<< std::endl;
        }
      std::cout<<"vetor patch"<< i << " patches tamanho"<<patches[i].size()<< std::endl;
        std::cout<<"-------------------------------"<< std::endl;  
    }

    //ler o numero de pontos de controlo

    std::getline(input, line);
    nr_control_p = std::stoi(line);
    std::cout<<"Nr de pontos controlo: "<<nr_control_p<< std::endl;

    // inicializar o vetor de pontos com nr_control_p elementos vazios
    points.resize(nr_control_p);

    // ler os pontos do arquivo de entrada e armazená-los num vetor
    for (int i = 0; i < nr_control_p; i++)
    {
        std::string line;
        std::getline(input, line);
        std::stringstream ss(line);

        std::string token;
        int j = 0;
        while (std::getline(ss, token, ','))
        {
        
            double coord = std::stod(token);
            if (j == 0) 
            {
                points[i].x = coord;
            } else if (j == 1) 
            {
                points[i].y = coord;
            } else if (j == 2) 
            {
                points[i].z = coord;
            }
            j++;
        
        }
        std::cout<<"ponto: "<<" "<<points[i].x<<" "<< points[i].y<<" "<<points[i].z<< std::endl;
        std::cout<<"-------------------------------"<< std::endl;  
    }
    input.close();
    

    //grelhas por patches

    for (int i=0;i<nr_patches;i++)
    {
        std::vector<Point> aux;
        for(int j=0; j<16;j++)
        {
            aux.push_back(points[patches[i][j]]);
            //printf("%f -- %f -- %f\n",points[patches[i][j]].x,points[patches[i][j]].y,points[patches[i][j]].z);
        }
        to_output(aux,tessellation_value,filepath);
    }
}



int drawSphere(float radius, int slices, int stacks,char* filepath)
{

	std::ofstream file;
    file.open (filepath);
    if (!file.is_open()) {
        std::cout << "Erro ao abrir o arquivo." << std::endl;
        return -1;
    }

    const float deltaStacks = 1.0 / (float)stacks;
    const float deltaSlices = 1.0 / (float)slices;

   
    const float deltaTheta = M_PI / stacks;
    const float deltaPhi = 2 * M_PI / slices;

    for (int i = 0; i < stacks; i++) 
    {
        const float theta1 = i * deltaTheta;
        const float theta2 = (i + 1) * deltaTheta;

        for (int j = 0; j < slices; j++) 
        {
            const float phi1 = j * deltaPhi;
            const float phi2 = (j + 1) * deltaPhi;

            const float normalx1=sin(theta1) * cos(phi1);
            const float normaly1=sin(theta1) * sin(phi1);
            const float normalz1=cos(theta1);
            const float x1 = radius * sin(theta1) * cos(phi1);
            const float y1 = radius * sin(theta1) * sin(phi1);
            const float z1 = radius * cos(theta1);
            float xText0 = deltaSlices*i;
            float yText0 = deltaStacks*j;

            const float normalx2=sin(theta2) * cos(phi1);
            const float normaly2=sin(theta2) * sin(phi1);
            const float normalz2=cos(theta2);
            const float x2 = radius * sin(theta2) * cos(phi1);
            const float y2 = radius * sin(theta2) * sin(phi1);
            const float z2 = radius * cos(theta2);
            float xText1 = deltaSlices*(i+1);
            float yText1 = deltaStacks*j;

            const float normalx3=sin(theta2) * cos(phi2);
            const float normaly3=sin(theta2) * sin(phi2);
            const float normalz3=cos(theta2);
            const float x3 = radius * sin(theta2) * cos(phi2);
            const float y3 = radius * sin(theta2) * sin(phi2);
            const float z3 = radius * cos(theta2);
            float xText2 = deltaSlices*(i+1);
            float yText2 = deltaStacks*(j+1);

            const float normalx4=sin(theta1) * cos(phi2);
            const float normaly4=sin(theta1) * sin(phi2);
            const float normalz4=cos(theta1);
            const float x4 = radius * sin(theta1) * cos(phi2);
            const float y4 = radius * sin(theta1) * sin(phi2);
            const float z4 = radius * cos(theta1);
            float xText3 = deltaSlices*(i);
            float yText3 = deltaStacks*(j+1);

			file << x1 << " "<< y1 << " " << z1 <<std::endl;
            file << xText0 << " "<< yText0 <<std::endl;
            file << normalx1 << " "<< normaly1 << " " << normalz1 <<std::endl;

			file << x2 << " "<< y2 << " " << z2 <<std::endl;
            file << xText1 << " "<< yText1 <<std::endl;
            file << normalx2 << " "<< normaly2 << " " << normalz2 <<std::endl;

			file << x3 << " "<< y3 << " " << z3 <<std::endl;
            file << xText2 << " "<< yText2 <<std::endl;
            file << normalx3 << " "<< normaly3 << " " << normalz3 <<std::endl;


			file << x1 << " "<< y1 << " " << z1 <<std::endl;
            file << xText0 << " "<< yText0 <<std::endl;
            file << normalx1 << " "<< normaly1 << " " << normalz1 <<std::endl;

			file << x3 << " "<< y3 << " " << z3 <<std::endl;
            file << xText2 << " "<< yText2 <<std::endl;
            file << normalx3 << " "<< normaly3 << " " << normalz3 <<std::endl;

			file << x4 << " "<< y4 << " " << z4 <<std::endl;
            file << xText3 << " "<< yText3 <<std::endl;
            file << normalx4 << " "<< normaly4 << " " << normalz4 <<std::endl;

        }
    }

	file.close();
    return 0;
}



int drawBox(int length, int side, char* filepath) 
{
    std::ofstream file;
    file.open(filepath);

    if (!file.is_open()) {
        std::cout << "failed to open " << filepath << '\n';
        return -1;
    } 

    float imppar, w, limitesup, limiteinf;
    if (side % 2 != 0) 
    {
        imppar = 0.5;
        w = (side / 2) + 0.5;
        limitesup = (side / 2) + 1;
        limiteinf = -(side / 2);
    } else 
    {
        imppar = 1;
        w = (side / 2);
        limitesup = side / 2;
        limiteinf = -(side / 2) + 1;
    }

    for (int j = limiteinf; j < limitesup; j++) 
    {
        for (int i = limiteinf; i < limitesup; i++) 
        {

    // baixo
            float X1=(imppar + i)* length , X2=(-imppar + i)* length ,Y1= -w* length ,Y2=-w* length , Z1=(-imppar + j)* length , Z2=(imppar + j)* length ;



            float x1_normal = imppar + i;
            float x2_normal = -imppar + i;
            float y1_normal = -w;
            float y2_normal = -w;
            float z1_normal = -imppar + j ;
            float z2_normal = imppar + j;

            float xTex1 = (1.0f / (float)side) * i;
            float yTex1 = (1.0f / (float)side) * j;

            float xTex2 = (1.0f / (float)side) * i;
            float yTex2 = (1.0f / (float)side) * (j+1);

            float xTex3 = (1.0f / (float)side) * (i+1);
            float yTex3 = (1.0f / (float)side) * (j+1);

            float xTex4 = (1.0f / (float)side) * (i+1);
            float yTex4 = (1.0f / (float)side) * (j+1);

            float xTex5 = (1.0f / (float)side) * (i+1);
            float yTex5 = (1.0f / (float)side) * j;

            float xTex6 = (1.0f / (float)side) * i;
            float yTex6 = (1.0f / (float)side) * j;

            file << X1 << " "<< Y1 << " " << Z1 <<std::endl;
            file << xTex1 << " "<< yTex1 <<std::endl;
            file << x1_normal << " "<< y1_normal << " " << z1_normal <<std::endl;
            file << X1 << " "<< Y2 << " " << Z2 << std::endl;
            file << xTex2 << " "<< yTex2 <<std::endl;
            file << x1_normal << " "<< y2_normal << " " << z2_normal <<std::endl;
            file << X2 << " "<< Y2 << " " << Z1 << std::endl;
            file << xTex3 << " "<< yTex3 <<std::endl;
            file << x2_normal << " "<< y2_normal << " " << z1_normal <<std::endl;
    
            file << X2 << " "<< Y2 << " " << Z2 << std::endl;
            file << xTex4 << " "<< yTex4 <<std::endl;
            file << x2_normal << " "<< y2_normal << " " << z2_normal <<std::endl;
            file << X2 << " "<< Y1 << " " << Z1 << std::endl;
            file << xTex5 << " "<< yTex5 <<std::endl;
            file << x2_normal << " "<< y1_normal << " " << z1_normal <<std::endl;
            file << X1 << " "<< Y1 << " " << Z2 << std::endl;
            file << xTex6 << " "<< yTex6 <<std::endl;
            file << x1_normal << " "<< y1_normal << " " << z2_normal <<std::endl;


    // costas
            xTex1 = (1.0f / (float)side) * i;
            yTex1 = (1.0f / (float)side) * j;

            xTex2 = (1.0f / (float)side) * i;
            yTex2 = (1.0f / (float)side) * (j+1);

            xTex3 = (1.0f / (float)side) * (i+1);
            yTex3 = (1.0f / (float)side) * (j+1);

            xTex4 = (1.0f / (float)side) * (i+1);
            yTex4 = (1.0f / (float)side) * (j+1);

            xTex5 = (1.0f / (float)side) * (i+1);
            yTex5 = (1.0f / (float)side) * j;

            xTex6 = (1.0f / (float)side) * i;
            yTex6 = (1.0f / (float)side) * j;

            X1=(imppar + i),X2= (-imppar + i), Y1=(imppar + j), Y2=(-imppar + j),Z1= -w,Z2= -w;

            file <<  X1 * length << " "<< Y1 * length << " "<< Z1 * length <<std::endl;
            file << xTex1 << " "<< yTex1 <<std::endl;
            file <<  X1  << " "<< Y1  << " "<< Z1  <<std::endl;
            file <<  X1 * length << " "<< Y2 * length << " "<< Z2 * length << std::endl;
            file << xTex2 << " "<< yTex2 <<std::endl;
            file <<  X1  << " "<< Y2 << " "<< Z2 << std::endl;
            file <<  X2 * length << " "<< Y2 * length << " "<< Z1 * length << std::endl;
            file << xTex3 << " "<< yTex3 <<std::endl;
            file <<  X2  << " "<< Y2  << " "<< Z1 << std::endl;
    
            file <<  X2 * length << " "<< Y2 * length << " "<< Z2 * length << std::endl;
            file << xTex4 << " "<< yTex4 <<std::endl;
            file <<  X2  << " "<< Y2  << " "<< Z2  << std::endl;
            file <<  X2 * length << " "<< Y1 * length << " "<< Z1 * length << std::endl;
            file << xTex5 << " "<< yTex5 <<std::endl;
            file <<  X2  << " "<< Y1  << " "<< Z1  << std::endl;
            file <<  X1 * length << " "<< Y1 * length << " "<< Z2 * length << std::endl;
            file << xTex6 << " "<< yTex6 <<std::endl;
            file <<  X1  << " "<< Y1<< " "<< Z2  << std::endl;


    // esquerda
            xTex1 = (1.0f / (float)side) * i;
            yTex1 = (1.0f / (float)side) * j;

            xTex2 = (1.0f / (float)side) * i;
            yTex2 = (1.0f / (float)side) * (j+1);

            xTex3 = (1.0f / (float)side) * (i+1);
            yTex3 = (1.0f / (float)side) * (j+1);

            xTex4 = (1.0f / (float)side) * (i+1);
            yTex4 = (1.0f / (float)side) * (j+1);

            xTex5 = (1.0f / (float)side) * (i+1);
            yTex5 = (1.0f / (float)side) * j;

            xTex6 = (1.0f / (float)side) * i;
            yTex6 = (1.0f / (float)side) * j;
            X1=-w, X2=-w,Y1= (imppar + i),Y2= (-imppar + i),Z1= (imppar + j),Z2= (-imppar + j);

            file <<  X1 * length << " "<< Y1 * length << " "<< Z1 * length <<std::endl;
            file << xTex1 << " "<< yTex1 <<std::endl;
            file <<  X1 << " "<< Y1  << " "<< Z1  <<std::endl;
            file <<  X1 * length << " "<< Y2 * length << " "<< Z2 * length << std::endl;
            file << xTex2 << " "<< yTex2 <<std::endl;
            file <<  X1  << " "<< Y2  << " "<< Z2  << std::endl;
            file <<  X2 * length << " "<< Y2 * length << " "<< Z1 * length << std::endl;
            file << xTex3 << " "<< yTex3 <<std::endl;
            file <<  X2  << " "<< Y2  << " "<< Z1  << std::endl;
    
            file <<  X2 * length << " "<< Y2 * length << " "<< Z2 * length << std::endl;
            file << xTex4 << " "<< yTex4 <<std::endl;
            file <<  X2  << " "<< Y2  << " "<< Z2  << std::endl;
            file <<  X2 * length << " "<< Y1 * length << " "<< Z1 * length << std::endl;
            file << xTex5 << " "<< yTex5 <<std::endl;
            file <<  X2  << " "<< Y1  << " "<< Z1  << std::endl;
            file <<  X1 * length << " "<< Y1 * length << " "<< Z2 * length << std::endl;
            file << xTex6 << " "<< yTex6 <<std::endl;
            file <<  X1  << " "<< Y1  << " "<< Z2 << std::endl;

    // cima

            xTex1 = (1.0f / (float)side) * i;
            yTex1 = (1.0f / (float)side) * j;

            xTex2 = (1.0f / (float)side) * i;
            yTex2 = (1.0f / (float)side) * (j+1);

            xTex3 = (1.0f / (float)side) * (i+1);
            yTex3 = (1.0f / (float)side) * (j+1);

            xTex4 = (1.0f / (float)side) * (i+1);
            yTex4 = (1.0f / (float)side) * (j+1);

            xTex5 = (1.0f / (float)side) * (i+1);
            yTex5 = (1.0f / (float)side) * j;

            xTex6 = (1.0f / (float)side) * i;
            yTex6 = (1.0f / (float)side) * j;

            X1=(-imppar + i), X2=(imppar + i),Y1= w,Y2= w, Z1=(-imppar + j),Z2= (imppar + j);

            file <<  X1 * length << " "<< Y1 * length << " "<< Z1 * length <<std::endl;
            file << xTex1 << " "<< yTex1 <<std::endl;
            file <<  X1  << " "<< Y1  << " "<< Z1  <<std::endl;
            file <<  X1 * length << " "<< Y2 * length << " "<< Z2 * length << std::endl;
            file << xTex2 << " "<< yTex2 <<std::endl;
            file <<  X1  << " "<< Y2  << " "<< Z2  << std::endl;
            file <<  X2 * length << " "<< Y2 * length << " "<< Z1 * length << std::endl;
            file << xTex3 << " "<< yTex3 <<std::endl;
            file <<  X2  << " "<< Y2  << " "<< Z1 << std::endl;
    
            file <<  X2 * length << " "<< Y2 * length << " "<< Z2 * length << std::endl;
            file << xTex4 << " "<< yTex4 <<std::endl;
            file <<  X2  << " "<< Y2  << " "<< Z2  << std::endl;
            file <<  X2 * length << " "<< Y1 * length << " "<< Z1 * length << std::endl;
            file << xTex5 << " "<< yTex5 <<std::endl;
            file <<  X2 << " "<< Y1 << " "<< Z1 << std::endl;
            file <<  X1 * length << " "<< Y1 * length << " "<< Z2 * length << std::endl;
            file << xTex6 << " "<< yTex6 <<std::endl;
            file <<  X1 << " "<< Y1  << " "<< Z2 << std::endl;


    // frente

            xTex1 = (1.0f / (float)side) * i;
            yTex1 = (1.0f / (float)side) * j;

            xTex2 = (1.0f / (float)side) * i;
            yTex2 = (1.0f / (float)side) * (j+1);

            xTex3 = (1.0f / (float)side) * (i+1);
            yTex3 = (1.0f / (float)side) * (j+1);

            xTex4 = (1.0f / (float)side) * (i+1);
            yTex4 = (1.0f / (float)side) * (j+1);

            xTex5 = (1.0f / (float)side) * (i+1);
            yTex5 = (1.0f / (float)side) * j;

            xTex6 = (1.0f / (float)side) * i;
            yTex6 = (1.0f / (float)side) * j;

            X1=(-imppar + i),X2= (imppar + i), Y1=(imppar + j),Y2= (-imppar + j),Z1= w,Z2= w;

            file <<  X1 * length << " "<< Y1 * length << " "<< Z1 * length <<std::endl;
            file << xTex1 << " "<< yTex1 <<std::endl;
            file <<  X1 << " "<< Y1  << " "<< Z1  <<std::endl;
            file <<  X1 * length << " "<< Y2 * length << " "<< Z2 * length << std::endl;
            file << xTex2 << " "<< yTex2 <<std::endl;
            file <<  X1  << " "<< Y2  << " "<< Z2  << std::endl;
            file <<  X2 * length << " "<< Y2 * length << " "<< Z1 * length << std::endl;
            file << xTex3 << " "<< yTex3 <<std::endl;
            file <<  X2  << " "<< Y2 << " "<< Z1 << std::endl;

            file <<  X2 * length << " "<< Y2 * length << " "<< Z2 * length << std::endl;
            file << xTex4 << " "<< yTex4 <<std::endl;
            file <<  X2 << " "<< Y2  << " "<< Z2  << std::endl;
            file <<  X2 * length << " "<< Y1 * length << " "<< Z1 * length << std::endl;
            file << xTex5 << " "<< yTex5 <<std::endl;
            file <<  X2  << " "<< Y1 << " "<< Z1 << std::endl;
            file <<  X1 * length << " "<< Y1 * length << " "<< Z2 * length << std::endl;
            file << xTex6 << " "<< yTex6 <<std::endl;
            file <<  X1  << " "<< Y1  << " "<< Z2  << std::endl;

    // Direita


            xTex1 = (1.0f / (float)side) * i;
            yTex1 = (1.0f / (float)side) * j;

            xTex2 = (1.0f / (float)side) * i;
            yTex2 = (1.0f / (float)side) * (j+1);

            xTex3 = (1.0f / (float)side) * (i+1);
            yTex3 = (1.0f / (float)side) * (j+1);

            xTex4 = (1.0f / (float)side) * (i+1);
            yTex4 = (1.0f / (float)side) * (j+1);

            xTex5 = (1.0f / (float)side) * (i+1);
            yTex5 = (1.0f / (float)side) * j;

            xTex6 = (1.0f / (float)side) * i;
            yTex6 = (1.0f / (float)side) * j;
            X1=w,X2=w,Y1=(-imppar + i),Y2= (imppar + i),Z1= (imppar + j),Z2= (-imppar + j);

            file << X1 * length << " "<< Y1 * length << " "<< Z1 * length <<std::endl;
            file << xTex1 << " "<< yTex1 <<std::endl;
            file << X1 << " "<< Y1  << " "<< Z1  <<std::endl;
            file << X1 * length << " "<< Y2 * length << " "<< Z2 * length << std::endl;
            file << xTex2 << " "<< yTex2 <<std::endl;
            file << X1  << " "<< Y2  << " "<< Z2  << std::endl;
            file << X2 * length << " "<< Y2 * length << " "<< Z1 * length << std::endl;
            file << xTex3 << " "<< yTex3 <<std::endl;
            file << X2  << " "<< Y2  << " "<< Z1  << std::endl;
    
            file <<  X2 * length << " "<< Y2 * length << " "<< Z2 * length << std::endl;
            file << xTex4 << " "<< yTex4 <<std::endl;
            file <<  X2  << " "<< Y2  << " "<< Z2  << std::endl;
            file <<  X2 * length << " "<< Y1 * length << " "<< Z1 * length << std::endl;
            file << xTex5 << " "<< yTex5 <<std::endl;
            file <<  X2  << " "<< Y1 << " "<< Z1  << std::endl;
            file <<  X1 * length << " "<< Y1 * length << " "<< Z2 * length << std::endl;
            file << xTex6 << " "<< yTex6 <<std::endl;
            file <<  X1  << " "<< Y1  << " "<< Z2  << std::endl;

		}
	}

    file.close();
    return 0;
}



void drawCone(float radius, float height, int slices, int stacks, char* filepath) 
{
    std::ofstream file;
    file.open (filepath);
    
    // Define as coordenadas de textura para a base do cone
    float baseTextureU = 0;
    float baseTextureV = 0;

    for (int i = 0; i < slices; i++) 
    {
        float angulo = 2 * M_PI * i / slices;
        float angulo2 = 2 * M_PI * (i + 1) / slices;

        // Define as coordenadas de textura para os vértices laterais do cone
        float lateralTextureU1 = (float)i / slices;
        float lateralTextureU2 = (float)(i + 1) / slices;
        float lateralTextureV1 = 0.0;
        float lateralTextureV2 = 1.0;

        file << 0.0<< " "<< -height / 2 <<" " <<0.0  <<std::endl;
        file << baseTextureU << " "<< baseTextureV <<std::endl;
        file <<  0.0  << " "<< -height / 2  << " "<< 0.0  << std::endl;
        file << radius * sin(angulo2)<< " "<< -height / 2 <<" " <<radius * cos(angulo2) <<std::endl;
        file << lateralTextureU2 << " "<< lateralTextureV1 <<std::endl;
        file <<  sin(angulo2)  << " "<< -height / 2  << " "<< cos(angulo2) << std::endl;
        file << radius * sin(angulo)<< " "<< -height / 2 <<" " <<radius * cos(angulo)  <<std::endl;
        file << lateralTextureU1 << " "<< lateralTextureV1 <<std::endl;
        file <<  sin(angulo)  << " "<< -height / 2  << " "<< cos(angulo) << std::endl;

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
            file << lateralTextureU1 << " "<< lateralTextureV2 <<std::endl;
            file <<  sin(angulo)  << " "<< y1 << " "<< cos(angulo) << std::endl;
            file << raio2 * sin(angulo)<< " "<< y2<<" " <<raio2 * cos(angulo)<<std::endl;
            file << lateralTextureU1 << " "<< lateralTextureV1 <<std::endl;
            file <<  sin(angulo)  << " "<< y2 << " "<< cos(angulo) << std::endl;
            file << raio2 * sin(angulo2)<< " "<< y2<<" " <<raio2 * cos(angulo2) <<std::endl;
            file << lateralTextureU2 << " "<< lateralTextureV1 <<std::endl;
            file <<  sin(angulo2)  << " "<< y2<< " "<< cos(angulo2) << std::endl;


            file << raio2 * sin(angulo2)<< " "<< y2<<" " <<raio2 * cos(angulo2)  <<std::endl;
            file << lateralTextureU2 << " "<< lateralTextureV1 <<std::endl;
            file <<  sin(angulo2)  << " "<< y2 << " "<< cos(angulo2) << std::endl;
            file << raio1 * sin(angulo2)<< " "<< y1<<" " <<raio1 * cos(angulo2)<<std::endl;
            file << lateralTextureU2 << " "<< lateralTextureV2 <<std::endl;
            file <<  sin(angulo2)  << " "<< y1 << " "<< cos(angulo2) << std::endl;
            file << raio1 * sin(angulo)<< " "<< y1<<" " <<raio1 * cos(angulo)<<std::endl;
            file << lateralTextureU1 << " "<< lateralTextureV2 <<std::endl;
            file <<  sin(angulo)  << " "<< y1 << " "<< cos(angulo) << std::endl;
        }
    }
    file.close();
}



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



void drawTorus(int slices, float smallerRadius, float biggerRadius, char* filepath)
{
    std::ofstream file;
    file.open(filepath);

    float angle = 360.0f / slices;
    for (int i = 0; i < slices; ++i) {
        float currAngle = ((angle * M_PI) / 180.0f) * i;
        float nextAngle = ((angle * M_PI) / 180.0f) * (i + 1);

        float x1 = smallerRadius * sinf(currAngle);
        float z1 = smallerRadius * cosf(currAngle);
        float x2 = biggerRadius * sinf(currAngle);
        float z2 = biggerRadius * cosf(currAngle);
        float x3 = biggerRadius * sinf(nextAngle);
        float z3 = biggerRadius * cosf(nextAngle);
        float x4 = smallerRadius * sinf(nextAngle);
        float z4 = smallerRadius * cosf(nextAngle);

        file << x1 << " 0.0 " << z1 << std::endl;
        file << x2 << " 0.0 " << z2 << std::endl;
        file << x3 << " 0.0 " << z3 << std::endl;

        file << x1 << " 0.0 " << z1 << std::endl;
        file << x3 << " 0.0 " << z3 << std::endl;
        file << x4 << " 0.0 " << z4 << std::endl;
    }

    file.close();
}

int main(int argc,char**argv){
    int opcao;
    printf("1- Sphere\n2- Box\n3- Cone\n4- Plane\n5- Torus\n6- Bezier\n7- Cilinder\nOpção:");
    scanf("%d", &opcao);

    vector<Point> pontos, normais;
    vector<float> texture;
    if(opcao == 7){

    }
    if ((strcmp(argv[1],"sphere")==0 ) && argc==6){
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

    }else if ((strcmp(argv[1],"cone")==0)&& argc==7){
        char *ficheiro=argv[6];
        float radius= atof(argv[2]);
        float height=atof(argv[3]);
        int slices =atoi(argv[4]);
        int stacks = atoi(argv[5]);

        drawCone(radius,height,slices,stacks,ficheiro);
        printf("cone\n");
    }else if ((strcmp(argv[1],"plane")==0)&& argc==5){
        char *ficheiro=argv[4];
        
        int length=atoi(argv[2]);
        int  divisions=atoi(argv[3]);
       
	    drawPlane(length,divisions,ficheiro);
        printf("plano\n");

    }else if ((strcmp(argv[1],"torus")==0)&& argc==6){
        char *ficheiro=argv[5];
        
		int slices=atoi(argv[2]);
        float inradius=atof(argv[3]);
        float outradios=atof(argv[4]);
       
	    drawTorus(slices, inradius, outradios,ficheiro);
        printf("torus\n");
    }else if ((strcmp(argv[1],"bezier")==0)&& argc==5){
        char *ficheiro=argv[4];
        
		char *ficheiro_points=argv[2];
        float tessellation_value=atof(argv[3]);
       
	    generate_bezier(ficheiro_points,tessellation_value,ficheiro);
        printf("Bezier\n");
    }
}