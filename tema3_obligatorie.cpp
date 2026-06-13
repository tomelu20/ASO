#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Structura care defineste o sarcina (Modelul)
struct TodoItem {
    int id;
    std::string title;
    bool isCompleted;
};

// Clasa care gestioneaza logica aplicatiei (Controller-ul)
class TodoManager {
private:
    std::vector<TodoItem> todoList;
    int nextId = 1;

public:
    // C: Adaugare sarcina
    void addTodo(const std::string& title) {
        if (title.empty()) {
            std::cout << "Eroare: Titlul nu poate fi gol!\n";
            return;
        }
        todoList.push_back({nextId++, title, false});
        std::cout << "Sarcina a fost adaugata cu succes!\n";
    }

    // R: Afisare sarcini (Interfata/View)
    void displayTodos() const {
        std::cout << "\n================ LISTA TODO ================\n";
        if (todoList.empty()) {
            std::cout << " Nu ai nicio sarcina in lista. Bucura-te de zi! 🎉\n";
            std::cout << "============================================\n";
            return;
        }

        for (const auto& item : todoList) {
            std::string status = item.isCompleted ? "[✓] (Finalizat)" : "[ ] (In lucru) ";
            std::cout << item.id << ". " << status << " - " << item.title << "\n";
        }
        std::cout << "============================================\n";
    }

    // U: Schimbare stare (Bifare/Debifare)
    void toggleTodo(int id) {
        for (auto& item : todoList) {
            if (item.id == id) {
                item.isCompleted = !item.isCompleted;
                std::cout << "Starea sarcinii " << id << " a fost modificata!\n";
                return;
            }
        }
        std::cout << "Eroare: Sarcina cu ID-ul " << id << " nu a fost gasita.\n";
    }

    // D: Stergere sarcina
    void deleteTodo(int id) {
        auto it = std::remove_if(todoList.begin(), todoList.end(), [id](const TodoItem& item) {
            return item.id == id;
        });

        if (it != todoList.end()) {
            todoList.erase(it, todoList.end());
            std::cout << "Sarcina cu ID-ul " << id << " a fost stearsa!\n";
        } else {
            std::cout << "Eroare: Sarcina cu ID-ul " << id << " nu a fost gasita.\n";
        }
    }
};

// Punctul de intrare in aplicatie
int main() {
    TodoManager manager;
    int opțiune = 0;

    // Adaugam cateva date de test la inceput
    manager.addTodo("Incepe proiectul in C++");
    manager.addTodo("Cumpara cafea");

    while (true) {
        manager.displayTodos();
        std::cout << "Meniu:\n";
        std::cout << "1. Adauga o sarcina noua\n";
        std::cout << "2. Schimba starea unei sarcini (Bifeaza/Debifeaza)\n";
        std::cout << "3. Sterge o sarcina\n";
        std::cout << "4. Iesire\n";
        std::cout << "Alege o optiune (1-4): ";
        
        std::cin >> opțiune;
        std::cin.ignore(); // Curatam bufferul pentru a putea citi texte cu spatii ulterior

        if (opțiune == 4) {
            std::cout << "La revedere!\n";
            break;
        }

        if (opțiune == 1) {
            std::string title;
            std::cout << "Introdu titlul sarcinii: ";
            std::getline(std::cin, title);
            manager.addTodo(title);
        } 
        else if (opțiune == 2) {
            int id;
            std::cout << "Introdu ID-ul sarcinii de modificat: ";
            std::cin >> id;
            manager.toggleTodo(id);
        } 
        else if (opțiune == 3) {
            int id;
            std::cout << "Introdu ID-ul sarcinii de sters: ";
            std::cin >> id;
            manager.deleteTodo(id);
        } 
        else {
            std::cout << "Optiune invalida! Incearca din nou.\n";
        }
    }

    return 0;
}