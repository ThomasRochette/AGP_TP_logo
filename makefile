CC = gcc
flag = -Wall -g
head = logoint.h
objet = lex.yy.c logogrammaire.tab.c

all : $(objet) $(head)
	$(CC) logoint.c logosvg.c lex.yy.c logogrammaire.tab.c -o logotest -lm

logogrammaire.tab.c : logogrammaire.y
	bison -d logogrammaire.y

logogrammaire.tab.h : logogrammaire.y
	bison -d logogrammaire.y
	
lex.yy.c : logolex.l logogrammaire.tab.h
	flex logolex.l

clean :
	rm lex.yy.c logogrammaire.tab.c logogrammaire.tab.h logotest


