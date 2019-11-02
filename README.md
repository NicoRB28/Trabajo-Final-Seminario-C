# Trabajo-Final-Seminario-C
Análisis de datos abiertos - Localización de basurales
Seminario de lenguajes opción C 2019
A raiz de un estudio sobre el impacto ambiental de los basurales de la cuenca Matanza -
Riachuelo realizado en el año 2017, surgió la necesidad de obtener información estadı́stica
sobre los datos que dicho estudio arrojó. Para facilitar su difusión y entendimiento por
personas ajenas a la materia especı́fica de medio ambiente, se ha requerido procesar
los datos para poder generar un mapa que muestre gráficamente los distintos basurales
encontrados.
A tal fin, se tiene a disposición el dataset de basurales de la cuenca Matanza - Riachuelo
de 2017 en formato CSV, el cual deberá ser utilizado por un programa que permita cargar
ese archivo y realizar una serie de operaciones sobre sus datos, para obtener finalmente
la información deseada.
Realizar un programa que, tomando como entrada el dataset en formato CSV y una
serie de argumentos, procese la información y permita realizar diferentes operaciones
sobre la misma.
El programa deberá admitir los siguientes argumentos:
-h|-a|--help|--ayuda:
Muestra qué argumentos admite el programa con una ayuda breve para cada uno.
-l|--leer archivo:
Carga el archivo CSV de nombre “archivo”.
-s|--salida archivo:
Indica el nombre del archivo donde se generará la secuencia de puntos. Si se indica
como archivo “-” o se omite este argumento, la salida se envı́a a la salida estándar.
-m|--municipio:
Indica que se generará un único punto por cada municipio.
Modo de procesar los parámetros:
Si se envı́a el parámetro -h el programa muestra una ayuda con todos los paráme-
tros y termina de inmediato (el resto de los parámetros aunque aparezcan antes se
ignoran).
El parámetro -l es obligatorio y no se puede repetir, le sigue un nombre de archivo.
El parámetro -s es obligatorio y no se puede repetir, le sigue un nombre de archivo.
Si se encuentra -s sin -l mostrar un mensaje de error y finalizar el programa.
El parámetro -m es opcional, si se envı́a se ejecutará la funcionalidad de la etapa
2 del trabajo. Si se encuentra -m sin -s mostrar un mensaje de error y finalizar el
programa.
Especificar -l o -s sin pasar un nombre de archivo debe mostrar de ser posible un
mensaje de error y el programa debe terminar de inmediato.
Si no se puede abrir el archivo de entrada o el de salida, el programa deberá mostrar
un error indicando el nombre del archivo que no pudo abrir y terminar el programa de
inmediato.
Durante la fase de procesamiento de parámetros y apertura de archivos si se detecta
algún error el programa deberá terminar con uno de los siguientes códigos de error
(número indicado a la izquierda):
65. Si falta un argumento requerido.
66. Si falta el nombre de archivo en -l o -s.
67. Si hay argumentos extra o desconocidos.
68. Si no se pudo abrir un archivo para lectura.
69. Si no se pudo abrir un archivo para escritura.
Agregar los códigos de error que sean necesarios para reportar otros errores posibles,
como por ejemplo: archivo CSV no válido o campo muy largo.
Parte 1
Entrega: Semana 24/06/2019
Implementar la funcionalidad necesaria para los argumentos -l y -s (o sus versiones
largas).
A partir del archivo CSV recibido como parámetro de -l el programa deberá generar
un archivo con puntos para mostrar en mapcustomizer.com usando la opción “Bulk
Entry” que muestre los basurales con el siguiente formato:
latitud,longitud {tipologia: denominacion} <tipo_de_marcador>
Por ejemplo, si se tuviera un CSV con información de dos basurales se generarı́a un
archivo similar al siguiente:
34.902503,-57.9381686 {microbasural: Hipódromo de La Plata} <yellow-dot>
34.903492,-57.9376769 {punto de arrojo: Vı́as del tren} <tan-dot>
  
