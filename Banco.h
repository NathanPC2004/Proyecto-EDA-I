#ifndef  BANCO_INC
#define  BANCO_INC
//malloc
#include <stdlib.h>
//true o false
#include <stdbool.h>
//puntos de control
#include <assert.h>
//imprimir
#include <stdio.h>
//manipulacion de cadenas
#include <string.h>

typedef struct Saldo{
    int pesos;
    int centavos;
} Saldo;

typedef struct Usuario{
    char nombre[33];
    int num_cuenta;
    Saldo saldo;
    char contraseña[9];
    int nip;
    struct Usuario* next;
    struct Usuario* prev;
} Usuario;

typedef struct Banco{
    Usuario* first;
    Usuario* last;
    Usuario* cursor;
    int len;
} Banco;
//Declaracion de funciones
Banco* Banco_New();
void Cuenta_Nueva(Banco *this);
Usuario* Usuario_New(int num_cuenta, char* nombre,
                     char* contraseña, int nip);
void Banco_MakeEmpty(Banco *this);
void Banco_Pop_Front(Banco *this);
void Banco_Push_Back(Banco *this);
int Banco_Num_Usuarios(Banco *this);
void Banco_Print_Usuarios(Banco* this);
void Banco_Delete( Banco *this);
bool Banco_vacio(Banco *this);
//funciones para iniciar sesión 
//si se puede poner la ñ?
void Banco_find_cuenta(Banco* this, int cuenta);
void Banco_cmp_contraseña(Banco* this, char []);
void Usuario_Menu(Banco* this);
//Funciones a las que el usuario tiene acceso
void Usuario_Imprimir_Datos(Banco* this);
void Usuario_Cambio_Contraseña(Banco* this);
void Usuario_Transferencia(Banco* this, Banco* other,
                           int pesos, int centavos, int nip);
void Usuario_retiro(Usuario* this, int pesos, int centavos);

//Funcion auxiliar oara administrar las transacciones
bool Transaccion_valida(Banco*this, int cantidad_p, int cantidad_c);
//Funcion por si el usuario desea eliminar su cuenta 
//o si es baneado del banco
void Usuario_Delete(*Banco this);
bool Cmp_Cadena(char *1, char *2);

#endif
