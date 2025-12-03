#include "Historico.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

// Adicionar registro ao histórico
void Historico::adicionarRegistro(const RegistroTreino& registro) {
    // Implementar
}

// Exibir histórico completo
void Historico::exibirHistorico() const {
    // Implementar
}

// Getter de registros
const std::vector<RegistroTreino>& Historico::getRegistros() const {
    static std::vector<RegistroTreino> vazio; // Placeholder para compilar
    return vazio; // Implementar
}

// Carregar histórico do arquivo
void Historico::carregarDeArquivo() {
    // Implementar
}

// Salvar histórico no arquivo
void Historico::salvarEmArquivo() const {
    // Implementar
}
