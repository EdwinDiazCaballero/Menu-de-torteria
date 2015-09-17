/*  Para que funcione este programa debe existir un MenuTorteria.txt con el siguiente formato:
    1 Torta Cubana      40
    2 Torta Jamon       15
    3 Torta Especial    55
    4 Refresco          10
*/
// EQUIPO NEGRO

//Librerias
# include<stdio.h>
# include<stdlib.h>
# include<conio.h>
# include<time.h>

//Función de créditos
creditos()
{
    printf("\n\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n\n");
    printf("\t\t\tCREDITOS:\n\n");
    printf("Programa elaborado para Programaci%cn avanzada y m%ctodos num%cricos\n\n",162,130,130);
    printf("EQUIPO NEGRO:\n \tD%caz Caballero Edwin\n\tCuevas Mondrag%cn Ricardo\n\tRaziel Tonatiuh Sandoval Zavala\n",161,162);
    printf("\tRivera Garcia Arturo\n\tOlmos Cruz Edwin Ernesto\n\tGarrido Rodriguez Laeyla Monserrat\n\n");
    printf("U.N.A.M.\tFACULTAD DE INGENIER%cA\n\n",161);
}

//Declaración de dos variables globales
int n, j=0;
float tot_pagar=0.0;
float ventas_dia=0.0;

//Tipo de estructura para guardar los datos que se leen del archivo
struct lectura_menu
{
    char leetorta[20];
    int clave;
    float precio;
};

//Tipo de estructura para guardar los datos de las tortas
struct torta_precio
{
    char *torta;
    float precio;
};

//Variable global para guardar orden
struct torta_precio guard_orden[500];

//Función que imprime la fecha y la hora desde un archivo
int Fecha_y_hora_en_arch()
{

        FILE *fecha;
        fecha=fopen("VentasDía.txt", "a+");

        time_t tiempo = time(0);
        struct tm *tlocal = localtime(&tiempo);
        char output[128];
        strftime(output,128,"\n%a/%b/%Y %H:%M:%S\n",tlocal);
        fputs(output, fecha);

        fclose(fecha);

        return 0;
}

//Función que imprime el menú de la torteria
int imp_menu()
{
    int resp;   //Variable para la respuesta
    int i=0;
    char c;      //Variable contadora para imprimir
    struct lectura_menu lectura[4/*Esto varia según el numero de elementos que haya en el texto*/];//Variables para guardar los datos obtenidos del archivo
    FILE *ap;//Apuntador a FILE, sirve para abrir y recorrer el archivo

    //Borrear pantalla
    system("cls");

    ap=fopen("MenuTorteria.txt","r");//Abre el archivo especificado con la operación que hará en el

    printf("\t\t\tMen%c\n\n", 163);

    for(i=0; i<4; i++)
    {
        fscanf(ap, "%d", &lectura[i].clave);
        fgets(lectura[i].leetorta, 18, ap);
        fscanf(ap, "%f", &lectura[i].precio);

        printf("\t%d\t%s$%.2f\n", lectura[i].clave, lectura[i].leetorta, lectura[i].precio);
    }

    fclose(ap);

    //Opción de salir
    printf("\n\n\t99\tSalir\n\n", 162);

    //Obtencion del resultado
    printf("\tQu%c desea ordenar:\t", 130);
    scanf("%d", &resp);
    n=resp;

    return resp;
}

