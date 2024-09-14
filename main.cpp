#include <iostream>

//Проект будет содержать
//-Открытие и сохранение текстовых файлов.
//-Редактирование текста (ввод, удаление, копирование, вставка).
//-Поддержка различных форматов файлов (например, .txt).
//-Навигация по тексту (стрелки, поиск по тексту).
//-Undo/Redo.


#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Document {
public:
    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Could not open the file!" << std::endl;
            return;
        }
        lines.clear();
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
        std::cout << "File loaded successfully." << std::endl;
    }

    void saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (!file) {
            std::cerr << "Could not open the file for writing!" << std::endl;
            return;
        }
        for (const auto& line : lines) {
            file << line << std::endl;
        }
        file.close();
        std::cout << "File saved successfully." << std::endl;
    }

    void insertText(const std::string& text, size_t lineNum) {
        if (lineNum >= lines.size()) {
            lines.push_back(text);
        } else {
            lines[lineNum].append(text);
        }
    }

    void print() const {
        for (size_t i = 0; i < lines.size(); ++i) {
            std::cout << i + 1 << ": " << lines[i] << std::endl;
        }
    }

private:
    std::vector<std::string> lines;
};

class TextEditor {
public:
    void run() {
        std::string command;
        while (true) {
            std::cout << "Enter command (open, save, edit, print, exit): ";
            std::cin >> command;

            if (command == "open") {
                std::string filename;
                std::cout << "Enter filename: ";
                std::cin >> filename;
                document.loadFromFile(filename);
            } else if (command == "save") {
                std::string filename;
                std::cout << "Enter filename: ";
                std::cin >> filename;
                document.saveToFile(filename);
            } else if (command == "edit") {
                size_t lineNum;
                std::string text;
                std::cout << "Enter line number: ";
                std::cin >> lineNum;
                std::cout << "Enter text: ";
                std::cin.ignore(); // Очистка буфера
                std::getline(std::cin, text);
                document.insertText(text, lineNum - 1);
            } else if (command == "print") {
                document.print();
            } else if (command == "exit") {
                break;
            } else {
                std::cout << "Unknown command!" << std::endl;
            }
        }
    }

private:
    Document document;
};

int main() {
    TextEditor editor;
    editor.run();
    return 0;
}