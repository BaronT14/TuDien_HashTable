#include <iostream>
#include <conio.h>
#include <iomanip>
#include <string>
using namespace std;
// hash table
#define Hash_Size 100

struct Word
{
    string word;
    string type;
    string mean;
};

typedef Word itemtype;

struct node
{
    itemtype data;
    node *next;
};

node *hashTable[Hash_Size];

void init(node *hashTable[])
{
    for (int i = 0; i < Hash_Size; i++)
    {
        hashTable[i] = NULL;
    }
}

int hash_func(itemtype data)
{
    int h = 0;
    for (int i = 0; i < data.word.length(); i++)
    {
        h += (int)tolower(data.word[i]) * (i + 1); // tolower chuyển thành chữ thường
    }
    return h;
}

void InputWord(itemtype &data)
{
    cout << "Nhap tu: ";
    getline(cin, data.word);
    cout << "Nhap loai tu: ";
    getline(cin, data.type);
    cout << "Nhap nghia cua tu: ";
    getline(cin, data.mean);
}

node *createNode(itemtype data)
{
    node *p = new node;
    if (p == NULL)
    {
        cout << "Khong du bo nho cap phat!!!";
        _getch();
        return NULL;
    }
    p->data = data;
    p->next = NULL;
    return p;
}

void insert(node *hashTable[], itemtype data)
{
    int index = hash_func(data);
    node *r = hashTable[index];
    node *tmp = createNode(data);
    if (hashTable[index] == NULL)
    {
        hashTable[index] = tmp;
        return;
    }
    else
    {
        while (r->next != NULL)
        {
            r = r->next;
        }
        hashTable[index]->next = tmp; // add node tail list
    }
}
// begin duyet
void khung()
{
    cout << left << setw(30) << "Word" << setw(10) << "Type" << setw(30) << "Mean" << endl;
}

void duyetNode(node *p)
{
    cout << left << setw(30) << p->data.word << setw(10) << p->data.type << setw(30) << p->data.mean << endl;
}

void duyetHT(node *hashTable[])
{
    for (int i = 0; i < Hash_Size; i++)
    {
        if (hashTable[i] != NULL)
        {
            node *p = hashTable[i];
            while (p != NULL)
            {
                duyetNode(hashTable[i]);
                p = p->next;
            }
        }
    }
}
// end duyet
void updateWord(node *hashTable[], itemtype data)
{
    int h = hash_func(data);
    node *r = hashTable[h];
    if (r != NULL)
    {
        while (r != NULL)
        {
            int t = hash_func(r->data);
            if (t == h)
            {
                r->data = data;
                break;
            }
            r = r->next;
        }
    }
}
node *find(itemtype data)
{
    int index = hash_func(data);
    node *curr = hashTable[index];
    while (curr)
    {
        if (curr->data.word.compare(data.word) == 0 || curr->data.mean.compare(data.mean) == 0)
        {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

int main()
{

    _getch();
    return 21;
}