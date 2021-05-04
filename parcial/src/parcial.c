/*
 ============================================================================
 Name        : PROYECTO.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cliente.h"
#include "compra.h"
#include "utn.h"
#include "validaciones.h"
#include "inform.h"

#define CANT_CLIENTES 100
#define CANT_COMPRAS 1000

int main(void) {
	setbuf(stdout,NULL);
	Cliente arrayClientes[CANT_CLIENTES];
	Compra arrayCompras[CANT_COMPRAS];
	int idClientes=0;
	int idCompras=0;
	int opcion;
	int auxIndice;
	int auxIndiceCompras;
	int auxIdCliente;
	int auxId;
	int auxIdVenta;
	int contadorIndicesClientes;
	int contadorComprasPendientes=0;
	fflush(stdin);
	cli_inicializoArray(arrayClientes, CANT_CLIENTES);//INICIALIZO ARRAy
	com_inicializoArray(arrayCompras, CANT_COMPRAS);//INICIALIZO ARRAY

	cli_altaForzadaArray(arrayClientes,CANT_CLIENTES,0,&idClientes,"stefano","44320339000","mugetti");//altas forzadas
	cli_altaForzadaArray(arrayClientes,CANT_CLIENTES,1,&idClientes,"jose","25640339000","pepe");//altas forzadas
	cli_altaForzadaArray(arrayClientes,CANT_CLIENTES,2,&idClientes,"alan","99990339000","paco");//altas forzadas
	contadorIndicesClientes=2;//0-1-2

	com_altaForzadaArray(arrayCompras,CANT_COMPRAS,0,&idCompras,1,"rojo","alsina",20,200);//altas forzadas
	com_altaForzadaArray(arrayCompras,CANT_COMPRAS,1,&idCompras,0,"verde","alberdi",50,300);
	com_altaForzadaArray(arrayCompras,CANT_COMPRAS,2,&idCompras,1,"ro","rofi",30,100);
	com_altaForzadaArray(arrayCompras,CANT_COMPRAS,3,&idCompras,2,"rober","fino",90,990);
	com_altaForzadaArray(arrayCompras,CANT_COMPRAS,4,&idCompras,2,"resd","oroo",60,1000);
	contadorComprasPendientes=4;//0-1-2-3-4
	do{
	if(get_int(&opcion,3,"Ingrese una opcion\n"	//MENU
							"1)DAR DE ALTA UN CLIENTE\n"
							"2)MODIFICAR DATOS DE CLIENTE\n"
							"3)BAJA DE CLIENTE\n"
							"4)REALIZAR COMPRA\n"
							"5)PAGAR COMPRA\n"
							"6)CANCELAR COMPRA\n"
							"7)IMPRIMIR CLIENTES\n"
							"8)INFORME\n"
							"9)SALIR\n","Opcion incorrecta.",1,9,2,0)==1)
	{
			switch(opcion)
			{
			case 1://FUNCIONANDO
				auxIndice=getEmptyIndex(arrayClientes,CANT_CLIENTES);//BUSCO UN INDICE VACIO
				if(auxIndice>=0)
				{
					if(cli_altaArray(arrayClientes,CANT_CLIENTES,auxIndice,&idClientes)!=0)//ALTA DE ARRAY CLIENTES
					{
						printf("Carga fallida.\n");
						contadorIndicesClientes++;
					}
					else
					{
						printf("Carga realizada con exito\n");
					}
				}
				break;
			case 2://FUNCIONANDO
				cli_imprimirArray(arrayClientes, CANT_CLIENTES);
				if(get_int(&auxId,2,"Indique el id del cliente a modificar:\n","ID invalido.",0,100,2,0)==1)
				{
					auxIndice=cli_buscarId(arrayClientes, CANT_CLIENTES,auxId);//valida el id ingresado
					if(auxIndice >=0)
					{
						cli_modificarArray(arrayClientes, CANT_CLIENTES, auxIndice);//modifica los datos
						printf("Modificacion realizada con exito\n");
					}
					else
					{
						printf("Modificacion no realizada.\n");
					}
				}
				break;
			case 3://FUNCIONANDO
				if(get_int(&auxIdCliente,2,"Indique el id del cliente a dar de baja:\n","ID invalido",0,100,2,0)==1)//PIDO ID
				{
					auxIndice =cli_buscarId(arrayClientes,CANT_CLIENTES,auxIdCliente);//BUSCO EL ID Y LO GUARDO EN LA VARIABLE AUXILIAR
					if(auxIndice >= 0 && info_listarCompra(arrayCompras,arrayClientes,CANT_COMPRAS,CANT_CLIENTES,auxIdCliente)==0)//SI EL ID EXISTE -> auxIndice >= 0 y listo sus compras
					{
						com_bajaArray(arrayCompras,CANT_COMPRAS,arrayClientes,CANT_CLIENTES,auxIdCliente);//doy de baja al cliente y sus compras
					}
					else
					{
						printf("El cliente no tiene compras.\n");
					}
				}
				break;
			case 4: //FUNCIONANDO
				auxIndiceCompras=com_getEmptyIndex(arrayCompras,CANT_COMPRAS);//BUSCO ARRAY LIBRE EN EL ARRAYCOMPRAS
				if(auxIndiceCompras>=0)
				{
					if(get_int(&auxId,3,"Ingrese el id del cliente:\n", "ERROR",0,contadorIndicesClientes,2,0)==1)  //INGRESA EL ID DEL CLIENTE
					{
						if(cli_buscarId(arrayClientes,CANT_CLIENTES,auxId) == -1)//SI LA FUNCION RETORNA =1 EL ID NO EXISTE
						{
							printf("El ID no existe.\n");
						}
						else
						{
							if(com_altaArray(arrayCompras,CANT_COMPRAS,auxIndiceCompras,&idCompras,auxId)==0)//INGRESA LOS DATOS QUE PIDE LA FUNCION
							{
								contadorComprasPendientes++;
								printf("Carga realizada con exito\n");
								printf("ID de la venta:%d\n",idCompras);
							}
						}
					}
				}
				break;
			case 5:////FUNCIONANDO
				com_imprimirArray(arrayCompras,CANT_COMPRAS);//MUESTO LAS COMPRAS CON SU ID
					get_int(&auxIdVenta, 3, "Ingrese el id de la compra:\n", "Error\n", 0,contadorComprasPendientes, 2, 0);
						if(info_listarVentas(arrayCompras, arrayClientes, CANT_COMPRAS, CANT_CLIENTES,auxIdVenta,1)==0)//Lista la informacion del cliente del id de la venta ingresada
						{
							if(com_pagarCompra(arrayCompras,CANT_COMPRAS,auxIdVenta)==0)//funcion que cambia el estado de la venta de "pendiente" a "cobrada"
							{
								contadorComprasPendientes--;
							}
						}
				break;
			case 6://FUNCIONANDO
				com_imprimirArray(arrayCompras,CANT_COMPRAS);//MUESTO LAS COMPRAS CON SU ID (((DEBUG))))
				if(get_int(&auxIdVenta, 3, "Ingrese el id de la venta:\n", "El id es incorrecto.\n",0,contadorComprasPendientes,2,0)==1)	//ACA PIDO UN CUIT
				{
					com_buscarVentasDeCliente(arrayCompras,CANT_COMPRAS,arrayClientes,auxIdVenta);	//ACA MUESTRO LAS DOS ENTIDADES
					if(com_buscarId(arrayCompras,CANT_COMPRAS,auxIdVenta) != -1) //SI LA FUNCION RETORNA =1 EL ID NO EXISTE
					{
						if(info_listarVentas(arrayCompras, arrayClientes, CANT_COMPRAS, CANT_CLIENTES,auxIdVenta,auxId)==0)//Lista la informacion del cliente del id de la venta ingresada
						{
							com_cancelarCompra(arrayCompras, CANT_COMPRAS, arrayClientes,CANT_CLIENTES,auxId);//CANCELACION DE LA COMPRA
							contadorComprasPendientes--; //SE VA A CANCELAR SI ESTA PENDIENTE
						}
					}
				}
				break;
			case 7://IMPRIMO EL ARRAY DE CLIENTES
				cli_imprimirArray(arrayClientes,CANT_CLIENTES);
				break;
			case 8:
				info_subMenu(arrayCompras,CANT_COMPRAS,contadorComprasPendientes);//	info_submenu
				break;
			}
		}
	}while(opcion != 9);
	printf("\n¡¡QUE TENGA UN BUEN DIA!!\nVUELVA PRONTO.\n");

return EXIT_SUCCESS;
}
