//Project: Hospital Database
//Date: 20/05/2020
#include "Hospital.h"


int main() {     //Main, aqui encontramos la creacion de dos punteros dinamicos: objeto doctor y objeto paciente 

    Doctor* allDoctors = new Doctor[20];
    Paciente* allPacientes = new Paciente[20];
    Gerente* allGerentes = new Gerente[20];
    allGerentes[0].pedirDatos();
    system("CLS");
    allGerentes[0].print();
    menuGeneral(allDoctors, allPacientes, allGerentes);  //Pasamos los punteros al menu, para trabajar con ellos y sus diferentes opciones
    delete[] allGerentes;
    delete[] allPacientes;    //El respectivo destructor de cada una de las clases creadas dinamicamente
    delete[] allDoctors;
    return 0;
}