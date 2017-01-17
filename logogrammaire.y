%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "logoint.h"

	void yyerror(const char *str){
		fprintf(stderr,"error : %s\n", str);
		exit(1);
	}
	int yywrap(){
		return 1;
	}
	%}

	// Grammaire

	%token FORWARD LEFT RIGHT REPEAT ENTIER CIRCLE PENUP RED BLACK WHITE YELLOW GREEN BLUE

	%union{
		int intval;
		programme prog;
		char* couleur;
	}

%type <intval> FORWARD LEFT RIGHT CIRCLE ENTIER Mouvement
%type <prog> Instruction Programme
%type <couleur> PENUP RED BLACK WHITE YELLOW GREEN BLUE COULEUR
%%
Programme: Instruction
			{$$=$1;root=$$;}
		 | Programme Instruction
			{$$=ajouterInstFin($1,$2);root=$$;}

Instruction: Mouvement ENTIER COULEUR
			{$$=creerINST($1, $2, $3, 1, NULL);}
			|Mouvement ENTIER PENUP
			{$$=creerINST($1, $2, "none", 0, NULL);}
			|Mouvement ENTIER
			{$$=creerINST($1, $2, "red", 1, NULL);}
		 	|REPEAT ENTIER '['Programme']'
			{$$=creerINST(4, $2, "red", 1, $4);}

Mouvement: FORWARD
			{$$=1;}
		  |LEFT
			{$$=2;}
		  |RIGHT
			{$$=3;}
      |CIRCLE
      {$$=5;}

COULEUR: RED
			{$$="red";}
			|BLACK
			{$$="black";}
			|WHITE
			{$$="white";}
			|YELLOW
			{$$="yellow";}
			|GREEN
			{$$="green";}
			|BLUE
			{$$="blue";}
			%%

int main(){
	yyparse();
	afficherProg(root,0);
	FILE *file;

  if((file=fopen("testSVG.svg","w+"))==NULL){
		fprintf(stderr,"\nERREUR : Impossible d'écrire dans le fichier\n");
		return(EXIT_FAILURE);
	}

	creerSVG(file);
  float x1,y1, angle;
	x1=250;
	y1=250;
	angle=0;
	ajouterInstFinSVG(root, file, &x1, &y1, &angle);
	terminerSVG(file);
  fclose(file);

	return 0;
}
