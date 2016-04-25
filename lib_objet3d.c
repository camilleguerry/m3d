#include <assert.h>
#include <math.h>
#include "lib_3d.h"
#include "lib_objet3d.h"
#include "lib_mat.h"
#include "lib_surface.h"


// cree un nouveau maillon, cf cours algo
t_maillon* __cree_maillon(t_triangle3d *face, Uint32 couleur)
{
	t_maillon* pt_maillon = NULL;
	pt_maillon = malloc(sizeof(t_maillon));
	pt_maillon->face= face;
	pt_maillon->couleur=couleur;
	 

	return pt_maillon;
}

// insere en tete le maillon, cf cours algo
void __insere_tete(t_objet3d *pt_objet, t_maillon *pt_maillon)
{
	
	pt_maillon->pt_suiv= pt_objet->tete;
	pt_objet->tete= pt_maillon;

}

t_objet3d *objet_vide()
{
	t_objet3d *pt_objet = NULL;
	t_maillon *pt_tete = NULL;

	pt_objet=malloc(sizeof(t_objet3d));

	pt_objet->tete= pt_tete;
	pt_objet->est_camera=false;
	pt_objet->est_trie=false;
	return pt_objet;
}

t_objet3d *camera()
{
	t_objet3d *pt_objet = objet_vide();
	pt_objet->est_camera=true;
	return objet_vide();
}

t_objet3d* parallelepipede(double lx, double ly, double lz)
{
	t_objet3d *pt_objet = NULL;
	pt_objet=objet_vide();	
	
	//t_point3d *p1
	//t_point3d *p2;
	//t_point3d *p3;
	t_triangle3d *face1;

	//t_point3d *p4;
	t_triangle3d *face2;

	//t_point3d *p5;
	t_triangle3d *face3;

	//t_point3d *p6;
	t_triangle3d *face4;

	t_triangle3d *face5;
	
	//t_point3d *p7;
	t_triangle3d *face6;
	
	t_triangle3d *face7;

	//t_point3d *p8;
	t_triangle3d *face8;

	t_triangle3d *face9;
	t_triangle3d *face10;
	t_triangle3d *face11;
	t_triangle3d *face12;

	pt_objet = objet_vide();
	
	/*p1=definirPoint3d(-lx/2, -ly/2, lz/2);	
	p2=definirPoint3d(lx/2, -ly/2,lz/2);
	p3=definirPoint3d(-lx/2, ly/2, lz/2);
	p4=definirPoint3d(lx/2,ly/2,lz/2);
	p5=definirPoint3d(-lx/2, ly/2, -lz/2);
	p6=definirPoint3d(lx/2, ly/2, -lz/2);
	p7=definirPoint3d(lx/2, -ly/2, -lz/2);
	p8=definirPoint3d(-lx/2, -ly/2, -lz/2);*/

	face1=definirTriangle3d(definirPoint3d(-lx/2, -ly/2, lz/2),definirPoint3d(lx/2, -ly/2,lz/2), definirPoint3d(lx/2,ly/2,lz/2));
	face2=definirTriangle3d(definirPoint3d(-lx/2, -ly/2, lz/2), definirPoint3d(lx/2,ly/2,lz/2), definirPoint3d(-lx/2, ly/2, lz/2));

	face3=definirTriangle3d(definirPoint3d(lx/2,ly/2,lz/2), definirPoint3d(-lx/2, ly/2, lz/2), definirPoint3d(-lx/2, ly/2, -lz/2));	
	face4=definirTriangle3d(definirPoint3d(lx/2,ly/2,lz/2), definirPoint3d(lx/2, ly/2, -lz/2), definirPoint3d(-lx/2, ly/2, -lz/2));

	face5=definirTriangle3d(definirPoint3d(lx/2, -ly/2,lz/2), definirPoint3d(lx/2,ly/2,lz/2), definirPoint3d(lx/2, ly/2, -lz/2));
	face6=definirTriangle3d(definirPoint3d(lx/2, -ly/2,lz/2), definirPoint3d(lx/2, -ly/2, -lz/2), definirPoint3d(lx/2, ly/2, -lz/2));

	face7=definirTriangle3d(definirPoint3d(-lx/2, -ly/2, lz/2), definirPoint3d(-lx/2, ly/2, lz/2), definirPoint3d(-lx/2, -ly/2, -lz/2));	
	face8=definirTriangle3d(definirPoint3d(-lx/2, ly/2, -lz/2), definirPoint3d(-lx/2, -ly/2, -lz/2), definirPoint3d(-lx/2, ly/2, lz/2));

	face9=definirTriangle3d(definirPoint3d(-lx/2, -ly/2, -lz/2), definirPoint3d(lx/2, ly/2, -lz/2), definirPoint3d(-lx/2, ly/2, -lz/2));
	face10=definirTriangle3d(definirPoint3d(-lx/2, -ly/2, -lz/2), definirPoint3d(lx/2, -ly/2, -lz/2), definirPoint3d(lx/2, ly/2, -lz/2));

	face11=definirTriangle3d(definirPoint3d(-lx/2, -ly/2, lz/2), definirPoint3d(-lx/2, -ly/2, -lz/2), definirPoint3d(lx/2, -ly/2, -lz/2));
	face12=definirTriangle3d(definirPoint3d(-lx/2, -ly/2, lz/2), definirPoint3d(lx/2, -ly/2,lz/2), definirPoint3d(lx/2, -ly/2, -lz/2));
	
	t_maillon* maillon1 = __cree_maillon(face1,ROUGEC);
	t_maillon* maillon2 = __cree_maillon(face2,ROUGEC);
	t_maillon* maillon3 = __cree_maillon(face3,VERTC);
	t_maillon* maillon4 = __cree_maillon(face4,VERTC);
	t_maillon* maillon5 = __cree_maillon(face5,BLEUC);
	t_maillon* maillon6 = __cree_maillon(face6,BLEUC);
	t_maillon* maillon7 = __cree_maillon(face7,JAUNEC);
	t_maillon* maillon8 = __cree_maillon(face8,JAUNEC);
	t_maillon* maillon9 = __cree_maillon(face9,MARRON1);
	t_maillon* maillon10 = __cree_maillon(face10,MARRON1);
	t_maillon* maillon11 = __cree_maillon(face11,ROSEC);
	t_maillon* maillon12 = __cree_maillon(face12,ROSEC);

	__insere_tete(pt_objet,maillon1); 
	__insere_tete(pt_objet,maillon2);
	__insere_tete(pt_objet,maillon3);
	__insere_tete(pt_objet,maillon4);
	__insere_tete(pt_objet,maillon5);
	__insere_tete(pt_objet,maillon6);
	__insere_tete(pt_objet,maillon7);
	__insere_tete(pt_objet,maillon8);
	__insere_tete(pt_objet,maillon9);
	__insere_tete(pt_objet,maillon10);
	__insere_tete(pt_objet,maillon11);
	__insere_tete(pt_objet,maillon12);

	return pt_objet;
}

