#include <iostream> //librería standard
#include <fstream> //librería de manejo de archivos
#include <string> //librería string
#include <iomanip> //librería de formato para los datos de salida
#include <locale.h>//libreria para caracteres de diferentes idiomas

using namespace std;

char menu();//Función para desplegar el menú principal
int contarLineas();//Función que cuenta las líneas del archivo de texto
void mensajeFinal(string mensajeF);//Función que imprime un mensaje final al usuario
void darDeAlta();//Función/Módulo de altas
void darDeBaja();//Función/Módulo de bajas
char consultar();//Función/Módulo de consultas
void verTodosLosRegistros(int lineasL);//Función que parte del módulo de consultas para imprimir toda la base de datos
void verRegistrosActivos(int lineasL);//Función que parte del módulo de consultas para imprimir solo los registros activos a altas

//Función principal
int main()
{
    setlocale(LC_CTYPE, "Spanish");//Llamar función de la librería locale para admitir caracteres del idioma español en pantalla

    char respuesta;//Esta variable determinará el curso del programa

    respuesta='a';//La variable se inicializa en 'a' para que pueda entrar al ciclo while

    while (respuesta=='a'||respuesta=='b'||respuesta=='c')//Ciclo while que permite el acceso a cada funcionalidad del programa
    {
        respuesta=menu();//El valor de retorno de la función "menu()" se asigna a esta variable para que pueda ser evaluada nuevamente

        switch (respuesta)//Estatuto switch que finalmente da acceso a cada funcionalidad del programa
        {
            /*Si el usuario ingresa en caracter 'a', 'b' o 'c', el programa sigue el curso del módulo correspondiente.
            Tras la ejecución de un módulo, el programa regresa al menú principal. Sin embargo, si la variable "respuesta"
            tiene un caracter diferente a 'a', 'b' o 'c', el programa finaliza, lo cual se indica en el menú principal al usuario*/
        case 'a':
            darDeAlta();//Para respuesta='a', se ejecuta el módulo de altas, y se "rompe" el estatuto switch
            break;
        case 'b':
            darDeBaja();//Para respuesta='b', se ejecuta el módulo de bajas, y se "rompe" el estatuto switch
            break;
        case 'c':
            respuesta=consultar();/*Para respuesta='c', se ejecuta el módulo de consultas, el cual al final regresa un valor
            que se asigna a la variable "respuesta" para que el programa pueda regresar al menú principal, y se "rompe" el estatuto switch*/
            break;
        default://El caso por defecto implica una variable "respuesta" diferente de 'a', 'b' o 'c', de modo que el programa finaliza.
            break;
        }
    }

    //Una vez que el usuario se dispone a finalizar el programa, se imprime un último mensaje
    system("CLS");

    cout << "-------------------------------------------------" << endl << "Vuelve pronto"
    << endl << "-------------------------------------------------" << endl;

    return 0;
}

char menu()//Función para desplegar el menú principal
{
    system("CLS");//Se limpia lo que hay en pantalla tras la posible ejecución de un módulo

    char opcion;//El valor de esta variable se retornará para determinar qué caso del estatuto switch ejecutar

    //Impresión de indicaciones al usuario
    cout << "-------------------------------------------------" << endl << "¡Bienvenido al menú principal! Elige una opción"
    << endl << "-------------------------------------------------" << endl << "A. Realizar una alta" << endl
    << "B. Realizar una baja" << endl << "C. Consultar el registro" << endl << endl << "Ingresa cualquier otro valor para salir"
    << endl << "-------------------------------------------------" << endl;

    cin >> opcion;//Inicialización de la variable "opcion"
    cin.sync();//Limpieza de búfer
    opcion=tolower(opcion);/*Para el caso de entradas en mayúsculas, éstas se cambiarán a minúsculas con el fin de que el usuario
    tenga "libertad" de cometer algún error al ingresar su entrada*/

    return opcion;
}

int contarLineas()//Función que cuenta las líneas del archivo de texto
{
    string registro;//Variable para vaciar el contenido del archivo de texto y poder "evaluarlo"
    int lineasLeidas;//Variable cuyo valor será el de las líneas con texto del archivo de texto
    //Declaración y asignación de la variable tipo fstream que permitirá acceder al archivo de texto "Registro.txt"
    ifstream consulta;
    consulta.open("Registro.txt");

    if (consulta.fail())//Si el archivo presenta un error o no existe, se retornará un valor de -1
    {
        return -1;
    }

    else
    {
       while (getline(consulta,registro))//Ciclo while que sumará 1 línea leída mientras encuentre líneas con texto en el archivo
        lineasLeidas++;

       return lineasLeidas;/*El valor de retorno será el número de líneas con texto en el archivo, con el fin de
       que cada módulo lo utilice a su manera*/
    }

    consulta.close();//Cierre de la variable tipo fstream
}

