#include "cilindro.h"


void cilindro(vector<float> *p,vector<float> *n,vector<float> *t, float altura, float raio, float lados){
    float tex_factor = 1.0/lados, tex_raio = 0.4375-0.25;
    
	float delta = 2.0f * M_PI / lados;
    
	for (int i = 0; i < lados; ++i) {
		
        // topo
		t->push_back(0.4375);
		t->push_back(0.1875);
		n->push_back(0.0);
		n->push_back(1.0);
		n->push_back(0.0);
		p->push_back(0.0);
		p->push_back(altura/2.0);
		p->push_back(0.0);
        
		t->push_back(0.4375 + tex_raio*sin( i * delta));
		t->push_back(0.1875 + tex_raio*cos( i * delta));
		n->push_back(0.0);
		n->push_back(1.0);
		n->push_back(0.0);
		p->push_back(raio * sin( i * delta));
		p->push_back(altura/2.0);
		p->push_back(raio * cos( i * delta));
        
		t->push_back(0.4375 + tex_raio*sin( (i+1) * delta));
		t->push_back(0.1875 + tex_raio*cos( (i+1) * delta));
		n->push_back(0.0);
		n->push_back(1.0);
		n->push_back(0.0);
		p->push_back(raio * sin( (i+1) * delta));
		p->push_back(altura/2.0);
		p->push_back(raio * cos( (i+1) * delta));
        
		// corpo
		t->push_back((i+1)* tex_factor);
		t->push_back(1.0);
		n->push_back(sin( (i+1) * delta));
		n->push_back(0.0);
		n->push_back(cos( (i+1) * delta));
		p->push_back(raio * sin( (i+1) * delta));
		p->push_back(altura/2.0);
		p->push_back(raio * cos( (i+1) * delta));
        
		t->push_back(i* tex_factor);
		t->push_back(1.0);
		n->push_back(sin( i * delta));
		n->push_back(0.0);
		n->push_back(cos( i * delta));
		p->push_back(raio * sin( i * delta));
		p->push_back(altura/2.0);
		p->push_back(raio * cos( i * delta));
        
		t->push_back(i* tex_factor);
		t->push_back(0.375);
		n->push_back(sin( i * delta));
		n->push_back(0.0);
		n->push_back(cos( i * delta));
		p->push_back(raio * sin( i * delta));
		p->push_back(-altura/2.0);
	    p->push_back(raio * cos( i * delta));
        
		t->push_back((i+1)* tex_factor);
		t->push_back(0.375);
		n->push_back(sin( (i+1) * delta));
		n->push_back(0.0);
		n->push_back(cos( (i+1) * delta));
		p->push_back(raio * sin( (i+1) * delta));
		p->push_back(-altura/2.0);
		p->push_back(raio * cos( (i+1) * delta));
        
		t->push_back((i+1)* tex_factor);
		t->push_back(1.0);
		n->push_back(sin( (i+1) * delta));
		n->push_back(0.0);
		n->push_back(cos( (i+1) * delta));
		p->push_back(raio * sin( (i+1) * delta));
		p->push_back(altura/2.0);
		p->push_back(raio * cos( (i+1) * delta));
        
		t->push_back(i* tex_factor);
		t->push_back(0.375);
		n->push_back(sin( i * delta));
		n->push_back(0.0);
		n->push_back(cos( i * delta));
		p->push_back(raio * sin( i * delta));
		p->push_back(-altura/2.0);
		p->push_back(raio * cos( i * delta));
        
		//base
		t->push_back(0.8125);
		t->push_back(0.1875);
		n->push_back(0.0);
		n->push_back(-1.0);
		n->push_back(0.0);
		p->push_back(0.0);
		p->push_back(-altura/2.0);
		p->push_back(0.0);
        
		t->push_back(0.8125 + tex_raio*sin( (i+1) * delta));
		t->push_back(0.1875 + tex_raio*cos( (i+1) * delta));
		n->push_back(0.0);
		n->push_back(-1.0);
		n->push_back(0.0);
		p->push_back(raio * sin( (i+1) * delta));
		p->push_back(-altura/2.0);
		p->push_back(raio * cos( (i+1) * delta));
        
		t->push_back(0.8125 + tex_raio*sin( i * delta));
		t->push_back(0.1875 + tex_raio*cos( i * delta));
		n->push_back(0.0);
		n->push_back(-1.0);
		n->push_back(0.0);
		p->push_back(raio * sin( i * delta));
		p->push_back(-altura/2.0);
		p->push_back(raio * cos( i * delta));
	}
}