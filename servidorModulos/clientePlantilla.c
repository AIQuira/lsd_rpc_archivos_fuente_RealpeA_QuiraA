/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "InterfaceServidorModulosServidorDisplay.h"

void notificarModulos(char *host)
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
	for (int i = 0, i < 3; i++)
	{
		strcpy(objNotificacion.modulos[i].identificacionUsuario, vectormodulos[i].identificacionusuario);
		objNotificacion.modulos[i].noModulo = vectormodulos[i].noModulo;
		objNotificacion.modulos[i].turno = vectormodulos[i].numeroTurno;
		objNotificacion.modulos[i].ocupado = vectormodulos[i].ocupado;
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

int main(int argc, char *argv[])
{
	char *host;

	if (argc < 2)
	{
		printf("usage: %s server_host\n", argv[0]);
		exit(1);
	}
	host = argv[1];
	notificar_modulos_1(host);
	exit(0);
}
