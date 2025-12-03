#include "Historico.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

// Adicionar registro ao histórico
void Historico::adicionarRegistro(const RegistroTreino& registro) {
    registros.push_back(registro);
}

// Exibir histórico completo
void Historico::exibirHistorico() const {
    if (registros.empty()) {
        std::cout << "Historico vazio." << std::endl;
        return;
    }
    std::cout << "=== Historico de Treinos ===" << std::endl;
    for (const auto& r : registros) {
        std::cout << r.dataHora << " | Ficha ID: " << r.idFicha << " | Nome: " << r.nomeFicha
                  << " | Tempo (min): " << std::fixed << std::setprecision(2) << r.tempoTotal
                  << " | Calorias: " << std::fixed << std::setprecision(2) << r.caloriasTotal
                  << std::endl;
    }
}

// Getter de registros
const std::vector<RegistroTreino>& Historico::getRegistros() const {
    return registros;
}

// Carregar histórico do arquivo
void Historico::carregarDeArquivo() {
    registros.clear();
    std::ifstream in("historico.txt");
    if (!in.is_open()) return;

    std::string linha;
    while (std::getline(in, linha)) {
        if (linha.empty()) continue;
        std::stringstream ss(linha);
        std::string campo;
        std::vector<std::string> campos;
        while (std::getline(ss, campo, ';')) {
            campos.push_back(campo);
        }
        // Espera entrada de 5 campos: dataHora;idFicha;nomeFicha;tempo;calorias
        if (campos.size() < 5) continue;
        RegistroTreino r;
        r.dataHora = campos[0];
        try {
            r.idFicha = std::stoi(campos[1]);
        } catch (...) { r.idFicha = 0; }
        r.nomeFicha = campos[2];
        try {
            r.tempoTotal = std::stod(campos[3]);
        } catch (...) { r.tempoTotal = 0.0; }
        try {
            r.caloriasTotal = std::stod(campos[4]);
        } catch (...) { r.caloriasTotal = 0.0; }
        registros.push_back(r);
    }
    in.close();
}

// Salvar histórico no arquivo
void Historico::salvarEmArquivo() const {
    std::ofstream out("historico.txt", std::ios::trunc);
    if (!out.is_open()) return;
    for (const auto& r : registros) {
        out << r.dataHora << ";" << r.idFicha << ";" << r.nomeFicha << ";"
            << r.tempoTotal << ";" << r.caloriasTotal << "\n";
    }
    out.close();
}
