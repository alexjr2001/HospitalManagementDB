#include "Hospital.h"

//Variables generales que utilizaremos dentro del menu general (moverlas dentro del menu general)
int iPac = 0;
int iDoc = 0;
int iGer = 1;

string nombreClinica;


//FUNCIONES GENERALES

void printPassword(string clave) {                //Ayudara a imprimir la clave con * para asegurar que no se vea despues de ser implementada
    int largo = clave.length();
    int i = 0;
    cout << "\nSu password es: ";
    while (i < largo) {
        cout << "*";
        i++;
    }
    cout << endl;
    return;
}

string mensajes[1000];
string emisores[1000];
int idEmisores[1000];
string mensajesLeidos[1000];
string emisoresLeidos[1000];
int IDemisoresLeidos[1000];
void recibirMensaje(string mensaje, string name, int id) {      //Recibe y prepara los mensajes para que el gerente los vea            
    string parte1 = "\n\nMensaje del doctor(a) ";
    string concatenar = parte1 + name + "\n\n" + mensaje;

    int i = 0;
    bool find = false;
    while (find == false) {
        if (mensajes[i].length() <= 0) { //Introduce el mensaje en el índice correcto
            mensajes[i] = concatenar;
            emisores[i] = name;
            idEmisores[i] = id;
            find = true;
        }
        else {
            i++;
        }
    }
    cout << "ENVIADO";
    return;
}


//CLASE BASE: PERSONA-------------------------------------------------------
void Persona::pedirdatos() {    //Pide los datos que cualquier persona tiene
    cout << "Ingrese el nombre completo: ";
    getline(cin, name);
    cout << "\nIngrese su edad: ";
    cin >> edad;
    cout << "\nIngrese su numero de DNI: ";
    cin >> no_DNI;
    cout << "\nIngrese su sexo \n'M' (Masculino) o 'F' (Femenino) o 'O' (Otros): ";
    cin.ignore();
    cin >> sexo;
    return;
}
void Persona::print() { //Imprimir datos
    cout << name;
    cout << "\nEdad: " << edad;
    if (sexo == 'M' || sexo == 'm') {  //Le damos mas especificacion al Sexo ingresado
        cout << "\nSexo: Masculino";
    }
    else if (sexo == 'F' || sexo == 'f') {
        cout << "\nSexo: Femenino";
    }
    else if (sexo == 'O' || sexo == 'o') {
        cout << "\nSexo: Otros";
    }
    else {
        cout << "\nVuelva a ingresar su sexo!!!!!!!!!!!!!!!!";
    }
    cout << "\nNo DNI: " << no_DNI;
    return;
}



//CLASE DOCTOR------------------------------------------------------------------------

string doctores[10000]; //Nombres   //Arrays que almacenarán cada dato de cada doctor
string especialidades[10000]; //Especialidades
int IDdoctores[10000]; //IDexistentes
int Doctor::doctorID = 10000;
void Doctor::pedirDatos() { 			// Creamos función para pedir los datos
    cout << "\nCREANDO UN DOCTOR(A) \n\n";
    cin.ignore();
    Persona::pedirdatos();
    cout << "\nIngrese su especialidad: ";
    cin.ignore();
    getline(cin, especialidad);
    cout << "\nIngrese su clave: ";
    cin >> password;

    for (int i = 0; i < 31; i++) { //Se crean horarios de manera automatica
        int turno = rand() % 5;
        turnos[i] = turno;
        if (turnos[i] == 4) {  	//Si le toca noche, al siguiente día no puede trabajar
            turnos[i + 1] = 0;
            i++;
        }
        cantidadCitasDia[i] = 0; //Inicializamos la cantidad de citas que tiene ese dia
    }
    doctores[id - 10000] = name;  //Agregamos los datos a cada array
    especialidades[id - 10000] = especialidad;
    IDdoctores[id - 10000] = id;
    return;
}
void Doctor::print() {   //	Le da la bienvenida al doctor(a)
    cout << "\nBienvenido Dr(a). ";
    Persona::print();  //Llamamos a la funcion imprimir de la clase padre
    cout << "\nSu ID es el número: " << id << "\nSu especialidad es: " << especialidad;
    printPassword(password); //Imprime el password encriptado
    return;
}

