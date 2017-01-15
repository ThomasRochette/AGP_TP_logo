%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "logoint.h"
#include "logogrammaire.tab.h"

%}

%%
[0-9]+ yylval.intval=atoi(yytext); return ENTIER;
"FORWARD" return FORWARD;
"LEFT" return LEFT;
"RIGHT" return RIGHT;
"REPEAT" return REPEAT;
"CIRCLE" return CIRCLE;
"[" return '[';
"]" return ']';
\n /* ignore retour chariot*/
[ \t]+ /* ignore espace et tab*/
%%