void mensajeFinal(string mensajeF)/*Función que imprime un mensaje final al usuario, personalizable, hasta cierto punto, con
el parámetro "mensajeF" de acuerdo al módulo utilizado*/
{
    char resp;//El uso de esta variable es con el fin de detener el programa

    cout << endl << "-------------------------------------------------------"
    << endl << mensajeF << endl << endl<< "Ingresa cualquier valor para continuar" << endl
    << "-------------------------------------------------------" << endl;

    cin >> resp;//Una vez que el usuario ingrese un valor, el programa continuará
}

void darDeAlta()//Función/Módulo de altas
{
    ofstream escritura;//Variable tipo fstream para imprimir los datos en el archivo

    string mensaje;//Mensaje que será utilizado en la función "mensajeFinal(string mensajeF)" como parámetro
    int numRegistro=1;//Contador de registros inicializado en 1 para un primer usuario
    int lineasLeidas;//Contador de líneas con texto en el archivo
    string nombre, aPaterno, aMaterno;//Datos del usuario
    int edad, escuelaTipo;//Datos del usuario
    string escuelaTipo2;//Variable para cambiar el tipo de escuela de un valor entero a un string
    string respuesta1, respuesta2, respuesta3, respuesta4, respuesta5;//Variables que almacenarán las respuestas del usuario

    //Asignación del archivo "Registro.txt" a la variable tipo fstream "escritura"
    escritura.open("Registro.txt",ios::app);//La opción ios::app permite agregar nuevos registros al archivo sin sobreescribir su contenido

    lineasLeidas=contarLineas();/*Uso de la función para contar las líneas con texto en el archivo, cuyo valor de retorno se asigna a
    la variable "lineasLeidas"*/

    for (int i=0; i<lineasLeidas; i=i+10)/*Ciclo for que permitirá saber cuántos registros se han hecho, para al final
    crear una clave única de acuerdo a ello*/
    {
        numRegistro++;//El contador de registros aumentará si existe un determinado número de líneas (10 líneas por registro)
    }

    system("CLS");//Limpieza de pantalla

    //Mensaje con instrucciones para el usuario
    cout << "-------------------------------------------------------" << endl << "Ingresa los datos que se solicitan" << endl
    << "-------------------------------------------------------" << endl << endl;

    //Captura de datos
    cout << setw(18) << left <<"Nombre(s): ";
    getline(cin,nombre);
    cout << setw(18) << "Apellido paterno: ";
    getline(cin,aPaterno);;
    cout << setw(18) << "Apellido materno: ";
    getline(cin,aMaterno);
    cout << setw(18) << "Edad: ";
    cin >> edad;
    cout << "Tipo de escuela\n1. Pública" << setw(19) << "\n2. Privada: ";
    cin >> escuelaTipo;
    cin.sync();
    cout << endl << "¿Cuál crees que es la mejor manera de tomar clases? ";
    getline(cin,respuesta1);
    cout << endl <<"¿Cuál ha sido tu mayor dificultad en las clases en línea? ";
    getline(cin,respuesta2);
    cout << endl <<"¿Cómo realizas tus trabajos en equipo? ";
    getline(cin,respuesta3);
    cout << endl <<"¿Qué haces en tu tiempo libre? ";
    getline(cin,respuesta4);
    cout << endl <<"Si pudieras diseñar una clase, ¿cómo lo harías? ";
    getline(cin,respuesta5);


    //Traducción a palabras del tipo de escuela del estudiante
    if (escuelaTipo == 1)
        escuelaTipo2 = "Pública";
    else if (escuelaTipo == 2)
        escuelaTipo2 = "Privada";
    else
        escuelaTipo2 = "n/a";

    //Impresión de datos en el archivo, el cual se asignó a la variable tipo fstream "escritura"
    escritura << "A" << setw(6) << setfill('0') << right << numRegistro << endl;//Creación y escritura de la clave única de registro
    //Escritura del resto de datos del usuario en el archivo
    escritura << nombre << " " << aPaterno << " " << aMaterno << endl
                << edad << endl
                << escuelaTipo2 << endl
                << respuesta1 << endl
                << respuesta2 << endl
                << respuesta3 << endl
                << respuesta4 << endl
                << respuesta5 << endl
                << "Activo" << endl;//La palabrá "Activo" se traduce en un estado de alta

    //Cierre de variable tipo fstream
    escritura.close();

    /*Creación e impresión del mensaje final del módulo para el usuario, a través de la variable "mensaje" como parámetro de la función
    mensajeFinal(string mensajeF)*/
    mensaje="¡Registro exitoso!";
    mensajeFinal(mensaje);
}

