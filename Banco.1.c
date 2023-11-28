//Estructura de las funciones
#include "Banco.h"

Banco* Banco_New(){
    Banco* b = (Banco*)malloc(sizeof(Banco));
    if(b){
        b->first=b->last=b->cursor=NULL;
        b->len=0;
    }
    return b;
}
void Banco_Delete(Banco**this){
    assert( *this );
    Banco_MakeEmpty(*this );
    free( *this );
    *this = NULL;
}
//funcion que pregunte los datos al nuevo usuario
void Cuenta_Nueva(Banco *this){
    char nombre[33]='\0';
    char contraseña[9]='\0';
    char contraseña2[9]='\0';
    int nip;
    printf("Ingrese su nombre de usuario:\n");
    scanf("%s",&nombre);
    printf("\nIngresa el nip que usaras:\n");
    scanf("%d",&nip);
    printf("\nIngrese su contraseña, no mas de 9 caracteres:\n");
    scanf("%s",&contraseña);
    printf("\nConfirma tu contraseña:\n");
    scanf("%s",&contraseña2);
    if (Cmp_Cadena(contraseña,contraseña2)==true){
        Usuario* u = Usuario_New(this,nombre,contraseña,nip)
        if(u){
            Banco_Push_Back(this,u);
            printf("Cuenta creada con éxito, inicie sesion para comtinuar\n");
        }
        else{
        printf("Error al crear la cuenta, intente de nuevo mas tarde.\n");
        }
    }
    else{
        printf("Error, las contraseñas no coinciden\n");
    }
}
Usuario* Usuario_New(Banco *this, char* nombre,
                     char* contraseña, int nip){
    Usuario* u = (Usuario*)malloc(sizeof(Usuario));
    if(u){
        u->saldo->pesos=0;
        u->saldo->centavos=0;
        strncpy(u -> nombre, nombre, 33);
        strncpy(u -> contraseña, contraseña, 9);
        u->nip=nip;
        u->num_cuenta = this->len +1;
    }
}
void Banco_MakeEmpty(Banco *this){
    while(this->len >0){
        DLL_Pop_front(this);
    }
}
void Banco_Pop_Front(Banco *this){
    assert( this->len );
    if( this->len > 1 )  { 
       Usuario* x = this->first->next;
       free( this->first );
       x->prev = NULL;
       this->first = x;
    } else{
       free( this->first );
       this->first = this->last = this->cursor = NULL;
    }
    --this->len;
}
void Banco_Push_Back(Banco *this, Usuario *n){
    assert( n );

    if( this->first != NULL ){
       this->last->next = n;
       n->prev = this->last;
       this->last = n;
    } else{
       this->first = this->last = this->cursor = n;
    }
    ++this->len;
}
int Banco_Num_Usuarios(Banco *this){
    return this->len;
}
void Banco_Print_Usuarios(Banco* this){
    this->cursor = this->first;
    while( this->cursor != NULL){
        Usuario_Imprimir_Datos(this);
    }
}
bool Banco_Vacio(Banco *this){
    return this->first ==NULL;
}
//funciones para iniciar sesión 
void Banco_Find_User(Banco* this, char *user){
    Usuario* it = this->first;
    while( it != NULL){
        if(Cmp_Cadena(this->nombre,user)==true){
            this->cursor = it;
            break;
        }
    }
}
bool Banco_cmp_contraseña(Banco* this, char *nombre){
    return Cmp_Cadena(this->cursor->contraseña,nombre);
}
void Usuario_Menu(Banco* this);
//Funciones a las que el usuario tiene acceso
void Usuario_Imprimir_Datos(Banco* this){
    printf("Nombre: %s\nNumero de cuenta: %03d\n
        Saldo: $%02d.%02d\nContraseña: %s\nNip: %d\n\n", 
        this->cursor->nombre, this->cursor->num_cuenta,
        this->cursor->saldo->pesos, this->cursor->saldo->centavos, 
        this->cursor->contraseña, this->cursor->nip);
}
void Usuario_Cambio_Contraseña(Banco* this);
void Usuario_Transferencia(Banco* this, Banco* other,
                           int pesos, int centavos, int nip);
void Usuario_Retiro(Usuario* this, int pesos, int centavos);

//Funcion auxiliar oara administrar las transacciones
bool Transaccion_valida(Banco*this, int cantidad_p, int cantidad_c){
    int a= (this->saldo->pesos);
    int b= this->saldo->centavos;
    return (0< a - cantidad_p && 0< b - cantidad_c);
}
//Funcion por si el usuario desea eliminar su cuenta 
//o si es baneado del banco
void Usuario_Delete(*Banco_this);
bool Cmp_Cadena(char* 1, char *2){
    return (strcmp(1,2) == 0);
}
    
