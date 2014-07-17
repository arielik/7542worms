7542worms
=========

Worms game coded in C++ for 75.42 FIUBA assignment

*====================================================
*		Compilacion y Ejecución
*====================================================

Prepararse para le ejecucion:
----------------------------
	1- Configurar pantalla del cliente
		Puede ajustarse el tamaño de la pantalla. Para esto se debe modificar el siguiente archivo
		C:\random-fiuba-game\randomgame\Debug\config\client.properties
		
	2- Ubicarse en Carpete de ejecutables desde DOS:
	
		C:\random-fiuba-game\randomgame\Release
		C:\random-fiuba-game\randomgame\Debug

Ejecutar Servidor
-----------------
	Sintaxis:
		\> randomgame-server <archivo.yaml>

	Ejemplo
		\> randomgame-server res/levels/level.yaml

	Nota: el puerto del servidor es 10025 y es fijo

Ejecutar Cliente
----------------

	Sintaxis:
		\> randomgame-client <myUsuario> <ip> <puerto>

	Ejemplo
		\> randomgame-client nestor localhost 10025
