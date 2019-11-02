
#ifndef _GENERADOR_ARCHIVOS_H
#define _GENERADOR_ARCHIVOS_H
#include"struct_parte_dos.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"lector_linea.h"
void generar_archivo(FILE*,FILE*);
parte_dos* generar_archivo_municipio(FILE*,FILE*,int*);
int asignar_valor_segun_tipo(tipologia_t);
int buscar_id_vector(parte_dos [], int, int);

#endif
