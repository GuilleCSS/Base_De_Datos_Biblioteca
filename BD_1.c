#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char Titulo[30];
    char Genero[20];
    char Autor[50];
    char Disponibilidad[15];
    char Ubicacion[50];
    int Popularidad;
    struct node *next;
};

struct node *head=NULL;

void guardarLibros() {
    FILE *archivo;
    struct node *temp = head;
    
    archivo = fopen("libros.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.");
        return;
    }

    while (temp != NULL) {
        fprintf(archivo, "%s|%s|%s|%s|%s|%d\n", temp->Titulo, temp->Genero, temp->Autor, temp->Disponibilidad, temp->Ubicacion, temp->Popularidad);
        temp = temp->next;
    }
    
    fclose(archivo);
}

void cargarLibros() {
    FILE *archivo;
    struct node *nuevo, *temp;

    archivo = fopen("libros.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.");
        return;
    }

    while (1) {
        nuevo = (struct node*)malloc(sizeof(struct node));
        if (fscanf(archivo, " %[^|]| %[^|]| %[^|]| %[^|]| %[^|]| %d\n", nuevo->Titulo, nuevo->Genero, nuevo->Autor, nuevo->Disponibilidad, nuevo->Ubicacion, &(nuevo->Popularidad)) != EOF) {
            nuevo->next = NULL;
        
            if (head == NULL) {
                head = nuevo;
                temp = nuevo;
            } else {
                temp->next = nuevo;
                temp = temp->next;
            }
        } else {
            break;
        }
    }
    
    fclose(archivo);
}

struct usuario
{
    char Nombre[50];
    char NumeroCelular[15];
    char Historial[100];
    struct usuarios *next;
};

struct usuario *headUs=NULL;

void guardarUsuarios() {
    FILE *archivo;
    struct usuario *temp = headUs;
    
    archivo = fopen("usuarios.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.");
        return;
    }

    while (temp != NULL) {
        fprintf(archivo, "%s|%s|%s\n", temp->Nombre, temp->NumeroCelular, temp->Historial);
        temp = temp->next;
    }
    
    fclose(archivo);
}

void cargarUsuarios() {
    FILE *archivo;
    struct usuario *nuevo, *temp;

    archivo = fopen("usuarios.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.");
        return;
    }

    while (1) {
        nuevo = (struct usuario*)malloc(sizeof(struct usuario));
        if (fscanf(archivo, " %[^|]| %[^|]| %[^\n]", nuevo->Nombre, nuevo->NumeroCelular, nuevo->Historial) != EOF) {
            nuevo->next = NULL;
        
            if (headUs == NULL) {
                headUs = nuevo;
                temp = nuevo;
            } else {
                temp->next = nuevo;
                temp = temp->next;
            }
        } else {
            break;
        }
    }
    
    fclose(archivo);
}

void devolucion()
{
	struct node *tempLib;
	tempLib=head;
	char NombreLib[30];
	printf("\nIngresa el Titulo del libro:\n");
	fgets(NombreLib, sizeof(NombreLib),stdin);
	while(strcmp(NombreLib, tempLib->Titulo) != 0){
    	tempLib=tempLib->next;
	}
	if(tempLib != NULL && strcmp(tempLib->Disponibilidad, "Prestado\n") == 0){
    	printf("\nSe ha Devuelto el Libro\n");
    	strcpy(tempLib->Disponibilidad, "Disponible\n");
	}
}

