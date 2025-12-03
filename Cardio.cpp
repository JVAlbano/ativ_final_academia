#include "Cardio.h"
#include <iostream>
#include <iomanip>

// Construtor para novos cadastros
Cardio::Cardio(std::string nome, int duracao, double caloriasPorMinuto) 
    : Exercicio(nome), duracao(duracao), caloriasPorMinuto(caloriasPorMinuto) {
    // tudo atribuído na lista de inicialização
}

// Construtor para leitura de arquivo
Cardio::Cardio(int id, std::string nome, bool ativo, int duracao, double caloriasPorMinuto)
    : Exercicio(id, nome, ativo), duracao(duracao), caloriasPorMinuto(caloriasPorMinuto) {
    // nada mais
}

// Exibir detalhes do exercício
void Cardio::exibirDetalhes() const {
    std::cout << "Tipo: Cardio | ID: " << id << " | Nome: " << nome
              << " | Status: " << (ativo ? "Ativo" : "Inativo")
              << " | Duracao: " << duracao << " min"
              << " | Cal/min: " << std::fixed << std::setprecision(2) << caloriasPorMinuto
              << std::endl;
}

// Calcular tempo estimado (duração em minutos)
double Cardio::calcularTempoEstimado() const {
    return static_cast<double>(duracao);
}

// Calcular calorias gastas
double Cardio::calcularCaloriasGastas() const {
    return duracao * caloriasPorMinuto;
}

// Retornar tipo do exercício (1 = Cardio)
int Cardio::getTipo() const {
    return 1;
}

// Getter de duração
int Cardio::getDuracao() const {
    return duracao;
}

// Getter de calorias por minuto
double Cardio::getCaloriasPorMinuto() const {
    return caloriasPorMinuto;
}
