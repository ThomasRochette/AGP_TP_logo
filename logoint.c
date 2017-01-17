#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct elemInst{
  int type;// forward 1; left 2; right 3; repeat 4; erreur 0; circle 5
  int value;
  char* couleur;
  int opacity;
  struct elemInst* repeter;// instruction à répéter
  struct elemInst* suivant;// instruction suivante
}INST;

typedef INST* programme;

INST *creerINST(int type, int val, char* couleur, int opacity, programme repeter){
  INST *newinstruction = (INST*) malloc(sizeof(INST));
  if(type >0 && type<6){
    newinstruction->type=type;
    newinstruction->value=val;
    newinstruction->couleur=couleur;
    newinstruction->opacity=opacity;
    newinstruction->repeter=repeter;
    newinstruction->suivant=NULL;
  }else{
    newinstruction->type=0;
    newinstruction->value=0;
    newinstruction->couleur="NULL";
    newinstruction->opacity=0;
    newinstruction->repeter=NULL;
    newinstruction->suivant=NULL;
  }
  return newinstruction;
}

INST *ajouterInstFin(INST *prog, INST *newinst){
  if(prog==NULL){
    return newinst;
  }else{
    prog->suivant = ajouterInstFin(prog->suivant,newinst);
    return prog;
  }

}

void ajouterInstFinRepeat(INST *prog, INST *newinst){
  if(prog->type==4){
     ajouterInstFin(prog->repeter,newinst);
  }
}

void afficherProg(programme logo, int repeat){
  int i;
  for(i=0;i<repeat;i++){
    printf("  ");
  }
  if(logo->type==1){
    printf("Forward %d %s\n",logo->value, logo->couleur);
  }else if(logo->type==2){
    printf("Left %d\n",logo->value);
  }else if(logo->type==3){
    printf("Right %d\n",logo->value);
  }else if(logo->type==5){
    printf("Circle %d %s\n",logo->value,logo->couleur);
  }else if(logo->type==4){
    printf("Repeat %d fois : \n",logo->value);
    if(logo->repeter!=NULL){
      afficherProg(logo->repeter, repeat+1);
    }
  }
  if(logo->suivant!=NULL){
    afficherProg(logo->suivant, repeat);
  }
}