void prestamo()
{
	struct usuario *temp;
	struct node *tempLib;
	temp=headUs;
	tempLib=head;
	int opc1;
	int indice;
	char NombreLib[30];
	char Nombretemp[50];
	
	printf("Ingresa tu nombre:");
	fgets(Nombretemp, sizeof(Nombretemp),stdin);
	while(strcmp(temp->Nombre,Nombretemp) != 0)
    {
        temp=temp->next;    
    }
    printf("\nUsuario: %s",temp->Nombre);
    printf("\nSelecciona el metodo para buscar un libro:\n");
    printf("\n1.Buscar por Genero\n");
    printf("\n2.Buscar por Titulo\n");
    printf("\n3.Buscar por Autor\n");
    printf("\n--------------------------------------\n");
    scanf("%d",&opc1);
    fflush(stdin);
    switch(opc1)
    {
		case 1:
	    	searchGen();
	    break;
	    case 2:
	    	searchTit();
	    break;
	    case 3:
	    	searchAut();
	    break;
	}
	printf("\nIngresa el Titulo del libro\n");
	fgets(NombreLib, sizeof(NombreLib),stdin);
    while(strcmp(NombreLib, tempLib->Titulo) != 0){
    	tempLib=tempLib->next;
	}
	if(tempLib != NULL && strcmp(tempLib->Disponibilidad, "Disponible\n") == 0){
		strcpy(tempLib->Disponibilidad, "Prestado\n");
		// Concatenar arreglo2 al final de arreglo1
    	// Agregar separador entre los títulos
strcat(temp->Historial, tempLib->Titulo);
/*
strcat(temp->Historial, "|");  // Separador entre títulos

// Añadir una nueva línea al final del historial si no está presente
if (temp->Historial[strlen(temp->Historial) - 1] != '\n') {
    strcat(temp->Historial, "\n");
}
*/
    	printf("\nUbicación del Libro: %s\n", tempLib->Ubicacion);
    	tempLib->Popularidad++;
    	printf("\nSe ha apartado el libro\n");
	}
	else{
		printf("\nEl libro no esta disponible\n");
	}
    // Eliminar caracteres de nueva línea o espacio en blanco al final del historial
size_t len = strlen(temp->Historial);
while (len > 0 && (temp->Historial[len - 1] == '\n' || temp->Historial[len - 1] == ' ')) {
    temp->Historial[--len] = '\0';
}
    
}

void createUs()
{
    struct usuario *NewUs, *temp;
    NewUs=(struct usuario *) malloc(sizeof(struct usuario));
    printf("\nNombre: ");
    fgets(NewUs->Nombre, sizeof(NewUs->Nombre),stdin);
    printf("\nIngresa un número de celular:");	
	fgets(NewUs->NumeroCelular, sizeof(NewUs->NumeroCelular),stdin);
	NewUs->Historial[0] = '\0';
    NewUs->next=NULL;
    if(headUs==NULL)
    {
        headUs=NewUs;
    }
    else
    {
        temp=headUs;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=NewUs;
    }
}

void displayUs()
{
    struct usuario *temp;
    if(headUs==NULL)
    {
        printf("\nLa lista esta vacian\n");
        return;
    }
    else
    {
        temp=headUs;
        printf("\nLos usuarios existentes son: \n");
        while(temp!=NULL)
        {
            printf("\nNombre: %s",temp->Nombre);
            printf("Numero de celular: %s",temp->NumeroCelular);
            printf("Historial de Prestamos: %s\n",temp->Historial);
            temp=temp->next;
        }
    }
}

void searchTit()
{
	
	char busqueda[20];
	printf("Titulo a buscar:");
	fgets(busqueda, sizeof(busqueda),stdin);
	struct node *temp;
	 if(head==NULL)
    {
        printf("\nLa lista esta vacian\n");
        return;
    }
    else
    {
        temp=head;
        printf("\nLibros con el mismo titulo: \n");
        int i=1;
        while(temp!=NULL)
        {
        	if(strcmp(temp->Titulo,busqueda) == 0){
	        	printf("ID:%d\n", i);
	            printf("Titulo: %s\n",temp->Titulo);
	            printf("Genero: %s\n",temp->Genero);
	            printf("Autor: %s\n",temp->Autor);
	            printf("Disponibilidad: %s\n",temp->Disponibilidad);
	            	if(temp->Disponibilidad=="Disponible\n"){
	            		printf("Ubicacion: %s\n",temp->Ubicacion);		
					}
			}
            i++;
            temp=temp->next;
        }
    }
}

