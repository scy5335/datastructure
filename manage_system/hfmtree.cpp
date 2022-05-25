#include "hfmtree.h"


void hfmCompress(string srcAddr, string dstAddr, char* extraInfo, int infoSize)
{
    fstream ifs,ofs;
    int i,j;
    int max=0;

    ifs.open(srcAddr,ios::in|ios::binary);//打开待压缩文件
    if(!ifs.is_open())
    {
        qDebug()<<"打开失败";
        return;
    }

    int size = fs::file_size(srcAddr);//计算文件大小
    unsigned char* buf = new unsigned char[size]();//注意要用无符号char，否则会访问负数下标数组
    hfmTree* tree=new hfmTree();

    ifs.read((char*)buf,size);//将文件读入内存中
    for(i=0;i<size;i++)
    {
        tree->node[buf[i]].weight++;//统计字节出现的频率
    }

    tree->coding();//对字节进行编码
    ofs.open(dstAddr,ios::out|ios::trunc|ios::binary);//打开输出文件

    unsigned char byteOut=0;
    unsigned int cnt=0;
    string s;

    for(i=0;i<256;i++)//根据最大频率计算存储频率需要的字节数
    {
        max=tree->node[i].weight>max?tree->node[i].weight:max;
    }
    int Bytes = ceil(ceil(log2(max))/8.0);


    ofs.put((char)Bytes);//写入存储频率需要的字节数
    ofs.write((char*)&size,4);//写入原文件大小

    unsigned char temp=infoSize;//信息大小不得超过255字节，否则截断
    ofs.put(temp);//写入信息的大小
    if(extraInfo!=nullptr&&temp!=0)
    {
        ofs.write(extraInfo,temp);
    }

    //将字节出现频率 按字节的二进制大小顺序写入文件
    for(i=0;i<256;i++)
    {
        ofs.write((char*)&tree->node[i].weight,Bytes);
    }


    //按字节写入
    for(i=0;i<size;i++)
    {
        s= tree->node[buf[i]].code;
        for(j=0;j<s.length();j++)
        {
            byteOut<<=1;
            cnt++;
            if(s[j]=='1')
                byteOut+=1;
            if(cnt%8==0)
            {
                ofs.put(byteOut);
            }
        }
    }
    //剩余的比特左对齐
    if(cnt%8!=0)
    {
        byteOut<<=(8-cnt/8);
        ofs.put(byteOut);
    }

    ifs.close();
    ofs.close();
    delete tree;
    delete[] buf;
}


int hfmDecode(string fileAddr, string dstAddr, char* extraInfo)
{
    fstream ifs,ofs;
    ifs.open(fileAddr,ios::in|ios::binary);
    if(!ifs.is_open())
    {
        qDebug()<<"文件打开失败，请检查文件路径";
        return -1;
    }

    int size = fs::file_size(fileAddr);//计算文件大小
    int bufSize=size;
    unsigned char Bytes=1, tempSize=0;
    int i, j;
    int temp;
    int originSize=0;

    //辅助信息读取
    ifs.read((char*)&Bytes,1),bufSize-=1;
    ifs.read((char*)&originSize,4),bufSize-=4;
    ifs.read((char*)&tempSize,1),bufSize-=1;
    if(tempSize!=0)//如果读取到的额外信息大小不为0
    {
        if(extraInfo!=nullptr)//如果输入了合法的地址
            ifs.read(extraInfo,tempSize);
        else//否则额外信息作废，跳过这部分
            ifs.seekg(tempSize,ios::cur);
        bufSize-=tempSize;
    }

    hfmTree* tree=new hfmTree();
//    qDebug()<<"原字节数："<<originSize;
    for(int i=0;i<256;i++)//树的重建
    {
        ifs.read((char*)&tree->node[i].weight,Bytes);
//        qDebug()<<tree->node[i].weight;
    }
    bufSize-=256*Bytes;

    tree->build();
    unsigned char* buf = new unsigned char[bufSize+5]();//注意要用无符号char，否则会访问负数下标数组
    ifs.read((char*)buf,bufSize);
    ofs.open(dstAddr,ios::out|ios::binary|ios::trunc);
    if(!ofs.is_open())
        return -1;

    for(i=0;i<bufSize;i++)
    {
        for(j=7;j>=0;j--)
        {
            temp=tree->search((buf[i]>>j)&0x1);
            if(temp!=-1)
            {
                ofs.put((char)temp);
                originSize--;
                if(originSize==0)
                    break;
            }
        }
        if(originSize==0)
            break;
    }
    ifs.close();
    ofs.close();
    delete[] buf;
    delete tree;
    return tempSize;
}


