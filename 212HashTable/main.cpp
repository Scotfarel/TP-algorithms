//
//  Created by izakharov on 10/05/20
//
//  Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
//  Хранимые строки непустые и состоят из строчных латинских букв.
//  Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
//  Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае,
//  когда коэффициент заполнения таблицы достигает 3/4.
//  Структура данных должна поддерживать операции добавления строки в множество, удаления строки из
//  множества и проверки принадлежности данной строки множеству.
//
//  1_2. Для разрешения коллизий используйте двойное хеширование.
//  Требования: В таблице запрещено хранение указателей на описатель элемента.
//  Формат входных данных:
//  Каждая строка входных данных задает одну операцию над множеством. Запись операции состоит из типа операции и
//  следующей за ним через пробел строки, над которой проводится операция.
//  Тип операции  – один из трех символов:
//    +  означает добавление данной строки в множество;
//    -  означает удаление  строки из множества;
//    ?  означает проверку принадлежности данной строки множеству.
//  При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом множестве.
//  При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.
//  Формат выходных данных:
//  Программа должна вывести для каждой операции одну из двух строк OK или FAIL, в зависимости от того,
//  встречается ли данное слово в нашем множестве.
//


#include <iostream>
#include <vector>
#include <string>

template<class T> struct HashFunc;

size_t getHash(const std::string& key, size_t m) {
    size_t hash = 0;
    for (char i: key) {
        hash = hash * m + i;
    }
    return hash;
}

size_t getDoubleHash(const std::string& key, size_t i, size_t tableSize) {
    size_t h1 = getHash(key, 7);
    size_t h2 = getHash(key, 13);
    h2 = h2 * 2 + 1;
    return (h1 + i * h2) % tableSize;
}

template<> struct HashFunc<std::string> {
    size_t operator()(const std::string& key, int i, int m) {
        return getDoubleHash(key, i, m);
    }
};

template <class Hash = HashFunc<std::string>>
class HashTable {
    struct Item {
    private:
        const std::string del = "Jonathan Joestar";
        const std::string nil = "Robert .E.O. Speedwagon";

    public:
        Item(std::string item_key, std::string item_value) : key(std::move(item_key)), value(std::move(item_value)) {};
        Item() : key(nil), value(nil) {};

        std::string key;
        std::string value;

        Item &operator=(const Item& other) {
            key = other.key;
            value = other.value;
            return *this;
        }

        bool isNil() const { return key == nil; }
        bool isDel() const { return key == del; }
        void setNil() { key = nil; }
        void setDel() { key = del; }
    };

public:
    explicit HashTable(Hash hash = Hash()) : elemAmount(0), table(8), hash(std::move(hash)) {};
    HashTable &operator=(const HashTable &) = delete;
    bool add(const std::string& key, const std::string& value);
    bool has(const std::string& key);
    bool del(const std::string& key);
    void growTable();

private:
    int elemAmount;
    std::vector<Item> table;
    Hash hash;
};


template<class Hash>
bool HashTable<Hash>::add(const std::string& key, const std::string& value) {
    if ((elemAmount * 4 + 1) >= table.size() * 3) {
        growTable();
    }

    int deleted_index = 0;
    bool found = false;

    for (int step = 0; step < table.size(); step++) {
        size_t hash_index = hash(key, step, table.size());

        if (table[hash_index].isNil()) {
            table[hash_index] = Item(key, value);
            elemAmount++;
            return true;
        }

        if (table[hash_index].key == key) {
            return false;
        }

        if (table[hash_index].isDel() and not found) {
            found = true;
            deleted_index = hash_index;
        }
    }

    if (found) {
        table[deleted_index] = Item(key, value);
        elemAmount++;
        return true;
    }

    return false;
}

template<class Hash>
bool HashTable<Hash>::has(const std::string& key) {
    int step = 0;
    size_t index = hash(key, step, table.size());
    for (; step < table.size() and not table[index].isNil(); step++) {
        if (table[index].key == key) {
            return true;
        }
        index = hash(key, step, table.size());
    }
    return false;
}

template<class Hash>
bool HashTable<Hash>::del(const std::string& key) {
    if (!(has(key)))
        return false;

    int step = 0;
    size_t index = hash(key, step, table.size());
    for (; step < table.size() and not table[index].isNil(); step++) {
        if (table[index].key == key) {
            table[index].setDel();
            elemAmount--;
            return true;
        }
        index = hash(key, step, table.size());
    }
    return false;
}

template<class Hash>
void HashTable<Hash>::growTable() {
    std::vector<Item> newTable(table.size() * 2);
    for (auto &i : newTable) {
        i.setNil();
    }

    std::vector<Item> oldTable(table);
    table = newTable;
    for (const auto& elem : oldTable) {
        if (not elem.isNil() and not elem.isDel()) {
            add(elem.key, elem.value);
            elemAmount--;
        }
    }
}


int main() {
    auto* table = new HashTable<>();
    char operation = '\0';
    std::string key;
    bool flag = false;
    while (std::cin >> operation >> key) {
        switch (operation) {
            case '+':
                flag = table->add(key, key);
                break;
            case '-':
                flag = table->del(key);
                break;
            case '?':
                flag = table->has(key);
                break;
            default:
                break;
        }
        if (flag) {
            std::cout << "OK" << std::endl;
        } else {
            std::cout << "FAIL" << std::endl;
        }
    }

    delete table;
    return 0;
}
