#include <iostream>
#include <string>  
#include <cmath>
#include <iomanip>
using namespace std;

string alphabet  = "ABCDEFGHIJKLMN#OPQRSTUVWXYZ";


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
        if(user_input[i] >= 'A' && user_input[i] <= 'Z' || user_input[i] >= 'a' && user_input[i] <= 'z' || user_input[i] == '#') {
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
        cout << "Bod ingresa el mensaje: ";
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



int main(){
    string plain_text, final_res;
    int n = 0;
    long double p = 3491, q = 8219, e = 97, i = 0, plain_value = 0, res_int, j = 0;
    cout << "\t RSA: Equipo 6\n";
    cout << "----------------------------------------------------------------------\n";
    cout << "Encriptación usando RSA, al ingresa el texto plano si se necesita usar una ñ (enie) favor de ingresar un #.\n";

    plain_text = get_user_input();
    n = p * q;  
    cout << "Frase cifrada: " << endl; 
    for(i = 0; i < plain_text.length(); i++){
        res_int = 0;
        for(j = 0; j < alphabet.length(); j++){
            if (plain_text[i] == alphabet[j]){
                plain_value = j; 
                break; 
            }
        }

        res_int = pow(plain_value, e); 
        res_int = fmod(res_int, n); 
        cout << setprecision(0) << fixed << res_int << " "; 
    }
    return 0; 

}