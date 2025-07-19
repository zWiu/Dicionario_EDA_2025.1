#include <iostream>
#include <exception>
#include <windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <unicode/unistr.h>
#include <unicode/uchar.h>
#include <unicode/ustring.h>

using namespace std;
namespace std
{
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

            if (u_isspace(c) && !tratada.isEmpty())
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

    ofstream new_file("resultados/" + name_file + "_dictionary_avl.txt");

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

void general_test(string structure, string name_file, string num)
{
    size_t n = 1;
    try
    {
        n = stoi(num);
    }
    catch (const invalid_argument &e)
    {
        cerr << "Passe um valor válido para n" << endl;
        return;
    }
    catch (const out_of_range &e)
    {
        cerr << "Passe um intervalo de n válido" << endl;
        return;
    }

    if (structure == "dictionary_avl" || structure == "all")
    {
        Dictionary_Tree<AVL, icu::UnicodeString, int> avl_unicode;
        size_t duracao = 0;
        for (size_t i = 0; i < n; i++)
        {
            avl_unicode.clear();
            ifstream file("livros/" + name_file + ".txt");
            if (!file.is_open())
            {
                cerr << "Falha ao abrir arquivo: " << name_file << endl;
                return;
            }

            string entrada;

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

                    if (u_isspace(c) && !tratada.isEmpty())
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

            duracao += avl_unicode.get_duration();
        }
        stringstream buffer;
        streambuf *antigo = cout.rdbuf();

        cout.rdbuf(buffer.rdbuf());

        buffer << "Tempo total de teste: " << duracao << "ms" << endl;
        buffer << "Tempo médio para construção do dictionary_avl: " << duracao / (static_cast<double>(n)) << "ms" << endl;
        buffer << "-----------------------------------------------------" << endl;
        avl_unicode.show();

        cout.rdbuf(antigo);

        ofstream new_file("resultados/" + name_file + "_dictionary_avl.txt");

        if (!new_file.is_open())
        {
            cerr << "Falha ao abrir arquivo: " << name_file << endl;
            return;
        }

        string entrada;
        icu::UnicodeString normalizada;
        while (getline(buffer, entrada))
        {
            normalizada = icu::UnicodeString::fromUTF8(entrada);
            new_file << normalizada << endl;
        }

        new_file.close();
    }
    if (structure == "dictionary_rbt" || structure == "all")
    {
        Dictionary_Tree<RBT, icu::UnicodeString, int> rbt_unicode;
        size_t duracao = 0;
        for (size_t i = 0; i < n; i++)
        {
            rbt_unicode.clear();
            ifstream file("livros/" + name_file + ".txt");
            if (!file.is_open())
            {
                cerr << "Falha ao abrir arquivo: " << name_file << endl;
                return;
            }

            string entrada;

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

                    if (u_isspace(c) && !tratada.isEmpty())
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

            duracao += rbt_unicode.get_duration();
        }
        stringstream buffer;
        streambuf *antigo = cout.rdbuf();

        cout.rdbuf(buffer.rdbuf());

        buffer << "Tempo total de teste: " << duracao << "ms" << endl;
        buffer << "Tempo médio para construção do dictionary_rbt: " << duracao / (static_cast<double>(n)) << "ms" << endl;
        buffer << "-----------------------------------------------------" << endl;
        rbt_unicode.show();

        cout.rdbuf(antigo);

        ofstream new_file("resultados/" + name_file + "_dictionary_rbt.txt");

        if (!new_file.is_open())
        {
            cerr << "Falha ao abrir arquivo: " << name_file << endl;
            return;
        }

        string entrada;
        icu::UnicodeString normalizada;
        while (getline(buffer, entrada))
        {
            normalizada = icu::UnicodeString::fromUTF8(entrada);
            new_file << normalizada << endl;
        }

        new_file.close();
    }
    if (structure == "dictionary_open_hash" || structure == "all")
    {
        Dictionary_Hash<OpenAdressingHashTable, icu::UnicodeString, int> open_hash_unicode;
        size_t duracao = 0;
        for (size_t i = 0; i < n; i++)
        {
            open_hash_unicode.clear();
            ifstream file("livros/" + name_file + ".txt");
            if (!file.is_open())
            {
                cerr << "Falha ao abrir arquivo: " << name_file << endl;
                return;
            }

            string entrada;

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

                    if (u_isspace(c) && !tratada.isEmpty())
                    {
                        tratada = tratada.toLower();
                        open_hash_unicode[tratada] = open_hash_unicode[tratada] + 1;
                        tratada.remove();
                    }
                }
                if (!tratada.isEmpty())
                {
                    tratada = tratada.toLower();
                    open_hash_unicode[tratada] = open_hash_unicode[tratada] + 1;
                }
            }

            duracao += open_hash_unicode.get_duration();
        }
        stringstream buffer;
        streambuf *antigo = cout.rdbuf();

        cout.rdbuf(buffer.rdbuf());

        buffer << "Tempo total de teste: " << duracao << "ms" << endl;
        buffer << "Tempo médio para construção do dictionary_open_hash: " << duracao / (static_cast<double>(n)) << "ms" << endl;
        buffer << "-----------------------------------------------------" << endl;
        open_hash_unicode.show();

        cout.rdbuf(antigo);

        ofstream new_file("resultados/" + name_file + "_dictionary_open_hash.txt");

        if (!new_file.is_open())
        {
            cerr << "Falha ao abrir arquivo: " << name_file << endl;
            return;
        }

        string entrada;
        icu::UnicodeString normalizada;
        while (getline(buffer, entrada))
        {
            normalizada = icu::UnicodeString::fromUTF8(entrada);
            new_file << normalizada << endl;
        }

        new_file.close();
    }
    if (structure == "dictionary_chained_hash" || structure == "all")
    {
        Dictionary_Hash<ChainedHashTable, icu::UnicodeString, int> chained_hash_unicode;
        size_t duracao = 0;
        for (size_t i = 0; i < n; i++)
        {
            chained_hash_unicode.clear();
            ifstream file("livros/" + name_file + ".txt");
            if (!file.is_open())
            {
                cerr << "Falha ao abrir arquivo: " << name_file << endl;
                return;
            }

            string entrada;

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

                    if (u_isspace(c) && !tratada.isEmpty())
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

            duracao += chained_hash_unicode.get_duration();
        }
        stringstream buffer;
        streambuf *antigo = cout.rdbuf();

        cout.rdbuf(buffer.rdbuf());

        buffer << "Tempo total de teste: " << duracao << "ms" << endl;
        buffer << "Tempo médio para construção do dictionary_chained_hash: " << duracao / (static_cast<double>(n)) << "ms" << endl;
        buffer << "-----------------------------------------------------" << endl;
        chained_hash_unicode.show();

        cout.rdbuf(antigo);

        ofstream new_file("resultados/" + name_file + "_dictionary_chained_hash.txt");

        if (!new_file.is_open())
        {
            cerr << "Falha ao abrir arquivo: " << name_file << endl;
            return;
        }

        string entrada;
        icu::UnicodeString normalizada;
        while (getline(buffer, entrada))
        {
            normalizada = icu::UnicodeString::fromUTF8(entrada);
            new_file << normalizada << endl;
        }

        new_file.close();
    }
}

int main(int argc, char *argv[])
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    string str;
    if (argc > 3 && string(argv[3]) == "general_test")
    {
        general_test(argv[1], argv[2], argv[4]);
    }
    else
    {
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
            else if (str == "dictionary_avl")
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
            else if (str == "dictionary_rbt")
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
            else if (str == "dictionary_chained_hash")
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
            else if (str == "dictionary_open_hash")
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
}