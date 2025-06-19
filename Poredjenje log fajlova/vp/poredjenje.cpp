#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Block {
    int start_line;
    int end_line;
    int value;
};

int main() {
    std::ifstream input_file("game_log.txt");  // Ulazni fajl
    if (!input_file.is_open()) {
        std::cerr << "Ne mogu da otvorim game_log!" << std::endl;
        return 1;
    }

    std::ofstream output_file("rezultati.txt");  // Izlazni fajl
    if (!output_file.is_open()) {
        std::cerr << "Ne mogu da kreiram rezultati.txt!" << std::endl;
        return 1;
    }

    std::vector<Block> blocks;
    std::string line;
    int current_line = 0;
    int current_value = -1;
    int block_start = 1;

    while (std::getline(input_file, line)) {
        current_line++;

        if (line == "1" || line == "2") {
            int value = std::stoi(line);

            if (value != current_value) {
                if (current_value != -1) {
                    blocks.push_back({block_start, current_line - 1, current_value});
                }
                block_start = current_line;
                current_value = value;
            }
        }
    }

    if (current_value != -1) {
        blocks.push_back({block_start, current_line, current_value});
    }

    // Upis rezultata u fajl
    for (const auto& block : blocks) {
        output_file << "Blok " << block.value << ": Redovi "
                   << block.start_line << " - " << block.end_line << "\n";
    }

    input_file.close();
    output_file.close();

    std::cout << "Rezultati su sacuvani u rezultati.txt!" << std::endl;
    return 0;
}