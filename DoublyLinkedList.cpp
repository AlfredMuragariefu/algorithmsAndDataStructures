#include <iostream>
using namespace std;
struct DoublyLinkedList
{
    int Data;
    DoublyLinkedList *next, *prior;
};
void MakeDoubleList(int n, DoublyLinkedList** Head, DoublyLinkedList* Prior){
    if(n > 0){
        (*Head) = new DoublyLinkedList();//Выделяем память под новый элемент
        cout << "Enter value: ";
        cin >> (*Head) ->Data ;//вводим значение информационного поля
        (*Head) -> prior = Prior;
        (*Head) -> next = nullptr; // Обнуление адресного поля
        MakeDoubleList(n-1,&((*Head)-> next), (*Head));
    }
    else (*Head) = nullptr;
}
void PrintDoubleList(DoublyLinkedList* Head){
    if(Head != nullptr){
        cout << Head -> Data << "\t";
        PrintDoubleList(Head->next);
    } else cout << "\n";
}
DoublyLinkedList* InsertItemDoubleList(DoublyLinkedList* Head, int number, int DataItem){
    number--;
    DoublyLinkedList *NewItem = new(DoublyLinkedList);
    NewItem->Data = DataItem;
    NewItem->prior = nullptr;
    NewItem->next = nullptr;
    if(Head == nullptr){//Если список пуст
        Head = NewItem;
    }
    else{
        DoublyLinkedList *Current = Head;
        for (int i = 1; i < number && Current->next != nullptr ; i++) {
            Current = Current->next;
            if(number == 0){
                NewItem->next = Head;
                Head->prior = NewItem;
                Head = NewItem;
            } else {
               if(Current->next != nullptr){
                   Current -> next -> prior = NewItem;
               }
               NewItem -> next = Current -> next;
               Current -> next = NewItem;
               NewItem -> prior = Current;
               Current = NewItem;
            }
        }
        return Head;
    }
}
DoublyLinkedList* DeleteItemDoubleList(DoublyLinkedList* Head, int Number){
    DoublyLinkedList *ptr;//вспомогательный указатель
    DoublyLinkedList *Current = Head;
    for (int i = 1; i < Number && Current != nullptr; i++)
        Current = Current->next;
    if (Current != nullptr){//проверка на корректность
        if (Current->prior == nullptr){//удаляем первый элемент
            Head = Head->next;
            delete(Current);
            Head->prior = nullptr;
            Current = Head;
        }
        else {//удаляем непервый элемент
            if (Current->next == nullptr) {
                //удаляем последний элемент
                Current->prior->next = nullptr;
                delete(Current);
                Current = Head;
            }
            else {//удаляем непервый и непоследний элемент
                ptr = Current->next;
                Current->prior->next =Current->next;
                Current->next->prior =Current->prior;
                delete(Current);
                Current = ptr;
            }
        }
    }
    return Head;
}
bool FindItemDoubleList(DoublyLinkedList* Head, int DataItem){
    DoublyLinkedList *ptr; //вспомогательный указатель
    ptr = Head;
    while (ptr != nullptr){//пока не конец списка
        if (DataItem == ptr->Data) return true;
        else ptr = ptr->next;
    }
    return false;
}
bool EmptyDoubleList(DoublyLinkedList* Head){
    if (Head!= nullptr)  return false;
    else  return true;
}
//освобождение памяти, выделенной под двунаправленный список
void DeleteDoubleList(DoublyLinkedList* Head){
    if (Head != nullptr){
        DeleteDoubleList(Head->next);
        Head -> Data = NULL;
    }
}
int main(){
    DoublyLinkedList* Head = nullptr;
    MakeDoubleList(5, &Head, Head);
    PrintDoubleList(Head);
    InsertItemDoubleList(Head,3, 51);
    PrintDoubleList(Head);
    DeleteItemDoubleList(Head,3);
    PrintDoubleList(Head);
    cout << FindItemDoubleList(Head, 3) << "\n";
    DeleteDoubleList(Head);
    cout << FindItemDoubleList(Head,3) << "\n";
    system("pause");
    return 0;
}