#ifndef SearchAlgo_h
#define SearchAlgo_h

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h> 
#include <math.h>
#include <utility>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <cstddef>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long int64;

int strLen(const string& str);
int powX(int x, int y);
size_t str_find(const std::string& str, const std::string& substr);
int64 calcHush(const string & str, int len, int indStart);
size_t rk_find(const std::string& str, const std::string& substr);
size_t kmp_find(std::string findStr, string str);

#endif