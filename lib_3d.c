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
{	// TODO
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

	// TODO
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
	// TODO
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
	// TODO
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
	

}

void rotationTriangle3d(t_triangle3d *t, t_point3d *centre, float degreX, float degreY, float degreZ)
{
	int i;
	int j;
	t_point3d *p_aux;
	p_aux=(t_point3d*) malloc(sizeof(t_point3d));	
	
	
	for (i=0; i<3; i++){
		t->abc[0]->xyzt[i]=(t->abc[0]->xyzt[i])-centre->xyzt[i];
		t->abc[1]->xyzt[i]=(t->abc[1]->xyzt[i])+centre->xyzt[i];
		t->abc[2]->xyzt[i]=(t->abc[2]->xyzt[i])+centre->xyzt[i];
	}


	double mrotationX[4][4];
	
	mrotationX[0][0]=1;
	mrotationX[0][1]=0;
	mrotationX[0][2]=0;
	mrotationX[0][3]=0;
	
	mrotationX[1][0]=0;
	mrotationX[1][1]=cos((M_PI*degreX)/180);
	mrotationX[1][2]=-sin((M_PI*degreX)/180);
	mrotationX[1][3]=0;

	mrotationX[2][0]=0;
	mrotationX[2][1]=sin((M_PI*degreX)/180);
	mrotationX[2][2]=cos((M_PI*degreX)/180);
	mrotationX[2][3]=0;

	mrotationX[3][0]=0;
	mrotationX[3][1]=0;
	mrotationX[3][2]=0;
	mrotationX[3][3]=1;

	double mrotationY[4][4];
	
	mrotationY[0][0]=cos((M_PI*degreY)/180);
	mrotationY[0][1]=0;
	mrotationY[0][2]=sin((M_PI*degreY)/180);
	mrotationY[0][3]=0;

	mrotationY[1][0]=0;
	mrotationY[1][1]=1;
	mrotationY[1][2]=0;
	mrotationY[1][3]=0;

	mrotationY[2][0]=-sin((M_PI*degreY)/180);
	mrotationY[2][1]=0;
	mrotationY[2][2]=cos((M_PI*degreY)/180);
	mrotationY[2][3]=0;
	
	mrotationY[3][0]=0;
	mrotationY[3][1]=0;
	mrotationY[3][2]=0;
	mrotationY[3][3]=1;
	
	
	double mrotationZ[4][4];/*={\
			{cos,-sin,0,0},\
			{;*/

	mrotationZ[0][0]= cos((M_PI*degreZ)/180);
	mrotationZ[0][1]=-sin((M_PI*degreZ)/180);
	mrotationZ[0][2]=0;
	mrotationZ[0][3]=0;

	mrotationZ[1][0]= sin((M_PI*degreZ)/180);
	mrotationZ[1][1]=cos((M_PI*degreZ)/180);
	mrotationZ[1][2]=0;
	mrotationZ[1][3]=0;

	mrotationZ[2][0]=0;
	mrotationZ[2][1]=0;
	mrotationZ[2][2]=1;
	mrotationZ[2][3]=0;
	
	mrotationZ[3][0]=0;
	mrotationZ[3][1]=0;
	mrotationZ[3][2]=0;
	mrotationZ[3][3]=1;
	
	for (i=0; i<3; i++){
		multiplicationVecteur3d(p_aux, mrotationX, t->abc[i]);
		for (j=0; j<4; j++){
			t->abc[i]->xyzt[j]=p_aux->xyzt[j];
		}
		multiplicationVecteur3d(p_aux, mrotationY, t->abc[i]);
		for (j=0; j<4; j++){
			t->abc[i]->xyzt[j]=p_aux->xyzt[j];
		}
		multiplicationVecteur3d(p_aux, mrotationZ, t->abc[i]);
		for (j=0; j<4; j++){
			t->abc[i]->xyzt[j]=p_aux->xyzt[j];
		}
	};

	for (i=0; i<3; i++){
		t->abc[0]->xyzt[i]=(t->abc[0]->xyzt[i])+centre->xyzt[i];
		t->abc[1]->xyzt[i]=(t->abc[1]->xyzt[i])+centre->xyzt[i];
		t->abc[2]->xyzt[i]=(t->abc[2]->xyzt[i])+centre->xyzt[i];
	}



	
	free(p_aux);
}

void transformationTriangle3d(t_triangle3d *t, double mat[4][4])
{
	// TODO

}

