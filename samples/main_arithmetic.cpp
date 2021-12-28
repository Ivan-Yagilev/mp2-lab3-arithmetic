// реализация пользовательского приложения

#include <arithmetic.h>

using namespace std;

int main()
{
    string str;
    int c = 1;
    while (c == 1)
    {
        try {     
            cout << "Original expression:" << endl;
            cin >> str;        
            validation(str);
            Solver r;
            r.string_to_lexeme(str);
            cout << "Lexeme:" << endl;
            r.print();
            cout << endl << "Reverse Polish notation:" << endl;
            r.lexeme_to_reverse();
            r.print();
            cout << endl << endl;
            cout << "Result: " << endl << r.calculation();
            cout << endl << endl;

            cout << "1. Continue" << endl << "2. Exit" << endl;
            cin >> c;
        }

        catch (char* ch)
        {
            cout << ch << endl;
        }
    }
    return 0;
}

