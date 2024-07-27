#include <iostream>
#include <ctime>
using namespace std;
void characters(int a){
    srand(time(0));
    int x,j;
    
    for(int i = 0;i<=a/7;i++)
    {
        x = rand() % a + 1;
        cout << x ;
    }
}
int realcharacterslower(int a){
    srand(time(0));
    int z;
    char b[28] = {'f','g','h','i','l','m','n','a','b','c','u','v'};
    for(int j = 0; j <= a/7;j++)
    {
        z = rand() % 12+1;
    cout << b[z];
    }
}
int realcharacters(int a){
    srand(time(0));
    int y;
    char b[28] = {'Q','R','V','J','X','F','H','S','L','W','G','T','K','U','Y','Z'};
    for(int k = 0; k <= a/7;k++)
    {
        y = rand() % 14 + 1;
    cout << b[y];
    }
}
int realcharacterslower2(int a){
    srand(time(0));
    int z;
    char b[28] = {'w','d','j','k','e','o','p','q','r','s','t','x','y','z'};
    for(int j = 0; j <= a/7;j++)
    {
        z = rand() % 13 + 1;
    cout << b[z];
    }
}
void symbols(int a) {
    srand(time(0)); 
    const char* symbols[] = {
        ">", ",", ".",  "O_O","?", "-", "_" "^", "&","#", "$", "%", "[", "]", ":", ";", "\"","@",  "*", "(", ")", "+",
         "'", "<",":-P", ":P", ";-)""/","J", "=",   "{", "}","!",":-)", ":)", ":-(",
        "|", "~", "`", ":(",":'(", ":-/",
    };
    int numSymbols = sizeof(symbols) / sizeof(symbols[0]);
    for (int i = 0; i < a/7; i++) {
        int y = rand() % numSymbols; 
        cout << symbols[y];
    }
    cout << endl;
}
int realcharacters2(int a){
    srand(time(0));
    int y;
    char b[28] = {'D','E','p','B','P','A','C','I','M','N','O'};
    for(int k = 0; k <= a/7;k++)
    {
        y = rand() % 10 + 1;
    cout << b[y];
    }
}
void symbols2(int a) {
    srand(time(0)); 
    const char* symbols[] = {
        "-", "_", "=",   "{", "}","!", "^", "&","#", "$", "%", "[", "]", ":", ";", "\"","@",  "*", "(", ")", "+",
         "'", "<",":-P", ":P", ";-)", ":O", ":-D", ":D", ";)" ">_<", "^_^", "-_-"
    };
    int numSymbols = sizeof(symbols) / sizeof(symbols[0]);
    for (int i = 0; i < a/7; i++) {
        int y = rand() % numSymbols; 
        cout << symbols[y];
    }
    cout << endl;
}

int main(){
    int numin;
    cout <<"Enter length of your password : \n";
    cin >> numin;
    if (numin < 8) {
        numin = 8;
        cout << "Length set to minimum of 8." << endl;
    }
    characters(numin);
    realcharacters(numin);
    realcharacterslower(numin);
    symbols(numin);
    realcharacters2(numin);
    realcharacterslower2(numin);
    symbols2(numin);
    return 0;
}