/*Declaracion de datos a transferir entre el Administrador Modulos y el Servidor Modulos*/
/*Declaracion de constantes*/
const MAXIDENTIFICACION = 10;
/*Declaracion de la estructura que permite almacenar los datos de un turno generado*/
struct modulo{
    int noModulo;
    bool estado;
};
/*Definicion de las operaciones que se pueden realizar*/
program autorizar_usuarios{
version autorizar_usuarios_version{
bool seleccionarNumeroModulo(int noModulo)=1;
bool liberarModulo(int noModulo)=2;
}=1;
}=0x20000003;