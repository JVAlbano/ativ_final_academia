#include "Sistema.h"
#include "Cardio.h"
#include "Forca.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
#include <algorithm>

Sistema::Sistema() {
    carregarDados();
}

Sistema::~Sistema() {
    salvarDados();
    // Deletar ponteiros de exercicios e fichas
    for (auto p : exercicios) {
        delete p;
    }
    exercicios.clear();

    for (auto f : fichas) {
        delete f;
    }
    fichas.clear();
}

// Carregar dados dos arquivos
void Sistema::carregarDados() {
    // Carregar exercicios.txt
    std::ifstream inEx("exercicios.txt");
    if (inEx.is_open()) {
        std::string linha;
        while (std::getline(inEx, linha)) {
            if (linha.empty()) continue;
            std::stringstream ss(linha);
            std::string campo;
            std::vector<std::string> campos;
            while (std::getline(ss, campo, ';')) campos.push_back(campo);

            if (campos.size() < 1) continue;
            int tipo = 0;
            try { tipo = std::stoi(campos[0]); } catch(...) { continue; }

            if (tipo == 1 && campos.size() == 6) {
                // Cardio: 1;ID;NOME;DURACAO;CALORIAS_POR_MIN;STATUS
                int id = std::stoi(campos[1]);
                std::string nome = campos[2];
                int duracao = std::stoi(campos[3]);
                double calpm = std::stod(campos[4]);
                bool status = (std::stoi(campos[5]) != 0);
                Cardio* c = new Cardio(id, nome, status, duracao, calpm);
                exercicios.push_back(c);
            } else if (tipo == 2 && campos.size() == 8) {
                // Forca: 2;ID;NOME;CARGA;SERIES;REPETICOES;DESCANSO;STATUS
                int id = std::stoi(campos[1]);
                std::string nome = campos[2];
                double carga = std::stod(campos[3]);
                int series = std::stoi(campos[4]);
                int reps = std::stoi(campos[5]);
                int descanso = std::stoi(campos[6]);
                bool status = (std::stoi(campos[7]) != 0);
                Forca* f = new Forca(id, nome, status, carga, series, reps, descanso);
                exercicios.push_back(f);
            }
        }
        inEx.close();
    }

    // Carregar fichas.txt
    std::ifstream inF("fichas.txt");
    if (inF.is_open()) {
        std::string linha;
        while (std::getline(inF, linha)) {
            if (linha.empty()) continue;
            std::stringstream ss(linha);
            std::string campo;
            std::vector<std::string> campos;
            while (std::getline(ss, campo, ';')) campos.push_back(campo);
            if (campos.size() < 3) continue;
            int idFicha = std::stoi(campos[0]);
            std::string nomeFicha = campos[1];
            int totalEx = std::stoi(campos[2]);
            Ficha* ficha = new Ficha(idFicha, nomeFicha);
            // ids dos exercicios começam em campos[3] até 3+totalEx-1
            for (int i = 0; i < totalEx; ++i) {
                int idx = 3 + i;
                if (idx < (int)campos.size()) {
                    int idEx = std::stoi(campos[idx]);
                    Exercicio* ex = buscarExercicioPorId(idEx);
                    if (ex) ficha->adicionarExercicio(ex);
                }
            }
            fichas.push_back(ficha);
        }
        inF.close();
    }

    // Carregar histórico
    historico.carregarDeArquivo();
}

// Salvar dados nos arquivos
void Sistema::salvarDados() {
    // Salvar exercicios.txt
    std::ofstream outEx("exercicios.txt", std::ios::trunc);
    if (outEx.is_open()) {
        for (auto ex : exercicios) {
            if (!ex) continue;
            int tipo = ex->getTipo();
            if (tipo == 1) {
                Cardio* c = dynamic_cast<Cardio*>(ex);
                if (c) {
                    outEx << "1;" << c->getId() << ";" << c->getNome() << ";" << c->getDuracao()
                          << ";" << c->getCaloriasPorMinuto() << ";" << (c->isAtivo() ? 1 : 0) << "\n";
                }
            } else if (tipo == 2) {
                Forca* f = dynamic_cast<Forca*>(ex);
                if (f) {
                    outEx << "2;" << f->getId() << ";" << f->getNome() << ";" << f->getCarga()
                          << ";" << f->getSeries() << ";" << f->getRepeticoes() << ";" << f->getTempoDescanso()
                          << ";" << (f->isAtivo() ? 1 : 0) << "\n";
                }
            }
        }
        outEx.close();
    }

    // Salvar fichas.txt
    std::ofstream outF("fichas.txt", std::ios::trunc);
    if (outF.is_open()) {
        for (auto f : fichas) {
            if (!f) continue;
            outF << f->getId() << ";" << f->getNome() << ";" << f->getExercicios().size();
            for (auto ex : f->getExercicios()) {
                if (ex) outF << ";" << ex->getId();
            }
            outF << "\n";
        }
        outF.close();
    }

    // Salvar histórico
    historico.salvarEmArquivo();
}

