#pragma once
#include <iostream>
#include <string>
using namespace std;
//FUNCIONALIDADES GENERALES
void printPassword(string clave);     //Ayudara a imprimir la clave con * para asegurar que no se vea despues de ser implementada
void recibirMensaje(string mensaje, string name, int id);

//Clase Base: Persona
class Persona { //Clase base
public:            //Datos generales
    string name;
    int edad;
    char sexo;
    int no_DNI;
    Persona() { //Constructor
        name = " ";
        edad = 0;
        sexo = ' ';
        no_DNI = 0;
    }
    Persona(string _name, int _edad, char _sexo, int _dni) :
        name(_name), edad(_edad), sexo(_sexo), no_DNI(_dni)
    {}
    void pedirdatos();

    void print();
};


//CLASE DOCTOR

class Doctor :public Persona { //Creamos la clase hija Doctor 
private: //Creamos Datos privadas y publicadas
    int id;
    bool activo;
public:
    static int doctorID;
    string especialidad;
    int turnos[31];
    int cantidadCitasDia[31];
    string password;

    bool darActivo() { return activo; }
    int darID() { return id; }
    Doctor() {  //Inicializamos mediante el Constructor
        especialidad = "Sin especialidad";
        id = doctorID;
        doctorID++;
        password = " ";
        activo = true;
    }

    void pedirDatos(); 			// Creamos función para pedir los datos

    void print();       //	Le da la bienvenida al doctor(a)

    void print_Horarios();  //Si solicita imprimir su horario está función se activa

    void printInfo();//Imprime datos especificos para el paciente que lo solicita 

    void cambiarHorario(int dia_);  //Permitirá que el gerente cambie el horario

    void cambiarAct(); //Permite al gerente cambiar su actividad

    void mostrarAct(); //Muestra si está activo al gerente

    void cambiarInfo(); //Permite cambiar su información en diferentes partes del codigo
    void recibirCita(int diaCita); //El doctor recibe una nueva cita y le da la hora de su cita al paciente

    void menuDoctor(); //Creamos la funcion para el menu del doctor
};

//PACIENTE

class Paciente : public Persona {      //El cliente es una pieza fundamental en una base de datos de algun hospital, por lo que se convierte en hija de la clase Persona
private:
    bool activo;
    int id;
    int iEnf;
public:  //Colocamos las caracteristicas del cliente, las mas importante
    static int clienteID;
    double estatura;
    double peso;
    double presion;
    string* enfermedad;

    Paciente() {                   //Definimos sus caracteristicas por defecto, para no provocar mostrar archivos basura
        estatura = 0.0;
        peso = 0.0;
        presion = 0.0;
        enfermedad = new string[100];
        iEnf = 0;
        activo = true;
        id = clienteID;
        clienteID++;             //aumenta su ID
    }
    int darID();  //Da el ID

    bool darAct(); //Da la actividad de la cuenta

    void cambiarAct();  //Cambiar la actividad de la cuenta

    void mostrarAct(); //Muestra la actividad de la cuenta

    void crearc();       //Ingresar los datos para crear un nuevo objeto

    void printc();       //Immprimir los datos ingresados

    void cambiarinfo(); //Modificar la informacion del paciente


    void mostrarHistorial(); //Muestra la lista de enfermedades ingresadas

    void menuPaciente(Doctor* allDoctors); //Menu del paciente, con todas las opciones pertinentes

    ~Paciente() {
        delete[] enfermedad;
    }
};



//Gerente


class Gerente : public Persona {
private:
    int id;
public:
    static int gerenteID;
    string password;

    int darID() { return id; }

    Gerente() {
        password = "";
        id = gerenteID;
        gerenteID++;
    }
    Gerente(string _name, int _edad, char _sexo, int _dni, string _password) :Persona(_name, _edad, _sexo, _dni), password(_password) {
        id = gerenteID;
        gerenteID++;
    }

    void pedirDatos(); // Creamos función para pedir los datos

    void print();   //	Le da la bienvenida al doctor(a)


    void imprimirMensajes();

    void menuGerente(Doctor* allDoctors, Paciente* allPacientes, Gerente* allGerentes);
};


void menuGeneral(Doctor* allDoctors, Paciente* allPacientes, Gerente* allGerentes);  //Menu donde se desenvuelve el programa