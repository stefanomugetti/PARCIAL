/*
 * inform.c
 *
 *  Created on: Apr 30, 2021
 *      Author: Stefano
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "validaciones.h"
#include "cliente.h"
#include "compra.h"
#define CANT_COMPRAS 1000
#define CANT_CLIENTES 100


/*
 * brief indica la cantidad de compras pendientes
 * param arrayCompras puntero al array de compras
 * param limiteCompras indica el tamaño del array de compras
 * return retorna -1(ERROR) Y 0(EXITO)
 */
int info_cantComprasPendientes(Compra* arrayCompras,int limiteCompras)
{
	int retorno=-1;
	int i;
	int contadorComprasPendientes;
	if(arrayCompras != NULL && limiteCompras >= 0)
	{
		for(i=0;i<limiteCompras;i++)
		{
			if(strncmp(arrayCompras[i].estadoCompra,"Pendiente a cobrar",22)==0)
			{
				contadorComprasPendientes++;
				retorno=0;
				printf("ABRA ENTRAO?");
			}
		}
		printf("La cantidad de compras pendientes es:%d",contadorComprasPendientes);
	}


	return retorno;
}
/*
 * brief lista la informacion de la venta
 * param arrayCompras puntero al array de compras
 * param arrayClientes puntero al array de clientes
 * param limiteCompras indica el tamaño del array de compras
 * param limiteClientes indica el tamaño del array de clientes
 * param auxIdCliente indica el id del cliente  que corresponde
 * return retorna -1(ERROR) Y 0(EXITO)
 */
int info_listarCompra(Compra* arrayCompras,Cliente* arrayClientes,int limiteCompras,int limiteClientes,int auxIdCliente)
{
	int retorno=-1;
	int i;

	if(arrayCompras != NULL && arrayClientes != NULL && limiteCompras > 0 && limiteClientes > 0 )
	{
		for(i=0;i<limiteCompras;i++)
		{
			if(arrayCompras[i].isEmpty==0)
			{
			if(arrayCompras[i].idCliente == auxIdCliente)
			{
			//	indiceArrayCompras=com_buscarId(arrayCompras,limiteCompras,auxIdCliente);
				printf("ID CLIENTE:%d\n------COMPRAS:\nCANTIDAD DE BARBIJOS:%d-----"
													"COLOR DE BARBIJO:%s-----"
													"DIRECCION DE ENTREGA:%s\n",auxIdCliente,arrayCompras[i].cantBarbijos,arrayCompras[i].colorBarbijo,arrayCompras[i].direccionDeEntrega);
				retorno=0;
			}
			}
		}
	}
	return retorno;
}
/*
 * brief lista la informacion del cliente al que le pertenece la compra
 * param arrayCompras puntero al array de compras
 * param arrayClientes puntero al array de clientes
 * param limiteCompras indica el tamaño del array de compras
 * param limiteClientes indica el tamaño del array de clientes
 * param auxIdCliente indica el id del cliente  que corresponde
 * return retorna -1(ERROR) Y 0(EXITO)
 */
int info_listarVentas(Compra* arrayCompras,Cliente* arrayClientes,int limiteCompras,int limiteClientes,int auxIdVenta,int idCliente)
{
	int retorno=-1;
	int i;
	int auxIdCliente;
	int indiceArrayCliente;
	if(arrayCompras != NULL && arrayClientes != NULL && limiteCompras > 0 && limiteClientes > 0 )
	{

		for(i=0;i<limiteCompras;i++)
		{
			if(arrayCompras[i].isEmpty==0)
			{
				if(arrayCompras[i].id==auxIdVenta)
				{
					auxIdCliente=arrayCompras[i].idCliente;
					indiceArrayCliente=cli_buscarId(arrayClientes,limiteCompras,auxIdCliente);
					printf("ID CLIENTE:%d---NOMBRE:%s-----CUIT:%s-----APELLIDO:%s----\n",arrayClientes[indiceArrayCliente].id,arrayClientes[indiceArrayCliente].nombre,arrayClientes[indiceArrayCliente].apellido,arrayClientes[indiceArrayCliente].cuit);
					retorno=0;
				}
			}
		}
	}
	return retorno;
}
/*
 * brief calcula el importe mas bajo por unidad de todas las ingresadas
 * param arrayCompras puntero al array de compras
 * param limiteCompras indica el tamaño del array de compras
 * param importeMasBajo puntero al importe mas bajo, que se devolvera
 * param auxIdCompra puntero al id de la compra especifico
 */
int	info_calcularImporteMasBajo(Compra* arrayCompras,int limiteCompras,float* importeMasBajo,int* auxIdCompra)
{
	int retorno=-1;
	int i;
	float importeBase=10000;
	float importeSegunCantidad;
	float primerValor=0;
	int flag=0;
	if(arrayCompras != NULL && limiteCompras > 0 && importeMasBajo >=0)
	{
		for(i=0;i<limiteCompras;i++)
		{
			if(arrayCompras[i].isEmpty==0)
			{
				importeSegunCantidad=(float)arrayCompras[i].importe/arrayCompras[i].cantBarbijos;
				if(importeSegunCantidad<=importeBase && flag==0)
				{
					primerValor=importeSegunCantidad;
					flag++;
				}
				if(importeSegunCantidad < primerValor && flag != 0)
				{
					*importeMasBajo=importeSegunCantidad;
						*auxIdCompra=arrayCompras[i].id;
				}
			}
		}
		retorno=0;
	}
	return retorno;
}
/*
 * brief aparece un submenu en consola y da a elegir opciones, luego se ejecutara la que el usuario decida
 * param arrayCompra define el array de las compras
 * param limiteCompras define el tamaño del array
 * param comprasPendientes contador de las compras en estado pendiente
 * return retorna -1(ERROR) y 0(EXITO)
 */
int info_subMenu(Compra* arrayCompras,int limiteCompras,int comprasPendientes)
{
	int retorno=-1;
	int opcion;
	float importeMasBajo;
	int auxIdCompra;
	if(get_int(&opcion,2,"\n--SUBMENU--\n"
						"INGRESE UNA OPCION:\n"
						"1)Mostrar color de barbijo que se compró mas veces.\n"//NO PUDE REALIZARLO
						"2)Mostrar cantidad de compras pendientes.\n"
						"3)Mostrar compra con “precio por unidad” mas bajo.\n","La opcion es incorrecta\n",1,3,2,0)==1)
	{
		switch(opcion)
		{
		case 1:
			com_calcularColorBarbijoMasComprado(arrayCompras,CANT_COMPRAS);
			break;
		case 2:
			printf("La cantidad de compras pendientes es:%d\n",comprasPendientes);
			break;
		case 3:
			info_calcularImporteMasBajo(arrayCompras,CANT_COMPRAS,&importeMasBajo,&auxIdCompra);
			printf("El importe mas bajo es:%.2f--ID DE LA COMPRA:%d\n",importeMasBajo,auxIdCompra);
			break;
		}
	}
	return retorno;
}