void darDeBaja()//Función/Módulo de bajas
{
    system("CLS");//Se limpia lo que hay en pantalla tras la posible ejecución de un módulo

    //Variables tipo fstream para la manipulación de los archivos de texto
    ifstream consulta;
    ofstream baja;

    string mensaje;//Mensaje que será utilizado en la función "mensajeFinal(string mensajeF)" como parámetro
    string clave, nombre, edad, escuelaTipo, res1, res2, res3, res4, res5, estado;//Variables para la manipulación de datos en el registro
    string claveIng;//Variable para la clave única de registro que ingresará el usuario
    int lineasLeidas;//Contador de líneas con texto en el archivo

    lineasLeidas=contarLineas();//Conteo de líneas con texto en el archivo

    if (lineasLeidas==-1)//Si el archivo de registro presenta un error o no existe, se mostrará al usuario y se regresará al menú principal
    {
        mensaje="¡Error! Archivo de registro inexistente";
        mensajeFinal(mensaje);
    }

    else
    {
        //Asignación de archivos a las variables tipo fstream
        consulta.open("Registro.txt");
        baja.open("temp.txt");//Este archivo será el nuevo registro con la baja llevada a cabo

        //Impresión de instrucciones para el usuario
        cout << "-------------------------------------------------------" << endl << "Ingresa la clave única de registro" << endl
        << "-------------------------------------------------------" << endl << endl;

        cin >> claveIng;//Entrada del usuario de la clave única de registro

        for (int i=0; i<lineasLeidas; i=i+10)//Ciclo for que permitirá asignar cada dato de cada registro a una variable
        {
            getline(consulta, clave);
            getline(consulta, nombre);
            getline(consulta, edad);
            getline(consulta, escuelaTipo);
            getline(consulta, res1);
            getline(consulta, res2);
            getline(consulta, res3);
            getline(consulta, res4);
            getline(consulta, res5);
            getline(consulta, estado);

            if (clave==claveIng)/*Si la clave ingresada por el usuario coincide con la del registro en turno, su estado correspondiente
            cambiará a "Inactivo" y, tanto este dato como el resto, se escribirán en el archivo "temp.txt"*/
            {
                estado="Inactivo";
                baja << clave << endl << nombre << endl << edad << endl << escuelaTipo << endl << res1
                << endl << res2 << endl << res3 << endl << res4 << endl << res5 << endl << estado << endl;
            }
            else/*Si la clave ingresada por el usuario no coincide con la del registro en turno, todos los datos pasarán sin modificación
            alguna al archivo "temp.txt"*/
            {
                baja << clave << endl << nombre << endl << edad << endl << escuelaTipo << endl << res1
                << endl << res2 << endl << res3 << endl << res4 << endl << res5 << endl << estado << endl;
            }

        }

        //Una vez que se hayan evaluado todas las líneas del registro, las variables tipo fstream se cerrarán
        consulta.close();
        baja.close();

        /*Dado que el archivo "Registro.txt" queda obsoleto, éste es sustituido por el archivo con el registro actualizado
        "temp.txt", al cual se le cambia el nombre para que sea, en todo sentido, el nuevo registro*/
        remove("Registro.txt");
        rename("temp.txt","Registro.txt");

        //Impresión de un mensaje final para el usuario
        mensaje="¡Proceso realizado con éxito!\n\nLa baja no se reflejará si la clave ingresada no existe";
        mensajeFinal(mensaje);
    }
}

