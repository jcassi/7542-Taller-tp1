# 7542-Taller-tp1

Trabajo práctico n.°1 - Taller de Programación I - Curso Veiga

El trabajo práctico consta de dos programas: el cliente y el servidor.

En el programa cliente, este lee líneas de un archivo y se las envía al servidor, del cual las recibe encriptadas. A continuación, se encuentra el diagrama de clase del TDA Client

![](https://github.com/jcassi/7542-Taller-tp1/blob/master/Client.png)

Consiste en
-	Un socket por el cual se realiza la comunicación con el servidor
-	El archivo del cual se obtienen las líneas a encriptar
-	El cifrador
-	El protocolo, el cual se encarga de comunicarse con el servidor siguiendo los requerimientos del enunciado

Primero se inicia el cliente, luego se intenta conectar al servidor y, si lo logra, se pasa a la parte central del programa, la de enviar y recibir datos del servidor. En este paso primero se lee una línea del programa, se la pasa al protocolo para que la envíe al servidor y es también el protocolo quien se encarga de recibir la respuesta encriptada. La ventaja de utilizar el protocolo es que el ciente no necesita saber cómo se deben enviar y recibir los datos del servidor, es el protocolo quien se ocupa de colocar el largo de la línea en los primeros dos bytes, así como también de leer los primeros dos bytes de la respuesta para saber cuántos bytes deben venir del servidor.
Después el cifrador se encarga de sumarles un offset a los caracteres, pues estos son recibidos como bytes de números de 0 a 25 y se deben imprimir como caracteres de la A a la Z. Finalmente se imprime este resultado por stdout.
Este proceso se repite mientras queden líneas por leer del archivo. En la siguiente figura se observa el diagrama de secuencia mostrando la comunicación con el servidor:

![](https://github.com/jcassi/7542-Taller-tp1/blob/master/client_iterate.png)

El otro programa de este trabajo es el servidor, quien se encarga de recibir líneas del cliente y devolérselas encriptadas. En la siguiente figura se observa el diagrama de clase del TDA Server

![](https://github.com/jcassi/7542-Taller-tp1/blob/master/Server.png)

Consiste en
-	El socket listener por el cual el servidor va a escuchar conexiones
-	El socket peer por el cual se conecta al cliente
-	El cifrador, el cual se encarga de encriptar el mensaje

En primer lugar, se inicia el servidor con el puerto deseado y la clave a usar por el cifrador. El servidor queda escuchando posibles conexiones (en este trabajo sólo se permite una). Luego, una vez que el cliente se haya conectado, se reciben dos bytes de éste, los cuales consisten en el largo de la línea a recibir a continuación. Después de haber recibido esa cantidad de bytes establecida por los dos primeros, se le pasa esa línea al cifrador para que la encripte. Finalmente se envían primero dos bytes con el largo de la línea encriptada y luego se pasa la línea misma. Para el servidor también se intentó utilizar el TDA Protocol, pero,  si bien el mensaje recibido por el cliente era el esperado, al ejecutar el programa con Valgrind se detecteron errores que pudieron ser solucionados al momento de esta entrega.
Este proceso se repite mientras el cliente siga enviando mensajes a ecriptar. Una vez que termina, se cierran los sockets y se destruye el cifrador.

![](https://github.com/jcassi/7542-Taller-tp1/blob/master/server_iterate.png)
Para el cifrado en primer lugar se almacena la clave recibida por parámetro en una matriz. Luego, por cada línea a encriptar se realiza el siguiente proceso: primero se filtran los caracteres que no estén entre A y Z. Luego se mapea A->0, B->1, …, Z->25. Después se calcula el largo que debe tener la línea en base al largo de la clave y se rellena el mensaje con ceros, de ser necesario. Se multiplica este vector por la matriz tomando de a bloques de n bytes, siendo n la cantidad de columnas de la misma. Por último, se aplica el módulo 26 y se pasa ese vector de enteros a caracteres.
