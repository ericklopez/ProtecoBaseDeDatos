/*
	Programa que simula una tienda
	Hecho por Erick
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo{
	char producto[20];
	int cantidad;
	float precio;
	struct nodo *sig;
}Nodo;

Nodo* removerLista(Nodo *inicio, unsigned int index);
Nodo* borrarLista(Nodo *inicio);
void imprimirLista(Nodo *inicio);
Nodo* ingresarLista(Nodo *inicio, char prod[20], int cant ,double prec);
Nodo* leerLista(Nodo *inicio);
Nodo* guardarLista(Nodo *inicio);
Nodo* modificarLista(Nodo *inicio);

int main(int argc, char const *argv[])
{
	Nodo *lista=NULL;
	int op, eliminar, agregarCantidad;
	float agregarPrecio;
	char agregarProducto[20];

	lista = leerLista(lista);

	do{
		system("clear");
		printf("\n\t Bienvenido a la tienda n.n/ \n");
		printf("\n1.- Muestra el inventario");
		printf("\n2.- Modificar un producto");
		printf("\n3.- Eliminar un producto");
		printf("\n4.- Agregar un producto");
		printf("\n5.- Salir");
		printf("\nSeleccione una opcion: ");
		scanf("%d",&op);

		switch(op){

			case 1: 
				system("clear");
				imprimirLista(lista);
				getchar();
				getchar();
				break;

			case 2: 
				system("clear");
				modificarLista(lista);
				getchar();
				getchar();
				break;

			case 3:
				system("clear");
				imprimirLista(lista);
				printf("¿Que producto quiere eliminar?: ");
				scanf("%d", &eliminar);
				removerLista(lista, eliminar);
				printf("\nSe eliminó el producto :)");
				getchar();
				getchar();
				break;

			case 4:
				system("clear");
				printf("Escriba el nombre del producto que se quiere agregar (sin espacios): ");
				scanf("%s", agregarProducto);
				printf("\nPrecio del producto: ");
				scanf("%f", &agregarPrecio);
				printf("\nIngresa la cantidad en el inventario: ");
				scanf("%d", &agregarCantidad);
				printf("\nSe agregó el producto :D ");
				getchar();
				getchar();
				break;

			case 5:
				system("clear");
				lista=guardarLista(lista);
				borrarLista(lista);
				printf("\n\n\t Gracias, vuelva pronto n.n/");
				getchar();
				getchar();
				system("clear");
				break;

			default:
				printf("\n Opción no válida :C ");
				getchar();
				getchar();

		}
	
	}while(op!=5);

	return 0;
}

Nodo* removerLista(Nodo *inicio, unsigned int index){
	Nodo *nodoActual=inicio;
	if(inicio==NULL)
		return NULL;
	else if(index==0){
		nodoActual=inicio->sig;
		free(inicio);
		return nodoActual;
	}
	else{
		Nodo *anterior=inicio;
		int i=0;
		while(i<index && nodoActual->sig!=NULL){
			anterior=nodoActual;
			nodoActual=nodoActual->sig;
			i++;
		}
		anterior->sig=nodoActual->sig;
		free(nodoActual);
		if(i==0)
			return NULL;
	}
	return inicio;
}

Nodo *borrarLista(Nodo *inicio){
	if(inicio==NULL)
		return NULL;

	Nodo *nodoActual=inicio;
	Nodo *nodoSig=inicio->sig;
	while(nodoSig!=NULL){
		free(nodoActual);
		nodoActual=nodoSig;
		nodoSig=nodoActual->sig;
	}
	free(nodoActual);
	return NULL;
}

void imprimirLista(Nodo *inicio){
	Nodo *nodoActual = inicio;
	int i =0;
	printf("    Producto  |  Cantidad |  Precio\n\n\n");
	while(nodoActual != NULL){
		printf("%d.- %s  |  %d  |  %.2lf\n",++i,nodoActual->producto,nodoActual->cantidad,nodoActual->precio);
		nodoActual = nodoActual->sig;
	}
}

Nodo* ingresarLista(Nodo *inicio, char prod[20], int cant, double prec){
	Nodo *nodoActual = inicio;
	if(inicio==NULL){
		nodoActual = malloc(sizeof(Nodo));
		nodoActual->cantidad = cant;
		nodoActual->precio = prec;
		strcpy(nodoActual->producto,prod);

		nodoActual->sig = NULL;
		inicio = nodoActual;
	}
	else{
		while(nodoActual->sig != NULL){
			nodoActual = nodoActual->sig;
		}
		Nodo *nuevoNodo = malloc(sizeof(Nodo));
		nuevoNodo->cantidad = cant;
		nuevoNodo->precio = prec;
		strcpy(nuevoNodo->producto,prod);
		nuevoNodo->sig = NULL;
		nodoActual->sig = nuevoNodo;
	}
	return inicio;
}

Nodo* leerLista(Nodo *inicio){
	FILE *apt = fopen("inventario.txt","r");
	char prod[20];
	int cant;
	double prec;	
	
	if(!apt){
		printf("Error al abrir el archivo\n");
		return inicio;
	}
	int i=0;
	while(!feof(apt)){
		fscanf(apt,"%s %d %lf\n",prod,&cant,&prec);
		inicio=ingresarLista(inicio,prod,cant,prec);
	}

	return inicio;
}

Nodo* guardarLista(Nodo *inicio){
	FILE *apt = fopen("inventario.txt","w");
	Nodo *nodoActual = inicio;

	while(nodoActual != NULL){
		fprintf(apt,"%s %d %.2lf\n",nodoActual->producto,nodoActual->cantidad,nodoActual->precio);
		nodoActual = nodoActual->sig;
	}

	return inicio;
}

Nodo* modificarLista(Nodo *inicio){
	Nodo *nodoActual=inicio;
	int index, opcion, cantidadNueva, i=1;
	float precioNuevo;

	imprimirLista(inicio);
	printf("Selecciona el articulo que desee modificar: ");
	scanf("%d", &index);

	while(i<index && nodoActual!= NULL){
		nodoActual=nodoActual->sig;
		i++;
	}

	do{
		system("clear");
		printf("\n\t ¿Que desea modificar?\n");
		printf("\n1.- Precio");
		printf("\n2.- Cantidad");
		printf("\n3.- Salir");
		printf("\nSeleccione una opción: ");
		scanf("%d", &opcion);

		switch(opcion){
			case1:
				printf("Precio Anterior:\t %.2lf \n", nodoActual->precio);
				printf("Precio nuevo: ");
				scanf("%f", &precioNuevo);
				nodoActual->precio=precioNuevo;
				break;

			case2:
				printf("Cantidad anterior:\t %d \n", nodoActual->cantidad);
				printf("Cantidad nueva: ");
				scanf("%d", &cantidadNueva);
				nodoActual->cantidad=cantidadNueva;
				break;

			case3:
				break;

			default:
				printf("La opcion no es válida :C \n");
		}
	}while(opcion!=3);

	return inicio;
}