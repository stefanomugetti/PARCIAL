/*
 * contrataciones.c
 *
 *  Created on: Apr 28, 2021
 *      Author: Stefano
 */

#include "cliente.h"
#include "compra.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "validaciones.h"

#define LEN_COLOR 20
#define LEN_DIRECCION 12

/*
 * brief IMPRIMO EL ARRAY DE Compras
 * param array Puntero al array de compras
 * param limite define el tama�o del array
 * return retorna 0(EXITO) y -1(ERROR)
 *
 */
int com_imprimir(Compra* pElemento)
{
	int retorno=-1;

		if(pElemento != NULL && pElemento->isEmpty == 0)
		{
			retorno=0;
			printf("DIRECCION DE ENTREGA:%s----"
					"CANTIDAD DE BARBIJOS:%d----"
					"COLOR DE BARBIJO:%s----"
					"ID VENTA:%d----ID CLIENTE:%d\n",pElemento->direccionDeEntrega,pElemento->cantBarbijos,pElemento->colorBarbijo,pElemento->id,pElemento->idCliente);
		}
	return retorno;
}
/*
 * brief llama a la funcion para imprimir al array
 * param array Puntero al array de Compra
 * param limite define el tama�o del array
 * return retorna 0(EXITO) y -1(ERROR)
 *
 */
int com_imprimirArray(Compra* arrayCompra,int limite)
{
	int i;
	int retorno=-1;
	if(arrayCompra != NULL && limite > 0 )
	{
		retorno=0;
		for(i=0;i<limite;i++)
		{
			com_imprimir(&arrayCompra[i]);
		}
	}
	return retorno;
}



/*
 * brief INICIALIZO EL ARRAY DE PERSONAS
 * param array Puntero al array de alumnos
 * param limite define el tama�o del array
 * return retorna 0(EXITO) y -1(ERROR)
 *
 */
int com_inicializoArray(Compra* arrayCompra,int limite)
{
	int retorno=-1;
	int i;
	if(arrayCompra != NULL && limite > 0)
	{
		retorno=0;
		for(i=0;i<limite;i++)
		{
			arrayCompra[i].isEmpty = 1;
		}
	}
	return retorno;
}
/*
 * brief da de alta un array
 * param limite define el tama�o del array
 * param indice define el indice del array
 * param idCompra puntero al id generado
 * param idCliente define el id del cliente
 * return retorna -1 (ERROR) y 0(EXITO)
 */
int com_altaArray(Compra* arrayCompra,int limite,int indice,int* idCompra,int idCliente)
{
	int retorno=-1;
	Compra auxiliar;
	if(arrayCompra != NULL && idCompra != NULL && limite > 0 && indice < limite && indice >= 0 && idCliente >= 0)
	{
		if(	get_text(auxiliar.colorBarbijo,10,"Ingrese color de barbijos:\n","ERROR",2)==1 &&
			get_int(&auxiliar.cantBarbijos,4,"Ingrese cantidad de barbijos:\n","ERROR\n",0,365,2,0)==1 &&
			get_text(auxiliar.direccionDeEntrega,10,"Ingrese direccion de entrega:\n","ERROR\n",2)==1)
			{
					strncpy(auxiliar.estadoCompra,"Pendiente",15);
					auxiliar.idCliente=idCliente;
					auxiliar.id=*idCompra;
					auxiliar.isEmpty=0;
					arrayCompra[indice]=auxiliar;
					(*idCompra)++;
					retorno=0;
			}
	}

	return retorno;
}
/*
 * brief permite cambiar el estado de la compra de pendiente a cobrada
 * param arrayCompra puntero al array de las compras
 * param limite define el tama�o del array
 * param indice define el indice especifico en el array
 * return retorna -1(ERROR) y 0(EXITO)
 */