void searchAut()
{
	
	char busqueda[20];
	printf("Autor a buscar:");
	fgets(busqueda, sizeof(busqueda),stdin);
	struct node *temp;
	 if(head==NULL)
    {
        printf("\nLa lista esta vacian\n");
        return;
    }
    else
    {
        temp=head;
        printf("\nLos elementos de este autor son: \n");
        int i=1;
        while(temp!=NULL)
        {
        	if(strcmp(temp->Autor,busqueda) == 0){
	        	printf("ID:%d\n", i);
	            printf("Titulo: %s\n",temp->Titulo);
	            printf("Genero: %s\n",temp->Genero);
	            printf("Autor: %s\n",temp->Autor);
	            printf("Disponibilidad: %s\n",temp->Disponibilidad);
	            	if(temp->Disponibilidad=="Disponible\n"){
	            		printf("Ubicacion: %s\n",temp->Ubicacion);		
					}
			}
            i++;
            temp=temp->next;
        }
    }
}

void searchGen()
{
	
	char busqueda[20];
	printf("Genero a buscar:");
	fgets(busqueda, sizeof(busqueda),stdin);
	struct node *temp;
	 if(head==NULL)
    {
        printf("\nLa lista esta vacian\n");
        return;
    }
    else
    {
        temp=head;
        printf("\nLos elementos de este genero son: \n");
        int i=1;
        while(temp!=NULL)
        {
        	if(strcmp(temp->Genero,busqueda) == 0){
	        	printf("ID:%d\n", i);
	            printf("Titulo: %s\n",temp->Titulo);
	            printf("Genero: %s\n",temp->Genero);
	            printf("Autor: %s\n",temp->Autor);
	            printf("Disponibilidad: %s\n",temp->Disponibilidad);
	            	if(temp->Disponibilidad=="Disponible\n"){
	            		printf("Ubicacion: %s\n",temp->Ubicacion);		
					}
			}
            i++;
            temp=temp->next;
        }
    }
}

void create()
{
    struct node *NewNode, *temp;
    NewNode=(struct node *) malloc(sizeof(struct node));
    printf("\nTitulo del libro: ");
    fgets(NewNode->Titulo, sizeof(NewNode->Titulo),stdin);
    printf("\nSelecciona el genero que mejor describe al libro:\n");
		printf("Biología\n");
		printf("Matematicas\n");
		printf("Química\n");
		printf("Geografía\n");
		printf("Física\n");
		printf("Idiomas\n");
		printf("Mecanica\n");
		printf("Suspenso\n");
		printf("Terror\n");
		printf("Policiacos\n");
		printf("Romance\n");
		printf("Ciencia Ficcion\n");
		printf("Mitologias\n");
		printf("Leyendas\n");
		printf("\n--------------------------------------\n");
		printf("\nIngresa el genero:");
		fgets(NewNode->Genero, sizeof(NewNode->Genero),stdin);
	printf("\nAutor del libro: ");
    fgets(NewNode->Autor, sizeof(NewNode->Autor),stdin);
    printf("\nDisponibilidad del libro (Disponible/Prestado): ");
    fgets(NewNode->Disponibilidad, sizeof(NewNode->Disponibilidad),stdin);
    printf("\nUbicacion del libro: ");
    fgets(NewNode->Ubicacion, sizeof(NewNode->Ubicacion),stdin);
    NewNode->Popularidad=0;
    NewNode->next=NULL;
    if(head==NULL)
    {
        head=NewNode;
    }
    else
    {
        temp=head;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=NewNode;
    }
}

void display()
{
    struct node *temp;
    if(head==NULL)
    {
        printf("\nLa lista esta vacian\n");
        return;
    }
    else
    {
        temp=head;
        printf("\nLos elementos de la lista son: \n");
        int i=1;
        while(temp!=NULL)
        {
        	printf("ID:%d\n", i);
            printf("Titulo: %s\n",temp->Titulo);
            printf("Genero: %s\n",temp->Genero);
            printf("Autor: %s\n",temp->Autor);
            printf("Disponibilidad: %s\n",temp->Disponibilidad);
            printf("Ubicacion: %s\n",temp->Ubicacion);
            printf("Numero de veces prestado: %d\n",temp->Popularidad);
            i++;
            temp=temp->next;
        }
    }
}

