#ifndef TRIE_H
#define TRIE_H

#include <cstring>
#include <cstdio>
#include <QDebug>

class trie
{

private:
    int ch[5005][256], id[5005];
    int nodecnt = 1;
public:
    trie();
    void addstring(char *S, int num);
    int findid(const char *S);
};

#endif // TRIE_H