void Doctor::print_Horarios() {   //Si solicita imprimir su horario está función se activa
    string parteDia;
    cout << "\nDIA\tTURNO\n";
    for (int i = 0; i < 31; i++) {
        if (i < 9) {
            cout << " "; 		//Solo para darle orden a la impresión
        }
        if (turnos[i] == 0) {
            parteDia = "    --   \n";
        }
        else if (turnos[i] == 1) {
            parteDia = "Turno Mañana\n";
        }
        else if (turnos[i] == 2) {
            parteDia = "Turno Tarde\n";
        }
        else if (turnos[i] == 3) {
            parteDia = "Turno Dia Entero\n";
        }
        else {
            parteDia = "Turno Noche\n";
        }
        cout << i + 1 << " | " << parteDia;
    }
    return;
}
void Doctor::printInfo() {  //Imprime datos especificos para el paciente que lo solicita
    cout << name << endl;
    cout << "\nSu ID es el número: " << id << "\nSu especialidad es: " << especialidad << endl;
    cout << "\nHorario del doctor\n";
    print_Horarios();
    return;
}

void Doctor::cambiarHorario(int dia_) { //Permitirá que el gerente cambie el horario
    int cambio;
    string parteDia;
    if (turnos[dia_ - 1] == 0) {			//Condicionales que le dan información
        parteDia = "no tiene turno";
    }
    else if (turnos[dia_ - 1] == 1) {
        parteDia = "tiene turno Mañana\n";

    }
    else if (turnos[dia_ - 1] == 2) {
        parteDia = "tiene turno Tarde\n";
    }
    else if (turnos[dia_ - 1] == 3) {
        parteDia = "tiene turno Todo el Dia\n";
    }
    else {
        parteDia = "tiene turno Noche\n";
    }
    cout << "\nEse día " << parteDia << "\n\nTURNOS\n\n 1) Dia Libre\n 2) Mañana\n 3) Tarde\n 4) Dia Entero\n 5) Noche\n\nIngrese la opción donde el doctor tendrá su turno: ";
    cin >> cambio;                 //Que turno cambiará para el horario
    turnos[dia_ - 1] = cambio - 1;

    return;
}

void Doctor::cambiarAct() {	//Para que el gerente cambie si el doctor está activo o no
    if (activo == true) {
        activo = false;
    }
    else {
        activo = true;
    }
    return;
}
void Doctor::mostrarAct() {	//Muestra si está el doctor activo o no
    cout << "La cuenta se encuentra ";
    if (activo == true) {
        cout << "activada!.";
    }
    else {
        cout << "NO activada.";
    }
    return;
}
void Doctor::cambiarInfo() { 				//Encapsulamos todo lo que es cambiar datos del doctor
    int select;
    cout << "\nQue desea modificar: \n 1) Nombre \n 2) Especialidad\n 3) Edad \n 4) Cambiar Password \nIngrese su opcion: ";
    cin >> select;
    system("CLS");
    switch (select) { //En cada caso editará la opción ingresada
    case 1:
        cout << "Ingrese su nombre: ";
        cin.ignore();
        getline(cin, name);
        break;
    case 2:
        cout << "Ingrese su espeialidad: ";
        cin.ignore();
        getline(cin, especialidad);
        break;
    case 3:
        cout << "Ingrese su edad: ";
        cin >> edad;
        break;
    case 4:
        cout << "Ingrese su nuevo password: ";
        cin >> password;
        break;
    default:
        cout << "Valor incorrecto\n Ingrese de nuevo\n";
        menuDoctor();
    }
    return;
}

