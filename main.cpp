#include <iostream>
#include <string>
#include "VigenereSquare.cpp"

using namespace std;

//
// Created by Joey Mafukidze on 25.10.20.
//
#include <string>
using namespace std;

/**
 * A class that defines all the functions used in this program.
 *
 * There are 3 functions: encrypt(), decrypt() and generateModifiedKey().
 */
class VigenereSquare{
public:
    std::string key;
    /**
     * @brief A explicit class constructor that allows implicit conversion.
     *
     * @details The constructor maintains constraints such as the keyword/password strictly being in uppercase for the integrity of the program.
     * It makes the necessary adjustments if it encounters a lowercase character. The accepted values are between A-Z(keyword), a-z(plain text) & the space character, ' ' or 0x20.
     *
     * @param key The code used to encrypt or decrypt plain text.
     */
    explicit VigenereSquare(const std::string& key){
        //check if the key is in capital letters
        for(char inKey : key){
            if(inKey >= 'A' && inKey <= 'Z')
                this->key += inKey;
                //if it a character is in lowercase, change it to uppercase
            else if(inKey >= 'a' && inKey <= 'z')
                this->key += std::to_string(inKey + 'A' - 'a');
        }
    }
    /**
     * @brief A function that displays the modified version of the key according to the user-defined plain text.
     *
     * @details When the character in the plain text is in lowercase, the function appends, the values of the password/key
     * character-by-character, in a string. When it encounters a space, it appends a space character and re-adjusts the position of the
     * the key 'pointer' to avoid the loss of characters in our string sequence.
     *
     * @param text The user-defined plain text.
     * @return A string, 'modifiedKey', which illustrates which character key is used to encode each plain text character.
     */
    std::string generateModifiedKey(std::string text){
        string modifiedKey;
        for (int positionInPlainText = 0, positionInKey = 0; positionInPlainText <= text.length(); positionInPlainText++){
            char currentCharacter = text[positionInPlainText];
            if(currentCharacter >= 'a' && currentCharacter <= 'z'){
                modifiedKey += key[positionInKey];
            }else if(currentCharacter == 0x20){
                modifiedKey += " ";
                positionInKey--;
            }else{
                continue;
            }
            positionInKey = (positionInKey + 1) % key.length();
        }
        return modifiedKey;
    }

    /**
     * @brief A function that is used to encrypt plain text using a keyword and the Vigenère cipher encoding algorithm.
     *
     * @details The algorithm encodes plain text by calculating the range between a character in the plain text and one in the keyword.
     * It uses that range to encodes by shifting the position by the range and producing a new character that satisfies our character definition set. A-Z & the space character, ' ' or 0x20.
     *
     * @param text the user-defined plain text.
     * @return the encrypted string.
     */
    string encrypt(string text){
        string encryptedString;

        for(int positionInPlainText = 0, positionInKey = 0; positionInPlainText <= text.length(); positionInPlainText++){
            char currentCharacter = text[positionInPlainText];

            if(currentCharacter >= 'a' && currentCharacter <= 'z'){
                currentCharacter += 'A' - 'a';
                encryptedString += (currentCharacter + key[positionInKey] - 2 * 'A') % 26 + 'A';
            }else if(currentCharacter == 0x20){//if the current character is a space '0x20'
                encryptedString += " ";
            }else{
                continue;
            }
            positionInKey = (positionInKey + 1) % key.length();
        }
        return encryptedString;
    }

    /**
     * A function that is used to decrypt encoded text using a keyword and the Vigenère cipher decoding algorithm.
     *
     * @param text the user-defined plain text.
     * @return the decrypted string.
     */
    string decrypt(string text){
        string decryptedString;

        for(int positionInEncryptedText = 0, positionInKey = 0; positionInEncryptedText <= text.length(); positionInEncryptedText++){
            char currentCharacter = text[positionInEncryptedText];
            if(currentCharacter >= 'A' && currentCharacter <= 'Z'){
                decryptedString += (currentCharacter - key[positionInKey] + 26) % 26 + 'A';
            }else if(currentCharacter == 0x20){//if the current character is a space '0x20'
                decryptedString += " ";
            }else{
                continue;
            }
            positionInKey = (positionInKey + 1) % key.length();
        }
        return decryptedString;
    }
};
int main(){

  VigenereSquare storedCipherKey("PASSWORD");

  string plainText;
  string password;
  cout << "Please enter in the text to be encrypted: " << endl;
  getline(cin, plainText);

  string encryptedText = storedCipherKey.encrypt(plainText);
  string decryptedText = storedCipherKey.decrypt(encryptedText);
  string modifiedPassword = storedCipherKey.generateModifiedKey(plainText);

  cout << "Your text: " + plainText + "\n" << endl;
  cout << "Encrypted Text: " << encryptedText << endl;
  cout << "Altered Password: " << modifiedPassword << endl;
  cout << "Decrypted Text: " << decryptedText << endl;
}