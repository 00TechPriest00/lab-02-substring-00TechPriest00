#include "SearchAlgo.h"
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
    while (--y > 0)
    {
        retval *= x;
    }
    return retval;
}

size_t str_find(const std::string& str, const std::string& substr)
{
    int a = strLen(str);
    int b = strLen(substr);
    for (int i = 0; i < b; i++)
    {
        if (substr[0] == str[i])
        {
            int j = 0;
            for (; j < a; j++)
            {
                if (substr[j] != str[i + j])
                {
                    break;
                }
            }
            if (j == a)
            {
                return i;
            }
        }
    }
    return -1;
}

size_t rk_find(const std::string& str, const std::string& substr)
{
    int prime = 11;
    int oldPrime = 11;
    int hush = 0;
    char a;
    for (int i = 0; i < strLen(substr); i++)
    {
        a = substr[i];
        if (i == 0)
        {

            hush = (int)a;
        }
        else
        {
        hush += ((int)a)*prime;
        prime = prime*oldPrime;
        }
    }
    prime = 11;
    int len = strLen(substr);
    int buff = 0;
    for (int j = 0; j < len; j++)
    {
        a = str[j];
        if (j == 0)
        {
            buff = (int)a;
        }
        else
        {
        buff += ((int)a)*prime;
        prime = prime*oldPrime;
        }
    }
    prime = 11;
    int cntr1 = 0;
    int cntr2 = strLen(substr);
    int totalch = strLen(str);
    while (buff != hush)
    {
        buff = (buff - ((int)str[cntr1])) / prime + ((int)str[cntr2])*powX(prime,len-1);
        cntr1++;
        cntr2++;
        if (cntr2 > totalch)
        {
            return -1;
        }
    }
    int cntr3 = cntr1;
    for (int k = 0; k < strLen(substr); k++)
    {
        if (str[cntr1] == substr[k])
        {
            cntr1++;
        }else
        {
            return -1;//Слово не найдено
        }
    }
    return cntr3;
}

//Алгоритм считающий длинну префикс функции
int *prefFunc(std::string str)
{
    int len = strLen(str);
    int counter = 0;
    int j = 0;
    int saverI = 0;

    int *prefFunc1 = new int[len];
    memset(prefFunc1, 0, len*sizeof(int));

    for (int i = 0; i < len; i++)
    {
        if (i == 0)
        {
            i++;
        }
        if (str[j] == str[i])
        {
            counter++;
            prefFunc1[i] = counter;
            if (i+1 <= len)
            {
            j++;
            saverI = i;
            i++;
            while (str[j] == str[i])
            {
                counter++;
                prefFunc1[i] = counter;
                if (i+1 <= len)
                {
                j++;
                i++;
                }else
                {
                    goto flag;
                }
            }
            if (str[j] != str[i])
            {
                counter = 0;
            }
            if (i < len)
            {
            i = saverI;
            }
            }
        }
            flag:
            j = 0;
            if (str[i] != str[0] && str[i] != str[j])
            {
                counter = 0;
            }
    }
    return prefFunc1;
}

/*int* prefFunc(string str)
{
    int len = strLen(str);
    int counter = 0;
    int j = len;
    int saverI = 0;
    int saverJ = 0;

    //arch arh;

    int *prefFunc1 = new int[len];

    for (int i = 0; i < len-1; i++)
    {
        if (i>0)
        {
            j--;
        }
        while (str[i] == str[j])
        {
            saverI = i;
            saverJ = j;
            i++;
            j--;
            counter++;
            prefFunc1[i] = counter;
        }
        counter = 0;
        i = saverI;
        j = saverJ;
    }
    return prefFunc1;
}*/

//Алгоритм Кнута - Морриса - Пратта
size_t kmp_find(std::string findStr, string str)
{
    int *prefFindStr = prefFunc(findStr);

    int index = 0;
    int i = 0;
    int lenStr = strLen(str);
    int iskZnach;
    int lenFindStr = strLen(findStr);

    while (i < lenStr)
    {
        while (findStr[index] == str[i] && index < lenFindStr)
        {
            i++;
            index++;
        }
        if (index < lenFindStr)
        {
        index = prefFindStr[index - 1];
        }
    }
    iskZnach = i - index + 1;
    delete[] prefFindStr;
    return iskZnach;
}