void Doctor::recibirCita(int diaCita) {			//Ayuda a darle la hora y el día que el paciente puede reservar una cita
    double hora = 7.50;
    int dia = diaCita - 1;
    cantidadCitasDia[dia] += 1;
    if (turnos[dia] == 0) {								//Para que no reserven un día que no trabaja
        cout << "\nEse día no trabaja\n";
    }
    else if (turnos[dia] > 3) {				//En la noche solo atiende emergencia
        cout << "\nDe noche solo se atiende emergencia\n";
    }
    else if (turnos[dia] == 3 && cantidadCitasDia[dia] == 25) {  //Para que no tenga muchas citas
        cantidadCitasDia[dia]--;
        cout << "El doctor se encuentra ya ocupado";
    }
    else if (cantidadCitasDia[dia] == 13) {
        cantidadCitasDia[dia]--;
        cout << "El doctor se encuentra ya ocupado";
    }
    else if (cantidadCitasDia[dia] % 2 == 1) {      //Algoritmo que le dará la hora al paciente que solicita la cita
        if (turnos[dia] == 2) {
           hora += (cantidadCitasDia[dia]*0.50) + 6.0;
        }
        else {
           hora += cantidadCitasDia[dia]*0.50;
        }
        cout << "\nCita reservada a las " << hora;
    }
    else {
        if (turnos[dia] == 2) {
           hora += (cantidadCitasDia[dia]*0.50) + 5.80;
        }
        else {
           hora += (cantidadCitasDia[dia]*0.50)-0.20;
        }
        cout << "\nCita reservada a las " << hora << "0";
    }
    return;
}

void Doctor::menuDoctor() { //Creamos la funcion para el menu del doctor
    int seleccion; //Almacena el Input que ingresará el usuario
    string clave;
    int tries = 0;  //Intentos que el doctor intenta poner la clave
    do {
        cout << "Ingrese su clave: ";
        cin >> clave;
        if (clave == password) {
            bool input = false;
            while (input == false) {
                cout << "\nMENU \n 1) Editar tus datos \n 2) Ver tu horario \n 3) Enviar solicitud a administración (Cambio de horario, una reunión, etc.) \n 4) Cerrar Sesión \n Ingrese el número de la opción: "; //Opciones que puede elegir el doctor
                cin >> seleccion;
                if (seleccion == 1) {  //Editar datos
                    input = true;
                    system("CLS");
                    cambiarInfo();
                    print();
                }
                else if (seleccion == 2) { //Imprimir Horario
                    input = true;
                    system("CLS");
                    cout << "Este es su horario \n";
                    print_Horarios();
                }
                else if (seleccion == 3) { //Mandar un mensaje
                    input = true;
                    string mensaje = " "; //almacenará el mensaje
                    system("CLS");
                    cout << "Dr(a)." << name << " Ingrese su solicitud con toda la informacion (Aprete Enter cuando termine): \n";
                    cin.ignore();
                    getline(cin, mensaje);
                    recibirMensaje(mensaje, name, id); //Funcion que pertenece a gerente para recibir los mensajes
                }
                else if (seleccion == 4) { //Cierra sesión
                    system("CLS");
                    break;
                }
                else { //Debug
                    system("CLS");
                    cout << "Opción incorrecta vuelva intentarlo\n";
                }
                cout << "\nQuieres regresar a tu menú personal? SI(0) o Cerrar sesion(1): "; //Para que regrese a su menú o cierre sesión
                cin >> input;
                system("CLS");
                if (input != 0 && input != 1) { break; }
            }
        }
        else { //Clave incorrecta
            system("cls");
            cout << "\nClave incorrecta ingrese de nuevo" << endl;
            tries++;
        }
    } while (tries < 5 && clave != password);
    if (tries >= 5) {
        cout << "Comuníquese con el administrador fallo su contraseña más de cinco veces\n"; //Le indica que se comunique con el administrador para cambiar su clave
    }
    return;
}


//CLASE PACIENTE--------------------------------------------

int Paciente::clienteID = 20000;
int Paciente::darID() { return id; } 
bool Paciente::darAct() { return activo; }

