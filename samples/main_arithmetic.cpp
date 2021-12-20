// реализация пользовательского приложения

#include <arithmetic.h>

using namespace std;

int main()
{
    string str;
    for (size_t i = 0; i < 100; i++)
    {
        try {
            cout << "Original expression:" << endl;
            getline(cin, str);
            validation(str);
            Arithmetic res;
            res.string_to_lexeme(str);
            cout << endl << "Reverse Polish notation:" << endl;
            res.term_to_polish();
            res.print();
            cout << endl << endl;
            cout << "Result: " << endl << res.calculate();
            cout << endl << endl;
        }

        catch (char* ch)
        {
            cout << ch << endl;
        }
    }
    return 0;
}