// Buscar exercício por ID
Exercicio* Sistema::buscarExercicioPorId(int id) {
    for (auto ex : exercicios) {
        if (ex && ex->getId() == id) return ex;
    }
    return nullptr;
}

// Buscar ficha por ID
Ficha* Sistema::buscarFichaPorId(int id) {
    for (auto f : fichas) {
        if (f && f->getId() == id) return f;
    }
    return nullptr;
}

// Cadastrar novo exercício
void Sistema::cadastrarExercicio() {
    int tipo;
    std::cout << "Escolha tipo de exercicio (1 = Cardio, 2 = Forca): ";
    std::cin >> tipo;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (tipo == 1) {
        std::string nome;
        int duracao;
        double calpm;
        std::cout << "Nome: ";
        std::getline(std::cin, nome);
        std::cout << "Duracao (min): ";
        std::cin >> duracao;
        std::cout << "Calorias por minuto: ";
        std::cin >> calpm;
        Cardio* c = new Cardio(nome, duracao, calpm);
        exercicios.push_back(c);
        std::cout << "Cardio cadastrado com ID " << c->getId() << std::endl;
    } else if (tipo == 2) {
        std::string nome;
        double carga;
        int series, repeticoes, descanso;
        std::cout << "Nome: ";
        std::getline(std::cin, nome);
        if (nome.empty()) std::getline(std::cin, nome);
        std::cout << "Carga (kg): ";
        std::cin >> carga;
        std::cout << "Series: ";
        std::cin >> series;
        std::cout << "Repeticoes: ";
        std::cin >> repeticoes;
        std::cout << "Tempo de descanso (segundos): ";
        std::cin >> descanso;
        Forca* f = new Forca(nome, carga, series, repeticoes, descanso);
        exercicios.push_back(f);
        std::cout << "Forca cadastrado com ID " << f->getId() << std::endl;
    } else {
        std::cout << "Tipo invalido." << std::endl;
    }
    pausar();
}

// Listar exercícios ativos
void Sistema::listarExercicios() {
    std::cout << "=== Exercicios Cadastrados ===" << std::endl;
    for (auto ex : exercicios) {
        if (ex && ex->isAtivo()) {
            ex->exibirDetalhes();
        }
    }
    pausar();
}

// Desativar exercício
void Sistema::excluirExercicio() {
    int id;
    std::cout << "ID do exercicio a desativar: ";
    std::cin >> id;
    Exercicio* ex = buscarExercicioPorId(id);
    if (ex) {
        ex->desativar();
        std::cout << "Exercicio " << id << " desativado." << std::endl;
    } else {
        std::cout << "Exercicio nao encontrado." << std::endl;
    }
    pausar();
}

// Criar nova ficha
void Sistema::criarFicha() {
    std::string nome;
    std::cout << "Nome da ficha: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, nome);
    Ficha* f = new Ficha(nome);
    fichas.push_back(f);
    std::cout << "Ficha criada com ID " << f->getId() << std::endl;
    pausar();
}

// Excluir uma ficha
void Sistema::excluirFicha() {
    if (fichas.empty()) {
        std::cout << "Nenhuma ficha cadastrada." << std::endl;
        pausar();
        return;
    }

    std::cout << "Fichas cadastradas:" << std::endl;
    for (auto f : fichas) {
        std::cout << f->getId() << " - " << f->getNome() << std::endl;
    }

    int id;
    std::cout << "Digite o ID da ficha que deseja excluir: ";
    std::cin >> id;

    for (auto it = fichas.begin(); it != fichas.end(); ++it) {
        if ((*it)->getId() == id) {
            delete *it;
            fichas.erase(it);
            std::cout << "Ficha removida com sucesso!" << std::endl;
            pausar();
            return;
        }
    }

    std::cout << "Ficha nao encontrada!" << std::endl;
    pausar();
}