t_objet3d* sphere(double r, double nlat, double nlong)
{
	t_objet3d *pt_objet = NULL;

	pt_objet = objet_vide();

	// TODO

	return pt_objet;
}

t_objet3d* sphere_amiga(double r, double nlat, double nlong)
{
	t_objet3d *pt_objet = NULL;

	pt_objet = objet_vide();

	// TODO


	return pt_objet;
}

t_objet3d* arbre(double lx, double ly, double lz)
{
	t_objet3d *pt_objet = NULL;

	pt_objet = objet_vide();
	// TODO

	return pt_objet;

}

t_objet3d* damier(double lx, double lz, double nx, double nz)
{
	t_objet3d *pt_objet = NULL;

	pt_objet = objet_vide();

	// TODO

	return pt_objet;

}

t_objet3d *copierObjet3d(t_objet3d *o) // attention, effectue une copie mirroir
{
	t_objet3d *n = objet_vide();

	// TODO

	return n;
}

void composerObjet3d(t_objet3d* o, t_objet3d* o2) /* o = o+o2, o2 ne signifiera plus rien */
{

	// TODO

}

void libererObjet3d(t_objet3d *o)
{
	t_maillon *p_aux ;
	libererTriangle3d(o->tete->face);
    while(o->tete!=NULL) 
    {
        p_aux=o->tete->pt_suiv;
		if (p_aux!=NULL){
			libererTriangle3d(p_aux->face);
		};
        free (o->tete);
        o->tete=p_aux;
    }
	
}

//effectue un tri des faces de l'objet dans l'ordre des z decroissants => cf algorithme du peintre
void __trier_objet(t_objet3d *pt_objet)
{
	// TODO

}

void dessinerObjet3d(t_surface *surface, t_objet3d* pt_objet)
{
	t_maillon *p_aux;
	p_aux= pt_objet->tete;
	

	while (p_aux != NULL) 
	{  
		remplirTriangle3d(surface, p_aux->face, p_aux->couleur);
		p_aux=p_aux->pt_suiv;
	};
	free(p_aux);
}

void translationObjet3d(t_objet3d* pt_objet, t_point3d *vecteur)
{
	t_maillon *pt_aux;
	pt_aux = pt_objet->tete;
	while (pt_aux !=NULL){
		translationTriangle3d(pt_aux->face, vecteur);
		pt_aux=pt_aux->pt_suiv;
	}
	free(pt_aux);	

}

void rotationObjet3d(t_objet3d* pt_objet, t_point3d *centre, float degreX, float degreY, float degreZ)
{
	t_maillon *pt_aux;
	pt_aux = pt_objet->tete;
	while (pt_aux !=NULL){
		rotationTriangle3d(pt_aux->face, centre, degreX, degreY, degreZ);
		pt_aux=pt_aux->pt_suiv;
	}
	free(pt_aux);
}

void transformationObjet3d(t_objet3d* pt_objet, double mat[4][4])
{
	t_maillon *pt_aux;
	pt_aux = pt_objet->tete;
	while (pt_aux !=NULL){
		transformationTriangle3d(pt_aux->face, mat);
		pt_aux=pt_aux->pt_suiv;
	}
	free(pt_aux);

}

