#ifndef HFMTREE_H
#define HFMTREE_H

#include<QDebug>
#include<string>
#include<fstream>
#include<filesystem>
#include<queue>

using namespace std;
namespace fs = std::filesystem;

void hfmCompress(string srcAddr, string dstAddr, char* extraInfo, int infoSize);
int hfmDecode(string fileAddr, string dstAddr, char* extraInfo);

class huffmanNode
{
public:
    int weight;
    string code;
    int parent,left,right;
    huffmanNode();
    bool operator<(const huffmanNode*other);
};

class hfmTree
{
public:
    huffmanNode *node;
    int root;
    hfmTree();
    void coding();
    void build();
    int search(int x);
    ~hfmTree();

private:
    int cur;
    void coding(int index, char app);
    int supLen;
    int* index;
    void swap(int *a,int *b);
    void cmpswap(int *a,int *b);
    int partition(int array[],int l,int r);
    void quicksort_m(int array[],int left,int right);
    void insertsort(int array[],int left,int right);
    int quicksort(int array[],int left,int right);
};
#endif // HFMTREE_H
