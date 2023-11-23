
// Materia: Programación I, Paralelo 1

// Autor: Marvin Mollo Ramirez

// Fecha creación: 22/11/2023

// Fecha modificación: 22/11/2023

// Número de ejericio: 1

// Problema planteado: 
/*Escribe un programa que tenga un menú de tres opciones:
 
"	Ingreso de datos de los equipo de la LPFB.
"	Ingreso los resultados de los partidos.
"	Reporte de la tabla de posiciones
"	Salir
La primera opción debe ingresar los datos de los nombres de los equipos de la ligade acuerdo con la siguiente estructura y estos sean almacenados en un archivo binario llamado "EquiposLPFB.bin", se debe considerar en no duplicar los equipos de futbol por el Nombre del Equipo
struct structEquiposLPFB
{
    char nombreEquipo[50];
    char colorCamiseta[50];
    char departamento[30];
    int anioCreacion;
}; 
La segunda opción debe ingresar los resultados de los partidos, que debe almacenarse en el archivo "ResultadosLPFB.bin" de acuerdo a la siguiente estructura, se debe considerer que solo se debe colocar resultados de los equipos ingresados en el archive "EquiposLPFB.bin":
struct structResultadosLPFB
{
    char nombreEquipoLocal[50];
    char nombreEquipoVisitante[50];
    int golesEquipoLocal;
    Int golesEquipoVisitante;
    char fechaPartido[10]
};
La tercera opción debe dar un reporte de la tabla de posiciones
//no hice una porque no tenia ni idea como hacerla, este fue mi intento ;(
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <algorithm>
using namespace std;

const int MAX_EQUIPOS = 100;

struct Equipo
{
    char nombreEquipo[50];
    char colorCamiseta[50];
    char departamento[30];
    int puntos;
};

bool equipoExiste(const Equipo equipos[], int numEquipos, const char nombre[])
{
    for (int i = 0; i < numEquipos; ++i)
    {
        if (strcmp(equipos[i].nombreEquipo, nombre) == 0)
        {
            return true; // El equipo ya existe
        }
    }
    return false; // El equipo no existe
}

void ingresarEquipo(Equipo equipos[], int &numEquipos)
{
    if (numEquipos >= MAX_EQUIPOS)
    {
        cerr << "Se ha alcanzado el límite máximo de equipos." << endl;
        return;
    }

    Equipo equipo;
    cout << "Ingrese el nombre del equipo: ";
    cin.ignore();
    cin.getline(equipo.nombreEquipo, 50);

    // Verificar si el equipo ya existe
    if (equipoExiste(equipos, numEquipos, equipo.nombreEquipo))
    {
        cout << "¡Error! El equipo ya está registrado." << endl;
        return;
    }

    cout << "Ingrese el color de la camiseta: ";
    cin.getline(equipo.colorCamiseta, 50);

    cout << "Ingrese el departamento: ";
    cin.getline(equipo.departamento, 30);

    cout << "Ingrese la cantidad de puntos del equipo: ";
    cin >> equipo.puntos;

    // Guardar el equipo en la estructura
    equipos[numEquipos] = equipo;
    numEquipos++;

    // Guardar el equipo en el archivo
    ofstream archivoEquipos("EquiposLPFB.bin", ios::binary | ios::app);

    if (!archivoEquipos)
    {
        cerr << "Error al abrir el archivo de equipos." << endl;
        exit(1);
    }

    archivoEquipos.write(reinterpret_cast<char *>(&equipo), sizeof(Equipo));

    archivoEquipos.close();

    cout << "Equipo ingresado exitosamente." << endl;
}

bool compararEquipos(const Equipo &a, const Equipo &b)
{
    return a.puntos > b.puntos;
}

void generarTablaPosiciones(Equipo equipos[], int numEquipos)
{
    // Ordenar el arreglo de equipos por puntos de forma descendente
    sort(equipos, equipos + numEquipos, compararEquipos);

    // Mostrar la tabla de posiciones
    cout << setw(50) << setfill('-') << "" << setfill(' ') << endl;
    cout << setw(30) << "Tabla de Posiciones" << endl;
    cout << setw(50) << setfill('-') << "" << setfill(' ') << endl;
    cout << setw(20) << left << "Equipo" << setw(10) << right << "Puntos" << endl;
    cout << setw(50) << setfill('-') << "" << setfill(' ') << endl;

    for (int i = 0; i < numEquipos; ++i)
    {
        cout << setw(20) << left << equipos[i].nombreEquipo << setw(10) << right << equipos[i].puntos << endl;
    }

    cout << setw(50) << setfill('-') << "" << setfill(' ') << endl;
}

int main()
{
    Equipo equipos[MAX_EQUIPOS];
    int numEquipos = 0;

    int opcion;

    do
    {
        cout << "Menu:" << endl;
        cout << "1. Ingreso de datos de los equipos de la LPFB." << endl;
        cout << "2. Reporte de la tabla de posiciones." << endl;
        cout << "3. Salir." << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            ingresarEquipo(equipos, numEquipos);
            break;
        case 2:
            generarTablaPosiciones(equipos, numEquipos);
            break;
        case 3:
            cout << "Saliendo del programa." << endl;
            break;
        default:
            cout << "Opción no válida. Inténtelo de nuevo." << endl;
        }

    } while (opcion != 3);

    return 0;
}

