/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "InterfaceClienteServidorModulos.h"
#include "InterfaceServidorModulosServidorDisplay.h"
#include "InterfaceAdminModulosServidorModulos.h"
#include <stdio.h>
#include <stdbool.h>

int numeroTurno = 0;
int cantidadUsuariosFila = 0;
nodo_turno turnos[20];
usuario filaVirtual[10];
modulo vectorModulos[3];
moduloAdministrador vectorModuloAdministrador[3];

int consultarNumeroModuloDisponible();
void notificarModulos();
nodo_turno *generarturno_1_svc(char **argp, struct svc_req *rqstp)
{
	static nodo_turno result;
	numeroTurno++;
	int posicion = consultarNumeroModuloDisponible();
	printf("\n");
	if (posicion == -1)
	{
		printf("\n Los modulos se encuentran ocupados");
		strcpy(filaVirtual[cantidadUsuariosFila].identificacionUsuario, *argp);
		filaVirtual[cantidadUsuariosFila].numeroTurnoAsignado = numeroTurno;
		cantidadUsuariosFila++;
		printf("\n El usuario se agrego a la fila virtual");
	}
	else
	{
		printf("\n El modulo en la posicion %d esta libre y se asignara al usuario con identificacion %s", (posicion + 1), *argp);
		vectorModulos[posicion].ocupado = true;
		vectorModulos[posicion].numeroTurno = numeroTurno;
		strcpy(vectorModulos[posicion].identificacionUsuario, *argp);
	}
	result.numeroTurno = numeroTurno;
	result.cantidadUsuariosFilaVirtual = cantidadUsuariosFila;
	strcpy(result.identificacionUsuario, *argp);
	notificarModulos();
	printf("\n");

	return &result;
}
void notificarModulos()
{
	CLIENT *datosConexionServidor;
	void *resultadoEnvio;
	char ipServidor[20];
	strcpy(ipServidor, "localhost");

#ifndef DEBUG
	// Con clnt_create se obtiene la ubicación al servidor display
	datosConexionServidor = clnt_create(ipServidor, notificar_modulos, notificar_modulos_version, "udp");
	if (datosConexionServidor == NULL)
	{
		clnt_pcreateerror(ipServidor);
		exit(1);
	}
#endif /* DEBUG */
	notificacion objNotificacion;
	for (int i = 0; i < 3; i++)
	{
		strcpy(objNotificacion.modulos[i].identificacionUsuario, vectorModulos[i].identificacionUsuario);
		objNotificacion.modulos[i].noModulo = vectorModulos[i].noModulo;
		objNotificacion.modulos[i].turno = vectorModulos[i].numeroTurno;
		objNotificacion.modulos[i].ocupado = vectorModulos[i].ocupado;
	}
	objNotificacion.cantidadUsuariosFilaVirtual = cantidadUsuariosFila;
	// Se invoca el procedimiento remoto para enviar la notificación
	resultadoEnvio = enviarnotificacion_1(&objNotificacion, datosConexionServidor);
	if (resultadoEnvio == (void *)NULL)
	{
		clnt_perror(datosConexionServidor, "call failed");
	}
#ifndef DEBUG
	// Se liberan recursos del lado del cliente
#endif /* DEBUG */
}
int consultarNumeroModuloDisponible()
{
	int posicion = -1;
	for (int i = 0; i < 3; i++)
	{
		if (vectorModulos[i].ocupado == false)
		{
			posicion = i;
			break;
		}
	}
	return posicion;
}

int *seleccionarnumeromodulo_1_svc(int *argp, struct svc_req *rqstp)
{
	static int result;

	if (vectorModuloAdministrador[*argp - 1].estado == 0) // Verifica si el modulos está libre
	{
		vectorModuloAdministrador[*argp - 1].estado = 1; // Asigna el módulo
		result = 0;										 // Éxito
		printf("Módulo %d asignado correctamente. \n", *argp);
	}
	else
	{
		result = 1;
		printf("Error: El módulo %d ya está ocupado. \n", *argp);
	}

	return &result;
}

int *liberarmodulo_1_svc(int *argp, struct svc_req *rqstp)
{
	static int result;

	if (vectorModuloAdministrador[*argp - 1].estado == 1)
	{													 // Verifica si el modulos está libre
		vectorModuloAdministrador[*argp - 1].estado = 0; // Libera el módulo
		printf(" Módulo %d liberado correctamente. \n", *argp);
		if (cantidadUsuariosFila > 0)
		{
			vectorModuloAdministrador[*argp - 1].estado = 1; // Asigna el módulo
			strcpy(vectorModulos[*argp - 1].identificacionUsuario, filaVirtual[0].identificacionUsuario);
			printf(" El modulo en la posicion %d esta libre y se asignara al usuario con identificacion %s.\n", *argp, filaVirtual[0].identificacionUsuario);
			vectorModulos[*argp - 1].numeroTurno = filaVirtual[0].numeroTurnoAsignado;
			vectorModulos[*argp - 1].ocupado = true;
			// Mueve los usuarios en la fila
			for (int i = 0; i < cantidadUsuariosFila; i++)
			{
				strcpy(filaVirtual[i].identificacionUsuario, filaVirtual[i + 1].identificacionUsuario);
				filaVirtual[i].numeroTurnoAsignado = filaVirtual[i+1].numeroTurnoAsignado;
			}
			cantidadUsuariosFila--;
			notificarModulos();
		}
		else
		{
			vectorModulos[*argp - 1].ocupado = false;
			notificarModulos();
		}

		result = 0; // Éxito
	}
	else
	{
		result = 1;
		printf(" Error: El módulo %d ya está libre. \n", *argp);
	}

	return &result;
}