//Función que guarda la orden, compara si quieres otra cosa y realiza la cuenta total.
int orden(struct torta_precio guar_ini, int j)
{
    //Variables necesaria para recibir la respuesta si quieres más cosas y contador
    int resp2, i, n,c,f;

    //Variables que guarda el efectivo y te da el cambio.
    float efectivo, cambio;

    //Borrar pantalla.
    system("cls");

    n=j-1;

    //Impresion de la orden y sumatoria del total
    printf("\t\t\tOrden\n\n");
    printf("\t%s\t$%.2f",guar_ini.torta, guar_ini.precio);
    tot_pagar=tot_pagar+guar_ini.precio;

    //guardado de la orden
    guard_orden[n].torta=guar_ini.torta;
    guard_orden[n].precio=guar_ini.precio;

    //Pregunta si deseas algo más y obtención de respuesta
    printf("\n\nDesea ordenar algo m%cs?\n\n",160);
    printf("1) Si\t\t2) No\n\n\t\t");
    scanf("%d", &resp2);

    //comparación de respuesta si desea algo más
    if(resp2==2)
    {
        system("cls");
        printf("\n\n\tPresione cualquier tecla para obtener la orden final:");
        getch();

        //Impresión de la cuenta final.
        system("cls");
        printf("\t\t\tCuenta final\n\n");

        //IMPRESION DE FECHA Y HORA EN EL ARCHIVO
        Fecha_y_hora_en_arch();

        //Impresión de la cuenta, el total y obtención del efectivo.
        for(i=0; i<j; i++)
        {
            printf("\n\n\t%s\t$%.2f", guard_orden[i].torta, guard_orden[i].precio);
            FILE *ventas;
            ventas=fopen("VentasDía.txt", "a+");
            fprintf(ventas, "\n\n\t%s\t$%.2f", guard_orden[i].torta, guard_orden[i].precio);
            fclose(ventas);
        }

        ventas_dia+=tot_pagar;

        printf("\n\n\tTotal :\t$%.2f", tot_pagar);
        printf("\n\nEfectivo:\t$");
        scanf("%f", &efectivo);
        if (efectivo==tot_pagar){
          printf("\nNo hay cambio gracias por su compra");
         }

      if (efectivo<tot_pagar){
          c=tot_pagar-efectivo;
          printf("\nLe faltan $%i", c );
     scanf("%i", &f);
              while(c!=f)
                    {
                    printf(" \n\nLe falta $ %d \n \n",c);
                     printf(" \nIngrese la cantidad correcta por favor%d \n ",c);
                          scanf("%i", &f);
                                               }
     printf(" Muchas Gracias \n");
     }
     if (efectivo>tot_pagar){//Impresión de el cambio que se entregará.

     c=efectivo-tot_pagar;
     printf("\nAqui tiene su cambio: $ %i\n", c);

}
        printf("\nFecha y hora de compra:  \n\n");
           system ("time/t");
           system ("date/t");


        //Reinicio de las variables.
        tot_pagar=0.0;
        j=0;
        getch();
        return j;
    }

    return j;
}

//Funcion principal
int main()
{
    //PARTE QUE BORRÁ EL REGISTRO ANTERIOR PARA EMPEZAR DESDE CERO EL ARCHIVO(ES OPCIONAL)
    FILE *registro;
    registro=fopen("VentasDía.txt","w");
    fclose(registro);

    struct torta_precio guar_ini[4];

        do
        {
            j++;
            imp_menu();
            //Utilizando el valor que regresa la funcion para ver cual es cierta
            switch (n)
            {
                case 99:
                    creditos();
                    getch();

                    FILE *total;
                    total=fopen("VentasDía.txt","a+");
                    fprintf(total, "\n\n\t\tVentas del dia:\t $%.2f",ventas_dia);
                    fclose(total);

                    exit (0);
                break;

                case 1:
                    guar_ini[0].torta="Cubana";
                    guar_ini[0].precio=40.00;
                    j=orden(guar_ini[0], j);
                break;

                case 2:
                    guar_ini[1].torta="Jamon";
                    guar_ini[1].precio=15.00;
                    j=orden(guar_ini[1], j);
                break;

                case 3:
                    guar_ini[2].torta="Pierna";
                    guar_ini[2].precio=25.00;
                    j=orden(guar_ini[2], j);
                break;

                case 4:
                    guar_ini[3].torta="Refresco";
                    guar_ini[3].precio=10.00;
                    j=orden(guar_ini[3], j);
                break;

                default:
                    system("cls");
                    printf("\n\n\tOpci%cn invalida presione cualquier tecla para seleccionar otra", 162);
                    j=j-1;
                    getch();

            }
        }while(1);

    return 0;
}
