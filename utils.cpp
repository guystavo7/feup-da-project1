//
// Created by gustavobastos on 22/03/26.
//

#include "utils.h"

#include <iostream>
#include <fstream>
#include <string>

// Função que compara até 'limiteLinhas' de dois ficheiros
bool file_comparator(const std::string& caminho1, const std::string& caminho2, int limiteLinhas) {
    // Abre os ficheiros em modo de texto (padrão)
    std::ifstream ficheiro1(caminho1);
    std::ifstream ficheiro2(caminho2);

    // Verifica se houve algum erro ao abrir os ficheiros
    if (!ficheiro1.is_open() || !ficheiro2.is_open()) {
        std::cerr << "Erro: Não foi possível abrir um ou ambos os ficheiros.\n";
        return false;
    }

    std::string linha1, linha2;
    int linhasLidas = 0;

    // Lê os ficheiros linha a linha até atingir o limite estipulado
    while (linhasLidas < limiteLinhas) {
        // Tenta extrair a próxima linha de cada ficheiro
        bool sucesso1 = (bool)std::getline(ficheiro1, linha1);
        bool sucesso2 = (bool)std::getline(ficheiro2, linha2);

        // Se um ficheiro chegou ao fim mas o outro não, são diferentes
        if (sucesso1 != sucesso2) {
            return false;
        }

        // Se ambos os ficheiros chegaram ao fim antes do limite,
        // significa que são idênticos até ao seu término.
        if (!sucesso1 && !sucesso2) {
            break;
        }

        // Compara o conteúdo das duas linhas
        if (linha1 != linha2) {
            return false; // Encontrou uma diferença
        }

        linhasLidas++;
    }

    return true; // Se o loop terminou sem retornar false, as linhas comparadas são iguais
}

int file_len(const std::string& filePath) {
    std::ifstream file(filePath);

    // Check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file: " << filePath << "\n";
        return -1; // Return -1 to indicate an error occurred
    }

    int lineCount = 0;
    std::string line;

    // Read the file line by line until the end
    while (std::getline(file, line)) {
        lineCount++;
    }

    return lineCount;
}