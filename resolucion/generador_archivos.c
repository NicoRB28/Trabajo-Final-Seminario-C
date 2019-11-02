#include<stdio.h>
#include<stdlib.h>
#include"sitio.h"
#include"procesador_errores.h"
#include"generador_archivos.h"
#include"lector_linea.h"
#include"struct_parte_dos.h"

int buscar_id_vector(parte_dos vector[],int id,int diml){
	
	for(int i = 0; i<diml; i++){
	
		if(vector[i].id == id){
			return i;
		}
	}
	return -1;

}


int asignar_valor_segun_tipo(tipologia_t tipo){

	if(tipo == 0){
		return 1;
	}else if(tipo == 1){
		return 2;
	}else if(tipo == 2){
		return 3;
	}else if(tipo == 3){
		return 4;
	}

	return 0;
}

parte_dos* generar_archivo_municipio(FILE* input,FILE *output,int* cantidad){

	sitio_t basural;
	int cantLinea=0,posicion,valor,err,tamlinea = 10;
	int tam = sizeof(parte_dos)*5;
	parte_dos* vector = malloc(tam);
	parte_dos elemento_vector;
	elemento_vector.tot = 0;
	char* linea = NULL;
	char* buffer = NULL;
	char* string_error = malloc(22);
	while(!feof(input)){

		linea = leer_linea(&buffer,input,&tamlinea);

		if(cantLinea == 0){
			cantLinea++;
			free(linea);
			continue;
		}
		if(strlen(linea)==0){
			free(linea);
			break;
		}
		err = linea_csv_a_sitio_t(linea,&basural);
		cantLinea++;
		if(err == 0){
			valor = asignar_valor_segun_tipo(basural.sitios_tipologia);
			posicion = buscar_id_vector(vector,basural.municipios_id,*cantidad);
			if(posicion != -1){
				vector[posicion].tot +=valor;
			}else{

				elemento_vector.id = basural.municipios_id;
				strcpy(elemento_vector.latitud,basural.sitios_latitud);
				strcpy(elemento_vector.longitud,basural.sitios_longitud);
				elemento_vector.tot = valor;


				vector[(*cantidad)++] = elemento_vector;
				if((*cantidad) == tam/sizeof(parte_dos)){

					tam *=2;
					vector = realloc(vector,tam);
				}
			}

		}else{
			obtener_error(&string_error,err);
			fprintf(stderr,"error al leer la linea: %d, la causa del error es:%s\n",cantLinea,string_error);


		}
		//este free se agrego por valgrind y resto bytes perdidos
		free(linea);
	}
	free(string_error);
	return vector;

}

void generar_archivo(FILE *input,FILE *output){
	sitio_t basural;
	int cantLinea = 0;
	int err,tamlinea = 10;
	char marcador[16];
	char tipo[16];
	char* linea=NULL;
	char* buffer=NULL;
	char* string_error = malloc(22);
	//mientras no llego al final del archivo
	while(!feof(input)){

		linea = leer_linea(&buffer,input,&tamlinea);
		if(cantLinea == 0){

			++cantLinea;
			free(linea);
			continue;
		}
		if(strlen(linea)==0){
			free(linea);
			break;
		}
		err = linea_csv_a_sitio_t(linea,&basural);
		++cantLinea;
		if(err == 0){
		//leo una linea del archivo y despues comparo los datos
		//comparo los tipos para determinar el marcador correspondiente
		//y cambio el valor del enumerador por el string correspondiente
			if(basural.sitios_tipologia == 0){
				strcpy(tipo,"punto de arrojo");
				strcpy(marcador,"tan-dot");
			}else	if(basural.sitios_tipologia==1){
				strcpy(tipo,"Microbasural");
				strcpy(marcador,"yellow-dot");
			}else	if(basural.sitios_tipologia == 2){
				strcpy(tipo,"basural");
				strcpy(marcador,"orange-dot");
			}else if(basural.sitios_tipologia==3){
				strcpy(tipo,"macrobasural");
				strcpy(marcador,"default-dot");
			}
		//escribo en el archivo de salida los datos
		fprintf(output,"%s,%s{%s : %s}<%s>\n",basural.sitios_latitud,basural.sitios_longitud,tipo,basural.sitios_denominacion,marcador);

		}else{
			obtener_error(&string_error,err);
			fprintf(stderr,"se produjo un error al convertir la linea:%d, la causa del error es:%s\n",cantLinea,string_error);

		}
		free(linea);
	}
	free(string_error);

}
