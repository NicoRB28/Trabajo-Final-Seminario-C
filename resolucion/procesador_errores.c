#include "sitio.h"
#include <stdlib.h>
#include <string.h>
#include "procesador_errores.h"
void obtener_error (char** tipo_error,int num){
	
	

	if(num == 1){
		strcpy(*tipo_error,"campo muy largo");
	}else if(num == 2){
		strcpy(*tipo_error,"faltan campos");
	}else if(num == 3){
		strcpy(*tipo_error,"campo no es numerico");
	}else if(num == 4){
		strcpy(*tipo_error, "tipologia no valida");
	}



}
