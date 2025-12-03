#include "Cardio.h"
#include <iostream>

// Construtor para novos cadastros
Cardio::Cardio(std::string nome, int duracao, double caloriasPorMinuto) 
    : Exercicio(nome) {
    // Implementar
}

// Construtor para leitura de arquivo
Cardio::Cardio(int id, std::string nome, bool ativo, int duracao, double caloriasPorMinuto)
    : Exercicio(id, nome, ativo) {
    // Implementar
}

// Exibir detalhes do exercício
void Cardio::exibirDetalhes() const {
    // Implementar
}

// Calcular tempo estimado (duração em minutos)
double Cardio::calcularTempoEstimado() const {
    return 0.0; // Implementar
}

// Calcular calorias gastas
double Cardio::calcularCaloriasGastas() const {
    return 0.0; // Implementar
}

// Retornar tipo do exercício (1 = Cardio)
int Cardio::getTipo() const {
    return 0; // Implementar
}

// Getter de duração
int Cardio::getDuracao() const {
    return 0; // Implementar
}

// Getter de calorias por minuto
double Cardio::getCaloriasPorMinuto() const {
    return 0.0; // Implementar
}
