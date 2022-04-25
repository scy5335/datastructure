#include "trie.h"

trie::trie(){
    memset(ch, 0, sizeof ch);
    memset(id, 0, sizeof id);
}

void trie::addstring(char *S, int num){
    int len = (int)strlen(S), now = 0;
    for (int i = 0; i < len; i++){
        unsigned char nxtch = (unsigned char)S[i];
        if (!ch[now][nxtch])
            ch[now][nxtch] = nodecnt ++;
        now = ch[now][nxtch];
    }
    id[now] = num;
}

int trie::findid(const char *S){
    int len = (int)strlen(S), now = 0;
    for (int i = 0; i < len; i++){
        unsigned char nxtch = (unsigned char)S[i];
        if (!ch[now][nxtch])
            return -1;
        now = ch[now][nxtch];
    }
    return id[now];
}
