#include<stdio.h>
#include<stdlib.h>
#include "lector_linea.h"


char* leer_linea(char** buffer, FILE* input,int *tamlinea){
	*buffer = malloc(*tamlinea);
	int c, cant = 0;
	while(((c=getc(input))!=EOF) && (c!='\n')){
		if(cant>=(*tamlinea)){
			(*tamlinea) *=2;
			*buffer = realloc(*buffer,(*tamlinea));
		}
		(*buffer)[cant++]=(char)c;
	}
	(*buffer)[cant]='\0';
	return *buffer;
}
