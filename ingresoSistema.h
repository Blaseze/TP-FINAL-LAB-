#ifndef INGRESOSISTEMA_H_INCLUDED
#define INGRESOSISTEMA_H_INCLUDED

typedef struct
{
    char dniPaciente[30];
    char contrasenia[10];
    int nivel;

}UsuarioPaciente;

typedef struct
{
    char usuarioAdmin[10];///default Admin1234
    char contraAdmin[10];///default Dios1234
}UsuarioAdmin;

typedef struct
{
    char usuarioAdministrativo[10];
    char contraAdministrativo[10];
     int nivel;//1 
}UsuarioAdministrativo;

typedef struct
{
    char usuarioTecnico[10];
    char contraTecnico[10];
     int nivel;//2 tecnico
}UsuarioTecnico;


#endif // INGRESOSISTEMA_H_INCLUDED
