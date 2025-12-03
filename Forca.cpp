#include "Forca.h"
#include <iostream>
#include <iomanip>

// Construtor para novos cadastros
Forca::Forca(std::string nome, double carga, int series, int repeticoes, int tempoDescanso)
    : Exercicio(nome), carga(carga), series(series), repeticoes(repeticoes), tempoDescanso(tempoDescanso) {
    // inicializado na lista
}

// Construtor para leitura de arquivo
Forca::Forca(int id, std::string nome, bool ativo, double carga, int series, int repeticoes, int tempoDescanso)
    : Exercicio(id, nome, ativo), carga(carga), series(series), repeticoes(repeticoes), tempoDescanso(tempoDescanso) {
    // inicializado na lista
}

// Exibir detalhes do exercício
void Forca::exibirDetalhes() const {
    std::cout << "Tipo: Forca | ID: " << id << " | Nome: " << nome
              << " | Status: " << (ativo ? "Ativo" : "Inativo")
              << " | Carga: " << std::fixed << std::setprecision(2) << carga << " kg"
              << " | Series: " << series
              << " | Repeticoes: " << repeticoes
              << " | Descanso: " << tempoDescanso << " s"
              << std::endl;
}

// Calcular tempo estimado (em minutos)
double Forca::calcularTempoEstimado() const {
    // (Séries × Repetições × 3 seg) + (Séries × Tempo de Descanso) -> resultado em segundos
    double segundos = static_cast<double>(series) * static_cast<double>(repeticoes) * 3.0
                      + static_cast<double>(series) * static_cast<double>(tempoDescanso);
    return segundos / 60.0;
}

// Calcular calorias gastas
double Forca::calcularCaloriasGastas() const {
    // Fórmula: Séries × Repetições × Carga × 0.15.
    return static_cast<double>(series) * static_cast<double>(repeticoes) * carga * 0.15;
}

// Retornar tipo do exercício (2 = Força)
int Forca::getTipo() const {
    return 2;
}

// Getters
double Forca::getCarga() const { 
    return carga;
}

int Forca::getSeries() const { 
    return series;
}

int Forca::getRepeticoes() const { 
    return repeticoes;
}

int Forca::getTempoDescanso() const { 
    return tempoDescanso;
}