huffmanNode::huffmanNode()
{
    this->weight=0;
    this->left=-1;
    this->right=-1;
    this->parent=-1;
    this->code="";
}


hfmTree::hfmTree()
{
    this->node=new huffmanNode[512]();
    this->supLen=256;
    this->root=-1;
    this->index=new int[256]();
    for(int i=0;i<256;i++)
    {
        index[i]=i;
    }
}

void hfmTree::build()
{
    //按照node权重对index数组的下标排序
    queue<int> leafQ;
    queue<int> supQ;
    int i;
    quicksort(index,0,255);

    for(i=0;!node[index[i]].weight;i++);
    for(;i<256;i++)
    {
        leafQ.push(index[i]);
    }
    int min1,min2;
    while(true)
    {
        //取最小元素
        min1=-1;
        if(!leafQ.empty()&&!supQ.empty())
        {
            if(node[leafQ.front()].weight<=node[supQ.front()].weight)
            {
                min1=leafQ.front();
                leafQ.pop();
            }
            else
            {
                min1=supQ.front();
                supQ.pop();
            }
        }
        else if(leafQ.empty())
        {
            min1=supQ.front();
            supQ.pop();
        }
        else if(supQ.empty())
        {
            min1=leafQ.front();
            leafQ.pop();
        }
        //再取一个最小元素
        min2=-1;
        if(!leafQ.empty()&&!supQ.empty())
        {
            if(node[leafQ.front()].weight<=node[supQ.front()].weight)
            {
                min2=leafQ.front();
                leafQ.pop();
            }
            else
            {
                min2=supQ.front();
                supQ.pop();
            }
        }
        else if(leafQ.empty())
        {
            min2=supQ.front();
            supQ.pop();
        }
        else if(supQ.empty())
        {
            min2=leafQ.front();
            leafQ.pop();
        }
        node[min1].parent=node[min2].parent=supLen;
//        qDebug()<<node[min1].parent<<" "<<node[min2].parent;
        node[supLen].left=min1;
        node[supLen].right=min2;
//        qDebug()<<node[supLen].left<<" "<<node[supLen].right;
        node[supLen].weight=node[min1].weight+node[min2].weight;
//        qDebug()<<node[supLen].weight;
        if(leafQ.empty()&&supQ.empty())
        {
            this->root=supLen;
            this->cur=supLen;
            return;
        }
        supQ.push(supLen);
        supLen++;
    }

    return;
}

void hfmTree::coding()
{
    build();
    coding(node[root].left,'0');
    coding(node[root].right,'1');
}

int hfmTree::search(int x)
{
    if(x==0)
        cur=node[cur].left;
    else if(x==1)
        cur=node[cur].right;
    else
        qDebug()<<"输入错误";
    int temp=-1;
    if(node[cur].left==-1)
    {
        temp=cur;
        cur=root;
    }
    return temp;
}


hfmTree::~hfmTree()
{
    delete[]node;
    delete[]index;
}

void hfmTree::coding(int index, char app)
{
    //从root触发，途径的结点
//    qDebug()<<index;
    if(index==-1)
    {
        return;
    }
    else
    {
        node[index].code=node[node[index].parent].code + app;
    }
    coding(node[index].left,'0');
    coding(node[index].right,'1');
}

void hfmTree::swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void hfmTree::cmpswap(int *a, int *b)
{
    if(node[*a].weight > node[*b].weight)
        swap(a,b);
}

int hfmTree::partition(int array[], int l, int r)
{
    int pivot = array[r];
    int curpos = l;
    int j ;
    for( j = l;j<r;j++)
    {
        if(array[j] < pivot)
        {
            swap(&array[j],&array[curpos]);
            curpos++;
        }
    }

    swap(&array[r],&array[curpos]);
    return curpos;
}

void hfmTree::quicksort_m(int array[], int left, int right)
{
    if(right - left < 10)
        return ;

    int mid = (left+right)/2;
    swap(&array[mid],&array[right-1]);

    cmpswap(&array[left],&array[right-1]);
    cmpswap(&array[left],&array[right]);
    cmpswap(&array[right-1],&array[right]);

    int interval = partition(array,left+1,right-1);
    quicksort_m(array,left,interval-1);
    quicksort_m(array,interval+1,right);
}

void hfmTree::insertsort(int array[], int left, int right)
{
    for(int i=left+1;i<=right;i++)
    {
        for(int j=i;j>0;j--)
        {
            cmpswap(&array[j-1],&array[j]);
        }
    }

}

int hfmTree::quicksort(int array[], int left, int right)
{
    if(array == NULL)
        return -1;
    if(right < left)
        return -2;
    if (right == left)
        return 0;
    quicksort_m(array,left,right);
    insertsort(array,left,right);
    return 0;
}

