#ifndef PATHLIBRARY_H
#define PATHLIBRARY_H

#include <list>
#include "graph.h"
using namespace std;

class PathLibrary
{
public:
    PathLibrary();
private:
    list<list<list<int>>> pathInfo;
};

#endif // PATHLIBRARY_H
