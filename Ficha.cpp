#include "Ficha.h"
#include <iostream>
#include <iomanip>

int Ficha::proximoId = 1;

// Construtor para novos cadastros
Ficha::Ficha(std::string nome) {
    // Implementar
}

// Construtor para leitura de arquivo
Ficha::Ficha(int id, std::string nome) {
    // Implementar
}

// Destrutor (não deletar exercícios, apenas limpar vector)
Ficha::~Ficha() {
    // Implementar
}

// Adicionar exercício à ficha
void Ficha::adicionarExercicio(Exercicio* exercicio) {
    // Implementar
}

// Exibir ficha completa com exercícios e totais
void Ficha::exibirFicha() const {
    // Implementar
}

// Calcular tempo total da ficha
double Ficha::calcularTempoTotal() const {
    double total = 0.0;
    // Implementar
    return total;
}

// Calcular calorias totais da ficha
double Ficha::calcularCaloriasTotais() const {
    double total = 0.0;
    // Implementar
    return total;
}

// Getters
int Ficha::getId() const { 
    return 0; // Implementar
}

std::string Ficha::getNome() const { 
    return ""; // Implementar
}

const std::vector<Exercicio*>& Ficha::getExercicios() const {
    static std::vector<Exercicio*> vazio; // Placeholder para compilar
    return vazio; // Implementar
}

// Atualizar próximo ID
void Ficha::atualizarProximoId(int maiorId) {
    // Implementar
}