char consultar()//Función/Módulo de consultas
{
    system("CLS");//Se limpia lo que hay en pantalla tras la posible ejecución de un módulo

    string mensaje;//Mensaje que será utilizado en la función "mensajeFinal(string mensajeF)" como parámetro
    int lineasLeidas;//Contador de líneas con texto en el archivo
    char resp;//Esta variable determinará el curso del programa

    lineasLeidas=contarLineas();//Conteo de líneas con texto en el archivo

    if (lineasLeidas==-1)//Si el archivo de registro presenta un error o no existe, se mostrará al usuario y se regresará al menú principal
    {
        mensaje="¡Error! Archivo de registro inexistente";
        mensajeFinal(mensaje);
        return 'a';
    }

    else
    {
        //Impresión de instrucciones para el usuario
        cout << "-------------------------------------------------------" << endl << "Elige una opción"
        << endl << "-------------------------------------------------------" << endl << endl
        << "1. Ver todos los registros hechos hasta la fecha" << endl << "2. Ver solamente los registros activos"
        << endl << endl << "Ingresa cualquier otro valor para cancelar" << endl << endl;

        cin >> resp;

        if (resp=='1')//Con esta opción el usuario accederá a todos los registros
        {
            verTodosLosRegistros(lineasLeidas);
            return 'a';
        }
        else if (resp=='2')//Con esta opción el usuario accederá solamente a los registros activos
        {
            verRegistrosActivos(lineasLeidas);
            return 'a';
        }
        else//En caso de igresar otro valor, el usuario regresará al menú principal
        {
            return 'a';
        }
    }
}

void verTodosLosRegistros(int lineasL)/*Función que parte del módulo de consultas para imprimir toda la base de datos,
así como del número de líneas con texto leídas como parámetro*/
{
    system("CLS");//Limpieaza de pantalla

    ifstream consulta;//Creación de variable tipo fstream

    string mensaje;//Mensaje que será utilizado en la función "mensajeFinal(string mensajeF)" como parámetro
    string clave, nombre, edad, escuelaTipo, res1, res2, res3, res4, res5, estado;//Variables para la consulta de datos en el registro

    consulta.open("Registro.txt");//Asignación del archivo de registro a la variable tipo fstream


    for (int i=0; i<lineasL; i=i+10)//Ciclo for que imprimirá cada registro encontrado en el archivo
    {
      getline(consulta, clave);
      getline(consulta, nombre);
      getline(consulta, edad);
      getline(consulta, escuelaTipo);
      getline(consulta, res1);
      getline(consulta, res2);
      getline(consulta, res3);
      getline(consulta, res4);
      getline(consulta, res5);
      getline(consulta, estado);

      cout << "----------------------------------------------------------------------" << endl;
      cout << "Clave: " << clave << endl << "Nombre: " << nombre << endl << "Edad: " << edad
      << endl << "Tipo de escuela: " << escuelaTipo << endl << "Respuesta 1: " << res1
      << endl << "Respuesta 2: " << res2 << endl << "Respuesta 3: " << res3 << endl
      << "Respuesta 4: " << res4 << endl << "Respuesta 5: " << res5 << endl << "Estado: " << estado << endl;
      cout << "----------------------------------------------------------------------" << endl;
    }

    consulta.close();//Cierre de la variable tipo fstream

    //Impresión de mensaje final
    mensaje="Estos son todos los registros disponibles";
    mensajeFinal(mensaje);
}

void verRegistrosActivos(int lineasL)/*Función que parte del módulo de consultas para imprimir solo las altas de la base de datos,
así como del número de líneas con texto leídas como parámetro*/
{
    system("CLS");//Limpieza de pantalla

    ifstream consulta;//Creación de variable tipo fstream

    string mensaje;//Mensaje que será utilizado en la función "mensajeFinal(string mensajeF)" como parámetro
    string clave, nombre, edad, escuelaTipo, res1, res2, res3, res4, res5, estado;//Variables para la consulta de datos en el registro

    consulta.open("Registro.txt");//Asignación del archivo de registro a la variable tipo fstream


    for (int i=0; i<lineasL; i=i+10)//Ciclo for que imprimirá cada registro activo encontrado en el archivo
    {
      getline(consulta, clave);
      getline(consulta, nombre);
      getline(consulta, edad);
      getline(consulta, escuelaTipo);
      getline(consulta, res1);
      getline(consulta, res2);
      getline(consulta, res3);
      getline(consulta, res4);
      getline(consulta, res5);
      getline(consulta, estado);

      if (estado!="Inactivo")
      {
         cout << "----------------------------------------------------------------------" << endl;
      cout << "Clave: " << clave << endl << "Nombre: " << nombre << endl << "Edad: " << edad
      << endl << "Tipo de escuela: " << escuelaTipo << endl << "Respuesta 1: " << res1
      << endl << "Respuesta 2: " << res2 << endl << "Respuesta 3: " << res3 << endl
      << "Respuesta 4: " << res4 << endl << "Respuesta 5: " << res5 << endl << "Estado: " << estado << endl;
      cout << "----------------------------------------------------------------------" << endl;
      }
    }

    consulta.close();//Cierre de la variable tipo fstream

    //Impresión de mensaje final
    mensaje="Estos son todos los registros disponibles";
    mensajeFinal(mensaje);
}