void insertarI()
{
    struct node *NewNode, *temp;
    NewNode=(struct node *) malloc(sizeof(struct node));
    printf("\nTitulo del libro: ");
    fgets(NewNode->Titulo, sizeof(NewNode->Titulo),stdin);
    printf("\nSelecciona el genero que mejor describe al libro:\n");
		printf("Biología\n");
		printf("Matematicas\n");
		printf("Química\n");
		printf("Geografía\n");
		printf("Física\n");
		printf("Idiomas\n");
		printf("Mecanica\n");
		printf("Suspenso\n");
		printf("Terror\n");
		printf("Policiacos\n");
		printf("Romance\n");
		printf("Ciencia Ficcion\n");
		printf("Mitologias\n");
		printf("Leyendas\n");
		printf("\n--------------------------------------\n");
		printf("\nIngresa el genero:");
		fgets(NewNode->Genero, sizeof(NewNode->Genero),stdin);
    printf("\nAutor del libro: ");
    fgets(NewNode->Autor, sizeof(NewNode->Autor),stdin);
    printf("\nDisponibilidad del libro (Disponible/Prestado): ");
    fgets(NewNode->Disponibilidad, sizeof(NewNode->Disponibilidad),stdin);
    printf("\nUbicacion del libro: ");
    fgets(NewNode->Ubicacion, sizeof(NewNode->Ubicacion),stdin);
    NewNode->next=NULL;
    NewNode->Popularidad=0;
    if(head==NULL)
    {
        head=NewNode;
    }
    else
    {
        NewNode->next=head;
        head=NewNode;

    }

}

void insertarPos()
{
    struct node *temp,*NewNode;
    int i, pos;
    NewNode=(struct node *)malloc(sizeof (struct node));
    printf("\nEscribe la posicion: ");
    scanf("%d ",&pos);
    fflush(stdin);
    printf("\nTitulo del libro: ");
    fgets(NewNode->Titulo, sizeof(NewNode->Titulo),stdin);
    printf("\nSelecciona el genero que mejor describe al libro:\n");
		printf("Biología\n");
		printf("Matematicas\n");
		printf("Química\n");
		printf("Geografía\n");
		printf("Física\n");
		printf("Idiomas\n");
		printf("Mecanica\n");
		printf("Suspenso\n");
		printf("Terror\n");
		printf("Policiacos\n");
		printf("Romance\n");
		printf("Ciencia Ficcion\n");
		printf("Mitologias\n");
		printf("Leyendas\n");
		printf("\nIngresa el genero:");
		printf("\n--------------------------------------\n");
	    fgets(NewNode->Genero, sizeof(NewNode->Genero),stdin);
    printf("\nAutor del libro: ");
    fgets(NewNode->Autor, sizeof(NewNode->Autor),stdin);
    printf("\nDisponibilidad del libro (Disponible/Prestado): ");
    fgets(NewNode->Disponibilidad, sizeof(NewNode->Disponibilidad),stdin);;
    printf("\nUbicacion del libro: ");
    fgets(NewNode->Ubicacion, sizeof(NewNode->Ubicacion),stdin);
    NewNode->Popularidad=0;
    NewNode->next=NULL;
    if(pos==0)
    {
        NewNode->next=head;
        head=NewNode;

    }
    else
    {
        for(i=1,temp=head;i<pos-1;i++){
            temp=temp->next;
            if(temp==NULL)
            {
                printf("\nNo exite la posicion\n");
                return;
            }

        }
        NewNode->next=temp->next;
        temp->next=NewNode;
    }
}

void deletePos()
{
    int i, pos;
    struct node *NewNode,*temp;
    if(head==NULL)
    {
        printf("\nLa lista esta vacia\n");
        return;
    }
    else
    {
        printf("\nEscribe el ID del libro a borrar: ");
        scanf("%d",&pos);
        if(pos==0)
        {
            temp=head;
            head=head->next;
            printf("Se elimino el libro %s ",temp->Titulo);
            free(temp);
        }
        else
        {
            temp=head;
            for(i=0;i<pos-1;i++)
            {
                NewNode=temp;
                temp=temp->next;
                if(temp==NULL)
                {
                    printf("\n EL ID no existe \n");
                    return;
                }
            }
            NewNode->next=temp->next;
            printf("\nSe elimino el libro %s",temp->Titulo);
            free(temp);
        }
    }
}

