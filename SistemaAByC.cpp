#include <iostream> //librer�a standard
#include <fstream> //librer�a de manejo de archivos
#include <string> //librer�a string
#include <iomanip> //librer�a de formato para los datos de salida
#include <locale.h>//libreria para caracteres de diferentes idiomas

using namespace std;

char menu();//Funci�n para desplegar el men� principal
int contarLineas();//Funci�n que cuenta las l�neas del archivo de texto
void mensajeFinal(string mensajeF);//Funci�n que imprime un mensaje final al usuario
void darDeAlta();//Funci�n/M�dulo de altas
void darDeBaja();//Funci�n/M�dulo de bajas
char consultar();//Funci�n/M�dulo de consultas
void verTodosLosRegistros(int lineasL);//Funci�n que parte del m�dulo de consultas para imprimir toda la base de datos
void verRegistrosActivos(int lineasL);//Funci�n que parte del m�dulo de consultas para imprimir solo los registros activos a altas

//Funci�n principal
int main()
{
    setlocale(LC_CTYPE, "Spanish");//Llamar funci�n de la librer�a locale para admitir caracteres del idioma espa�ol en pantalla

    char respuesta;//Esta variable determinar� el curso del programa

    respuesta='a';//La variable se inicializa en 'a' para que pueda entrar al ciclo while

    while (respuesta=='a'||respuesta=='b'||respuesta=='c')//Ciclo while que permite el acceso a cada funcionalidad del programa
    {
        respuesta=menu();//El valor de retorno de la funci�n "menu()" se asigna a esta variable para que pueda ser evaluada nuevamente

        switch (respuesta)//Estatuto switch que finalmente da acceso a cada funcionalidad del programa
        {
            /*Si el usuario ingresa en caracter 'a', 'b' o 'c', el programa sigue el curso del m�dulo correspondiente.
            Tras la ejecuci�n de un m�dulo, el programa regresa al men� principal. Sin embargo, si la variable "respuesta"
            tiene un caracter diferente a 'a', 'b' o 'c', el programa finaliza, lo cual se indica en el men� principal al usuario*/
        case 'a':
            darDeAlta();//Para respuesta='a', se ejecuta el m�dulo de altas, y se "rompe" el estatuto switch
            break;
        case 'b':
            darDeBaja();//Para respuesta='b', se ejecuta el m�dulo de bajas, y se "rompe" el estatuto switch
            break;
        case 'c':
            respuesta=consultar();/*Para respuesta='c', se ejecuta el m�dulo de consultas, el cual al final regresa un valor
            que se asigna a la variable "respuesta" para que el programa pueda regresar al men� principal, y se "rompe" el estatuto switch*/
            break;
        default://El caso por defecto implica una variable "respuesta" diferente de 'a', 'b' o 'c', de modo que el programa finaliza.
            break;
        }
    }

    //Una vez que el usuario se dispone a finalizar el programa, se imprime un �ltimo mensaje
    system("CLS");

    cout << "-------------------------------------------------" << endl << "Vuelve pronto"
    << endl << "-------------------------------------------------" << endl;

    return 0;
}

char menu()//Funci�n para desplegar el men� principal
{
    system("CLS");//Se limpia lo que hay en pantalla tras la posible ejecuci�n de un m�dulo

    char opcion;//El valor de esta variable se retornar� para determinar qu� caso del estatuto switch ejecutar

    //Impresi�n de indicaciones al usuario
    cout << "-------------------------------------------------" << endl << "�Bienvenido al men� principal! Elige una opci�n"
    << endl << "-------------------------------------------------" << endl << "A. Realizar una alta" << endl
    << "B. Realizar una baja" << endl << "C. Consultar el registro" << endl << endl << "Ingresa cualquier otro valor para salir"
    << endl << "-------------------------------------------------" << endl;

    cin >> opcion;//Inicializaci�n de la variable "opcion"
    cin.sync();//Limpieza de b�fer
    opcion=tolower(opcion);/*Para el caso de entradas en may�sculas, �stas se cambiar�n a min�sculas con el fin de que el usuario
    tenga "libertad" de cometer alg�n error al ingresar su entrada*/

    return opcion;
}

