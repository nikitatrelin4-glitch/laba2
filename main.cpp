#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <sstream>


static const std::string B64_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


std::string base64_encode(const std::string& in) {
    std::string out;
    int val = 0, valb = -6;
    for (unsigned char c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back(B64_CHARS[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) out.push_back(B64_CHARS[((val >> 8) >>(valb + 8)) & 0x3F]);
    while (out.size() % 4) out.push_back('=');
    return out;
}

std::string base64_decode(const std::string& in) {
    int T[256];
    for (int i = 0; i < 256; i++) T[i] = -1;
    for (int i = 0; i < 64; i++) T[B64_CHARS[i]] = i;

    std::string out;
    int val = 0, valb = -8;
    for (unsigned char c : in) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return out;
}

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
        prev = nullptr;
        next = nullptr;
    }
};

class BrowserHistory {
private:
    Node* head;       
    Node* tail;     
    Node* current;    

    std::string format_time(std::time_t t) {
        char buf[20];
        std::strftime(buf, sizeof(buf), "%H:%M:%S", std::localtime(&t));
        return std::string(buf);
    }

    void clear_forward(Node* start_node) {
        while (start_node) {
            Node* to_delete = start_node;
            start_node = start_node->next;
            delete to_delete;
        }
    }

public:
    BrowserHistory() {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }

    ~BrowserHistory() {
        clear();
    }

    void visit(std::string url, bool bookmark = false, std::time_t t = std::time(nullptr)) {
        Node* new_node = new Node(url, bookmark, t);

        if (!head) {
            head = tail = current = new_node;
        }
        else {
            if (current->next) {
                clear_forward(current->next);
                current->next = nullptr;
                tail = current;
            }

            new_node->prev = current;
            current->next = new_node;
            tail = new_node;
            current = new_node;
        }
    }

    void back() {
        if (current && current->prev) {
            current = current->prev;
        }
        else {
            std::cout << "Это начало истории (некуда возвращаться)\n";
        }
    }

    void forward() {
        if (current && current->next) {
            current = current->next;
        }
        else {
            std::cout << "Это конец истории (вы на самой актуальной странице)\n";
        }
    }

    void toggle_bookmark() {
        if (current) {
            current->is_bookmarked = !current->is_bookmarked;
            std::cout << "Статус закладки изменен для: " << current->url << "\n";
        }
        else {
            std::cout << "История пуста, невозможно поставить закладку.\n";
        }
    }

    void search(std::string query) {
        if (!head) {
            std::cout << "История пуста.\n";
            return;
        }

        Node* temp = head;
        int position = 1;
        bool found = false;

        while (temp) {
            if (temp->url.find(query) != std::string::npos) {
                if (!found) std::cout << "\nРезультаты поиска:\n";
                std::cout << "Позиция: " << position << " | "
                    << "Время: " << format_time(temp->visit_time) << " | "
                    << "URL: " << temp->url << " | "
                    << "Закладка: " <<(temp->is_bookmarked ? "Да" : "Нет") << "\n";
                found = true;
            }
            temp = temp->next;
            position++;
        }

        if (!found) {
            std::cout << "Ничего не найдено по запросу: " << query << "\n";
        }
    }

    void clear() {
        Node* temp = head;
        while (temp) {
            Node* next_node = temp->next;
            delete temp;
            temp = next_node;
        }
        head = tail = current = nullptr;
    }

    void print_history() {
        if (!head) {
            std::cout << "\n=== История пуста ===\n";
            return;
        }

        std::cout << "\n------------------------------------------------------\n";
        std::cout << std::left << std::setw(3) << "   "
            << std::setw(10) << "Время" << " | "
            << std::setw(30) << "URL" << " | " << "Закладка\n";
        std::cout << "------------------------------------------------------\n";

        Node* temp = head;
        while (temp) {
            std::string marker = (temp == current) ? " > " : "   ";

            std::cout << marker
                << format_time(temp->visit_time) << " | "
                << std::left << std::setw(30) << temp->url << " | "
                <<(temp->is_bookmarked ? "[X]" : "[ ]") << "\n";
            temp = temp->next;
        }
        std::cout << "------------------------------------------------------\n";
    }

    void save_to_file() {
        if (!head) {
            std::cout << "Нечего сохранять, история пуста.\n";
            return;
        }

        std::string filename;
        std::cout << "Введите имя файла для сохранения (например, history.txt): ";
        std::cin >> filename;

        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cout << "Ошибка при создании файла!\n";
            return;
        }

        Node* temp = head;
        while (temp) {
            std::string data = temp->url + "|" + std::to_string(temp->visit_time) + "|" + (temp->is_bookmarked ? "1" : "0");
            file << base64_encode(data) << "\n";
            temp = temp->next;
        }
        file.close();
        std::cout << "История успешно сохранена в файл " << filename << "\n";
    }

    void load_from_file() {
        std::string filename;
        std::cout << "Введите имя файла для загрузки: ";
        std::cin >> filename;

        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "Файл не найден!\n";
            return;
        }

        clear();

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;

            std::string decoded = base64_decode(line);
            std::stringstream ss(decoded);
            std::string url, time_str, bookmark_str;

            if (std::getline(ss, url, '|') &&
                std::getline(ss, time_str, '|') &&
                std::getline(ss, bookmark_str, '|')) {

                std::time_t t = std::stoll(time_str);
                bool b = (bookmark_str == "1");
                visit(url, b, t);
            }
        }
        file.close();
        std::cout << "История успешно загружена!\n";
    }
};

int main() {
    std::setlocale(LC_ALL, "Russian");

    BrowserHistory browser;
    int choice;
    std::string input_str;

    while (true) {
        browser.print_history();

        std::cout << "\n=== МЕНЮ УПРАВЛЕНИЯ ИСТОРИЕЙ ===\n";
        std::cout << "1. Перейти на страницу (Visit)\n";
        std::cout << "2. Назад (Back)\n";
        std::cout << "3. Вперед (Forward)\n";
        std::cout << "4. Переключить закладку\n";
        std::cout << "5. Поиск по URL/домену\n";
        std::cout << "6. Очистить историю\n";
        std::cout << "7. Сохранить в файл\n";
        std::cout << "8. Загрузить из файла\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";

        if (!(std::cin >> choice)) {
            std::cout << "Некорректный ввод! Выход из программы.\n";
            break;
        }

        if (choice == 0) {
            std::cout << "Программа завершена.\n";
            break;
        }

        switch (choice) {
        case 1:
            std::cout << "Введите URL страницы: ";
            std::cin >> input_str;
            browser.visit(input_str);
            break;
        case 2:
            browser.back();
            break;
        case 3:
            browser.forward();
            break;
        case 4:
            browser.toggle_bookmark();
            break;
        case 5:
            std::cout << "Введите поисковый запрос (домен или часть URL): ";
            std::cin >> input_str;
            browser.search(input_str);
            break;
        case 6:
            browser.clear();
            std::cout << "История полностью очищена.\n";
            break;
        case 7:
            browser.save_to_file();
            break;
        case 8:
            browser.load_from_file();
            break;
        default:
            std::cout << "Неверный пункт меню! Попробуйте снова.\n";
        }
    }

    return 0;
}
