//Funciones
#include "Banco.h"


//Crea la nueva lista
Banco* Banco_New(){
    Banco* b = (Banco*)malloc(sizeof(Banco));
    if(b){
        b->first=b->last=b->cursor=NULL;
        b->len=0;
    }
    return b;
}

//Crea un nuevo usario (nodo)
Usuario* Usuario_New(Banco *this, char* nombre, char* contrasena, int nip){
    Usuario* u = (Usuario*)malloc(sizeof(Usuario));
    if(u){
        u->saldo.pesos=0;
        u->saldo.centavos=0;
        strncpy(u -> nombre, nombre, TAM_NOM);
        strncpy(u -> contrasena, contrasena, TAM_CON);
        u->nip=nip;
        u->num_cuenta = this->len +1;
    }
    return u;
}

//Inserta un usuario al final de la lista
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

//Compara cadenas
bool Cmp_Cadena(char a[], char b[]){
    return (strcmp(a,b) == 0);
}

//Saca el primer usuario de la lista 
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

//Vacia la lista
void Banco_MakeEmpty(Banco *this){
    while(this -> len > 0){
        Banco_Pop_Front(this);
    }
}

//Borra a lista
void Banco_Delete(Banco** this){
    assert( *this );
    
    Banco_MakeEmpty(*this );
    free( *this );
    *this = NULL;
}

//Apunta al siguiente usuario
void Usuario_Next(Banco* this){
    this -> cursor = this -> cursor -> next;
}

//Imprime la informacion del usuario
void Usuario_Imprimir_Datos(Banco* this){
    system("clear");
    printf("Nombre: %s\nNumero de cuenta: %03d\nSaldo: $%02d.%02d\nContraseña: %s\nNip: %d\n\n", 
        this->cursor->nombre, this->cursor->num_cuenta,
        this->cursor->saldo.pesos, this->cursor->saldo.centavos, 
        this->cursor->contrasena, this->cursor->nip);
}

//Numero de usuarios en la lista
int Banco_Num_Usuarios(Banco *this){
    return this->len;
}

//Imprime todos los usuarios
void Banco_Print_Usuarios(Banco* this){
    this->cursor = this->first;
    while( this->cursor != NULL){
        Usuario_Imprimir_Datos(this);
        Usuario_Next(this);
    }
}

//Inidica si la lista esta vacia
bool Banco_Vacio(Banco *this){
    return this->first ==NULL;
}

//funciones para iniciar sesión 
//Busca a Usuario por su nombre
bool Banco_Find_Usuario(Banco* this, char *usuario){
    Usuario* it = this->first;
    while( it != NULL){
        if(Cmp_Cadena(it->nombre,usuario)==true){
            this->cursor = it;
            return true;
            break;
        }
        it = it->next;
    }
    return false;
}

//Busca a Usuario por su numero de cuenta
bool Banco_Find_NumCuenta(Banco* this, int num){
    Usuario* it = this->first;
    while( it != NULL){
        if(num == it->num_cuenta){
            this->cursor = it;
            return true;
            break;
        }
        it = it -> next;
    }
    return false;
}

//Busca a Usuario por su numero de cuenta (Funcion auxiliar para transferencias)
bool Banco_Find_NumCuenta2(Banco* this, int num){
    Usuario* it = this->first;
    while( it != NULL){
        if(num == it->num_cuenta){
            this->cursor2 = it;
            return true;
            break;
        }
        it = it -> next;
    }
    return false;
}

//Cambiar contraseña
void Usuario_Cambio_Contrasena(Banco* this, char* n_contrasena){
    strncpy (this -> cursor -> contrasena, n_contrasena, 9);
}

//Funcion auxiliar oara administrar las transacciones
bool Transaccion_valida(Banco*this, int cantidad_p, int cantidad_c){
    int a= this->cursor->saldo.pesos;
    int b= this->cursor->saldo.centavos;
    return (0 < a - cantidad_p && 0 < b - cantidad_c);
}

//Elimina a un Usuario (nodo) de la lista
void Usuario_Delete(Banco **this){
    assert(*this);
    free(*this);
    *this = NULL;
}

