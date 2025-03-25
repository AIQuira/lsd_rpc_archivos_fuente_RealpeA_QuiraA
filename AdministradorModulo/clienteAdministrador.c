/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "InterfaceAdminModulosServidorModulos.h"

void administrar_modulos_1(char *host)
{
	CLIENT *clnt;
	int *result_1;
	int numeroModulo;
	int *result_2;
	int numeroModuloL;

#ifndef DEBUG
	clnt = clnt_create(host, administrar_modulos, administrar_modulos_version, "udp");
	if (clnt == NULL)
	{
		clnt_pcreateerror(host);
		exit(1);
	}
#endif /* DEBUG */

	printf("Admnistrador de modulos\n");
	int opcion;

	do
	{
		printf("===========    Menú   ===========\n");
		printf("      1. Seleccionar modulo      \n");
		printf("      2. Liberar modulo          \n");
		printf("      3. Salir                   \n");
		printf("===============    ==============\n");
		scanf("%d", &opcion);
		switch (opcion)
		{
		case 1:
			printf("Ingrese el modulo a seleccionar (1, 2 o 3): ");
			scanf("%d", &numeroModulo);
			if (numeroModulo < 1 || numeroModulo > 3)
			{
				printf("Número de módulo inválido. Debe ser 1, 2 o 3.\n");
				break;
			}
			result_1 = seleccionarnumeromodulo_1(&numeroModulo, clnt);
			if (result_1 == (bool_t *)NULL)
			{
				clnt_perror(clnt, "call failed");
			}
			else if (*result_1 == 1)
			{
				printf("El módulo %d ya se encuentra ocupado.\n", numeroModulo);
			}
			else
			{
				printf("Módulo %d asignado correctamente. \n", numeroModulo);
			}
			break;
		case 2:
			printf("Ingrese el modulo a liberar: ");
			scanf("%d", &numeroModuloL);
			if (numeroModuloL < 1 || numeroModuloL > 3)
			{
				printf("Número de módulo inválido. Debe ser 1, 2 o 3.\n");
				break;
			}
			result_2 = liberarmodulo_1(&numeroModuloL, clnt);
			if (result_2 == (bool_t *)NULL)
			{
				clnt_perror(clnt, "call failed");
			}
			else if (*result_2 == 1)
			{
				printf("El módulo %d ya está libre.\n", numeroModuloL);
			}
			else
			{
				printf("Módulo %d liberado correctamente.\n", numeroModuloL);
			}
			break;
		case 3:
			break;
		default:
			printf("Opcion no valida\n");
			break;
		}
	} while (opcion != 3);

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
	administrar_modulos_1(host);
	exit(0);
}