int contarLineas()//Funci�n que cuenta las l�neas del archivo de texto
{
    string registro;//Variable para vaciar el contenido del archivo de texto y poder "evaluarlo"
    int lineasLeidas;//Variable cuyo valor ser� el de las l�neas con texto del archivo de texto
    //Declaraci�n y asignaci�n de la variable tipo fstream que permitir� acceder al archivo de texto "Registro.txt"
    ifstream consulta;
    consulta.open("Registro.txt");

    if (consulta.fail())//Si el archivo presenta un error o no existe, se retornar� un valor de -1
    {
        return -1;
    }

    else
    {
       while (getline(consulta,registro))//Ciclo while que sumar� 1 l�nea le�da mientras encuentre l�neas con texto en el archivo
        lineasLeidas++;

       return lineasLeidas;/*El valor de retorno ser� el n�mero de l�neas con texto en el archivo, con el fin de
       que cada m�dulo lo utilice a su manera*/
    }

    consulta.close();//Cierre de la variable tipo fstream
}

void mensajeFinal(string mensajeF)/*Funci�n que imprime un mensaje final al usuario, personalizable, hasta cierto punto, con
el par�metro "mensajeF" de acuerdo al m�dulo utilizado*/
{
    char resp;//El uso de esta variable es con el fin de detener el programa

    cout << endl << "-------------------------------------------------------"
    << endl << mensajeF << endl << endl<< "Ingresa cualquier valor para continuar" << endl
    << "-------------------------------------------------------" << endl;

    cin >> resp;//Una vez que el usuario ingrese un valor, el programa continuar�
}

