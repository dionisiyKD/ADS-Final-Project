#include "list.h"

namespace MyList{

list::list() {
    head = NULL;
    tail = NULL;
    count = 0;
}
list::~list() {
    while (count) {
        node* tmp = head;
        head = head->next;
        delete tmp;
        count--;
    }
}

int list::get_data(int index) {
    node* tmp = head;
    for (int i = 0; i < index - 1; i++)
        tmp = tmp->next;
    return tmp->data;
}
int list::get_count() {
    return count;
}
node* list::get_item(int index){
    node* tmp = head;
    for (int i = 0; i < index - 1; i++)
        tmp = tmp->next;
    return tmp;
}

void list::add_head(node* tmp) {
    tmp->next = head;
    tmp->prev = NULL;

    if (count == 0) {
        head = tmp;
        tail = tmp;
    }
    else {
        head->prev = tmp;
        head = tmp;
    }
    count++;
}
void list::add_tail(node* tmp) {
    tmp->next = NULL;
    tmp->prev = tail;

    if (count == 0)
    {
        head = tmp;
        tail = tmp;
    }
    else
    {
        tail->next = tmp;
        tail = tmp;
    }
    count++;
}
void list::insert_after(int index, node* new_node) {
    while (index < 1 || index > count) {
        std::cout << "Неправильный индекс\nВведите пожалуйста правильный: ";
        std::cin >> index;
    }
    if (index == count) {
        add_tail(new_node);
        return;
    }

    node* before = head;
    for (int i = 0; i < index - 1; i++) {
        before = before->next;
    }
    node* after = before->next;

    before->next = new_node;
    after->prev = new_node;

    new_node->next = after;
    new_node->prev = before;

    count++;
}

void list::remove(int index) {
    while (index < 0 || index > count) {
        std::cout << "Incorrect index: ";
        return;
    }


    if (index == 1) {
        node* tmp = head;
        node* after = head->next;
        after->prev = NULL;
        head = after;
        delete tmp;
        count--;
        return;
    }
    if (index == count) {
        node* tmp = tail;
        node* before = tail->prev;
        before->next = NULL;
        tail = before;
        delete tmp;
        count--;
        return;
    }

    node* del = head;
    for (int i = 0; i < index - 1; i++)
        del = del->next;

    node* before = del->prev;
    node* after = del->next;

    before->next = after;
    after->prev = before;

    delete del;
    count--;
}
void list::clear(){
    node* tmp = new node();
    while(head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
    head = NULL;
    tail = NULL;
    count = 0;
}

void list::swap(int index_first, int index_second) {
    node* first = head;
    node* second = head;
    for (int i = 0; i < index_first; i++)
        first = first->next;
    for (int i = 0; i < index_second; i++)
        second = second->next;


    node* first_next = first->next;
    node* second_next = second->next;
    node* first_prev = first->prev;
    node* second_prev = second->prev;

    node tmp = *first;
    *first = *second;
    *second = tmp;

    first->next = first_next;
    second->next = second_next;
    first->prev = first_prev;
    second->prev = second_prev;
}
int list::search(int A) {
    node* tmp = head;
    for (int i = 0; i < count; i++) {
        if (tmp->data == A)
            return ++i;
        tmp = tmp->next;
    }
    return 0;
}

void list::print_from_head() {
    node* tmp = head;
    for (int i = 0; i < count; i++) {
        std::cout << tmp;
        tmp = tmp->next;
    }
    std::cout << std::endl << std::endl;
}
void list::print_from_tail() {
    node* tmp = tail;
    for (int i = 0; i < count; i++) {
        std::cout << tmp;
        tmp = tmp->prev;
    }
    std::cout << std::endl << std::endl;
}
void heapify(list& arr, int n, int i)
{
    int largest = i;

    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr.get_data(l+1) > arr.get_data(largest + 1))
        largest = l;

    if (r < n && arr.get_data(r + 1) > arr.get_data(largest + 1))
        largest = r;

    if (largest != i)
    {
        arr.swap(i, largest);
        heapify(arr, n, largest);
    }
}
void heapSort(list& arr) {
    int n = arr.get_count();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--)
    {
        arr.swap(0, i);
        heapify(arr, i, 0);
    }
}

}
