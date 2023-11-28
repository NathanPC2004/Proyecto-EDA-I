#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Saldo{
    int pesos;
    int centavos;
} Saldo;

typedef struct Usuario{
    char nombre[33];
    int num_cuenta;
    Saldo* saldo;
    char contraseña[9];
    int nip;
} Usuario;

//                  NEW SALDO                //
Saldo* Saldo_New(){
    Saldo* s = (Saldo*)malloc(sizeof(Saldo));
    
    assert(s);
    s -> pesos = 0;
    s -> centavos = 0;
    
    return s;
}

//                    NEW                   //
Usuario* Usuario_New(int num_cuenta, char* nombre, char* contraseña, int nip){
    Usuario* u = (Usuario*)malloc(sizeof(Usuario));
    
    assert(u);
    u -> saldo = Saldo_New();
    u -> num_cuenta = num_cuenta;
    u -> nip = nip;
    strncpy(u -> nombre, nombre, 33);
    strncpy(u -> contraseña, contraseña, 9);
    
    return u;
}

//               STES            //
void Usuario_SetNombre(Usuario* this, char* nombre){
    strncpy (this -> nombre, nombre, 33);
}

void Usuario_SetContraseña(Usuario* this, char* contraseña){
    strncpy (this -> contraseña, contraseña, 9);
}

//                 SALDO                //
void Usuario_InsertarSaldo(Usuario* this, int pesos, int centavos){
    this -> saldo -> pesos += pesos;
    this -> saldo -> centavos += centavos;
    
    if(this -> saldo -> centavos >= 100){
        this -> saldo -> centavos -= 100;
        this -> saldo -> centavos = this -> saldo -> centavos;
        
        ++this -> saldo -> pesos;
    }
}

void Usuario_RetirarSaldo(Usuario* this, int pesos, int centavos){
    this -> saldo -> pesos -= pesos;
    this -> saldo -> centavos -= centavos;
    
    if(this -> saldo -> centavos < 0){
        this -> saldo -> centavos += 100;
        this -> saldo -> centavos = this -> saldo -> centavos;
        
        --this -> saldo -> pesos;
    }
}

//               GETS            //
char* Usuario_GetNombre(Usuario* this){
    return this -> nombre;
}

int Usuario_GetNumCuenta(Usuario* this){
    return this -> num_cuenta;
}

Saldo* Usuario_GetSaldo(Usuario* this){
    return this -> saldo;
}

//                  TRANSFERIR                   //
void Usuario_Transferir(Usuario* this, Usuario* other, int pesos, int centavos){
    Usuario_RetirarSaldo(this, pesos, centavos);
    Usuario_InsertarSaldo(other, pesos, centavos);
}

//                   IMPRIMIR                  //
void Usuario_Imprimir(Usuario* this){
    printf("Nombre: %s\nNumero de cuenta: %03d\nSaldo: $%02d.%02d", 
    this->nombre, this->num_cuenta, this->saldo->pesos, this->saldo->centavos);
}

void Usuario_ImprimirSaldo(Usuario* this){
    printf("Saldo: $%02d.%02d", this->saldo->pesos, this->saldo->centavos);
}

//               DELETE               //
void Usuario_Delete(Usuario** this){
    assert(*this);
    free(*this);
    *this = NULL;
}

int main()
{
    Usuario* usuario_1 = Usuario_New(1, "Nathan Perez", "Pablito1", 1234);
    Usuario* usuario_2 = Usuario_New(2, "Alexis Ramirez", "Pablito2", 5678);
    
    Usuario_InsertarSaldo(usuario_1, 10, 50);
    printf("\n\n");
    Usuario_Imprimir(usuario_1);
    
    Usuario_InsertarSaldo(usuario_2, 10, 50);
    printf("\n\n");
    Usuario_Imprimir(usuario_2);
    
    Usuario_Transferir(usuario_1, usuario_2, 10, 50);
    printf("\n\n");
    Usuario_Imprimir(usuario_1);
    printf("\n");
    Usuario_Imprimir(usuario_2);
    
    Usuario_Delete(&usuario_1);
}
