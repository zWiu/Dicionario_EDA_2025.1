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

namespace std
{
    template <>
    struct hash<icu::UnicodeString>
    {
        size_t operator()(const icu::UnicodeString &uni_str) const
        {
            std::string utf8;
            uni_str.toUTF8String(utf8);
            return std::hash<std::string>()(utf8);
        }
    };
}

std::ostream &operator<<(std::ostream &os, const icu::UnicodeString &ustr)
{
    std::string utf8;
    ustr.toUTF8String(utf8);
    return os << utf8;
}
#include "./structures/ChainedHashTable.hpp"
#include "./structures/OpenAdressingHashTable.hpp"
#include "./structures/AVL.hpp"
#include "./structures/RBT.hpp"
#include "dictionary_tree.hpp"
#include "dictionary_hash.hpp"

void listArchive(string nameFile)
{
    ifstream file("livros/" + nameFile + ".txt");
    if (!file.is_open())
    {
        cerr << "Falha ao abrir arquivo: " << nameFile << endl;
        return;
    }

    string entrada;
    vector<icu::UnicodeString> vec_unicode_names;
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
                vec_unicode_names.push_back(tratada.toLower());
                tratada.remove();
            }
        }
        if (!tratada.isEmpty())
            vec_unicode_names.push_back(tratada.toLower());
    }

    file.close();

    for (const auto &uStr : vec_unicode_names)
    {
        string utf8str;
        uStr.toUTF8String(utf8str);
        int32_t codepointCount = u_countChar32(uStr.getBuffer(), uStr.length());

        cout << "Número de caracteres em \"" << utf8str << "\": " << codepointCount << "\n";
    }
}

void dictionary_AVL(string nameFile)
{
    ifstream file("livros/" + nameFile + ".txt");
    if (!file.is_open())
    {
        cerr << "Falha ao abrir arquivo: " << nameFile << endl;
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
            avl_unicode[tratada] = avl_unicode[tratada] + 1;
    }

    std::stringstream buffer;
    std::streambuf* antigo = std::cout.rdbuf();

    std::cout.rdbuf(buffer.rdbuf());

    avl_unicode.show();

    std::cout.rdbuf(antigo);

    std::string textoCapturado = buffer.str();
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
        cout << argv[i] << endl;
        str = argv[i];
        if (str == "liste")
        {
            if (i + 1 < argc)
            {
                i++;
                listArchive(argv[i]);
            }
            else
            {
                cerr << "Erro: 'liste' exige um argumento de caminho" << endl;
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
                cerr << "Erro: 'liste' exige um argumento de caminho" << endl;
            }
        }
    }
}