void Paciente::cambiarAct() { //Cambia la actividad de un paciente
    if (activo == true) {
        activo = false;
    }
    else {
        activo = true;
    }
}
void Paciente::mostrarAct() {   //Muestra la actividad de un paciente
    cout << "La cuenta se encuentra ";
    if (activo == true) {
        cout << "activada!.";
    }
    else {
        cout << "NO activada.";
    }
}
void Paciente::crearc() {                      //Ingresar los datos para crear un nuevo objeto
    cout << "CREANDO NUEVA CUENTA PACIENTE\n\n";
    cin.ignore();
    Persona::pedirdatos();
    cout << "\nIngrese su peso: ";
    cin >> peso;
    cout << "\nIngrese su altura: ";
    cin >> estatura;
    cout << "\nIngrese su presion: ";
    cin >> presion;
    cout << endl;
}
void Paciente::printc() {       //Immprimir los datos ingresados
    cout << "\nBienvenido Sr(a). ";
    Persona::print();
    cout << "\nPeso: " << peso << endl;
    cout << "Estatura: " << estatura << endl;
    cout << "Presion: " << presion << endl << endl;
    cout << "Codigo(ID): " << id << endl << endl;
}
void Paciente::cambiarinfo() {          //Función para modificar o actuallizar datos
    int submenu;
    cout << "\n1)Cambiar el Nombre.\n2)Cambiar la Edad.\n3)Cambiar Peso.\n4)Cambiar Estatura.\n5)Cambiar la Presion.\n\nIngrese el numero de la ocpion deseada: ";   //Editor del paciente
    cin >> submenu;
    system("cls");
    if (submenu == 1) {
        cout << "Ingrese el nuevo nombre: ";
        cin.ignore();
        getline(cin, name); cout << "Hecho!" << endl;
    }
    else if (submenu == 2) {
        cout << "Ingrese la nueva edad: ";
        cin >> edad; cout << "Hecho!" << endl;
    }
    else if (submenu == 3) {
        cout << "Ingrese el nuevo peso: ";
        cin >> peso; cout << "Hecho!" << endl;
    }
    else if (submenu == 4) {
        cout << "Ingrese la nueva estatura: ";
        cin >> estatura; cout << "Hecho!" << endl;
    }
    else if (submenu == 5) {
        cout << "Ingrese la nueva presion: ";
        cin >> presion; cout << "Hecho!" << endl;
    }
    else {
        cout << "\nCaracter no permitido.\n";
    }
}
void Paciente::mostrarHistorial() {     //Muestra el historial del paciente
    cout << "Historial del Paciente: \n";
    for (int i = 0; i < iEnf; i++) {
        cout << "  - " << enfermedad[i] << endl;
    }
    cout << endl << endl;
}
void Paciente::menuPaciente(Doctor* allDoctors) {           //Menú del paciente
    int menu, submenu, inputDNI;
    if (activo == true) {
        cout << "Ingrese su DNI: ";
        cin >> inputDNI;
        if (inputDNI != no_DNI) {
            cout << "\nContraseña incorrecta\n\n";
        }
        else {
            system("cls");
            while (true) {    //Hacemos que sea un bucle para que pueda siempre volver al menu principal del paciente
                cout << "\n\n------------------------------------------------\nMENU DEL PACIENTE\n  1)Revisar datos.\n  2)Solicitar consulta.\n  3)Cambiar informacion personal.\n  4)Mostrar Historial Medico. \n  5)Cerrar sesion.\n\nIngrese el numero de opcion deseada: ";
                cin >> menu;
                system("cls");
                if (menu == 1) {   //Impresion de los datos del paciente
                    printc();
                }
                else if (menu == 2) {
                    string nombredoc;
                    int IDdoc, diaCita;
                    bool founddoc = false;
                    cout << "\nIngrese su malestar o enfermedad: ";
                    cin.ignore();
                    getline(cin, enfermedad[iEnf]);
                    system("cls");
                    cout << "\n1)Ingrese el nombre de un doctor especifico.\n2)Ingrese el ID de un doctor especifico.\n\nIngrese el numero de la opcion deseada: ";   //Opciones de ayuda a cada paciente
                    cin >> submenu;
                    system("cls");
                    if (submenu == 1) {
                        cout << "Ingrese el nombre del Doctor: ";
                        cin.ignore();
                        getline(cin, nombredoc);
                        for (int i = 0; i < iDoc; i++) {
                            if (nombredoc == doctores[i]) {
                                founddoc = true;
                                allDoctors[i].printInfo();
                                cout << "\nIngrese el dia de la cita: "; cin >> diaCita;
                                allDoctors[i].recibirCita(diaCita);
                                iEnf++; system("cls");
                            }
                        }
                        if (founddoc == false) {
                            cout << "\nDoctor no encontrado\n";
                        }
                    }
                    else if (submenu == 2) {
                        cout << "Ingrese el ID del doctor: ";
                        cin >> IDdoc;
                        for (int i = 0; i < iDoc; i++) {
                            if (IDdoc == allDoctors[i].darID()) {
                                founddoc = true;
                                allDoctors[i].printInfo();
                                cout << "\nIngrese el dia de la cita: "; cin >> diaCita;
                                allDoctors[i].recibirCita(diaCita);
                                iEnf++; system("cls");
                            }
                        }
                        if (founddoc == false) {
                            cout << "\nDoctor no encontrado\n";
                        }
                    }
                    else {
                        cout << "\nCaracter no permitido.\n";
                    }
                }
                else if (menu == 3) {
                    cambiarinfo();
                }
                else if (menu == 4) {
                    mostrarHistorial();
                }
                else if (menu == 5) {   //Salir de la cuenta paciente
                    system("cls");
                    break;
                }
                else {
                    cout << "\nCaracter no permitido.\n";
                }
            }
        }
    }
    else {
        cout << "¡¡¡¡¡¡¡CUENTA DESACTIVADA!!!!!!!\nSi requiere su activacion, comuniquese con algun Administrador.\n";
    }
}


