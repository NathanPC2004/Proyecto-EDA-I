#include <stdlib.h>
//true o false
#include <stdbool.h>
//puntos de control
#include <assert.h>
//imprimir
#include <stdio.h>
//manipulacion de cadenas
#include <string.h>
//header
#include "Banco.h"

int main(){
    Banco* Banco = Banco_New();
    
    char o = '\0';
    char contrasena_b[TAM_CON] = {"BANCOMEX"};
    char contrasena[TAM_CON] = {'\0'};
    
    while(o != 'c'){
        printf("MENU PRINCIPAL\n");
        printf("Bienvenido al BANCOMEX\n\n");
        printf("a) Soy usuario\n");
        printf("b) Soy operador del banco\n");
        printf("c) Salir\n");
        scanf("%s", &o);
        system("clear");
        switch(o){
            case 'a':
                char  o2 = '\0';
                while(o2 != 'c'){
                    printf("MENU USUARIO\n\n");
                    printf("a) Iniciar sesión\n");
                    printf("b) Crear cuenta\n");
                    printf("c) Salir\n");
                    scanf("%s", &o2);
                    switch(o2){
                        case 'a':
                            Iniciar_sesion(Banco);
                            break;
                        case 'b':
                            Cuenta_Nueva(Banco);
                            break;
                        default:
                            printf("Opción invalida, intente de nuevo");
                            break;
                    }
                }
                break;
            case 'b':
                printf("Ingrese la contraseña:\n");
                printf("(La contraseña es ''BANCOMEX'')\n");
                scanf("%s", contrasena);
                if(Cmp_Cadena(contrasena, contrasena_b) == true){
                    Banco_Menu(Banco);
                }
                break;
            default:
               printf("Opción invalida, intente de nuevon\n");
               break;
        }
    }
    
    Banco_Delete(&Banco);
    return 0;
}
