#include <iostream>
#include <cmath>
#include <algorithm> 
#include <string>
#include <cstring>
using namespace std;

string alphabet  = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int menu() {
    /*
        Enseña el menú y regresa el input del usuario.
    */
    int menu_selection = 0, user_selection; 
    cout << "\t\t Vigenère Versión 2\n\n";
    cout << "1.- Encriptación\n";
    cout << "2.- Desencriptar\n"; 
    cout << "----------------------------------------------------------------------\n";
    cout << "Opción (1/2): ";
    cin >> user_selection; 

    return user_selection;
}


string remove_empty_spaces(char user_input[255]) {
    /*
        Según un grupo de caracteres que reciba la función elimina los espacios en blanco que encuentre.
    */
    int i = 0;
    string tmp, result;
    for(i = 0; i < strlen(user_input); i++){
        
        if(user_input[i] != ' '){
            tmp = tmp + user_input[i];
        }
    }
    result = tmp;
    return result;
}


bool is_valid(string user_input) {
    /*
        Valida que cada letra dentro del input del usuario (llave, plain text, cipher text) 
        esten dentro del abecedario (solo elimina la ñ).
    */
    int i = 0;
    for (i = 0; i < user_input.length(); i++) {
        if(user_input[i] >= 'A' && user_input[i] <= 'Z' || user_input[i] >= 'a' && user_input[i] <= 'z') {
            continue;
        } else {
            return false;
        }
    }
    return true; 
}


string get_user_input() {
    /*
        Recibe el input del usuario de la frase que se va a encriptar o desencriptar. 
        Se validad que este dentro del abecedario y se limpian los espacios 
        si es necesario. 
        Si el input es válido, se cambiará a mayúsculas. 
    */
    char raw_input[255];
    bool is_valid_input;
    string clean_user_input;
    do {
        cout << "Proporcione la frase: ";
        fflush(stdin);
        cin.getline(raw_input, sizeof(raw_input));
        if (sizeof(raw_input) > 0){
            clean_user_input = remove_empty_spaces(raw_input);
            is_valid_input = is_valid(clean_user_input);
            if(is_valid_input) {
                transform(clean_user_input.begin(), clean_user_input.end(), clean_user_input.begin(), ::toupper);
            } else {
                cout << "Entrada no válida..." << endl;
            }
        } else {
            cout << "Entrada no válida..." << endl;
        }
       
    } while (!is_valid_input);
    
    return clean_user_input;
}


string get_user_key(){
    /*
        Obtiene la lalve del usuario, solo tiene que obtener una letra. 
        En caso de que el usuario ingrese mas letras estas serán ignoradas. 
        Se validad que este en un rango de puras letras dentro del abecedario (inglés)
        aunque el usuario ingrese una minúscula, el programa lo valida.
    */
    string key;
    bool is_valid_input;
    do {
        cout << "Proporcione la primera letra de la llave: "; 
        fflush(stdin);
        cin >> key; 
        key = key[0];
        if (key.length() > 0){
            is_valid_input = is_valid(key);
            if(is_valid_input) {
                transform(key.begin(), key.end(), key.begin(), ::toupper);
            } else {
                cout << "La llave no es válida..." << endl;
            }
        } else {
            cout << "La llave no es válida..." << endl;
        }
    } while(!is_valid_input);
    return key;
}


void decrypt() {
    /*
        Para desencriptar solo se siguen los siguietnes pasos: 
            1) Tenemos la llave inicial dada por el usuario al igual que el texto cifrado. 
            2) Se limpia la frase y se eliminan espacios. 
            3) Para la llave, si el usuario mete mas de un caracter, se ingora todo menos el primero.
            4) Repetimos lo siguiente hasta finalizar la palabra
                4.1) Se va letra por letra en la frase cifrada. 
                4.2) Se busca la llave y la letra en la que vayamos su valor en el alfabeto: Ejemplo H = 7, N = 13
                4.3) Se calula k = abs(llave - letra)
                4.4) Si llave > letra
                    4.4.1) k = (26 - llave) + letra
                4.5) La llave cambia y se vuelve la siguiente letra del texto cifrado (en la que estamos)
                4.6) La frase se va armando de el alfabeto en la posición k.
    */
    string res = "", key, actual_value, cipher_text;
    int i = 0, j = 0, m = 0, n = 0, k = 0; 
    cipher_text = get_user_input();
    key = get_user_key();

    for(i = 0; i < cipher_text.length(); i++) {
        for(j = 0; j < 26; j++){
            actual_value = alphabet[j];
            if(key == actual_value) {
                m = j;
            } 
            if(cipher_text[i] == alphabet[j]) {
                n = j; 
            }
        }
        k = abs(m - n);
        if (m > n) {
            k = (26 - m) + n;
        }

        key = cipher_text[i];
        res = res + alphabet[k]; 
    }

    cout << "El texto plano es: " << res << "   " << endl;
}


void encrypt(){
    /*
        Para encriptar es casi el mismo proceso que para desencriptar: 
            1) Tenemos la llave inicial dada por el usuario al igual que el texto cifrado. 
            2) Se limpia la frase y se eliminan espacios. 
            3) Para la llave, si el usuario mete mas de un caracter, se ingora todo menos el primero.
            4) Repetimos lo siguiente hasta finalizar la palabra
                4.1) Se va letra por letra en la frase cifrada. 
                4.2) Se busca la llave y la letra en la que vayamos su valor en el alfabeto: Ejemplo H = 7, N = 13
                4.3) Se calula k = llave + letra
                4.4) Si k > 25
                    4.4.1) k = k - 26
                4.5) La frase cifrada se va armando de el alfabeto en la posición k.
                4.6) La nueva llave es la letra recien obtenida en el paso 4.5
    */
    string res = "", key, actual_value, plain_text;
    int i = 0, j = 0, m = 0, n = 0, k = 0; 

    plain_text = get_user_input();
    key = get_user_key();

    for(i = 0; i < plain_text.length(); i++) {
        for(j = 0; j < 26; j++){
            actual_value = alphabet[j];
            if(key == actual_value) {
                m = j;
            } 
            if(plain_text[i] == alphabet[j]) {
                n = j; 
            }
        }
        k = m + n;
        if (k > 25) {
            k = k - 26;
        }
        res = res + alphabet[k]; 
        key = alphabet[k];
    }
    cout << "El text cifrado es: " << res << "   " << endl;
}
    


int main() {
    /*
        Menú del programa, solo contiene dos opciones: 
        1) Encriptar un mensaj. 
        2) Desencriptar un mensaje.

        En caso de que el usuario ingrese otro valor, el programa no se rompe 
        indica error en la selección del proceso deseado y preguntará si quiere volver a empezar.

        Esta función solo es el controlador del programa.
    
    */
    char key[256];
    int user_selection, continue_selection; 

    do {
        user_selection = menu(); 

        switch (user_selection) {
        case 1:
            encrypt();
            break;
        case 2: 
            decrypt();
            break; 
        default:
            cout << "La opción ingresada no es válida...\n";
            cout << "Enter para continuar...";
            fflush(stdin);
            getchar();
            break;
        }

        cout << "Correr de nuevo? (1=Si, 2=No): ";
        fflush(stdin);
        cin >> continue_selection; 
    } while(continue_selection == 1);

    return 0;
}

