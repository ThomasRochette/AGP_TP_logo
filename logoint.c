#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct elemInst{
  int type;// forward 1; left 2; right 3; repeat 4; erreur 0; circle 5
  int value;
  struct elemInst* repeter;// instruction à répéter
  struct elemInst* suivant;// instruction suivante
}INST;

typedef INST* programme;

INST *creerINST(int type, int val, programme repeter){
  INST *newinstruction = (INST*) malloc(sizeof(INST));
  if(type >0 && type<6){
    newinstruction->type=type;
    newinstruction->value=val;
    newinstruction->repeter=repeter;
    newinstruction->suivant=NULL;
  }else{
    newinstruction->type=0;
    newinstruction->value=0;
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
    printf("Forward %d\n",logo->value);
  }else if(logo->type==2){
    printf("Left %d\n",logo->value);
  }else if(logo->type==3){
    printf("Right %d\n",logo->value);
  }else if(logo->type==5){
    printf("Circle %d\n",logo->value);
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

int test(){
  INST *inst1,*inst2,*inst3,*inst4,*inst5,*inst6;

  inst1=creerINST(1,570,NULL);
  inst2=creerINST(2,50,NULL);
  inst3=creerINST(3,50,NULL);
  inst4=creerINST(1,50,NULL);
  inst5=creerINST(4,50,inst4);
  inst6=creerINST(4,2,creerINST(1,3,NULL));
  ajouterInstFin(inst1,inst2);
  ajouterInstFin(inst1,inst5);
  ajouterInstFin(inst1,inst3);
  afficherProg(inst1,0);
  printf("\n");
  ajouterInstFinRepeat(inst5,creerINST(1,100,NULL));
  ajouterInstFinRepeat(inst5,inst6);
  afficherProg(inst1,0);
  printf("\n");
  free(inst1);
  free(inst2);
  free(inst3);
  free(inst4);
  free(inst5->repeter->suivant);
  free(inst5);
  free(inst6->repeter);
  free(inst6);


 

  return 0;
}
