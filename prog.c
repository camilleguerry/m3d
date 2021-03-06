#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "lib_surface.h"
#include "lib_2d.h"
#include "lib_3d.h"
#include "lib_objet3d.h"
#include "lib_scene3d.h"

//#define T2D
//#define T3D
#define O3D

int main(int argc,char** argv)
{
    t_surface *surface=NULL;
    int cpt = 0;
    int timestart;
    char buf[50];

#ifdef T2D
    t_point2d *p1 = definirPoint2d(10,50), *p2 = definirPoint2d(100,240), *p3 = definirPoint2d(50,300);
    t_triangle2d *t1 = definirTriangle2d(p1, p2, p3);
#endif
#ifdef T3D
    t_point3d *p10 = definirPoint3d(10,50,100), *p20 = definirPoint3d(100,240,100), *p30 = definirPoint3d(50,300,100);
    t_triangle3d *t10 = definirTriangle3d(p10, p20, p30);
#endif
#ifdef O3D
    
    t_point3d *origine = definirPoint3d(0,0,0), *vecteur, *vecteur2;
    t_objet3d *o10 = damier(700,1000,17,17);
	t_objet3d *o11= sphere(15, 10, 10);
	t_objet3d *o12= cylindreHexa(20, 90);
	t_objet3d *o13=parallelepipede(80, 30, 30);

	t_scene3d* scene1;
	scene1=definirScene3d(o10);
	ajouter_relation(ajouter_relation(ajouter_relation(scene1, o12), o13),o11);
	rotationScene3d(scene1->pt_fils->pt_fils,origine, 0, 20, 0);
	translationScene3d(scene1->pt_fils,definirPoint3d(200,45,-100));
	translationScene3d(scene1->pt_fils->pt_fils,definirPoint3d(-200,150,100));
	translationScene3d(scene1->pt_fils->pt_fils->pt_fils,definirPoint3d(0,-30,0));
	rotationScene3d(scene1->pt_fils,origine, 90, 0, 0);
	rotationScene3d(scene1->pt_fils->pt_fils,origine, -90, 0, 0);
	rotationScene3d(scene1,origine, 10, 20, 0);
	
	
#endif

    int i=0;

    surface=creerFenetre(RX,RY);
    timestart = SDL_GetTicks();


    while(i<50)
    {
        effacerFenetre(surface, 0);

#ifdef T2D
/*
 * etape 1 : ce n'est qu'un exemple... il faut desactiver le define T2D pour la suite
 */
        remplirTriangle2d(surface, t1, echelle_de_couleur(30*i));
        SDL_Delay(500);

#endif
#ifdef T3D
/*
 * etape 2 : ecrire le corps des fonctions de lib_mat.c et lib_3d.c
 * - commencer par definirTriangle3d et rotationTriangle3d
 * - tester en activant le define T3D
 * - terminer avec les autres fonctions
 */	
	printf("point A -> x: %f , y: %f, z: %f \n", t10->abc[0]->xyzt[0],t10->abc[0]->xyzt[1], t10->abc[0]->xyzt[2]);  
	printf("point B -> x: %f , y: %f, z: %f \n", t10->abc[1]->xyzt[0],t10->abc[1]->xyzt[1], t10->abc[1]->xyzt[2]);
	printf("point C -> x: %f , y: %f, z: %f \n", t10->abc[2]->xyzt[0],t10->abc[2]->xyzt[1], t10->abc[2]->xyzt[2]); 

    rotationTriangle3d(t10, p10, 0, 10, 0); // rotation d'axe Y
    remplirTriangle3d(surface, t10, echelle_de_couleur(30*i));
	SDL_Delay(500);
	
#endif
#ifdef O3D
/*
 * etape 3 : ecrire le corps des fonctions de lib_objet3d.c
 * - commencer par la definition d'un objet simple (parallelepipede) et l'affichage,
 * - continuer par les transformations
 * - finir par le tri des faces d'un objet et la composition des objets
 */
    vecteur = definirPoint3d(sin(i*M_PI/180),cos(i*M_PI/180),0);
	vecteur2=definirPoint3d(-5,0,0);
    //translationObjet3d(o10, vecteur);
	//rotationObjet3d(o11, origine, 0, 0,80);
    //dessinerObjet3d(surface, o11);
	//rotationScene3d(scene1->pt_fils->pt_fils->pt_fils,origine, 0, 0, 80);
	translationScene3d(scene1->pt_fils->pt_fils,vecteur2);
    free(vecteur);
	free(vecteur2);
	SDL_Delay(500);
	dessinerScene3d(surface, scene1);

	
#endif

        majEcran(surface);
        i += 1;
        cpt++;
        sprintf(buf,"%d FPS",(int)(cpt*1000.0/(SDL_GetTicks()-timestart)));
        SDL_WM_SetCaption(buf,NULL);
		
    }
   	libererObjet3d(o10);
	libererObjet3d(o11);
	libererObjet3d(o12);
	SDL_Quit();
    return 0;
}
