#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct elemInst{
  int type;// forward 1; left 2; right 3; repeat 4; erreur 0;
  int value;
  char* couleur;
  int opacity;
  struct elemInst* repeter;// instruction à répéter
  struct elemInst* suivant;// instruction suivante
}INST;

typedef INST* programme;

int creerSVG(FILE *file){

	fputs("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"500\" height=\"500\">\n<title>Exemple LOGO</title>\n<desc>Du LOGO.</desc>\n",file);
  return 0;
}

void ajouterInstFinSVG(INST *instructions, FILE *file, float *x1, float *y1, float *angle){
	int i;
  float x2, y2, orientation;

  orientation=*angle*M_PI/180;
	if(instructions->type==1){

		x2=*x1+(instructions->value)*cos(orientation);
		y2=*y1+(instructions->value)*sin(orientation);
 		fprintf(file, "<line x1=\"%.3f\" y1=\"%.3f\" x2=\"%.3f\" y2=\"%.3f\" stroke=\"%s\" stroke-opacity=\"%d\" />\n", *x1, *y1, x2, y2, instructions->couleur, instructions->opacity);
		*x1=x2;
		*y1=y2;

	}else if(instructions->type==2){
		*angle=*angle-(instructions->value);
	}else if(instructions->type==3){
		*angle=*angle+(instructions->value);
	}else if(instructions->type==4){
		for(i=0;i<(instructions->value);i++){
			ajouterInstFinSVG(instructions->repeter, file, x1, y1, angle);
		}
	}else if(instructions->type==5){
		fprintf(file, "<circle cx=\"%.3f\" cy=\"%.3f\" r=\"%d\" stroke=\"%s\" fill=\"none\" stroke-opacity=\"%d\" />\n", *x1, *y1, instructions->value, instructions->couleur, instructions->opacity);
  }

	if(instructions->suivant!=NULL){
		ajouterInstFinSVG(instructions->suivant, file, x1, y1, angle);
	}
}

int terminerSVG(FILE *file){
	fputs("</svg>",file);

	return 0;
}
