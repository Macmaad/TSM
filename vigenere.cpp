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
    char alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    string res = "", key, actual_value, cipher_text;
    int i = 0, j = 0, m = 0, n = 0, k = 0; 

    cout << "Proporcione la frase cifrada: ";
    cin >> cipher_text;
    cout << "Proporcione el inicio de la clave: "; 
    fflush(stdin);
    cin >> key; 

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

    cout << "El text cifrado es: " << res << "   ";
}
    


int main() {
    char key[256];
    int user_selection; 

    user_selection = menu(); 

    switch (user_selection) {
    case 1:
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


    // std::cout << "Enter key: "; 
    // std::cin.get (key, 256); 
    // if (*key == 'H') {
    //     std::cout << "Sale"; 
    // }

    return 0;
}