//CLASE GERENTE -----------------------------------------------------------

string gerentes[10000];
int IDGerente[10000];
int Gerente::gerenteID = 30000;
void Gerente::pedirDatos() { 			// Creamos función para pedir los datos
    cout << "\nCREANDO UN GERENTE \n\n";
    Persona::pedirdatos();
    cout << "\nIngrese su clave: ";
    cin.ignore();
    getline(cin, password);
    gerentes[id - 30000] = name;  //Agregamos los datos a cada array
    IDGerente[id - 30000] = id;

    return;
}
void Gerente::print() {   //	Le da la bienvenida al doctor(a)
    cout << "\nBienvenido Gerente ";
    Persona::print();  //Llamamos a la funcion imprimir de la clase padre
    cout << "\nSu ID es el número: " << id;
    printPassword(password);

    return;
}

void Gerente::imprimirMensajes() {  //Imprime los mensajes que se le nvían a los Gerentes
    int input;
    bool find = false;
    for (int i = 0; 0 < mensajes[i].length(); i++) {
        cout << i + 1 << ") Mensaje de " << emisores[i] << " " << idEmisores[i] << "\n";
    }

    cout << "\nIngrese que mensaje quiere ver (Sino para salir ingrese -1 y para ver los mensajes ya leídos ingrese 0): ";
    cin >> input;
    if (input == 0) {//Muestra mensajes leídos
        system("CLS");
        for (int i = 0; 0 < mensajesLeidos[i].length(); i++) {
            cout << i + 1 << ") Mensaje de" << emisoresLeidos[i] << " " << IDemisoresLeidos[i] << "\n";
        }
        cout << "\nIngrese que mensaje quiere ver: \n";
        cin >> input;
        system("CLS");
        cout << mensajesLeidos[input - 1] << endl << endl;
    }
    else if(input>0) { //Muestra el nuevo mensaje seleccionado
        system("CLS");
        cout << mensajes[input - 1] << endl << endl;
    }

    int i = 0;
    while (find == false && input>0) {                 //Movemos a los nuevos lugares los mensaje luego de ser leidos
        if (mensajesLeidos[i].length() <= 0) { 
            mensajesLeidos[i] = mensajes[input - 1];    //Se redireccionan de indice los mensajes
            emisoresLeidos[i] = emisores[input - 1];
            IDemisoresLeidos[i] = idEmisores[input - 1];
            if (mensajes[input].length() <= 0) {
                mensajes[input - 1] = "";
                emisores[input - 1] = "";
                idEmisores[input - 1] = 0;
            }
            else {
                for (int j = 0; mensajes[input + j].length() > 0; j++) {    //Se mueven los mensajes nuevos a su nuevo lugar
                    mensajes[(input - 1) + j] = mensajes[input + j];
                    mensajes[input + j] = "";
                    cout << mensajes[input + j];
                    emisores[(input - 1) + j] = emisores[input + j];
                    emisores[input + j] = "";
                    idEmisores[(input - 1) + j] = idEmisores[input + j];
                    idEmisores[input + j] = 0;
                }
            }
            find = true;
        }
        else {
            i++;
        }
    }
    return;
}