void darDeAlta()//Funci�n/M�dulo de altas
{
    ofstream escritura;//Variable tipo fstream para imprimir los datos en el archivo

    string mensaje;//Mensaje que ser� utilizado en la funci�n "mensajeFinal(string mensajeF)" como par�metro
    int numRegistro=1;//Contador de registros inicializado en 1 para un primer usuario
    int lineasLeidas;//Contador de l�neas con texto en el archivo
    string nombre, aPaterno, aMaterno;//Datos del usuario
    int edad, escuelaTipo;//Datos del usuario
    string escuelaTipo2;//Variable para cambiar el tipo de escuela de un valor entero a un string
    string respuesta1, respuesta2, respuesta3, respuesta4, respuesta5;//Variables que almacenar�n las respuestas del usuario

    //Asignaci�n del archivo "Registro.txt" a la variable tipo fstream "escritura"
    escritura.open("Registro.txt",ios::app);//La opci�n ios::app permite agregar nuevos registros al archivo sin sobreescribir su contenido

    lineasLeidas=contarLineas();/*Uso de la funci�n para contar las l�neas con texto en el archivo, cuyo valor de retorno se asigna a
    la variable "lineasLeidas"*/

    for (int i=0; i<lineasLeidas; i=i+10)/*Ciclo for que permitir� saber cu�ntos registros se han hecho, para al final
    crear una clave �nica de acuerdo a ello*/
    {
        numRegistro++;//El contador de registros aumentar� si existe un determinado n�mero de l�neas (10 l�neas por registro)
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
    cout << "Tipo de escuela\n1. P�blica" << setw(19) << "\n2. Privada: ";
    cin >> escuelaTipo;
    cin.sync();
    cout << endl << "�Cu�l crees que es la mejor manera de tomar clases? ";
    getline(cin,respuesta1);
    cout << endl <<"�Cu�l ha sido tu mayor dificultad en las clases en l�nea? ";
    getline(cin,respuesta2);
    cout << endl <<"�C�mo realizas tus trabajos en equipo? ";
    getline(cin,respuesta3);
    cout << endl <<"�Qu� haces en tu tiempo libre? ";
    getline(cin,respuesta4);
    cout << endl <<"Si pudieras dise�ar una clase, �c�mo lo har�as? ";
    getline(cin,respuesta5);


    //Traducci�n a palabras del tipo de escuela del estudiante
    if (escuelaTipo == 1)
        escuelaTipo2 = "P�blica";
    else if (escuelaTipo == 2)
        escuelaTipo2 = "Privada";
    else
        escuelaTipo2 = "n/a";

    //Impresi�n de datos en el archivo, el cual se asign� a la variable tipo fstream "escritura"
    escritura << "A" << setw(6) << setfill('0') << right << numRegistro << endl;//Creaci�n y escritura de la clave �nica de registro
    //Escritura del resto de datos del usuario en el archivo
    escritura << nombre << " " << aPaterno << " " << aMaterno << endl
                << edad << endl
                << escuelaTipo2 << endl
                << respuesta1 << endl
                << respuesta2 << endl
                << respuesta3 << endl
                << respuesta4 << endl
                << respuesta5 << endl
                << "Activo" << endl;//La palabr� "Activo" se traduce en un estado de alta

    //Cierre de variable tipo fstream
    escritura.close();

    /*Creaci�n e impresi�n del mensaje final del m�dulo para el usuario, a trav�s de la variable "mensaje" como par�metro de la funci�n
    mensajeFinal(string mensajeF)*/
    mensaje="�Registro exitoso!";
    mensajeFinal(mensaje);
}

void darDeBaja()//Funci�n/M�dulo de bajas
{
    system("CLS");//Se limpia lo que hay en pantalla tras la posible ejecuci�n de un m�dulo

    //Variables tipo fstream para la manipulaci�n de los archivos de texto
    ifstream consulta;
    ofstream baja;

    string mensaje;//Mensaje que ser� utilizado en la funci�n "mensajeFinal(string mensajeF)" como par�metro
    string clave, nombre, edad, escuelaTipo, res1, res2, res3, res4, res5, estado;//Variables para la manipulaci�n de datos en el registro
    string claveIng;//Variable para la clave �nica de registro que ingresar� el usuario
    int lineasLeidas;//Contador de l�neas con texto en el archivo

    lineasLeidas=contarLineas();//Conteo de l�neas con texto en el archivo

    if (lineasLeidas==-1)//Si el archivo de registro presenta un error o no existe, se mostrar� al usuario y se regresar� al men� principal
    {
        mensaje="�Error! Archivo de registro inexistente";
        mensajeFinal(mensaje);
    }

    else
    {
        //Asignaci�n de archivos a las variables tipo fstream
        consulta.open("Registro.txt");
        baja.open("temp.txt");//Este archivo ser� el nuevo registro con la baja llevada a cabo

        //Impresi�n de instrucciones para el usuario
        cout << "-------------------------------------------------------" << endl << "Ingresa la clave �nica de registro" << endl
        << "-------------------------------------------------------" << endl << endl;

        cin >> claveIng;//Entrada del usuario de la clave �nica de registro

        for (int i=0; i<lineasLeidas; i=i+10)//Ciclo for que permitir� asignar cada dato de cada registro a una variable
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
            cambiar� a "Inactivo" y, tanto este dato como el resto, se escribir�n en el archivo "temp.txt"*/
            {
                estado="Inactivo";
                baja << clave << endl << nombre << endl << edad << endl << escuelaTipo << endl << res1
                << endl << res2 << endl << res3 << endl << res4 << endl << res5 << endl << estado << endl;
            }
            else/*Si la clave ingresada por el usuario no coincide con la del registro en turno, todos los datos pasar�n sin modificaci�n
            alguna al archivo "temp.txt"*/
            {
                baja << clave << endl << nombre << endl << edad << endl << escuelaTipo << endl << res1
                << endl << res2 << endl << res3 << endl << res4 << endl << res5 << endl << estado << endl;
            }

        }

        //Una vez que se hayan evaluado todas las l�neas del registro, las variables tipo fstream se cerrar�n
        consulta.close();
        baja.close();

        /*Dado que el archivo "Registro.txt" queda obsoleto, �ste es sustituido por el archivo con el registro actualizado
        "temp.txt", al cual se le cambia el nombre para que sea, en todo sentido, el nuevo registro*/
        remove("Registro.txt");
        rename("temp.txt","Registro.txt");

        //Impresi�n de un mensaje final para el usuario
        mensaje="�Proceso realizado con �xito!\n\nLa baja no se reflejar� si la clave ingresada no existe";
        mensajeFinal(mensaje);
    }
}