//Inserta saldo en la cuenta
void Usuario_DepositarSaldo(Usuario* this, int pesos, int centavos){
    this -> saldo.pesos += pesos;
    this -> saldo.centavos += centavos;
    
    if(this -> saldo.centavos >= 100){
        this -> saldo.centavos -= 100;
        this ->saldo.centavos = this -> saldo.centavos;
        
        ++this ->saldo.pesos;
    }
}

//Retira saldo de la cuenta
void Usuario_RetirarSaldo(Usuario* this, int pesos, int centavos){
    this ->saldo.pesos -= pesos;
    this -> saldo.centavos -= centavos;
    
    if(this -> saldo.centavos < 0){
        this -> saldo.centavos += 100;
        this -> saldo.centavos = this -> saldo.centavos;
        
        --this -> saldo.pesos;
    }
}

//Realiza una transerencia entre dos cuentas
void Usuario_Transferir(Banco* this, int pesos, int centavos){
    Usuario_RetirarSaldo(this->cursor, pesos, centavos);
    Usuario_DepositarSaldo(this->cursor2, pesos, centavos);
}

//Devuelve el nombre del usuario
char* Usuario_Nombre(Banco* this){
    return this -> cursor -> nombre;
}

//Devuelve el umero de centa del usuario
int UsuarioGetNumCuenta(Banco* this){
    return this -> cursor -> num_cuenta;
}

//Devuelve el saldo del usuario
Saldo Usuario_Saldo(Banco* this){
    return this -> cursor -> saldo;
}

//Inicia la sesion de usario
void Iniciar_sesion(Banco *this){
    char nombre[TAM_NOM]={'\0'};
    char contrasena[TAM_CON]={'\0'};
    printf("Ingrese su nombre de usuario:\n");
    scanf("%s",nombre);
    if(Banco_Find_Usuario(this,nombre) == true){
        printf("\nIngrese su contraseña\n");
        scanf("%s",contrasena);
        if(Cmp_Cadena(this->cursor->contrasena,contrasena) == true){
            Usuario_Menu(this);
        }
        else{
            printf("Contraseña incorrecta, intente de nuevo\n");
        }
    }
}

//Menu que le aparece al usuario al iniciar sesion
void Usuario_Menu(Banco* this){
    char x='\0';
    int p=0;
    int c=0;
    char contrasena[TAM_CON]={'\0'};
    char contrasena2[TAM_CON]={'\0'};
    while(x != 'f'){
        printf("Hola %s\n\n", this->cursor->nombre);
        printf("a) Mostrar informacion de la cuenta\n");
        printf("b) Abonar a la cuenta\n");
        printf("c) Retiro de efectivo\n");
        printf("d) Transferencia\n");
        printf("e) Cambio de contraseÃ±a\n");
        printf("f) Salir\n\n");
        scanf("%c",&x);
        switch(x){
            case 'a':
                Usuario_Imprimir_Datos(this);
                break;
            case 'b':
                printf("Ingresa el monto a depositar, indica tambien los centavos\n");
                scanf("%d,%d",&p,&c);
                Usuario_DepositarSaldo(this->cursor,p,c);
                break;
            case 'c':
                printf("Ingresa el monto a retirar, indica tambien los centavos\n");
                scanf("%d,%d",&p,&c);
                Usuario_RetirarSaldo(this->cursor,p,c);
                break;
            case 'd':
                int cuenta = 0;
                printf("Ingresa el monto a transferir, indica tambien los centavos\n");
                scanf("%d,%d",&p,&c);
                printf("\nIngresa el numero de cuenta de destino\n");
                scanf("%d",&cuenta);
                if(Banco_Find_NumCuenta2(this, cuenta)){
                    Usuario_Transferir(this,p,c);
                } else{
                    printf("En numero de cuenta no existe\n");
                }
                break;
            case 'e':
                printf("\nIngrese su nueva contraseÃ±a, no mas de 9 caracteres:\n");
                scanf("%s",contrasena);
                printf("\nConfirma tu contraseÃ±a:\n");
                scanf("%s",contrasena2);
                if (Cmp_Cadena(contrasena,contrasena2)==true){
                    Usuario_Cambio_Contrasena(this,contrasena);
                }
                break;
            case 'f':
                printf("Hasta pronto %s\n",this->cursor->nombre);
                break;    
            default:
                printf("Opcion invalida, intente de nuevo\n");
                break;
        }
    }
    
}

