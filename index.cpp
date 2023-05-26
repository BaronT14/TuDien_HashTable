#include <iostream>
#include <conio.h>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;
// hash table
#define Hash_Size 100

struct Word
{
    string word;
    string type;
    string mean;
};

struct node
{
    Word data;
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

int hashstr(string data)
{
    int h = 0;
    for (int i = 0; i < data.length(); i++)
    {
        h += (int)tolower(data[i]) * (i + 1); // tolower chuyển thành chữ thường
    }
    return h % Hash_Size;
}

int hash_func(Word data)
{
    return hashstr(data.word);
}

void InputWord(Word &data)
{
    cout << "Nhap tu: ";
    getline(cin, data.word);
    cout << "Nhap loai tu: ";
    getline(cin, data.type);
    cout << "Nhap nghia cua tu: ";
    getline(cin, data.mean);
}

node *createNode(Word data)
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

void insert(node *hashTable[], Word data)
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

void deleteWord(node *hashTable[], string data)
{
    int h = hashstr(data);
    node *r = hashTable[h];
    node *prev = NULL;
    while (r->next != NULL)
    {
        if (r->data.word.compare(data) == 0)
        {
            if (prev != NULL)
            {
                prev->next = r->next;
            }
            else
            {
                hashTable[h] = r->next;
            }
            r->next = NULL;
            delete r;
            break;
        }
        prev = r;
        r = r->next;
    }
}
// doc tap tin
void readFile(node *hashTable[])
{
    ifstream f;
    f.open("INPUT.txt", ios::in);
    if (!f.eof())
    {
        Word data;
        getline(f, data.word);
        getline(f, data.type);
        getline(f, data.mean);
        insert(hashTable, data);
    }
    f.close();
}

// begin duyet
void khung()
{
    cout << left << setw(30) << "Word" << setw(10) << "Type" << setw(30) << "Mean" << endl;
}

void duyetNode(node *p)
{
    cout << p->data.word << " (" << p->data.type << ") :" << p->data.mean << endl;
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
void updateWord(node *hashTable[], Word data)
{
    int h = hash_func(data);
    node *r = hashTable[h];
    if (r != NULL)
    {
        int t = hash_func(r->data);
        do
        {
            t = hash_func(r->data);
            if (t == h)
            {
                r->data = data;
                break;
            }
            r = r->next;
        } while (r->next != NULL);
    }
}
node *findWord(string word)
{
    int index = hashstr(word);
    node *curr = hashTable[index];
    while (curr != NULL)
    {
        if (curr->data.word.compare(word) == 0)
        {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}
node *findMean(string mean)
{
    int index = hashstr(mean);
    node *curr = hashTable[index];
    while (curr != NULL)
    {
        if (curr->data.mean.compare(mean) == 0)
        {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

int main()
{
    init(hashTable);
    readFile(hashTable);
    duyetHT(hashTable);
    _getch();
    return 1;
}