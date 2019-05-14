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

int strLen(const string& str);
int powX(int x, int y);
size_t str_find(const string& str, const string& substr);
size_t rk_find(const string& str, const string& substr);
void test(string findStr, string str);

#endif