void Gerente::menuGerente(Doctor* allDoctors, Paciente* allPacientes, Gerente* allGerentes) { 
    { //Creamos la funcion para el menu del doctor donde podrá hacer todo tipo de modificación
        int seleccion; //Almacena el Input que ingresará el usuario
        string clave;
        int tries = 0;  //Intentos que el gerente intenta poner la clave
        do {
            cout << "Ingrese su clave: ";
            cin >> clave;
            system("cls");
            if (clave == password) {
                bool input = false;
                while (input == false) {
                    cout << "\nMENU \n 1) Editar tus datos \n 2) Ver mensajes\n 3) Crear Doctor o Paciente o Gerente \n 4) Mostrar datos de un doctor o paciente \n 5) Cerrar Sesión \n Ingrese el número de la opción: "; //Opciones que puede elegir el doctor
                    cin >> seleccion;
                    system("cls");
                    if (seleccion == 1) {  //Editar datos
                        input = true;
                        system("CLS");
                        cout << "\nQue desea modificar: \n 1) Nombre \n 2) Edad \n 3) Cambiar Password \nIngrese su opcion: ";
                        cin >> seleccion;
                        system("CLS");
                        switch (seleccion) { //En cada caso editará la opción ingresada
                        case 1:
                            cout << "Ingrese su nombre: ";
                            cin.ignore();
                            getline(cin, name);
                            break;
                        case 2:
                            cout << "Ingrese su edad: ";
                            cin >> edad;
                            break;
                        case 3:
                            cout << "Ingrese su nuevo password: ";
                            cin >> password;
                            break;

                        default:
                            cout << "Valor incorrecto\n Ingrese de nuevo\n";
                            menuGerente(allDoctors, allPacientes, allGerentes);
                        }
                        print();
                    }
                    else if (seleccion == 2) { //Imprimir Mensajes
                        input = true;
                        system("CLS");
                        imprimirMensajes();
                    }
                    else if (seleccion == 3) { //Crear Paciente o Doctor o Gerente
                        input = true;
                        system("cls");
                        int opcrear;
                        cout << "Presione (1) para crear un nuevo Paciente.\nPresione (2) para crear un nuevo Doctor.\nPresione (3) para crear un nuevo Gerente.\nIngrese el numero de la opcion: ";
                        cin >> opcrear;
                        system("cls");
                        if (opcrear == 1) {
                            allPacientes[iPac].crearc();
                            system("cls");
                            cout << "\n\nPaciente Creado\n\n";
                            allPacientes[iPac].printc();
                            iPac++;
                        }
                        else if (opcrear == 2) {
                            allDoctors[iDoc].pedirDatos();
                            system("cls");
                            cout << "\n\nDoctor Creado\n\n";
                            allDoctors[iDoc].print();
                            iDoc++;
                        }
                        else if (opcrear == 3) {
                            cin.ignore();
                            allGerentes[iGer].pedirDatos();
                            system("cls");
                            cout << "\n\nGerente Creado\n\n";
                            allGerentes[iGer].print();
                            iGer++;
                        }
                        else {
                            cout << "VALOR NO PERMITIDO.\n";
                        }
                    }
                    else if (seleccion == 4) { //Mostrar datos y/o modificarlos
                        input = true;
                        system("cls");
                        int inputIDPac, inputIDDoc, inputIDGer, inputID;        //Variable para ingresar el ID del usuario a buscar
                        bool foundGer = false;
                        cout << "\nIngrese el ID de la persona: ";
                        cin >> inputID;
                        if (inputID >= 10000 && inputID < 20000) {  //Si ingresa ID de doctor le da sus respectivas opciones
                            inputIDDoc = inputID;
                            for (int i = 0; i < iDoc; i++) {
                                if (inputIDDoc == allDoctors[i].darID()) {
                                    int opdoc;
                                    foundGer = true;
                                    allDoctors[i].print();
                                    cout << "\n\nPresione (1) para cambiar datos de de la cuenta.\nPresione (2) para cambiar la actividad de la cuenta.\nPresione (3) para cambiar los horarios.\nIngrese el numero de la opcion deseada: ";
                                    cin >> opdoc;
                                    system("cls");
                                    if (opdoc == 1) { //Modificar info del doctor
                                        allDoctors[i].cambiarInfo();
                                    }
                                    else if (opdoc == 2) {
                                        int subopdoc;
                                        allDoctors[i].mostrarAct();
                                        cout << "\n\nPresione (1) para cambiar la actividad de la cuenta.\nPresione (2) para mantener la actividad de la cuenta y volver al menu.\nIngrese la opcion deseada: ";
                                        cin >> subopdoc;
                                        if (subopdoc == 1) {
                                            allDoctors[i].cambiarAct();
                                        }
                                        else {
                                            break;
                                        }
                                    }
                                    else if (opdoc == 3) {
                                        int dia;
                                        cout << "\nIngrese que dia quiere cambiar(Numero): ";
                                        cin >> dia;
                                        allDoctors[i].cambiarHorario(dia);
                                    }
                                    else {
                                        cout << "Opcion no permitida.\n";
                                    }
                                    break;
                                }
                            }
                            if (foundGer == false) {
                                cout << "Doctor no encontrado\n";
                            }
                        }
                        else if (inputID >= 20000 && inputID < 30000) { //SI ingresa ID de paciente le da sus respectivas opciones
                            inputIDPac = inputID;
                            for (int i = 0; i < iPac; i++) {
                                if (inputIDPac == allPacientes[i].darID()) {
                                    int oppac, suboppac;
                                    foundGer = true;
                                    allPacientes[i].printc();
                                    cout << "\n\nPresione (1) para cambiar datos de de la cuenta.\nPresione (2) para cambiar la actividad de la cuenta.\nIngrese el numero de la opcion deseada: ";
                                    cin >> oppac;
                                    system("cls");
                                    if (oppac == 1) {
                                        allPacientes[i].cambiarinfo();
                                    }
                                    else if (oppac == 2) {
                                        allPacientes[i].mostrarAct();
                                        cout << "\n\nPresione (1) para cambiar la actividad de la cuenta.\nPresione (2) para mantener la actividad de la cuenta y volver al menu.\nIngrese la opcion deseada: ";
                                        cin >> suboppac;
                                        if (suboppac == 1) {
                                            allPacientes[i].cambiarAct();
                                        }
                                        else {
                                            break;
                                        }
                                    }
                                    else {
                                        cout << "Opcion no permitida.\n";
                                    }
                                    break;
                                }
                            }
                            if (foundGer == false) {
                                cout << "\nPaciente no encontrado\n";
                            }
                        }
                        else if (inputID >= 30000 && inputID < 40000) { //Si ingresa ID de otro Gerente, solo le mostrará los datos
                            inputIDGer = inputID;
                            for (int i = 0; i < iGer; i++) {
                                if (inputIDGer == allGerentes[i].darID()) {
                                    foundGer = true;
                                    allGerentes[i].print();
                                    break;
                                }
                            }
                            if (foundGer == false) {
                                cout << "\nGerente no encontrado\n";
                            }
                        }
                        else {
                            cout << "\nID no permitido.\n";
                        }
                    }
                    else if (seleccion == 5) { //Cerrar sesión
                        system("CLS");
                        break;
                    }
                    else { //Debug
                        system("CLS");
                        cout << "Opción incorrecta vuelva intentarlo\n";
                    }
                    cout << "\nQuieres regresar a tu menú personal? SI(0) o Cerrar sesion(1): ";
                    cin >> input;
                    system("CLS");
                    if (input != 0 && input != 1) { break; }
                }
            }
            else { //Clave incorrecta
                system("cls");
                cout << "\nClave incorrecta ingrese de nuevo" << endl;
                tries++;
            }
        } while (tries < 4 && clave != password);
        if (tries >= 4) {
            cout << "Comuníquese con otro administrador\n"; //Le indica que se comunique con el administrador para cambiar su clave
        }
    }

    return;
}

