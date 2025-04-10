/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "InterfaceClienteServidorModulos.h"
#include <stdio.h>

void autorizar_usuarios_1(char *host)
{
	CLIENT *clnt;
	nodo_turno *result_1;
	char *identificacion;

#ifndef DEBUG
	clnt = clnt_create(host, autorizar_usuarios, autorizar_usuarios_version, "udp");
	if (clnt == NULL)
	{
		clnt_pcreateerror(host);
		exit(1);
	}
#endif /* DEBUG */
	identificacion = (char *)malloc(50 * sizeof(char));
	printf("=========Sistema para la generacion de turnos=========\n");
	int opcion;
	do
	{
		printf("===========    Menú   ===========\n");
		printf("         1. Generar turno        \n");
		printf("         2. Salir                \n");
		printf("===============    ==============\n");
		printf("Digite opción: ");
		scanf("%d", &opcion);
		if (opcion == 1)
		{
			printf("\n Digite la identificación: ");
			scanf("%s", identificacion);
			result_1 = generarturno_1(&identificacion, clnt);
			if (result_1 == (nodo_turno *)NULL)
			{
				clnt_perror(clnt, "call failed");
			}
			else
			{
				printf("\n ===== Datos generados por el sistema =====");
				printf("\n Numero de identificacion: %s", (*result_1).identificacionUsuario);
				printf("\n Numero de turno: %d", (*result_1).numeroTurno);
				printf("\n Cantidad de usuarios en fila virtual: %d", (*result_1).cantidadUsuariosFilaVirtual);
				printf("\n");
			}
		} else {
			printf("Error: Opción no válida. \n");
		}
	} while (opcion != 2);

#ifndef DEBUG
	clnt_destroy(clnt);
#endif /* DEBUG */
}

int main(int argc, char *argv[])
{
	char *host;

	if (argc < 2)
	{
		printf("usage: %s server_host\n", argv[0]);
		exit(1);
	}
	host = argv[1];
	autorizar_usuarios_1(host);
	exit(0);
}