//Funcion que pregunta los datos al nuevo usuario
void Cuenta_Nueva(Banco *this){
    char nombre[TAM_NOM]={'\0'};
    char contrasena[TAM_CON]={'\0'};
    char contrasena2[TAM_CON]={'\0'};
    int nip;
    printf("Ingrese su nombre de usuario:\n");
    scanf("%s",nombre);
    printf("\nIngresa el nip que usaras:\n");
    scanf("%d",&nip);
    printf("\nIngrese su contraseña, no mas de 9 caracteres:\n");
    scanf("%s",contrasena);
    printf("\nConfirma tu contraseña:\n");
    scanf("%s",contrasena2);
    if (Cmp_Cadena(contrasena,contrasena2)==true){
        Usuario* u = Usuario_New(this,nombre,contrasena,nip);
        if(u){
            Banco_Push_Back(this,u);
            printf("Cuenta creada con éxito, inicie sesion para continuar\n");
        }
        else{
        printf("Error al crear la cuenta, intente de nuevo mas tarde.\n");
        }
    }
    else{
        printf("Error, las contraseñas no coinciden\n");
    }
}

//Funcion que pregunta los datos al banco
void Cuenta_Nueva_B(Banco *this){
    char nombre[TAM_NOM]={'\0'};
    char contrasena[TAM_CON]={'\0'};
    char contrasena2[TAM_CON]={'\0'};
    int nip;
    printf("Ingrese el nombre de usuario:\n");
    scanf("%s",nombre);
    printf("\nIngresa el nip que usara:\n");
    scanf("%d",&nip);
    printf("\nIngrese la contraseña, no mas de 8 caracteres:\n");
    scanf("%s",contrasena);
    printf("\nConfirma la contraseña:\n");
    scanf("%s",contrasena2);
    if (Cmp_Cadena(contrasena,contrasena2)==true){
        Usuario* u = Usuario_New(this,nombre,contrasena,nip);
        if(u){
            Banco_Push_Back(this,u);
            printf("Cuenta creada con éxito.");
        }
        else{
        printf("Error al crear la cuenta.");
        }
    }
    else{
        printf("Error, las contraseñas no coinciden\n");
    }
}

//Menu de los operadores del banco
void Banco_Menu(Banco* this){
    char x='\0';
    
    while(x != 'd'){
        system("clear");
        printf("MENU BANCO\n\n");
        printf("a) Ver lista de usuarios\n");
        printf("b) Buscar un usuario\n");
        printf("c) Añadir usuario\n");
        printf("d) Salir\n");
        scanf("%s", &x);
        switch(x){
            case 'a':
                Banco_Print_Usuarios(this);
                break;
            case 'b':
                char x2 = '\0';
                char nombre[TAM_NOM] = {'\0'};
                int num;
                while(x2 != 'c'){
                    printf("Bucar por:\n");
                    printf("a) Nombre\n");
                    printf("b) Numero de cuenta\n");
                    printf("c) Salir\n");
                    scanf("%s", &x2);
                    switch(x2){
                    case 'a':
                        printf("Ingresar nombre:\n");
                        scanf("%s", nombre);
                        Banco_Find_Usuario(this, nombre);
                        Usuario_Imprimir_Datos(this);
                        break;
                    case 'b':
                        printf("Ingresar numero de cuenta:n");
                        scanf("%d", &num);
                        Banco_Find_NumCuenta(this, num);
                        Usuario_Imprimir_Datos(this);
                        break;
                    default:
                        printf("Opcion invalida, intente de nuevo");
                        break;
                    }
                }
            case 'c':
                Cuenta_Nueva_B(this);
                break;
            default:
                printf("Opcion invalida, intente de nuevo");
                break;
        }
    }
}