// Adicionar exercício à ficha
void Sistema::adicionarExercicioFicha() {
    if (fichas.empty()) {
        std::cout << "Nenhuma ficha cadastrada." << std::endl;
        pausar();
        return;
    }
    std::cout << "Fichas disponiveis:" << std::endl;
    for (auto f : fichas) {
        std::cout << f->getId() << " - " << f->getNome() << std::endl;
    }
    int idFicha;
    std::cout << "Escolha ID da ficha: ";
    std::cin >> idFicha;
    Ficha* ficha = buscarFichaPorId(idFicha);
    if (!ficha) {
        std::cout << "Ficha nao encontrada." << std::endl;
        pausar();
        return;
    }

    std::cout << "Exercicios disponiveis:" << std::endl;
    for (auto ex : exercicios) {
        if (ex && ex->isAtivo()) {
            ex->exibirDetalhes();
        }
    }

    int idEx;
    std::cout << "Escolha ID do exercicio para adicionar: ";
    std::cin >> idEx;
    Exercicio* ex = buscarExercicioPorId(idEx);
    if (!ex) {
        std::cout << "Exercicio nao encontrado." << std::endl;
    } else {
        ficha->adicionarExercicio(ex);
        std::cout << "Exercicio adicionado na ficha." << std::endl;
    }
    pausar();
}

// Remover exercício da ficha
void Sistema::removerExercicioDaFicha() {
    if (fichas.empty()) {
        std::cout << "Nenhuma ficha cadastrada." << std::endl;
        pausar();
        return;
    }

    std::cout << "Fichas disponiveis:" << std::endl;
    for (auto f : fichas) {
        std::cout << f->getId() << " - " << f->getNome() << std::endl;
    }

    int idFicha;
    std::cout << "Escolha o ID da ficha: ";
    std::cin >> idFicha;

    Ficha* ficha = buscarFichaPorId(idFicha);
    if (!ficha) {
        std::cout << "Ficha nao encontrada." << std::endl;
        pausar();
        return;
    }

    std::cout << "Exercicios da ficha:" << std::endl;
    for (auto ex : ficha->getExercicios()) {
        std::cout << ex->getId() << " - " << ex->getNome() << std::endl;
    }

    int idEx;
    std::cout << "Informe o ID do exercicio que deseja remover: ";
    std::cin >> idEx;

    ficha->removerExercicio(idEx);
    pausar();
}


// Listar todas as fichas
void Sistema::listarFichas() {
    if (fichas.empty()) {
        std::cout << "Nenhuma ficha cadastrada." << std::endl;
        pausar();
        return;
    }
    for (auto f : fichas) {
        if (f) f->exibirFicha();
        std::cout << "-----------------------------" << std::endl;
    }
    pausar();
}

// Registrar treino realizado
void Sistema::registrarTreino() {
    if (fichas.empty()) {
        std::cout << "Nenhuma ficha cadastrada." << std::endl;
        pausar();
        return;
    }
    std::cout << "Fichas disponiveis:" << std::endl;
    for (auto f : fichas) {
        std::cout << f->getId() << " - " << f->getNome() << std::endl;
    }
    int idFicha;
    std::cout << "Escolha ID da ficha que foi realizada: ";
    std::cin >> idFicha;
    Ficha* ficha = buscarFichaPorId(idFicha);
    if (!ficha) {
        std::cout << "Ficha nao encontrada." << std::endl;
        pausar();
        return;
    }

    double tempo = ficha->calcularTempoTotal();
    double cal = ficha->calcularCaloriasTotais();

    RegistroTreino r;
    r.dataHora = getDataHoraAtual();
    r.idFicha = ficha->getId();
    r.nomeFicha = ficha->getNome();
    r.tempoTotal = tempo;
    r.caloriasTotal = cal;

    historico.adicionarRegistro(r);
    historico.salvarEmArquivo();

    std::cout << "Treino registrado: " << r.dataHora << " | Tempo: " << tempo << " min | Cal: " << cal << std::endl;
    pausar();
}

// Exibir histórico de treinos
void Sistema::exibirHistorico() {
    historico.exibirHistorico();
    pausar();
}
