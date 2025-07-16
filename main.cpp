#include <iostream>
#include <exception>
#include <windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unicode/unistr.h>
#include <unicode/uchar.h>
#include <unicode/ustring.h>

using namespace std;
namespace std{
    template <>
    struct hash<icu::UnicodeString>
    {
        size_t operator()(const icu::UnicodeString &uni_str) const
        {
            string utf8;
            uni_str.toUTF8String(utf8);
            return hash<string>()(utf8);
        }
    };
}

ostream &operator<<(ostream &os, const icu::UnicodeString &ustr)
{
    string utf8;
    ustr.toUTF8String(utf8);
    return os << utf8;
}

#include "./structures/ChainedHashTable.hpp"
#include "./structures/OpenAdressingHashTable.hpp"
#include "./structures/AVL.hpp"
#include "./structures/RBT.hpp"
#include "dictionary_tree.hpp"
#include "dictionary_hash.hpp"

void dictionary_AVL(string name_file)
{
    ifstream file("livros/" + name_file + ".txt");
    if (!file.is_open())
    {
        cerr << "Falha ao abrir arquivo: " << name_file << endl;
        return;
    }

    string entrada;
    Dictionary_Tree<AVL, icu::UnicodeString, int> avl_unicode;
    icu::UnicodeString tratada, normalizada;

    while (getline(file, entrada))
    {
        tratada.remove();
        normalizada = icu::UnicodeString::fromUTF8(entrada);
        for (int32_t i = 0; i < normalizada.length(); i++)
        {
            UChar c = normalizada.charAt(i);

            if (u_isalpha(c))
            {
                tratada.append(c);
            }

            if (c == '-' && i > 0 && i < normalizada.length() - 1)
            {
                if (u_isalpha(normalizada.charAt(i - 1)) && u_isalpha(normalizada.charAt(i + 1)))
                    tratada.append(c);
            }

            if (c == ' ' && !tratada.isEmpty())
            {
                tratada = tratada.toLower();
                avl_unicode[tratada] = avl_unicode[tratada] + 1;
                tratada.remove();
            }
        }
        if (!tratada.isEmpty())
        {
            tratada = tratada.toLower();
            avl_unicode[tratada] = avl_unicode[tratada] + 1;
        }
    }

    stringstream buffer;
    streambuf *antigo = cout.rdbuf();

    cout.rdbuf(buffer.rdbuf());

    avl_unicode.show();

    cout.rdbuf(antigo);

    ofstream new_file("resultados/" +  name_file + "/" + name_file + "_dictionary_avl.txt");

    if (!new_file.is_open())
    {
        cerr << "Falha ao abrir arquivo: " << name_file << endl;
        return;
    }

    while (getline(buffer, entrada))
    {
        normalizada = icu::UnicodeString::fromUTF8(entrada);
        new_file << normalizada << endl;
    }

    new_file.close();
}

void dictionary_RBT(string name_file)
{
    ifstream file("livros/" + name_file + ".txt");
    if (!file.is_open())
    {
        cerr << "Falha ao abrir arquivo: " << name_file << endl;
        return;
    }

    string entrada;
    Dictionary_Tree<RBT, icu::UnicodeString, int> rbt_unicode;
    icu::UnicodeString tratada, normalizada;

    while (getline(file, entrada))
    {
        tratada.remove();
        normalizada = icu::UnicodeString::fromUTF8(entrada);
        for (int32_t i = 0; i < normalizada.length(); i++)
        {
            UChar c = normalizada.charAt(i);

            if (u_isalpha(c))
            {
                tratada.append(c);
            }

            if (c == '-' && i > 0 && i < normalizada.length() - 1)
            {
                if (u_isalpha(normalizada.charAt(i - 1)) && u_isalpha(normalizada.charAt(i + 1)))
                    tratada.append(c);
            }

            if (c == ' ' && !tratada.isEmpty())
            {
                tratada = tratada.toLower();
                rbt_unicode[tratada] = rbt_unicode[tratada] + 1;
                tratada.remove();
            }
        }
        if (!tratada.isEmpty())
        {
            tratada = tratada.toLower();
            rbt_unicode[tratada] = rbt_unicode[tratada] + 1;
        }
    }

    stringstream buffer;
    streambuf *antigo = cout.rdbuf();

    cout.rdbuf(buffer.rdbuf());

    rbt_unicode.show();

    cout.rdbuf(antigo);

    ofstream new_file("resultados/" + name_file + "_dictionary_rbt.txt");

    if (!new_file.is_open())
    {
        cerr << "Falha ao abrir arquivo: " << name_file << endl;
        return;
    }

    while (getline(buffer, entrada))
    {
        normalizada = icu::UnicodeString::fromUTF8(entrada);
        new_file << normalizada << endl;
    }

    new_file.close();
}

