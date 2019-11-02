#include<getopt.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"sitio.h"
#include"procesador_errores.h"
#include"struct_parte_dos.h"
#include"generador_archivos.h"

int main(int argc, char* argv[])
{
	
	//variables para archivos
	FILE *input = NULL;
	FILE *output = NULL;
	
	//flags de argumentos y ch en particular para el retorno de getopt
	int ch,lflag,sflag,mflag,hflag,iflag;
	lflag=0;
	sflag=0;
	hflag=0;
	mflag=0;
	iflag=0;
	
	//variables usadas en procedimientos punto 2 y recuperatorio
	int cantidad = 0;
	parte_dos* vector = NULL;
	int max = -1;
	float grado_relativo;

	float inferior;

	//struct requerido por la funcion get_opt_long_only
	static struct option vector_opciones[]={
		{"help",no_argument,NULL,'h'},
		{"ayuda",no_argument,NULL,'a'},
		{"leer",required_argument,NULL,'l'},
		{"salida",optional_argument,NULL,'s'},
		{"municipio",no_argument,NULL,'m'},
		{"inferior",required_argument,NULL,'i'},
		{NULL,0,NULL,0}
	};
	
	while((ch = getopt_long_only(argc,argv,"mhal:s::i:",vector_opciones,NULL))!=-1){
		
		switch(ch){
			case 'h':case 'a':
				hflag++;
			break;
			case 'l':
				if(optarg == NULL){
					fprintf(stderr,"debe especificar un nombre de archivo\n");
					exit(66);
				}
				if((input = fopen(optarg,"rb"))==NULL){
					fprintf(stderr,"error al intentar abrir el archivo %s\n", optarg);
					exit(68);
				}
				lflag++;
			break;
			case 's':
				if((optarg == NULL) || ((strcmp(optarg,"-")==0))){
					output = stdout;
				}else if((output = fopen(optarg,"wb+"))==NULL){
					fprintf(stderr,"error al intentar abrir el archivo %s\n",optarg);
					if(input != NULL) fclose(input);
					exit(69);
				}
				sflag++;
			break;
			case 'm':
				mflag++;
			break;
			case 'i':
				inferior = strtof(optarg,NULL);
				if(inferior <=0){
					fprintf(stderr,"ERROR: el valor solicitado debe ser mayor a 0\n");
					exit(80);
				}
				iflag++;
			break;
			case '?':
				if(input == NULL){
					exit(66);
				}
				exit(67);
			break;
			default:
				exit (67);
			break;
		}
	}
	if(hflag==1){
		printf("[-h]|[-a]|[--help]|[--ayuda]\n");
		printf("[-l]|[--leer] <archivo>\n");
		printf("[-s]=<archivo>|[--salida]=<archivo>\n");
		printf("[-s]<Archivo>|[--s]=<archivo>\n");
	        printf("si --salida no es el ultimo argumento tomara la opcion siguiente como nombre del archivo");
		printf("de salida\n");
		printf("si se ingresa '-' como nombre de archivo se toma salida estandar\n");
		printf("[-m]|[--municipio]\n");
		printf("[-i]=<valor positivo mayor a 0> |[--inferior]=<valor positivo mayor a 0>\n");
		return 0;
	}
	if(sflag<1){
		printf("[-s] es necesario\n");
		if(input != NULL) free(input);
		exit(65);

	}else if(sflag >1){
		printf("[-s] no se puede repetir\n");
		if(output!=stdout){
			fclose(output);
		}
		if(input!=stdin){
			fclose(input);
		}

		exit(71);
	}
	if(lflag<1){
		printf("[-l] es necesario\n");

		exit(65);
	}else if(lflag >1){
		printf("error [-l] no se puede repetir\n");
		if(input!=stdin){
			fclose(input);
		}

		exit(71);
	}
	if(lflag == 1 && sflag == 1 && mflag == 1 && iflag == 0){
		//RESOLUCION --municipio (PARTE DOS INTEGRADOR)
		vector = generar_archivo_municipio(input,output,&cantidad);


		for(int i=0;i<cantidad;i++){
			if(vector[i].tot > max){
				max = vector[i].tot;
			}
		}
		grado_relativo =(float) max/4;
		printf("el grado relativo es: %.2f\n",grado_relativo);
		for ( int j = 0 ; j<cantidad ; j++){


			if(vector[j].tot < grado_relativo){
				fprintf(output,"%s,%s{id municipio:%d} <tan-dot>\n",vector[j].latitud,vector[j].longitud,vector[j].id);
			}else if(vector[j].tot < grado_relativo*2){
				fprintf(output,"%s,%s{id municipio:%d} <yellow-dot>\n",vector[j].latitud,vector[j].longitud,vector[j].id);
			}else if(vector[j].tot < grado_relativo*3){
				fprintf(output,"%s,%s{id municipio:%d} <orange-dot>\n",vector[j].latitud,vector[j].longitud,vector[j].id);
			}else if(vector[j].tot > grado_relativo){
				fprintf(output,"%s,%s{id municipio:%d} <default-dot>\n",vector[j].latitud,vector[j].longitud,vector[j].id);

			}


		}
	}else if(lflag == 1 && sflag == 1 && mflag == 1 && iflag == 1){
		
		//CONSIGNA DE RECUPERATORIO --inferior=nro
		

		printf("el numero solicitado es %.2f\n",inferior);
	 	vector = generar_archivo_municipio(input,output,&cantidad);
		for(int i=0;i<cantidad;i++){
			if(vector[i].tot > max){
				max = vector[i].tot;
			}
		}
		grado_relativo =(float) max/4;

		
		for (int i = 0; i<cantidad; i++){

			if(vector[i].tot < inferior){
				if(vector[i].tot < grado_relativo){
					fprintf(output,"%s,%s{id municipio:%d} <tan-dot>\n",vector[i].latitud,vector[i].longitud,vector[i].id);
				}else if(vector[i].tot < grado_relativo*2){
					fprintf(output,"%s,%s{id municipio:%d} <yellow-dot>\n",vector[i].latitud,vector[i].longitud,vector[i].id);
				}else if(vector[i].tot < grado_relativo*3){
					fprintf(output,"%s,%s{id municipio:%d} <orange-dot>\n",vector[i].latitud,vector[i].longitud,vector[i].id);
				}else if(vector[i].tot > grado_relativo){
					fprintf(output,"%s,%s{id municipio:%d} <default-dot>\n",vector[i].latitud,vector[i].longitud,vector[i].id);

				}			
			}


		}


	}else if(lflag == 1 && sflag == 1 && iflag == 1 && mflag != 1){
		fprintf(stderr, " si solicita --i o --inferior debe solicitar -m o --municipio");
		exit (65);
	}else if(lflag == 1 && sflag == 1){
		
		//RESOLUCION PARTE 1 
		
	       	generar_archivo(input, output);

	}else if( sflag == 1 && lflag != 1){

		printf("ERROR [-l es requerido si -s fue solicitado]\n");
		exit(65);
	}
	if(mflag == 1 && sflag != 1){
		printf("si solicito -m es necesario especificar -s\n");
		exit(65);
	}
	fclose(input);
	fclose(output);
	free(vector);
	return 0;
	

}
