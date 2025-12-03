#include "Ficha.h"
#include <iostream>
#include <iomanip>

int Ficha::proximoId = 1;

// Construtor para novos cadastros
Ficha::Ficha(std::string nome) {
    this->nome = nome;
    this->id = proximoId++;
    this->exercicios = std::vector<Exercicio*>();
}

// Construtor para leitura de arquivo
Ficha::Ficha(int id, std::string nome) {
    this->id = id;
    this->nome = nome;
    this->exercicios = std::vector<Exercicio*>();

    // Ajusta o contador se o id lido for maior
    if (id >= proximoId) {
        proximoId = id + 1;
    }
}

// Destrutor (não deletar exercícios, apenas limpar vector)
Ficha::~Ficha() {
    exercicios.clear(); // não deleta os exercícios, apenas limpa referências
}

// Adicionar exercício à ficha
void Ficha::adicionarExercicio(Exercicio* exercicio) {
    if (exercicio != nullptr) {
        exercicios.push_back(exercicio);
    }
}

// Exibir ficha completa com exercícios e totais
void Ficha::exibirFicha() const {
    std::cout << "Ficha ID: " << id << " | Nome: " << nome << std::endl;
    std::cout << "Exercicios (" << exercicios.size() << "):" << std::endl;
    for (const auto& ex : exercicios) {
        if (ex) ex->exibirDetalhes();
    }
    double tempo = calcularTempoTotal();
    double cal = calcularCaloriasTotais();
    std::cout << "Totais -> Tempo (min): " << std::fixed << std::setprecision(2) << tempo
              << " | Calorias: " << std::fixed << std::setprecision(2) << cal << std::endl;
}

// Calcular tempo total da ficha
double Ficha::calcularTempoTotal() const {
    double total = 0.0;
    for (const auto& ex : exercicios) {
        if (ex) total += ex->calcularTempoEstimado();
    }
    return total;
}

// Calcular calorias totais da ficha
double Ficha::calcularCaloriasTotais() const {
    double total = 0.0;
    for (const auto& ex : exercicios) {
        if (ex) total += ex->calcularCaloriasGastas();
    }
    return total;
}

// Getters
int Ficha::getId() const { 
    return id;
}

std::string Ficha::getNome() const { 
    return nome;
}

const std::vector<Exercicio*>& Ficha::getExercicios() const {
    return exercicios;
}

// Atualizar próximo ID
void Ficha::atualizarProximoId(int maiorId) {
    if (maiorId >= proximoId) {
        proximoId = maiorId + 1;
    }
}
