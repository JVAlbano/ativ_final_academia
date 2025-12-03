#include "Sistema.h"
#include "Cardio.h"
#include "Forca.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>

Sistema::Sistema() {
    carregarDados();
}

Sistema::~Sistema() {
    salvarDados();
    // Deletar ponteiros de exercicios e fichas
}

// Carregar dados dos arquivos
void Sistema::carregarDados() {
    // Carregar exercicios.txt
    // Carregar fichas.txt
    historico.carregarDeArquivo();
}

// Salvar dados nos arquivos
void Sistema::salvarDados() {
    // Salvar exercicios.txt
    // Salvar fichas.txt
    historico.salvarEmArquivo();
}

// Buscar exercício por ID
Exercicio* Sistema::buscarExercicioPorId(int id) {
    return nullptr; // Implementar
}

// Buscar ficha por ID
Ficha* Sistema::buscarFichaPorId(int id) {
    return nullptr; // Implementar
}

// Cadastrar novo exercício
void Sistema::cadastrarExercicio() {
    // Implementar
}

// Listar exercícios ativos
void Sistema::listarExercicios() {
    // Implementar
}

// Desativar exercício
void Sistema::excluirExercicio() {
    // Implementar
}

// Criar nova ficha
void Sistema::criarFicha() {
    // Implementar
}

// Adicionar exercício à ficha
void Sistema::adicionarExercicioFicha() {
    // Implementar
}

// Listar todas as fichas
void Sistema::listarFichas() {
    // Implementar
}

// Registrar treino realizado
void Sistema::registrarTreino() {
    // Implementar
}

// Exibir histórico de treinos
void Sistema::exibirHistorico() {
    // Implementar
}
