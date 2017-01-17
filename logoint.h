typedef struct elemInst{
  int type;// forward 1; left 2; right 3; repeat 4; erreur 0;
  int value;
  char* couleur;
  int opacity;
  struct elemInst* repeter;// instruction à répéter
  struct elemInst* suivant;// instruction suivante
}INST;

typedef INST* programme;

programme root;

INST *creerINST(int type, int val, char* couleur,int opacity, programme repeter);
INST *ajouterInstFin(INST *prog, INST *newinst);
void ajouterInstFinRepeat(INST *prog, INST *newinst);
void afficherProg(programme logo, int repeat);
int creerSVG(FILE *file);
void ajouterInstFinSVG(INST *instructions, FILE *file, float *x1, float *y1, float *angle);
int terminerSVG(FILE *file);
