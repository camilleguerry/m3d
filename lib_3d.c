#include "lib_surface.h"
#include "lib_3d.h"
#include "lib_2d.h"
#include "lib_mat.h"
#include <math.h>

typedef struct
{
	double m[4][4];
} t_matrice3d;

t_point3d *definirPoint3d(double x, double y, double z)	// attention malloc
{
	t_point3d *p;

	p  = (t_point3d*) malloc(sizeof(t_point3d));
	if (p!=NULL)
	{
		p->xyzt[0] = x;
		p->xyzt[1] = y;
		p->xyzt[2] = z;
		p->xyzt[3] = 1;
	}

	return p;
}

t_point3d *definirVecteur3d(double x, double y, double z)	// attention malloc
{	
	t_point3d *p = NULL;
	p  = (t_point3d*) malloc(sizeof(t_point3d));
	if (p!=NULL)
	{
		p->xyzt[0] = x;
		p->xyzt[1] = y;
		p->xyzt[2] = z;
		p->xyzt[3] = 0;
	}
	return p;
}

t_triangle3d *definirTriangle3d(t_point3d * a, t_point3d * b, t_point3d * c)	// attention malloc
{
	t_triangle3d *t = NULL;

	t=(t_triangle3d*) malloc(sizeof(t_triangle3d));
	if (t!=NULL)
	{
		t->abc[0]=a;	
		t->abc[1]=b;
		t->abc[2]=c;
	}
	return t;
}

t_triangle3d *copierTriangle3d(t_triangle3d *t)
{
	t_triangle3d *n = NULL;

	n=(t_triangle3d*) malloc(sizeof(t_triangle3d));
	if (n!=NULL)
	{
		n->abc[0]=t->abc[0];
		n->abc[1]=t->abc[1];
		n->abc[2]=t->abc[2];
	}

	return n;

}

void __copierTriangle3d(t_triangle3d *t1, t_triangle3d *t2){	//t1<-t2
	int i;
	int j;
	for (i=0; i<3; i++){
		for (j=0; j<4; j++){
			t1->abc[i]->xyzt[j]=t2->abc[i]->xyzt[j];
		};
	};
}
void libererTriangle3d(t_triangle3d *t)
{
	if (t!=NULL)
	{
		free(t->abc[0]);
		free(t->abc[1]);
		free(t->abc[2]);
	}
	free(t);
}

// effectue une conversion de 2D en 3D
t_point2d *__conversion_2d_3d(t_point3d *p3d)
{
	t_point2d *p2d;
	t_point3d *p3dtmp;
	double matrice_projection[4][4]={{1, 0, 0, 0},\
			{0, 1, 0, 0},\
			{0, 0, 1, 0},\
			{0, 0, 0, 1}};


	p2d = NULL;
	p3dtmp = (t_point3d*)malloc(sizeof(t_point3d));
	if (p3dtmp!=NULL)
	{
		multiplicationVecteur3d(p3dtmp, matrice_projection, p3d);

		p2d = definirPoint2d(p3dtmp->xyzt[0]+RX/2, p3dtmp->xyzt[1]+RY/2); // malloc implicite il faut faire un free plus tard... (dans une vingtaine de lignes)
	}

	free(p3dtmp);
	return p2d;
}

void remplirTriangle3d(t_surface * surface, t_triangle3d * triangle, Uint32 c)
{
	t_point2d *p2da, *p2db, *p2dc;
	t_triangle2d *t2d;
	p2da = __conversion_2d_3d(triangle->abc[0]);
	p2db = __conversion_2d_3d(triangle->abc[1]);
	p2dc = __conversion_2d_3d(triangle->abc[2]);

	t2d = definirTriangle2d(p2da, p2db, p2dc);

	remplirTriangle2d(surface, t2d, c);

	free(t2d);
	free(p2da); // le free est fait ici :)
	free(p2db);
	free(p2dc);

}

