#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "InterfaceAdminModulosServidorModulos.h"
#include "InterfaceClienteServidorModulos.h"

static void
administrar_modulos_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union
	{
		int seleccionarnumeromodulo_1_arg;
		int liberarmodulo_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc)
	{
	case NULLPROC:
		(void)svc_sendreply(transp, (xdrproc_t)xdr_void, (char *)NULL);
		return;

	case seleccionarNumeroModulo:
		_xdr_argument = (xdrproc_t)xdr_int;
		_xdr_result = (xdrproc_t)xdr_int;
		local = (char *(*)(char *, struct svc_req *))seleccionarnumeromodulo_1_svc;
		break;

	case liberarModulo:
		_xdr_argument = (xdrproc_t)xdr_int;
		_xdr_result = (xdrproc_t)xdr_int;
		local = (char *(*)(char *, struct svc_req *))liberarmodulo_1_svc;
		break;

	default:
		svcerr_noproc(transp);
		return;
	}
	memset((char *)&argument, 0, sizeof(argument));
	if (!svc_getargs(transp, (xdrproc_t)_xdr_argument, (caddr_t)&argument))
	{
		svcerr_decode(transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t)_xdr_result, result))
	{
		svcerr_systemerr(transp);
	}
	if (!svc_freeargs(transp, (xdrproc_t)_xdr_argument, (caddr_t)&argument))
	{
		fprintf(stderr, "%s", "unable to free arguments");
		exit(1);
	}
	return;
}

static void
autorizar_usuarios_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union
	{
		char *generarturno_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc)
	{
	case NULLPROC:
		(void)svc_sendreply(transp, (xdrproc_t)xdr_void, (char *)NULL);
		return;

	case generarTurno:
		_xdr_argument = (xdrproc_t)xdr_wrapstring;
		_xdr_result = (xdrproc_t)xdr_nodo_turno;
		local = (char *(*)(char *, struct svc_req *))generarturno_1_svc;
		break;

	default:
		svcerr_noproc(transp);
		return;
	}
	memset((char *)&argument, 0, sizeof(argument));
	if (!svc_getargs(transp, (xdrproc_t)_xdr_argument, (caddr_t)&argument))
	{
		svcerr_decode(transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t)_xdr_result, result))
	{
		svcerr_systemerr(transp);
	}
	if (!svc_freeargs(transp, (xdrproc_t)_xdr_argument, (caddr_t)&argument))
	{
		fprintf(stderr, "%s", "unable to free arguments");
		exit(1);
	}
	return;
}

void cargarModulos()
{
	for (int i = 0; i < 3; i++)
	{
		vectorModulos[i].noModulo = (i + 1);
		vectorModulos[i].ocupado = false;
	}
}

int main (int argc, char **argv) {
    register SVCXPRT *transp;

	pmap_unset(autorizar_usuarios, autorizar_usuarios_version);
    pmap_unset(administrar_modulos, administrar_modulos_version);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL)
	{
		fprintf(stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, autorizar_usuarios, autorizar_usuarios_version, autorizar_usuarios_1, IPPROTO_UDP))
	{
		fprintf(stderr, "%s", "unable to register (autorizar_usuarios, autorizar_usuarios_version, udp).");
		exit(1);
	}
    if (!svc_register(transp, administrar_modulos, administrar_modulos_version, administrar_modulos_1, IPPROTO_UDP))
	{
		fprintf(stderr, "%s", "unable to register (administrar_modulos, administrar_modulos_version, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL)
	{
		fprintf(stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, autorizar_usuarios, autorizar_usuarios_version, autorizar_usuarios_1, IPPROTO_TCP))
	{
		fprintf(stderr, "%s", "unable to register (autorizar_usuarios, autorizar_usuarios_version, tcp).");
		exit(1);
	}
    if (!svc_register(transp, administrar_modulos, administrar_modulos_version, administrar_modulos_1, IPPROTO_TCP))
	{
		fprintf(stderr, "%s", "unable to register (administrar_modulos, administrar_modulos_version, tcp).");
		exit(1);
	}

	cargarModulos();
	svc_run();
	fprintf(stderr, "%s", "svc_run returned");
	exit(1);
	/* NOTREACHED */
}