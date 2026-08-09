#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdint>

using namespace std;

enum {
    INIT, //Now havn't read any single character
    WORD, //Now reading normal word, ex: ls, grep...etc
    PIPE  //Just read a '|', and checking to see if there's another '|' after it
};

void parserToken(string &cmdLine, vector<string> &tokens) {
    //cmdLine : the entire command line entered by the user, ex: "ls | grep cpp"
    //tokens : the location where the results are stored one by one after the disassembly is complete

    int32_t status = INIT; // Nothing is read initially, so the state was set to INIT.

    string token = ""; //Temporarily store the string currently being composed.

    auto addToken = [&token, &tokens]() {
        
        //Store the current "token's" content into 'tokens' and clear the 'token'. 
        if (token != "") {
            tokens.push_back(token);
            token = "";
        }
        
    };


    for (const auto &c : cmdLine) {
        //Extract one character 'c' from cmdLine one at a time, from left to right
        
        if (status == INIT) {
            // Nothing is currently being composed.
            // First, determine what the current character 'c' is.
            
            
            if (isblank(c)) { // The current character 'c' is whitespace, and we're not reading a word, so skip it.
                continue; 
            }

            if (c == '|') { // The current character 'c' is '|'.
                status = PIPE; // The current character 'c' is '|'. Wait for the next character.
            }
            else {
                status = WORD; // The current character 'c' is not whitespace or '|', so start reading a word.
            }
            
            token.push_back(c); // Add the current character to the token.
        }
        //First, examine the current character to determine the status; then, add the current character to the token.
        

        else if (status == PIPE) {
            // The previous character was '|'.
            // Check the current character.
            
            
            if (isblank(c)) { // '|' is complete because the current character is whitespace.
              
                addToken();   // Add '|' to the list of tokens.
                status = INIT; // Go back to the initial state.
            }
            else if (c == '|') { // The current character is also '|', so the token becomes "||".
              
                token.push_back(c);  // Add the current character to the token.
                status = WORD;       // Start treating the token as a word.
            }
            else { // The current character is a normal character.
             
                addToken();          // Add '|' to the list of tokens.
                token.push_back(c);  // Start a new token with the current character.
                status = WORD;       // Start reading a word.
            }
        }
        
        else { // status == WORD: We are currently reading a word.

            if (isblank(c)) { // The current character is whitespace,
                // so the word is complete.
                status = INIT;
                addToken();  // Add the completed word to the list of tokens.
            } 
            else if (c == '|') {
                // The current character is '|',
                // so the current word is complete.
                status = PIPE;
                addToken();          // Add the previous word to the list of tokens.
                token.push_back(c);  // Start a new token with the current character.
            } 
            else { // The current character is not whitespace or '|',
                // so add it to the current token.
                token.push_back(c);  // Add the current character to the token.
                // status stays the same: WORD.
            }
        }
    }

    addToken(); // The last token may not have been added after the for loop ends.
    // There is no whitespace or '|' after it to trigger addToken(),
    // so we need to add it here.
}


int main() {
    string cmdLine;
    vector<string> tokens;

    cout << "Enter command: ";
    getline(cin, cmdLine);

    parserToken(cmdLine, tokens);

    cout << "\nTokens:\n";

    for (const auto &token : tokens) {
        cout << token << endl;
    }

    return 0;
}