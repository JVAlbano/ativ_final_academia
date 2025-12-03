#include "Forca.h"
#include <iostream>

// Construtor para novos cadastros
Forca::Forca(std::string nome, double carga, int series, int repeticoes, int tempoDescanso)
    : Exercicio(nome) {
    // Implementar
}

// Construtor para leitura de arquivo
Forca::Forca(int id, std::string nome, bool ativo, double carga, int series, int repeticoes, int tempoDescanso)
    : Exercicio(id, nome, ativo) {
    // Implementar
}

// Exibir detalhes do exercício
void Forca::exibirDetalhes() const {
    // Implementar
}

// Calcular tempo estimado (em minutos)
double Forca::calcularTempoEstimado() const {
    return 0.0; // Implementar
}

// Calcular calorias gastas
double Forca::calcularCaloriasGastas() const {
    return 0.0; // Implementar
}

// Retornar tipo do exercício (2 = Força)
int Forca::getTipo() const {
    return 0; // Implementar
}

// Getters
double Forca::getCarga() const { 
    return 0.0; // Implementar
}

int Forca::getSeries() const { 
    return 0; // Implementar
}

int Forca::getRepeticoes() const { 
    return 0; // Implementar
}

int Forca::getTempoDescanso() const { 
    return 0; // Implementar
}