char consultar()//Funci�n/M�dulo de consultas
{
    system("CLS");//Se limpia lo que hay en pantalla tras la posible ejecuci�n de un m�dulo

    string mensaje;//Mensaje que ser� utilizado en la funci�n "mensajeFinal(string mensajeF)" como par�metro
    int lineasLeidas;//Contador de l�neas con texto en el archivo
    char resp;//Esta variable determinar� el curso del programa

    lineasLeidas=contarLineas();//Conteo de l�neas con texto en el archivo

    if (lineasLeidas==-1)//Si el archivo de registro presenta un error o no existe, se mostrar� al usuario y se regresar� al men� principal
    {
        mensaje="�Error! Archivo de registro inexistente";
        mensajeFinal(mensaje);
        return 'a';
    }

    else
    {
        //Impresi�n de instrucciones para el usuario
        cout << "-------------------------------------------------------" << endl << "Elige una opci�n"
        << endl << "-------------------------------------------------------" << endl << endl
        << "1. Ver todos los registros hechos hasta la fecha" << endl << "2. Ver solamente los registros activos"
        << endl << endl << "Ingresa cualquier otro valor para cancelar" << endl << endl;

        cin >> resp;

        if (resp=='1')//Con esta opci�n el usuario acceder� a todos los registros
        {
            verTodosLosRegistros(lineasLeidas);
            return 'a';
        }
        else if (resp=='2')//Con esta opci�n el usuario acceder� solamente a los registros activos
        {
            verRegistrosActivos(lineasLeidas);
            return 'a';
        }
        else//En caso de igresar otro valor, el usuario regresar� al men� principal
        {
            return 'a';
        }
    }
}

void verTodosLosRegistros(int lineasL)/*Funci�n que parte del m�dulo de consultas para imprimir toda la base de datos,
as� como del n�mero de l�neas con texto le�das como par�metro*/
{
    system("CLS");//Limpieaza de pantalla

    ifstream consulta;//Creaci�n de variable tipo fstream

    string mensaje;//Mensaje que ser� utilizado en la funci�n "mensajeFinal(string mensajeF)" como par�metro
    string clave, nombre, edad, escuelaTipo, res1, res2, res3, res4, res5, estado;//Variables para la consulta de datos en el registro

    consulta.open("Registro.txt");//Asignaci�n del archivo de registro a la variable tipo fstream


    for (int i=0; i<lineasL; i=i+10)//Ciclo for que imprimir� cada registro encontrado en el archivo
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

    //Impresi�n de mensaje final
    mensaje="Estos son todos los registros disponibles";
    mensajeFinal(mensaje);
}

void verRegistrosActivos(int lineasL)/*Funci�n que parte del m�dulo de consultas para imprimir solo las altas de la base de datos,
as� como del n�mero de l�neas con texto le�das como par�metro*/
{
    system("CLS");//Limpieza de pantalla

    ifstream consulta;//Creaci�n de variable tipo fstream

    string mensaje;//Mensaje que ser� utilizado en la funci�n "mensajeFinal(string mensajeF)" como par�metro
    string clave, nombre, edad, escuelaTipo, res1, res2, res3, res4, res5, estado;//Variables para la consulta de datos en el registro

    consulta.open("Registro.txt");//Asignaci�n del archivo de registro a la variable tipo fstream


    for (int i=0; i<lineasL; i=i+10)//Ciclo for que imprimir� cada registro activo encontrado en el archivo
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

    //Impresi�n de mensaje final
    mensaje="Estos son todos los registros disponibles";
    mensajeFinal(mensaje);
}