void dictionary_Open_Hash(string name_file)
{
    ifstream file("livros/" + name_file + ".txt");
    if (!file.is_open())
    {
        cerr << "Falha ao abrir arquivo: " << name_file << endl;
        return;
    }

    string entrada;
    Dictionary_Hash<OpenAdressingHashTable, icu::UnicodeString, int> open_adress_hash_unicode;
    icu::UnicodeString tratada, normalizada;

    while (getline(file, entrada))
    {
        tratada.remove();
        normalizada = icu::UnicodeString::fromUTF8(entrada);
        for (int32_t i = 0; i < normalizada.length(); i++)
        {
            UChar c = normalizada.charAt(i);

            if (u_isalpha(c))
            {
                tratada.append(c);
            }

            if (c == '-' && i > 0 && i < normalizada.length() - 1)
            {
                if (u_isalpha(normalizada.charAt(i - 1)) && u_isalpha(normalizada.charAt(i + 1)))
                    tratada.append(c);
            }

            if (c == ' ' && !tratada.isEmpty())
            {
                tratada = tratada.toLower();
                open_adress_hash_unicode[tratada] = open_adress_hash_unicode[tratada] + 1;
                tratada.remove();
            }
        }
        if (!tratada.isEmpty())
        {
            tratada = tratada.toLower();
            open_adress_hash_unicode[tratada] = open_adress_hash_unicode[tratada] + 1;
        }
    }

    stringstream buffer;
    streambuf *antigo = cout.rdbuf();

    cout.rdbuf(buffer.rdbuf());

    open_adress_hash_unicode.show();

    cout.rdbuf(antigo);

    ofstream new_file("resultados/" + name_file + "_dictionary_open_adress_hash.txt");

    if (!new_file.is_open())
    {
        cerr << "Falha ao abrir arquivo: " << name_file << endl;
        return;
    }

    while (getline(buffer, entrada))
    {
        normalizada = icu::UnicodeString::fromUTF8(entrada);
        new_file << normalizada << endl;
    }

    new_file.close();
}

void dictionary_Chained_Hash(string name_file)
{
    ifstream file("livros/" + name_file + ".txt");
    if (!file.is_open())
    {
        cerr << "Falha ao abrir arquivo: " << name_file << endl;
        return;
    }

    string entrada;
    Dictionary_Hash<ChainedHashTable, icu::UnicodeString, int> chained_hash_unicode;
    icu::UnicodeString tratada, normalizada;

    while (getline(file, entrada))
    {
        tratada.remove();
        normalizada = icu::UnicodeString::fromUTF8(entrada);
        for (int32_t i = 0; i < normalizada.length(); i++)
        {
            UChar c = normalizada.charAt(i);

            if (u_isalpha(c))
            {
                tratada.append(c);
            }

            if (c == '-' && i > 0 && i < normalizada.length() - 1)
            {
                if (u_isalpha(normalizada.charAt(i - 1)) && u_isalpha(normalizada.charAt(i + 1)))
                    tratada.append(c);
            }

            if (c == ' ' && !tratada.isEmpty())
            {
                tratada = tratada.toLower();
                chained_hash_unicode[tratada] = chained_hash_unicode[tratada] + 1;
                tratada.remove();
            }
        }
        if (!tratada.isEmpty())
        {
            tratada = tratada.toLower();
            chained_hash_unicode[tratada] = chained_hash_unicode[tratada] + 1;
        }
    }

    stringstream buffer;
    streambuf *antigo = cout.rdbuf();

    cout.rdbuf(buffer.rdbuf());

    chained_hash_unicode.show();

    cout.rdbuf(antigo);

    ofstream new_file("resultados/" + name_file + "_dictionary_chained_hash.txt");

    if (!new_file.is_open())
    {
        cerr << "Falha ao abrir arquivo: " << name_file << endl;
        return;
    }

    while (getline(buffer, entrada))
    {
        normalizada = icu::UnicodeString::fromUTF8(entrada);
        new_file << normalizada << endl;
    }

    new_file.close();
}


int main(int argc, char *argv[])
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    string str;
    for (int i = 1; i < argc; i++)
    {
        cout << "$" << argv[i] << endl;
        str = argv[i];
        if (str == "all")
        {
            if (i + 1 < argc)
            {
                i++;
                dictionary_AVL(argv[i]);
                dictionary_RBT(argv[i]);
                dictionary_Open_Hash(argv[i]);
                dictionary_Chained_Hash(argv[i]);
            }
            else
            {
                cerr << "Erro: 'dictionary...' exige um argumento de caminho" << endl;
            }
        }
        else if(str == "dictionary_avl")
        {
            if (i + 1 < argc)
            {
                i++;
                dictionary_AVL(argv[i]);
            }
            else
            {
                cerr << "Erro: 'dictionary...' exige um argumento de caminho" << endl;
            }
        }
        else if(str == "dictionary_rbt")
        {
            if (i + 1 < argc)
            {
                i++;
                dictionary_RBT(argv[i]);
            }
            else
            {
                cerr << "Erro: 'dictionary...' exige um argumento de caminho" << endl;
            }
        }
        else if(str == "dictionary_chained_hash")
        {
            if (i + 1 < argc)
            {
                i++;
                dictionary_Chained_Hash(argv[i]);
            }
            else
            {
                cerr << "Erro: 'dictionary...' exige um argumento de caminho" << endl;
            }
        }
        else if(str == "dictionary_open_adress_hash")
        {
            if (i + 1 < argc)
            {
                i++;
                dictionary_Open_Hash(argv[i]);
            }
            else
            {
                cerr << "Erro: 'dictionary...' exige um argumento de caminho" << endl;
            }
        }
    }
}