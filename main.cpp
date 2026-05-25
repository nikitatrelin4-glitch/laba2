#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <sstream>

struct Node {
    std::string url;
    std::time_t visit_time;
    bool is_bookmarked;
    Node* prev;
    Node* next;

    Node(std::string u, bool b = false, std::time_t t = std::time(nullptr)) {
        url = u;
        is_bookmarked = b;
        visit_time = t;
        prev = next = nullptr;
    }
};

class BrowserHistory {
private:
    Node* head = nullptr;
    Node* tail = nullptr;
    Node* current = nullptr;

    std::string format_time(std::time_t t) {
        char buf[20];
        std::strftime(buf, sizeof(buf), "%H:%M:%S", std::localtime(&t));
        return std::string(buf);
    }

    void clear_forward(Node* start) {
        while (start) {
            Node* temp = start;
            start = start->next;
            delete temp;
        }
    }

public:
    ~BrowserHistory() { clear(); }

    void visit(std::string url, bool bookmark = false, std::time_t t = std::time(nullptr)) {
        Node* newNode = new Node(url, bookmark, t);

        if (!head) {
            head = tail = current = newNode;
        }
        else {
            if (current->next) {
                clear_forward(current->next);
                tail = current;
            }
            newNode->prev = current;
            current->next = newNode;
            tail = newNode;
            current = newNode;
        }
    }

    void back() {
        if (current && current->prev) current = current->prev;
        else std::cout << "Это начало истории!\n";
    }

    void forward() {
        if (current && current->next) current = current->next;
        else std::cout << "Это конец истории!\n";
    }

    void toggle_bookmark() {
        if (current) {
            current->is_bookmarked = !current->is_bookmarked;
            std::cout << "Статус закладки изменен.\n";
        }
    }

    void search(std::string query) {
        Node* temp = head;
        int idx = 1;
        bool found = false;
        while (temp) {
            if (temp->url.find(query) != std::string::npos) {
                std::cout << "\n[Найдено] Позиция: " << idx << "\n"
                    << "URL: " << temp->url << "\n"
                    << "Время посещения: " << format_time(temp->visit_time) << "\n"
                    << "В закладках: " <<(temp->is_bookmarked ? "Да" : "Нет") << "\n";
                found = true;
            }
            temp = temp->next;
            idx++;
        }
        if (!found) std::cout << "Ничего не найдено.\n";
    }

    void clear() {
        Node* temp = head;
        while (temp) {
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
        head = tail = current = nullptr;
    }

    void save() {
        std::string filename;
        std::cout << "Имя файла для сохранения: ";
        std::cin >> filename;

        std::ofstream file(filename);
        if (!file) { std::cout << "Ошибка записи!\n"; return; }

        Node* temp = head;
        while (temp) {
            file << temp->url << "|" << temp->visit_time << "|" << temp->is_bookmarked << "\n";
            temp = temp->next;
        }
        std::cout << "История сохранена в " << filename << "\n";
    }

    void load() {
        std::string filename;
        std::cout << "Имя файла для загрузки: ";
        std::cin >> filename;

        std::ifstream file(filename);
        if (!file) { std::cout << "Файл не найден!\n"; return; }

        clear();
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string url, t_str, b_str;

            if (std::getline(ss, url, '|') && std::getline(ss, t_str, '|') && std::getline(ss, b_str, '|')) {
                visit(url, b_str == "1", std::stoll(t_str));
            }
        }
        std::cout << "История загружена.\n";
    }

    void print_history() {
        if (!head) {
            std::cout << "\n--- История пуста ---\n";
            return;
        }

        std::cout << "\n------------------------------------------------------------\n";
        std::cout << "    | " << std::left << std::setw(12) << "Время"
            << " | " << std::setw(25) << "URL"
            << " | " << "Закладка\n";
        std::cout << "------------------------------------------------------------\n";

        Node* temp = head;
        while (temp) {
            std::string mark = (temp == current) ? "-->" : "   ";
            std::cout << mark << " | "
                << std::left << std::setw(12) << format_time(temp->visit_time) << " | "
                << std::setw(25) << temp->url << " | "
                <<(temp->is_bookmarked ? "[X]" : "[ ]") << "\n";
            temp = temp->next;
        }
        std::cout << "------------------------------------------------------------\n";

        if (current) {
            std::cout << "Текущая страница: " << current->url << "\n";
            std::cout << "Время перехода на неё: " << format_time(current->visit_time) << "\n";
        }
    }
};

int main() {
    std::setlocale(LC_ALL, "Russian");
    BrowserHistory bh;
    int choice;
    std::string input;

    while (true) {
        bh.print_history();
        std::cout << "\n1. Перейти | 2. Назад | 3. Вперед | 4. Закладка\n"
            << "5. Поиск   | 6. Сброс | 7. Сохранить | 8. Загрузить | 0. Выход\n"
            << "Выбор: ";

        if (!(std::cin >> choice)) break;
        if (choice == 0) break;

        switch (choice) {
        case 1: std::cout << "Введи URL: "; std::cin >> input; bh.visit(input); break;
        case 2: bh.back(); break;
        case 3: bh.forward(); break;
        case 4: bh.toggle_bookmark(); break;
        case 5: std::cout << "Что искать: "; std::cin >> input; bh.search(input); break;
        case 6: bh.clear(); std::cout << "История очищена.\n"; break;
        case 7: bh.save(); break;
        case 8: bh.load(); break;
        default: std::cout << "Неверный пункт меню.\n";
        }
    }
    return 0;
}