int main()
{
	int pasword=2468;
	int intento;
    int opc;
    int opc1;
    int opc2;
    menuPrincipal: // Etiqueta para el menú principal
    while(1){
        printf("\n                MENU	PRINCIPAL                       \n");
        printf("\n 1.Menu de Usuario\n");
        printf("\n 2.Menu Administrativon\n");
        printf("\n 3.Salir\n");
        printf("\n--------------------------------------\n");
        printf("Seleccione:\t");
        scanf("%d",&opc);
        fflush(stdin);
        switch(opc)
        {
            case 1:
            	menuUsuario:
                while(1)
					{
			        printf("\n                MENU DE USUARIO                             \n");
			        printf("\n 1.Crear Nuevo Usuario\n");
			        printf("\n 2.Solicitar Prestamo\n");
			        printf("\n 3.Hacer Devolucion\n");
			        printf("\n 4.Salir\n");;
			        printf("\n--------------------------------------\n");
			        printf("Seleccione:\t");
			        scanf("%d",&opc1);
			        fflush(stdin);
			        switch(opc1)
			        {	
			            case 1:
			            	createUs();
			            	break;
			            case 2:
			            	prestamo();
			            	break;	
			            case 3:
			            	devolucion();
			            	break;
			            case 4:
			                goto menuPrincipal;
			            default:
			                printf("\n NO existe la opcion\n");
			                break;
			        }
    			}
                break;
            case 2:
            	printf("\nIngresa la Contraseña:");
            	scanf("%d",&intento);
			    fflush(stdin);
			    if(intento != pasword){
			    	printf("\nContraseña Incorrecta\n");
					goto menuPrincipal;
				}
            	menuAdministrativo:
                while(1)
					{
			        printf("\n                MENU ADMINISTRATIVO                             \n");
			        printf("\n 1.Mostrar Contenido de la Base de Datos\n");
			        printf("\n 2.Agregar Nuevo Libro al Finalde la Base de Datos\n");
			        printf("\n 3.Agregar Nuevo Libro al Principio de la Base de Datos\n");
			        printf("\n 4.Agregar Nuevo Libro por Posición:\n");;
			        printf("\n 5.ELiminar por ID de la Base de Datos\n");
			        printf("\n 6.Buscar Libros por Genero\n");
			        printf("\n 7.Buscar Libros por Titulo\n");
			        printf("\n 8.Buscar Libros por Autor\n");
			        printf("\n 9.Mostrar Base de Datos de los Usuarios\n");
			        printf("\n 10.Guardar Base de Datos de los Libros\n");
			        printf("\n 11.Cargar Base de Datos de los Libros Desde el Archivo\n");
			        printf("\n 12.Guardar Base de Datos de los Usuarios\n");
			        printf("\n 13.Cargar Base de Datos de los Usuarios Desde el Archivo\n");
			        printf("\n 14.Salir\n");
			        printf("\n--------------------------------------\n");
			        printf("Seleccione:\t");
			        scanf("%d",&opc2);
			        fflush(stdin);
			        switch(opc2)
			        {
			            case 1:
			                display();
			                break;
			            case 2:
			                create();
			                break;
			            case 3:
			                insertarI();
			                break;
			            case 4:
			                insertarPos();
			                break;
			            case 5:
			                deletePos();
			                break;
			            case 6:
			            	searchGen();
			            	break;	
			            case 7:
			            	searchTit();
			            	break;
			            case 8:
			            	searchAut();
			            	break;
			            case 9:
			            	displayUs();
			            	break;	
			            case 10:
			            	guardarLibros();
			            	break;
			            case 11:
			            	cargarLibros();
			            	break;
			            case 12:
			            	guardarUsuarios();
			            	break;
			            case 13:
			            	cargarUsuarios();
			            	break;
			            case 14:
			                goto menuPrincipal;
			            default:
			                printf("\n NO existe la opcion\n");
			                break;
			        }
    			}
                break;
            case 3:
                exit(0);
                break;
            default:
                printf("\n NO existe la opcion\n");
                break;
        }
    }
    return 0;
}
