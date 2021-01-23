#include <iostream>
#include <cmath>
#include <algorithm> 
using namespace std;

int menu() {
    int menu_selection = 0, user_selection; 
    cout << "\t\t Vigenère Versión 2\n\n";
    cout << "1.- Encriptación\n";
    cout << "2.- Desencriptar\n"; 
    cout << "----------------------------------------------------------------------\n";
    cout << "Opción: ";
    cin >> user_selection; 

    return user_selection;
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
    char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}, cipher_text_c[255];
    string res = "", key, actual_value, cipher_text, tmp;
    int i = 0, j = 0, m = 0, n = 0, k = 0; 

    cout << "Proporcione la frase cifrada: ";
    fflush(stdin);
    cin.getline(cipher_text_c, sizeof(cipher_text_c));
    for(i = 0; i < strlen(cipher_text_c); i++){
        
        if(cipher_text_c[i] != ' '){
            tmp = tmp + cipher_text_c[i];
        }
        cipher_text = tmp;
    }


    cout << "Proporcione la priemra letra de la llave: "; 
    fflush(stdin);
    cin >> key; 
    key = key[0];

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

    cout << "El text plano es: " << res << "   ";
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
    char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}, plain_text_raw[255];
    string res = "", key, actual_value, plain_text, tmp;
    int i = 0, j = 0, m = 0, n = 0, k = 0; 

    cout << "Proporcione el texto plano: ";
    fflush(stdin);
    cin.getline(plain_text_raw, sizeof(plain_text_raw));
    for(i = 0; i < strlen(plain_text_raw); i++){
        
        if(plain_text_raw[i] != ' '){
            tmp = tmp + plain_text_raw[i];
        }
        plain_text = tmp;
    }

    cout << "Proporcione la primera letra de la llave: "; 
    fflush(stdin);
    cin >> key; 
    key = key[0];

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

    cout << "El text plano es: " << res << "   ";
}
    


int main() {
    char key[256];
    int user_selection; 

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
        cout << "Enter para finalizar...";
        fflush(stdin);
        getchar();
        break;
    }
    return 0;
}