//MENU GENERAL-----------------------------------------------------------------------------------------------------

void menuGeneral(Doctor* allDoctors, Paciente* allPacientes, Gerente* allGerentes) {  //Menu donde se desenvuelve el programa
    cout << "\n\nMuy buenas, ingrese el nombre de la clinica, por favor: ";
    getline(cin, nombreClinica);
    system("CLS");          //Al inicio del programa, iniciamos agregando el nombre de la clinica

    cout << "Clinica " << nombreClinica << endl;

    int inputIDPac;   //Variable para ingresar el ID del usuario al iniciar sesion
    int inputIDDoc;
    int inputIDGer;
    bool found = false;   //Variable para mostrar si se encontro el paciente
    while (true) {
        int menu;         //Creamos un menu
        int inputID;
        cout << "\nMENU\n\nPresione (1) Ingresar \nPresione (2) Registrarse como Paciente\n";
        cout << "Presione (3) salir del menu\n\n Presione la tecla deseada: ";
        cin >> menu;
        system("cls");
        if (menu == 1) {   //Iniciar sesión
            cout << "\nIngrese su ID: "; //Según el ID se identifica quien desea ingresar, luego se les pide su clave o DNI
            cin >> inputID;
            if (inputID >= 10000 && inputID < 20000) {
                inputIDDoc = inputID;
                bool correcto = false;
                int numeroDeDoctor = 0;
                while (correcto == false) {
                    for (int i = 0; i < 10000; i++) { //Verifica si el ID INGRESADO existe
                        if (inputIDDoc == IDdoctores[i]) {
                            if (allDoctors[i].darActivo() == false) {
                                cout << "Dr(a)." << doctores[i] << " No estás activo, por favor comuníquese con algún gerente/n";
                                numeroDeDoctor = -1;
                            }
                            else {
                                correcto = true;
                                numeroDeDoctor = i;
                            }
                            break;
                        }
                    }
                    if (correcto == true) {
                        allDoctors[numeroDeDoctor].menuDoctor();
                    }
                    else if (numeroDeDoctor == -1) {
                        break;
                    }
                    else {
                        std::cout << "ID inexistente, intentelo de nuevo\nIngrese su ID: ";
                        std::cin >> inputIDDoc;
                    }
                }
            }
            else if (inputID >= 20000 && inputID < 30000) { //ID de paciente
                inputIDPac = inputID;
                for (int i = 0; i < iPac; i++) {
                    if (inputIDPac == allPacientes[i].darID()) {
                        found = true;
                        allPacientes[i].menuPaciente(allDoctors);
                        break;
                    }
                }
                if (found == false) {
                    cout << "\nPaciente no encontrado\n";
                }
            }
            else if (inputID >= 30000 && inputID < 40000) { //ID de gerente
                inputIDGer = inputID;
                bool correcto = false;
                int numeroDeGerente = 0;
                while (correcto == false) {
                    for (int i = 0; i < 10000; i++) { //Verifica si el ID existe
                        if (inputIDGer == IDGerente[i]) {
                            correcto = true;
                            numeroDeGerente = i;
                            break;
                        }
                    }
                    if (correcto == true) {
                        allGerentes[numeroDeGerente].menuGerente(allDoctors, allPacientes, allGerentes);
                    }
                    else {
                        std::cout << "ID inexistente, intentelo de nuevo\nIngrese su ID: ";
                        std::cin >> inputIDGer;
                    }
                }
            }
            else {
                cout << "\nID no permitido.\n";
            }
        }
        else if (menu == 2) {    //Creacion de un nuevo Paciente sin necesidad de decirle al gerente
            allPacientes[iPac].crearc();
            system("cls");
            allPacientes[iPac].printc();
            iPac++;
        }
        else if (menu == 3) {
            cout << "Saliendo...\n";
            break;
        }
        else {
            cout << "Caracter no permitido\n";
        }
    }
    return;
}