#include <iostream>
using namespace std;
const int EN = 26;

void instruction() {
    cout << "   Элементы должны содержать только символы латинского языка!\n";
    cout << "1 - Добавление элемента в хеш-множество\n";
    cout << "2 - Удаление элемента из хеш-множества\n";
    cout << "3 - Удаление всех элементов хеш-множества\n";
    cout << "4 - Поиск заданного элемента в хеш-множестве\n";
    cout << "5 - Количество элементов хеш-множества\n";
    cout << "6 - Вывод хеш-множества одним массивом\n";
    cout << "0 - завершение работы программы\n\n";
}

template <typename T>
struct Node {
    T info;
    Node* next = nullptr;
    Node* prev = nullptr;
};
template <typename T>
struct List {
    int counting = 0;
    int position = 0;
    Node<T>* now = nullptr;
    Node<T>* first = nullptr;
    Node<T>* last = nullptr;

    void toIndex(int index) {
        if (abs(index - position) > (counting - 1 - index)) {
            now = last;
            position = counting - 1;
        }
        if (abs(index - position) > index) {
            now = first;
            position = 0;
        }
        if (index > position) { for (int i = 0; i < index - position; i++) { now = now->next; } }
        else { for (int i = 0; i < position - index; i++) { now = now->prev; } }
        position = index;
    }

    void add(T info) {
        Node<T>* node = new Node<T>();
        node->info = info;
        if (counting == 0) {
            first = node;
            last = node;
            now = node;
        }
        else {
            node->prev = last;
            last->next = node;
            last = node;
        }
        counting++;
    }

    void insert(int index, T info) {
        if (index < 0 || index > counting) { throw 0; }
        if (index == counting) {
            add(info);
            return;
        }
        toIndex(index);
        Node<T>* node = new Node<T>();
        node->info = info;
        node->prev = now->prev;
        now->prev = node;
        node->next = now;
        if (node->prev != nullptr) { node->prev->next = node; }
        else { first = node; }
        counting++;
        position++;
    }

    void removeAt(int index) {
        if (index < 0 || index >= counting) { throw 0; }
        toIndex(index);
        Node<T>* del = now;
        if (last == first) {
            clear();
            return;
        }
        if (del == last) {
            last = last->prev;
            last->next = nullptr;
            now = last;
            position--;
        }
        else if (del == first) {
            first = first->next;
            first->prev = nullptr;
            now = first;
        }
        else {
            now = now->next;
            del->next->prev = del->prev;
            del->prev->next = del->next;
        }
        delete del;
        counting--;
    }

    T elementAt(int index) {
        if (index < 0 || index >= counting) { throw 0; }
        toIndex(index);
        return now->info;
    }

    int count() { return counting; }

    void clear() {
        int kol = counting;
        for (int i = 0; i < kol; i++) {
            Node<T>* del = first;
            first = first->next;
            delete del;
        }
        last = nullptr;
        now = nullptr;
        position = 0;
        counting = 0;
    }
};

struct HashSet {
    int counting = 0;
    List<string> hash[EN] = {};

    int count() { return counting; }

    int hashfoo(string str) {
        if (str[0] - 65 < EN) { return str[0] - 65; }
        else { return str[0] - 97; }
    }

    void add(string str) {
        if (contains(str)) { return; }
        hash[hashfoo(str)].add(str);
        counting++;
    }

    bool contains(string str) {
        for (int i = 0; i < hash[hashfoo(str)].count(); i++) {
            if (hash[hashfoo(str)].elementAt(i) == str) { return true; }
        }
        return false;
    }

    void remove(string str) {
        if (!contains(str)) { return; }
        else {
            for (int i = 0; i < hash[hashfoo(str)].count(); i++) {
                if (hash[hashfoo(str)].elementAt(i) == str) {
                    hash[hashfoo(str)].removeAt(i);
                    counting--;
                    return;
                }
            }
        }
    }

    void clear() {
        for (int i = 0; i < EN; i++) { hash[i].clear(); }
        counting = 0;
    }

    string* ToArray() {
        string* str = new string[counting];
        int k = 0;
        for (int i = 0; i < EN; i++) {
            for (int j = 0; j < hash[i].count(); j++, k++) {
                str[k] = hash[i].elementAt(j);
            }
        }
        return str;
    }
};

int main() {
    system("chcp 1251>NULL");
    instruction();
    HashSet hash;
    while (true) {
        int parameter;
        string str;
        string* str1;
        cout << "\nВведите команду: ";
        cin >> parameter;
        switch (parameter) {
        case 1:
            cout << "Введите слово: ";
            cin >> str;
            hash.add(str);
            break;
        case 2:
            cout << "Введите слово: ";
            cin >> str;
            hash.remove(str);
            break;
        case 3:
            hash.clear();
            break;
        case 4:
            cout << "Введите слово: ";
            cin >> str;
            if (hash.contains(str)) { cout << "Слово содержится в хеш-множестве\n"; }
            else { cout << "Слово не содержится в хеш-множестве\n"; }
            break;
        case 5:
            cout << "Количество слов: " << hash.count() << endl;
            break;
        case 6:
            str1 = hash.ToArray(); 
            for (int i = 0; i < hash.count(); i++) { cout << str1[i] << " "; }
            cout << endl;
            break;
        case 0:
            return 0;
        default:
            cout << "Некорректная команда!";
        }
    }
}
