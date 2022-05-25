#include "hfmtree.h"


void hfmCompress(string srcAddr, string dstAddr, char* extraInfo, int infoSize)
{
    fstream ifs,ofs;
    int i,j;
    int max=0;

    ifs.open(srcAddr,ios::in|ios::binary);//�򿪴�ѹ���ļ�
    if(!ifs.is_open())
    {
        qDebug()<<"��ʧ��";
        return;
    }

    int size = fs::file_size(srcAddr);//�����ļ���С
    unsigned char* buf = new unsigned char[size]();//ע��Ҫ���޷���char���������ʸ����±�����
    hfmTree* tree=new hfmTree();

    ifs.read((char*)buf,size);//���ļ������ڴ���
    for(i=0;i<size;i++)
    {
        tree->node[buf[i]].weight++;//ͳ���ֽڳ��ֵ�Ƶ��
    }

    tree->coding();//���ֽڽ��б���
    ofs.open(dstAddr,ios::out|ios::trunc|ios::binary);//������ļ�

    unsigned char byteOut=0;
    unsigned int cnt=0;
    string s;

    for(i=0;i<256;i++)//�������Ƶ�ʼ���洢Ƶ����Ҫ���ֽ���
    {
        max=tree->node[i].weight>max?tree->node[i].weight:max;
    }
    int Bytes = ceil(ceil(log2(max))/8.0);


    ofs.put((char)Bytes);//д��洢Ƶ����Ҫ���ֽ���
    ofs.write((char*)&size,4);//д��ԭ�ļ���С

    unsigned char temp=infoSize;//��Ϣ��С���ó���255�ֽڣ�����ض�
    ofs.put(temp);//д����Ϣ�Ĵ�С
    if(extraInfo!=nullptr&&temp!=0)
    {
        ofs.write(extraInfo,temp);
    }

    //���ֽڳ���Ƶ�� ���ֽڵĶ����ƴ�С˳��д���ļ�
    for(i=0;i<256;i++)
    {
        ofs.write((char*)&tree->node[i].weight,Bytes);
    }


    //���ֽ�д��
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
    //ʣ��ı��������
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
        qDebug()<<"�ļ���ʧ�ܣ������ļ�·��";
        return -1;
    }

    int size = fs::file_size(fileAddr);//�����ļ���С
    int bufSize=size;
    unsigned char Bytes=1, tempSize=0;
    int i, j;
    int temp;
    int originSize=0;

    //������Ϣ��ȡ
    ifs.read((char*)&Bytes,1),bufSize-=1;
    ifs.read((char*)&originSize,4),bufSize-=4;
    ifs.read((char*)&tempSize,1),bufSize-=1;
    if(tempSize!=0)//�����ȡ���Ķ�����Ϣ��С��Ϊ0
    {
        if(extraInfo!=nullptr)//��������˺Ϸ��ĵ�ַ
            ifs.read(extraInfo,tempSize);
        else//���������Ϣ���ϣ������ⲿ��
            ifs.seekg(tempSize,ios::cur);
        bufSize-=tempSize;
    }

    hfmTree* tree=new hfmTree();
//    qDebug()<<"ԭ�ֽ�����"<<originSize;
    for(int i=0;i<256;i++)//�����ؽ�
    {
        ifs.read((char*)&tree->node[i].weight,Bytes);
//        qDebug()<<tree->node[i].weight;
    }
    bufSize-=256*Bytes;

    tree->build();
    unsigned char* buf = new unsigned char[bufSize+5]();//ע��Ҫ���޷���char���������ʸ����±�����
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
    //����nodeȨ�ض�index������±�����
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
        //ȡ��СԪ��
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
        //��ȡһ����СԪ��
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
        qDebug()<<"�������";
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
    //��root������;���Ľ��
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

