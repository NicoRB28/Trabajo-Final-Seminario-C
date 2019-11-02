

Forma de compilar: nuevo3.c procesador_errores.c sitio.c generador_archivos.c lector_linea.c -Wall -o <nombre_del_ejecutable>


Al ejecutar el programa tener en cuenta que, se ha utilizado getopt_long_only para evaluar los argumentos, por lo tanto, como --salida requiere un argumento de manera opcional, si se utiliza la forma simplificada (-s) el nombre del archivo debe ir inmediatamente seguido de la 's'(ej. -l linea-de-base-2017.csv -sNOMBRE_DEL_ARCHIVO_DE_SALIDA); en caso de utilizar la opcion extendida --salida requiere de un '=' antes del nombre del archivo (ej. -l linea-de-base-2017.csv --salida=NOMBRE_ARCHIVO_DE_SALIDA).

si no se desea crear un archivo de salida, se puede ejecutar -s -, -s , --salida=-. Estas opciones tomaran la salida estandar para imprimir los resultados correspondientes. 

-h imprime la lista de argumentos aceptados.
