#include <assert.h>
#include <math.h>
#include "lib_3d.h"
#include "lib_objet3d.h"
#include "lib_mat.h"
#include "lib_surface.h"
#include "lib_scene3d.h"

#define MATRICE_IDENTITE (double[4][4]){{1., 0., 0., 0.},{0., 1., 0., 0.},{0., 0., 1., 0.},{0., 0., 0., 1.}}

t_scene3d* definirScene3d(t_objet3d *pt_objet)
{

	t_scene3d* pt_maillon;
	pt_maillon=(t_scene3d*) malloc(sizeof(t_scene3d));
	int i, j;
	for(i=0; i<4; i++){
		for(j=0;j<4; j++){
			pt_maillon->descendant[i][j]=MATRICE_IDENTITE[i][j];
		}
	}
	for(i=0; i<4; i++){
		for(j=0;j<4; j++){
			pt_maillon->montant[i][j]=MATRICE_IDENTITE[i][j];
		}
	}
	
	pt_maillon->objet=pt_objet;

	return pt_maillon;
}

t_scene3d* ajouter_relation(t_scene3d* pt_feuille, t_objet3d *pt_objet) // ajout de l'objet en tete des fils
{
	t_scene3d* pt_maillon = definirScene3d(pt_objet);

	if (pt_maillon!=NULL)
	{
		pt_maillon->pt_pere = pt_feuille;
		pt_maillon->pt_suiv = pt_feuille->pt_fils;
		pt_feuille->pt_fils = pt_maillon;
	}

	return pt_maillon; // on retourne le lien vers la nouvelle sous scene
}

void translationScene3d(t_scene3d *pt_scene, t_point3d *vecteur)
{
	double mtranslation1[4][4]={
			{1,0,0, vecteur->xyzt[0]},\
			{0,1,0, vecteur->xyzt[1]},\
			{0,0,1, vecteur->xyzt[2]},\
			{0,0,0,1}};

	double mtranslation2[4][4]={
			{1,0,0, -vecteur->xyzt[0]},\
			{0,1,0, -vecteur->xyzt[1]},\
			{0,0,1, -vecteur->xyzt[2]},\
			{0,0,0,1}};

	
	if(pt_scene->objet->est_camera){
		multiplicationMatrice3d(pt_scene->descendant,pt_scene->descendant, mtranslation1);
		multiplicationMatrice3d(pt_scene->montant,pt_scene->montant, mtranslation2);}
	else{
		multiplicationMatrice3d(pt_scene->descendant,pt_scene->descendant, mtranslation2);
		multiplicationMatrice3d(pt_scene->montant, mtranslation1,pt_scene->montant);}
	
	
	
	
}


void rotationScene3d(t_scene3d *pt_scene, t_point3d *centre, float degreX, float degreY, float degreZ)
{

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


	double mrotationX2[4][4]={
				{1,0,0,0},\
				{0,cos((M_PI*(-degreX))/180),-sin((M_PI*(-degreX))/180),0},\
				{0,sin((M_PI*(-degreX))/180),cos((M_PI*(-degreX))/180), 0},\
				{0,0,0,1},\
				};
	

	double mrotationY2[4][4]= {
				{cos((M_PI*(-degreY))/180),0,sin((M_PI*(-degreY))/180),0},\
				{0,1,0,0},\
				{-sin((M_PI*(-degreY))/180),0,cos((M_PI*(-degreY))/180), 0},\
				{0,0,0,1},\
				};
	
	
	double mrotationZ2[4][4]={
			{cos((M_PI*(-degreZ))/180),-sin((M_PI*(-degreZ))/180),0,0},\
			{sin((M_PI*(-degreZ))/180),cos((M_PI*(-degreZ))/180),0,0},\
			{0,0,1,0},\
			{0,0,0,1},\
			};



	double mrotation1[4][4];
	multiplicationMatrice3d(mrotation1,mrotationX,mrotationY);
	multiplicationMatrice3d(mrotation1,mrotation1,mrotationZ);

	double mrotation2[4][4];
	multiplicationMatrice3d(mrotation2,mrotationZ2,mrotationY2);
	multiplicationMatrice3d(mrotation2,mrotation2,mrotationX2);


	if(pt_scene->objet->est_camera){
		multiplicationMatrice3d(pt_scene->descendant,pt_scene->descendant, mrotation1);
		multiplicationMatrice3d(pt_scene->montant, mrotation2,pt_scene->montant);}
	else{
		multiplicationMatrice3d(pt_scene->descendant,pt_scene->descendant, mrotation1);
		multiplicationMatrice3d(pt_scene->montant, mrotation2,pt_scene->montant);}
	

	
}


void dessinerScene3d(t_surface *surface, t_scene3d* pt_racine)
{
	if(pt_racine!=NULL){

		//transformationObjet3d(pt_racine->objet, pt_racine->descendant);
	
		//transformationObjet3d(pt_racine->objet, pt_racine->montant);
		t_scene3d* pt_aux;
		pt_aux=pt_racine;
		while (pt_aux!=NULL){
			transformationObjet3d(pt_aux->objet, pt_racine->descendant);	
			pt_aux=pt_aux->pt_fils;
					
		}
		pt_aux=pt_racine;
		dessinerObjet3d(surface, pt_racine->objet);
		dessinerScene3d(surface, pt_racine->pt_fils);
		while (pt_aux!=NULL){	
			transformationObjet3d(pt_aux->objet, pt_racine->montant);
			pt_aux=pt_aux->pt_fils;
		
		}
		
	}
			
}

/*
 * // il faut multiplier mes matrices \E0 celles du p\E8re pour inverser la relation
  copier_matrice(m, pt_pere->descendant);
  multiplication_matrice(pt_pere->descendant, pt_objet->montant, m);
  copier_matrice(m, pt_pere->montant);
  multiplication_matrice(pt_pere->montant, pt_objet->descendant, m);
*/

void changerCamera(t_scene3d *pt_objet) // modifie l'arbre de la scene pour que pt_objet en soit la racine, pt_racine ne veut plus rien dire
{

  //TODO
}