void translationTriangle3d(t_triangle3d *t, t_point3d *vecteur)
{
	int i;
	double mtranslation[4][4]={
			{1,0,0, vecteur->xyzt[0]},\
			{0,1,0, vecteur->xyzt[1]},\
			{0,0,1, vecteur->xyzt[2]},\
			{0,0,0,1}};

	for (i=0; i<3; i++){
		multiplicationVecteur3d(t->abc[i], mtranslation, t->abc[i]);	
	};	

}

void rotationTriangle3d(t_triangle3d *t, t_point3d *centre, float degreX, float degreY, float degreZ)
{
	int i;
	int j;
	t_point3d *p_aux;
	t_triangle3d *t_aux;
	p_aux=(t_point3d*) malloc(sizeof(t_point3d));
	t_aux=(t_triangle3d*) malloc(sizeof(t_triangle3d));
	
	
	double mtranslation[4][4]={
			{1,0,0, -centre->xyzt[0]},\
			{0,1,0, -centre->xyzt[1]},\
			{0,0,1, -centre->xyzt[2]},\
			{0,0,0,1}};

			
	
	for (i=0; i<3; i++){
		t_aux->abc[i]=(t_point3d*) malloc(sizeof(t_point3d));
		multiplicationVecteur3d(t_aux->abc[i], mtranslation, t->abc[i]);	
	};
	
	

	double mrotationX[4][4]={
				{1,0,0,0},\
				{0,cos((M_PI*degreX)/180),-sin((M_PI*degreX)/180),0},\
				{0,sin((M_PI*degreX)/180),cos((M_PI*degreX)/180), 0},\
				{0,0,0,1},\
				};
	

	double mrotationY[4][4]= {
				{cos((M_PI*degreY)/180),0,sin((M_PI*degreY)/180),0},\
				{0,1,0,0},\
				{-sin((M_PI*degreY)/180),0,cos((M_PI*degreY)/180), 0},\
				{0,0,0,1},\
				};
	
	
	double mrotationZ[4][4]={
			{cos((M_PI*degreZ)/180),-sin((M_PI*degreZ)/180),0,0},\
			{sin((M_PI*degreZ)/180),cos((M_PI*degreZ)/180),0,0},\
			{0,0,1,0},\
			{0,0,0,1},\
			};

	
	for (i=0; i<3; i++){
		multiplicationVecteur3d(t_aux->abc[i], mrotationX, t_aux->abc[i]);
		/*for (j=0; j<4; j++){
			t_aux->abc[i]->xyzt[j]=p_aux->xyzt[j];
		}*/
		multiplicationVecteur3d(t_aux->abc[i], mrotationY, t_aux->abc[i]);
		/*for (j=0; j<4; j++){
			t_aux->abc[i]->xyzt[j]=p_aux->xyzt[j];
		}*/
		multiplicationVecteur3d(t_aux->abc[i], mrotationZ, t_aux->abc[i]);
		/*for (j=0; j<4; j++){
			t_aux->abc[i]->xyzt[j]=p_aux->xyzt[j];
		}*/
	};


	double mtranslation2[4][4]={
			{1,0,0, centre->xyzt[0]},\
			{0,1,0, centre->xyzt[1]},\
			{0,0,1, centre->xyzt[2]},\
			{0,0,0,1}
		      };


	for (i=0; i<3; i++){
		multiplicationVecteur3d(t->abc[i], mtranslation2, t_aux->abc[i]);
	};
	
	transformationTriangle3d(t_aux, mtranslation2);
	t=t_aux;
	libererTriangle3d;
	free(p_aux);
}

void transformationTriangle3d(t_triangle3d *t, double mat[4][4]){
	int i;
	for (i=0; i<3; i++){
		t->abc[i]=(t_point3d*) malloc(sizeof(t_point3d));
		multiplicationVecteur3d(t->abc[i], mat, t->abc[i]);	
	};
		

}

