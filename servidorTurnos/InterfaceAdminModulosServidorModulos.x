/*Declaración de datos a transferir entre el administrados modulos y el servidor modulos*/

/*Declaracion de la estructura que permite alamcenar los datos de un modulo*/
struct moduloAdministrador{
    int numeroModulo;
    int estado;
};

/*Definicion de las operaciones que se pueden realizar*/
program administrar_modulos{
    version administrar_modulos_version{
        int seleccionarNumeroModulo(int noModulo)=1;
        int liberarModulo(int noModulo)=2;
    }=1;
}=0x20000003;