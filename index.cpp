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
    cin.ignore();
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

void inputHT(node *hashTable[])
{
    int n;
    cout << "Nhap so luong tu muon them: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        Word data;
        InputWord(data);
        insert(hashTable, data);
    }
}

void deleteWord(node *hashTable[], string data)
{
    int h = hashstr(data);
    node *r = hashTable[h];
    node *prev = NULL;
    if (r == NULL)
    {
        cout << "Khong co tu trong tu dien";
        _getch();
    }
    while (r != NULL)
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
            cout << "Da xoa!!!";
            _getch();
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
    while (!f.eof())
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
    cout << left << setw(25) << "Word" << setw(10) << "Type" << setw(30) << "Mean" << endl;
    cout << "-----------------------------------------------------------" << endl;
}

void duyetNode(node *p)
{
    cout << left << setw(25) << p->data.word << setw(10) << p->data.type << setw(30) << p->data.mean << endl;
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
                cout << "Da cap nhat thanh cong";
                _getch();
                return;
            }
            r = r->next;
        } while (r->next != NULL);
    }
    cout << "Cap nhat khong thanh cong";
    _getch();
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
    for (int i = 0; i < Hash_Size; i++)
    {
        node *curr = hashTable[i];
        while (curr != NULL)
        {
            if (curr->data.mean.compare(mean) == 0)
                return curr;
            curr = curr->next;
        }
    }
    return NULL;
}

void menu(int &luachon)
{
    cout << "\n+---------------MENU---------------+" << endl;
    cout << "| 1   .Tra cuu tu Tieng Anh        |" << endl;
    cout << "| 2   .Tra cuu tu Tieng Viet       |" << endl;
    cout << "| 3   .Hien thi toan bo Tu Dien    |" << endl;
    cout << "| 4   .Them tu vao Tu Dien         |" << endl;
    cout << "| 5   .Xoa tu khoi Tu Dien         |" << endl;
    cout << "| 6   .Cap nhat 1 tu trong Tu Dien |" << endl;
    cout << "| 0   .Thoat                       |" << endl;
    cout << "+----------------------------------+" << endl;
    cout << "Nhap lua chon: ";
    cin >> luachon;
}

void thucHienMenu(int luachon)
{
    switch (luachon)
    {
    case 1:
    {
        string data;
        cin.ignore();
        cout << "Nhap tu Tieng Anh muon tra cuu: ";
        getline(cin, data);
        node *p = findWord(data);
        if (p != NULL)
        {
            khung();
            duyetNode(p);
            _getch();
        }
        else
        {
            cout << "Khong co trong tu dien";
            _getch();
        }
    }
    break;
    case 2:
    {
        string data;
        cin.ignore();
        cout << "Nhap tu Tieng Viet muon tra cuu: ";
        getline(cin, data);
        node *p = findMean(data);
        if (p != NULL)
        {
            khung();
            duyetNode(p);
            _getch();
        }
        else
        {
            cout << "Khong co trong tu dien";
            _getch();
        }
    }
    break;
    case 3:
    {
        khung();
        duyetHT(hashTable);
        _getch();
    }
    break;
    case 4:
    {
        inputHT(hashTable);
    }
    break;
    case 5:
    {
        string data;
        cin.ignore();
        cout << "Nhap tu Tieng Anh muon xoa: ";
        getline(cin, data);
        deleteWord(hashTable, data);
    }
    break;
    case 6:
    {
        Word data;
        InputWord(data);
        updateWord(hashTable, data);
    }
    break;
    default:
        break;
    }
}

int main()
{
    init(hashTable);
    int c, luachon;
    cout << "1   . Nhap du lieu tu file" << endl;
    cout << "2   . Nhap du lieu tu ban phim" << endl;
    cout << "-----------------------------------" << endl;
    cout << "Nhap lua chon: ";
    cin >> c;
    switch (c)
    {
    case 1:
    {
        readFile(hashTable);
    }
    break;
    case 2:
    {
        inputHT(hashTable);
    }
    break;
    default:
        break;
    }
    do
    {
        menu(luachon);
        thucHienMenu(luachon);
    } while (luachon != 0);
    _getch();
    return 1;
}