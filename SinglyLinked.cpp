#include <iostream>
#include <cstdio>
using namespace std;
struct List{
    int Data;
    List *Next;
};
void MakeList(int n, List** Head){
    if(n > 0){
        // Выделяем память под новый элемент
        (*Head) = new List;
        cout << "Enter value: ";
        // Вводим значение информационного поля
        cin >> (*Head) ->Data;
        // Обнуление адресного поля
        (*Head)-> Next = nullptr;
        MakeList(n-1,&((*Head)->Next));
    }
}
void PrintList(List* Head){
    if(Head != nullptr){
        cout << Head -> Data << "\t";
        // Переход к следующему элементу
        PrintList(Head->Next);
    } else cout << "\n";
}
List* InsertItemList(List* Head, int num, int DataItem){
    num--;
    List *NewItem = new List;
    NewItem -> Data = DataItem;
    NewItem -> Next = nullptr;
    if(Head == nullptr){//Список пуст
        Head = NewItem;
    }
    else{// Список не пуст
        List *Current = Head;
        for (int i = 1; i < num && Current->Next != nullptr ; i++) {
            Current = Current -> Next;
        }
        if(num == 0){
            // вставляем элемент на первое место
            NewItem -> Next = Head;
            Head = NewItem;
        }
        else{// Вставляем новый элемент на непервое место
            if(Current->Next != nullptr){
                NewItem->Next = Current->Next;
            }
            Current->Next = NewItem;
        }
    }
    return Head;
}
List* DeleteItemList(List* Head, int num){
    List *ptr;// Вспопомогательный указатель
    List *Current = Head;
    for (int i = 1; i < num && Current != nullptr; ++i) {
        Current = Current->Next;
    }
    if(Current != nullptr){// проверка на корректность
        if(Current == Head){//Удаляем 1 элемент
            Head = Head -> Next;
            delete(Current);
            Current = Head;
        }
        else{// Удаляем не первый элемент
            ptr = Head;
            while (ptr->Next != Current){
                ptr = ptr->Next;
            }
            ptr->Next = Current->Next;
            delete(Current);
            Current = ptr;
        }
    }
    return Head;
}
bool FindItemList(List *Head, int DataItem){
    List *ptr; // вспомогательный указатель
    ptr = Head;
    while (ptr != nullptr){
        if(DataItem == ptr->Data){
            return true;
        }
        else ptr = ptr->Next;
    }
    return false;
}
void DeleteList(List* Head){
    if(Head != nullptr){
        DeleteList(Head->Next);
        Head ->Data = NULL;
    }
}
int main() {
    List* Head = nullptr;
    MakeList(5, &Head);
    PrintList(Head);
    InsertItemList(Head,3, 51);
    PrintList(Head);
    DeleteItemList(Head,3);
    PrintList(Head);
    cout << FindItemList(Head, 3) << "\n";
    DeleteList(Head);
    cout << FindItemList(Head,3) << "\n";
    system("pause");
    return 0;
}
    