int com_pagarCompra(Compra* arrayCompra,int limite,int indice)
{
	int retorno=-1;
	Compra auxiliar;
	int opcion;
	if(arrayCompra != NULL  && limite > 0 && indice < limite && indice >= 0)
	{
		printf("Esto bien.");
		if(get_int(&auxiliar.importe,3,"\nIngrese el importe a pagar:\n","ERROR\n",0,10000,2,0)==1)
			{
				if(get_int(&opcion,3,"Desea cambiar el estado de su venta a [COBRADA]?----0)NO---1)SI:\n","ERROR\n",0,1,2,0)==1)
				{
					if(opcion == 1)
					{
						printf("Estado cambiado a 'COBRADA'");
						strncpy(auxiliar.estadoCompra,"Cobrada",20);
						retorno=0;
					}
				}
			}
	}

	return retorno;
}
/*
 * brief da de alta forzadamente a un array
 */
int com_altaForzadaArray(Compra* arrayCompra,int limiteCompras,int indice,int* idCompra,int idCliente,char* colorBarbijo,char* direccionDeEntrega,int cantBarbijos,int importe)
{
	int retorno=-1;
	Compra auxiliar;
	if(arrayCompra != NULL && idCompra != NULL && limiteCompras > 0 && indice < limiteCompras && indice >= 0)
	{
		strncpy(auxiliar.direccionDeEntrega,direccionDeEntrega,LEN_DIRECCION);
		strncpy(auxiliar.colorBarbijo,colorBarbijo,LEN_COLOR);
		strncpy(auxiliar.estadoCompra,"Pendiente",20);
		auxiliar.cantBarbijos=cantBarbijos;
		auxiliar.idCliente=idCliente;

		auxiliar.importe=importe;
		auxiliar.id=*idCompra;
		auxiliar.isEmpty=0;
		arrayCompra[indice]=auxiliar;
		(*idCompra)++;
		retorno=0;
	}
	return retorno;
}
/*
 * brief permite modificar los datos de un array
 * param limite define el tama�o del array
 * param indice define el indice del array
 * return retorna -1 (ERROR) y 0(EXITO)
 */
int com_modificarArray(Compra* arrayCompra,int limite,int indice)
{
	int retorno=-1;
	int auxDias;
	if(arrayCompra != NULL && limite > 0 && indice < limite && indice >= 0 && arrayCompra[indice].isEmpty==0)
	{
		printf("Debug");
		if(get_int(&auxDias,10,"Ingrese cantidad de dias:\n","Error\n",0,365,2,0)==1)
				{
						retorno=0;
						arrayCompra[indice].cantBarbijos=auxDias;
				}
	}
	return retorno;
}
/*
 * brief permite dar de baja un array (clientes y compras)
 * param arrayCompra puntero al array de las compras
 * param arrayCliente puntero al array de los clientes
 * param limiteCompras define el tama�o del array
 * param limiteClientes define el tama�o del array
 * param id define el id del array a dar de baja
 * return retorna -1 (ERROR) y 0(EXITO)
 */
int com_bajaArray(Compra* arrayCompra,int limiteCompra,Cliente* arrayClientes,int limiteClientes,int idCliente)
{
	int retorno=-1;
	int opcion;
	int i;
	if(arrayCompra != NULL && limiteCompra > 0 && idCliente < limiteCompra && idCliente >= 0 && arrayCompra[idCliente].isEmpty==0)
	{
		if(get_int(&opcion,2,"CONFIRME SI QUIERE ELIMINAR LOS DATOS:\n"
				   	     	 "0)NO--"
				   	     	 "1)SI","OPCION INCORRECTA.\n",0,1,2,0)==1)
		{
			if(opcion==1)
			{
				for(i=0;i<limiteCompra;i++)
				{
					arrayClientes[idCliente].isEmpty=1;
						if(arrayCompra[i].idCliente == idCliente)
						{
							arrayCompra[i].isEmpty=1;
							retorno=0;
						}

			}

		}
	}
	}
		return retorno;
}
/*
 * brief cancela una compra
 * param arrayCompra puntero al array de las compras
 * param limiteCompra define el tama�o del arrayCompras
 * param arrayClientes puntero al array de los clientes
 * param limiteClientes define el tama�o del arrayClientes
 * param idCliente define el id especifico del cliente
 */
