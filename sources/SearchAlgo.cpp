//"Copyright 2019 Fedorov George"
#include "SearchAlgo.h"
#define PRIMEVAL 2

struct arch
{
    int buff = 0;
    int warning = 0;
};

int strLen(const string& str)
{
    int count = 0;
    int i = 0;
    while (str[i] != '\0')
    {
        count++;
        i++;
    }
    return count;
}

int powX(int x, int y)
{
    if (y == 0)
        return 1;

    int retval = x;
    while (y > 0)
    {
        y--;
        retval *= x;
    }
    return retval;
}

size_t str_find(const std::string& str, const std::string& substr)
{
    int a = strLen(str);
    int b = strLen(substr);
    for (int i = 0; i < a; i++)
    {
        if (substr[0] == str[i]){
            int j = 0;
            for (; j < b; j++)
            {
                if (substr[j] != str[i + j]){
                    break;
                }
            }
            if (j == b){
                return i;
            }
        }
    }
    return -1;
}

//--------------------------- RK_FIND ----------------------------------------
int calcHush(const string & str, int len, int indStart)
{
    int prime = PRIMEVAL;
    int oldPrime = PRIMEVAL;
    int hush = 0;
    char a;
    for (int i = indStart; i < indStart + len; i++)
    {
        a = str[i];
        if (i == indStart){
            hush = static_cast<int>(a);
        }else{
            hush += (static_cast<int>(a))*prime;
            prime = prime*oldPrime;
            if (hush >= INT_MAX){
                hush = 0;
            }
        }
    }
    return hush;
}

size_t rk_find(const std::string& str, const std::string& substr)
{
    int hush = 0;
    int buff = 0;
    int prime = PRIMEVAL;
    int cntr1 = 0;
    //int cntr2 = strLen(substr);
    int totalch = strLen(str);
    int len = strLen(substr);

    hush = calcHush(substr, strLen(substr), 0);
    buff = calcHush(str, strLen(substr), 0);
label:
    while (buff != hush)
    {
        if (cntr1 + len >= totalch){
            return -1;
        }

        int a, b, c, e;
        a = buff - static_cast<int>(str[cntr1]);
        b = a / prime;
        c = pow(prime, len - 1);
        e = (static_cast<int>(str[cntr1 + len]))*c;
        buff = b + e;
        cntr1++;
    }
    int cntr3 = cntr1;
    for (int k = 0; k < strLen(substr); k++)
    {
        if (str[cntr1] == substr[k]){
            cntr1++;
        }else{
            if (cntr1 < totalch - 1)
            {
                buff = calcHush(str, strLen(substr), cntr3 + 1);
                cntr1 = cntr3 + 1;
                goto label;
            }
            return -1;//Слово не найдено
        }
    }
    return cntr3;
}

//------------------------- KMP ФУНКЦИЯ ----------------------
//Алгоритм считающий префикс функцию
vector<int> prefFunc(string s)
{
    int n = s.length();
    vector<int> intArr(n);
    intArr[0] = 0;
    for (int i = 1; i < n; ++i)
    {
        int j = intArr[i - 1];
        while (j > 0 && s[i] != s[j])
        {
            j = intArr[j - 1];
        }
        if (s[i] == s[j]){
            ++j;
        }
        intArr[i] = j;
    }
    return intArr;
}

//Алгоритм Кнута - Морриса - Пратта
size_t kmp_find(string str, std::string findStr)
{
    vector<int> pIntArr = prefFunc(findStr);
    unsigned int sLen = str.length();
    for (unsigned int k = 0, i = 0; i < sLen; i++)
    {
        while ((k > 0) && (findStr[k] != str[i]))
            k = pIntArr[k - 1];

        if (findStr[k] == str[i])
            k++;

        if (k == findStr.length())//либо продолжаем поиск следующих вхождений
            return (i - findStr.length() + 1);
    }

    return -1;
}
