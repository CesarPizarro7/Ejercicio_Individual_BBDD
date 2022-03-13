//programa en C para consultar los datos de la base de datos
//Incluir esta libreria para poder hacer las llamadas en shiva2.upc.es
//#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	int partidas;
	int ganadas;
	char user[20]="cesar";
	char consulta [80];
	char consulta2 [80];
	
	printf("Dame el nombre de usuario del cual quieras saber el winrate:\n");
	scanf("%s",user);
	
	printf("\n");
	
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//inicializar la conexion
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "Juego",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	
	// consulta SQL para obtener una tabla con todos los datos
	// de la base de datos
	strcpy (consulta,"SELECT COUNT(participacion.partidaid) FROM (jugadores,participacion) WHERE jugadores.username = '"); 
	strcat (consulta, user);
	strcat (consulta,"' AND jugadores.id = participacion.jugadorid;");
	
	err=mysql_query (conn, consulta);
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	resultado = mysql_store_result (conn);
	
	row = mysql_fetch_row (resultado);
	
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	else
		while (row !=NULL) {
			
			partidas = atoi (row[0]);

			row = mysql_fetch_row (resultado);
	}
	
	
	// consulta2 SQL para obtener una tabla con todos los datos
	// de la base de datos
	strcpy (consulta2,"SELECT COUNT(partidas.ganador) FROM partidas WHERE partidas.ganador='"); 
	strcat (consulta2, user);
	strcat (consulta2,"';");
		
	err=mysql_query (conn, consulta2);
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
		
	resultado = mysql_store_result (conn);
		
	row = mysql_fetch_row (resultado);
	
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	else
		while (row !=NULL) {
			 
			ganadas = atoi (row[0]);
			
			row = mysql_fetch_row (resultado);
		}
	
	float winrate = (float)ganadas / (float)partidas;
	
	printf ("El usuario %s ha jugado un total de %d partidas ganando %d.\n", user, partidas, ganadas);
	printf("El WINRATE de %s es del %.2f%\n",user,winrate);
		
	mysql_close (conn);
	exit(0);
}