int com_cancelarCompra(Compra* arrayCompra,int limiteCompra,Cliente* arrayClientes,int limiteClientes,int idCliente)
{
	int retorno=-1;
	int opcion;
	int i;
	if(arrayCompra != NULL && limiteCompra > 0 && idCliente < limiteCompra && idCliente >= 0 )
	{
		if(get_int(&opcion,2,"CONFIRME SI QUIERE ELIMINAR LOS DATOS:\n"
				   	     	 "0)NO--"
				   	     	 "1)SI","OPCION INCORRECTA.\n",0,1,2,0)==1)
		{
			if(opcion==1)
			{
				for(i=0;i<limiteCompra;i++)
				{
					if(arrayCompra[i].idCliente == idCliente)
					{
						printf("Se cancelo la compra.\n");
						arrayCompra[i].isEmpty=1;
						retorno=0;
					}
				}
			}
		}
	}
		return retorno;
}
/*
 * brief permite buscar el id en un array
 * param limite define el tama�o del array
 * param valor buscado para comparar y buscar la igualdad;
 * return retorna -1 (ERROR) y != -1(EXITO)
 */

int com_buscarId(Compra* arrayCompra,int limite,int valorBuscado)
{
	int retorno=-1;
	int i;
	if(arrayCompra != NULL && limite > 0 && valorBuscado >= 0)
	{
		for(i=0;i<limite;i++)
		{
			if(arrayCompra[i].id==valorBuscado)
			{
				retorno=i;
				break;
			}
		}
	}
	return retorno;
}
/*
 * brief busca las ventas del cliente
 * param arrayCompra puntero del array de compras
 * param limiteCompra define el tama�o del array de compras
 * param arrayCliente puntero al array de los clientes
 * param auxIdVenta define el id auxiliar de la venta
 *
 */
int com_buscarVentasDeCliente(Compra* arrayCompra,int limiteCompra,Cliente* arrayCliente,int auxIdVenta)
{
	int retorno=0;
	int auxIdCliente;

	for(int i=0;i<limiteCompra;i++)
	{
		if(arrayCompra[i].isEmpty == 0)
		{
			auxIdCliente=arrayCompra->idCliente;

			if(auxIdCliente == arrayCliente[i].id)

				printf("NOMBRE:%s---",arrayCliente[i].nombre);

		}
	}
	return retorno;
}
/*
 * brief inicializa el array
 * param array puntero al array de clientes
 * param limite define el tama�o del array
 * return retorna -1(ERROR) y != -1(EXITO)
 *
 */
int com_getEmptyIndex(Compra* arrayCompra,int limite)
{
	int retorno=-1;
	int i;
	if(arrayCompra != NULL && limite > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(arrayCompra[i].isEmpty==1)
			{
				retorno=i;
				break;
			}
		}
	}
	return retorno;
}
/*
 *
int com_ordenarPorNombreYCantDias(Compra* arrayCompra,int limite)
{
	int retorno=-1;
	int i;
	int flagSwap;
	int auxCmp;
	Compra buffer;
	if(arrayCompra != NULL && limite > 0)
	{
		retorno=0;
		do{
			flagSwap=0;
			for(i=0;i<limite;i++)
			{
				if(arrayCompra[i].isEmpty || arrayCompra[i+1].isEmpty)
				{
					continue;
				}
				auxCmp=strncmp(arrayCompra[i].direccionDeEntrega,arrayCompra[i+1].direccionDeEntrega,LEN_NOMBRE);
				if( auxCmp> 0 ||
					(auxCmp == 0 && arrayCompra[i].cantBarbijos < arrayCompra[i+1].cantBarbijos))
				{
					flagSwap=1;
					buffer=arrayCompra[i];
					arrayCompra[i]=arrayCompra[i+1];
					arrayCompra[i+1]=buffer;
				}
			}
		limite--;
		}while(flagSwap);
	}
	return retorno;
}
 */

int com_calcularColorBarbijoMasComprado(Compra* arrayCompras,int limiteCompras)
{
	int retorno=0;
	int i;
	if(arrayCompras != NULL && limiteCompras >0)
	{
		for(i=0;i<limiteCompras;i++)
		{

		}
	}

	return retorno;
}

