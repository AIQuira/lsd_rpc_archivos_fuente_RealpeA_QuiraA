/*Declaracion de datos a transferir entre el servidor modulos y servidor display*/
/*Declaracion de constantes*/
const MAXIDENTIFICACION2 = 20;
/*Declaracion de la estructura que permite comunicar datos de las notificaciones*/
struct moduloActualizado{
int turno;
int noModulo;
bool ocupado;
char identificacionUsuario[MAXIDENTIFICACION2];
};
struct notificacion{
moduloActualizado modulos[3];
int cantidadUsuariosFilaVirtual;
};
/*Definicion de las operaciones que se pueden realizar*/
program notificar_modulos{
version notificar_modulos_version{
void enviarNotificacion(notificacion objNotificacion)=1;
}=1;
}=0x20000002;
