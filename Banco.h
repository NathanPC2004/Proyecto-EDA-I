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
#define TAM_NOM 33
#define TAM_CON 9


typedef struct Saldo{
    int pesos;
    int centavos;
} Saldo;

typedef struct Usuario{
    char nombre[TAM_NOM];
    int num_cuenta;
    Saldo saldo;
    char contrasena[TAM_CON];
    int nip;
    struct Usuario* next;
    struct Usuario* prev;
} Usuario;

typedef struct Banco{
    Usuario* first;
    Usuario* last;
    Usuario* cursor;
    Usuario* cursor2;
    int len;
} Banco;

//               BANCO            //
Banco* Banco_New(); 
void Banco_Push_Back(Banco *this, Usuario *n);
void Banco_Pop_Front(Banco *this);
void Banco_MakeEmpty(Banco *this);
void Banco_Delete(Banco** this);
int Banco_Num_Usuarios(Banco *this);
void Banco_Print_Usuarios(Banco* this);
bool Banco_Vacio(Banco *this);
bool Banco_Find_Usuario(Banco* this, char *usuario);
bool Banco_Find_NumCuenta(Banco* this, int num);
bool Banco_Find_NumCuenta2(Banco* this, int num);
//              USUARIO           //
Usuario* Usuario_New(Banco *this, char* nombre, char* contrasena, int nip);
void Usuario_Next(Banco* this);
void Usuario_Imprimir_Datos(Banco* this);
void Cuenta_Nueva(Banco *this);
void Cuenta_Nueva_B(Banco *this);
void Usuario_Delete(Banco **this);
void Usuario_DepositarSaldo(Usuario* this, int pesos, int centavos);
void Usuario_RetirarSaldo(Usuario* this, int pesos, int centavos);
void Usuario_Transferir(Banco* this, int pesos, int centavos);
void Usuario_Cambio_Contrasena(Banco* this, char* contrasena);
char* Usuario_Nombre(Banco* this);
int UsuarioGetNumCuenta(Banco* this);
Saldo Usuario_Saldo(Banco* this);
void Banco_Menu(Banco* this);
void Usuario_Menu(Banco* this);
void Iniciar_sesion(Banco *this);
//            AUXILIARES          //
bool Cmp_Cadena(char a[], char b[]);
bool Transaccion_valida(Banco*this, int cantidad_p, int cantidad_c);



#endif
