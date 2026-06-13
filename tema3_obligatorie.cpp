#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct TodoItem {
    int id;
    std::string title;
    bool isCompleted;
};

class TodoManager {
private:
    std::vector<TodoItem> todoList;
    int nextId = 1;

public:
    void addTodo(const std::string& title) {
        if (title.empty()) {
            std::cout << "titlul trebuie sa aibe nume\n";
            return;
        }
        todoList.push_back({nextId++, title, false});
        std::cout << "sarcina a fost adaugata\n";
    }

    void displayTodos() const {
        if (todoList.empty()) {
            std::cout << " nu ai sarcini in lista.\n";
            return;
        }

        for (const auto& item : todoList) {
            std::string status = item.isCompleted ? "(Finalizat)" : "(In lucru) ";
            std::cout << item.id << ". " << status << " - " << item.title << "\n";
        }
    }

    // U: Schimbare stare (Bifare/Debifare)
    void toggleTodo(int id) {
        for (auto& item : todoList) {
            if (item.id == id) {
                item.isCompleted = !item.isCompleted;
                std::cout << "starea sarcinii " << id << " a fost modificata\n";
                return;
            }
        }
        std::cout << "sarcina cu ID ul " << id << " nu a fost gasita\n";
    }

    // D: Stergere sarcina
    void deleteTodo(int id) {
        auto it = std::remove_if(todoList.begin(), todoList.end(), [id](const TodoItem& item) {
            return item.id == id;
        });

        if (it != todoList.end()) {
            todoList.erase(it, todoList.end());
            std::cout << "sarcina cu ID-ul " << id << " a fost stearsa\n";
        } else {
            std::cout << "sarcina cu ID-ul " << id << " nu a fost gasita\n";
        }
    }
};

int main() {
    TodoManager manager;
    int opțiune = 0;

    manager.addTodo("rezolva tema");
    manager.addTodo("cumpara cafea");

    while (true) {
        manager.displayTodos();
        std::cout << "Meniu:\n";
        std::cout << "1. Adauga o sarcina noua\n";
        std::cout << "2. Schimba starea unei sarcini\n";
        std::cout << "3. Sterge o sarcina\n";
        std::cout << "4. Iesire\n";
        std::cout << "Alege o optiune (1-4): ";
        
        std::cin >> opțiune;
        std::cin.ignore(); 

        if (opțiune == 1) {
            std::string title;
            std::cout << "introdu sarcina: ";
            std::getline(std::cin, title);
            manager.addTodo(title);
        } 
        else if (opțiune == 2) {
            int id;
            std::cout << "introdu ID ul sarcinii de modificat: ";
            std::cin >> id;
            manager.toggleTodo(id);
        } 
        else if (opțiune == 3) {
            int id;
            std::cout << "introdu ID ul sarcinii de sters: ";
            std::cin >> id;
            manager.deleteTodo(id);
        } 
        else {
            std::cout << "optiune invalida\n";
        }
    }

    return 0;
}