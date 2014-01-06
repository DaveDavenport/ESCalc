#include <iostream>
#include <stdlib.h>
#include <muParser.h>
#include "muParserInt.h"
#include <readline/readline.h>
#include <readline/history.h>

/**
 * TODO
 * * Allow switching 32bit/64bit.
 * * Use round from math lib.
 */
using namespace std;
using namespace mu;


const int kilob = 1024;
const int megab = 1024*1024;
const int gigab = 1024*1024*1024;

///////////////
// Postfix  //
///////////////
// SI
static value_type kilo ( value_type val ) { return 1000*val; }
static value_type mega ( value_type val ) { return 1000*1000*val; }
static value_type giga ( value_type val ) { return 1000*1000*1000*val; }

static value_type kilobyte(value_type val) { return kilob*val; }
static value_type megabyte (value_type val) { return megab*val; }
static value_type gigabyte (value_type val) { return gigab*val; }

static void print_help()
{
    cout << "Help:" <<endl;
    cout << "Supported postfixes:" << endl; 
    cout << "\tkb  kilobyte  (1024)" << endl;
    cout << "\tmb  megabyte  (1024kb)" << endl;
    cout << "\tgb  gigabyte  (1024mb)" << endl;
    cout << endl;
    cout << "\tk   kilo      (1000)" << endl;
    cout << "\tM   Mega      (1000k)" << endl;
    cout << "\tG   Giga      (1000M)" << endl;
}

int main (int argc, char **argv)
{
    // Setup readline
    const char *prompt = "> "; 
    using_history();


    // Create parser object.
    mu::ParserInt p;
    p.DefineOprtChars("mkgbMGx");
    value_type ans = 0;
    p.DefineVar("ans", &ans);
                       
    try{
        p.DefinePostfixOprt("kb", kilobyte);
        p.DefinePostfixOprt("mb", megabyte);
        p.DefinePostfixOprt("gb", gigabyte);

        // SI
        p.DefinePostfixOprt("k", kilo);
        p.DefinePostfixOprt("M", mega);
        p.DefinePostfixOprt("G", giga);
    } catch (Parser::exception_type &e) {
        std::cerr << "Error setting up muParser: " << e.GetMsg() << endl;
        return 1;
    }


    // Loop over a readline.
    do{
        try {
            // Read a new line.
            char *temp = readline(prompt);

            // Check for EOF
            if(temp == NULL) break;
            // Check for empty line.
            if(temp[0] == '\0'){
                free(temp);
                continue;
            }
            // check help.
            if(strncasecmp(temp, "help", 4) == 0) {
                print_help();
                free(temp);
                continue;
            }
            add_history(temp);
            // Calculate
            p.SetExpr(temp);


            // Print result.
            std::cout << "Result: "<<endl;
            long result = p.Eval();
            std::cout << "dec:   "<<dec <<(unsigned long)result<< " (unsigned)" << endl;
            std::cout << "dec:   "<< long(result) << " (signed)" << endl; 
            std::cout << "hex:   0x"<<hex << result << endl;

            std::cout  << "bit:   "; 
            unsigned long mask = 1<<31;
            for(int i =0 ; i  < 32; i++,mask>>=1) {
                std::cout << ((result&mask) == 0? 0:1);
                if((i%4) == 3) std::cout << " ";
            }
            std::cout << endl;
            std::cout << "Bytes: " << dec;

            std::cout << int(result%kilob) << "b, ";
            std::cout <<  int((result%megab)/kilob) << "kb, ";
            std::cout <<  int((result%gigab)/megab) << "mb, ";
            std::cout <<  int(result/gigab) << "gb" <<endl;

            // update ans variable
            ans = result;
            // Cleanup
            free(temp);
        } catch (Parser::exception_type &e) {
            std::cerr << "Error: " << e.GetMsg() << endl;
        }
    }while(true);

    return 0;
}
