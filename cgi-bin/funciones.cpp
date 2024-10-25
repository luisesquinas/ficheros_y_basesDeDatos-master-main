#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <string>
using namespace std;


int main() {

    // Obtener el método de la solicitud (GET o POST)
    const char* request_method = getenv("REQUEST_METHOD");
    char* query_string = nullptr;

    if (request_method != nullptr && strcmp(request_method, "GET") == 0) {
        // Si el método es GET, leer la cadena de consulta de la URL
        query_string = getenv("QUERY_STRING");
    } 
    else if (request_method != nullptr && strcmp(request_method, "POST") == 0) {
        // Si el método es POST, leer el contenido de la entrada estándar (stdin)
        const char* content_length_str = getenv("CONTENT_LENGTH");
        int content_length = 0;
        if (content_length_str != nullptr) {
            content_length = atoi(content_length_str); // Convertir a entero
        }
        query_string = new char[content_length + 1];  // Reservar espacio para el contenido POST
        cin.read(query_string, content_length);       // Leer desde stdin
        query_string[content_length] = '\0';          // Asegurarse de que sea una cadena terminada
    }


    // Inicializar variables
    char nombre[50] = "";
    char apellido[50] = "";
    char color[50] = "";
    char orden[50] = "";

    if (query_string != nullptr) {
        // Parsear los parámetros
        char* param = strdup(query_string);  // Hacer una copia de la cadena de consulta
        char* token = strtok(param, "&");    // Separar los parámetros
        while (token != nullptr) {
            if (sscanf(token, "nombre=%49s", nombre) == 1) {  }
            if (sscanf(token, "apellido=%49s", apellido) == 1) {  }
            if (sscanf(token, "color=%49s", color) == 1) {  }
            if (sscanf(token, "orden=%49s", orden) == 1) {  }
            token = strtok(nullptr, "&");    // Continuar con el siguiente parámetro
        }
        free(param);  // Liberar la memoria
    }



    

    if( string(orden) == "guardar"){
        // Crear fichero
        ofstream archivo("configuracion.config");
        // rellenar fichero
        archivo << nombre << "\n";
        archivo << apellido << "\n";
        archivo << color << "\n";
        // cerrar fichero
        archivo.close();
        
        cout << "Content-Type: text/plain\n\n";
        cout << "Fichero guardado";
    }

    if( string(orden) == "cargar"){


        // Abrir fichero
        ifstream archivo2("configuracion.config");
        
        // capturar contenido
        string n = "";
        string a = "";
        string c = "";
        string linea;
        getline(archivo2,linea);
        n = linea;
        getline(archivo2,linea);
        a = linea;
        getline(archivo2,linea);
        c = linea;
        // cerrar fichero
        archivo2.close();

        string respuesta = "{";
        respuesta += "\"nombre\":\"";
        respuesta += n;
        respuesta += "\", \"apellido\":\"";
        respuesta += a;
        respuesta += "\", \"color\":\"";
        respuesta += c;
        respuesta += "\", \"mensaje\":\"";
        respuesta += "Fichero cargado";
        respuesta += "\"}";
        // '{"nombre":"Oriol", "mensaje":"Fichero cargado"}'

        cout << "Content-Type: application/json\n\n";
        cout << respuesta;
    }



    return 0;
}