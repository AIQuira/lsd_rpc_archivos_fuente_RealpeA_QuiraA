/*Declaracion de datos a transferir entre el cliente y el servidor*/
/*Declaracion de constantes*/
const MAXIDENTIFICACION = 10;
/*Declaracion de la estructura que permite almacenar los datos de un turno generado*/
struct nodo_turno{
int numeroTurno;
int cantidadUsuariosFilaVirtual;
char identificacionUsuario[MAXIDENTIFICACION];
};
/*Definicion de las operaciones que se pueden realizar*/
program autorizar_usuarios{
version autorizar_usuarios_version{
nodo_turno generarTurno(string identificacion)=1;
}=1;
}=0x20000001;