// SPDX-License-Identifier:  MIT
// Copyright (C) 2023 - Prof. Igor Machado Coelho

#pragma once

// C includes
//
// helpers
#include <fmt/core.h>
#include <scn/scn.h>
// C++ includes
#include <math.h>

#include <array>
#include <cmath>
#include <iostream>
#include <optional>
#include <string>
#include <tuple>

//

using fmt::print;  // NOLINT
using scn::scan;   // NOLINT
namespace tbh {

constexpr int TAM{50};
constexpr auto VALOR_FALHA{std::nullopt};
constexpr auto VAZIO{""};
constexpr auto REMOVIDO{std::nullopt};

class TabelaHash {
  /* Lista do que fazer
  // TODO: Implementar funçao de remover
  //   TODO: Mudar retorno para std::optional<T>
      TODO: Mudar tipo do valor para Template

  TODO: Implementar redimensionamento da tabela

  TODO: Cronometrar perfomance da tabela

  TODO: Função para testar se a ordem dos caractéres gera hash diferente
    ?: Função que retorna a quantidade de colisões ?

  TODO: Usar dados de + alunos da UFF

  // TODO: Melhorar função de hash

  ?: Implementar biblioteca de testes ?
  */

 public:
  bool insere(std::string chave, int valor) {
    // Se estiver cheia, recusa inserção
    if (this->tamanho() == TAM) return false;

    int idx = this->hash(chave);
    auto chaveNoIdx = this->chaveNoIndex(idx);

    // Se a chaveNoIdx for nullopt ou igual a chave, encerra o loop e insere
    // nesse idx
    while ((chaveNoIdx.value_or(chave) != chave)) {
      idx = (idx + 1) % TAM;
      chaveNoIdx = this->chaveNoIndex(idx);
    }
    // print("{}/{}/{}: chaveNoIdx={}, chave={}\n", idx, colisoes, TAM,
    //       chaveNoIdx->empty(), chave);

    // Guardando novo chave-valor ou atualizando valor de chave existente
    this->items.at(idx) = std::make_tuple(chave, valor);
    this->N++;

    return true;
  }

  std::optional<int> recupera(std::string chave) {
    //
    int idx{this->hash(chave)};
    auto chaveNoIdx{this->chaveNoIndex(idx)};
    int colisoes{0};

    // Verifica a próxima enquanto:
    // 1: não possuir chave ou possuir chave diferente da requisitada
    // 2: não percorreu toda a tabela
    while ((!chaveNoIdx.has_value() || chaveNoIdx.value() != chave) &&
           (colisoes < TAM - 1)) {
      idx = (idx + 1) % TAM;
      chaveNoIdx = this->chaveNoIndex(idx);
      colisoes++;
    }

    // Se encontrou a chave no idx, retorna seu valor
    if (chaveNoIdx == chave) return this->valorNoIndex(idx);

    // Não encontrou a chave, retorna valor de falha
    return VALOR_FALHA;
  }

  std::optional<int> remove(std::string chave) {
    int idx{this->hash(chave)};
    auto chaveNoIdx{this->chaveNoIndex(idx)};
    int colisoes{0};

    // Verifica a próxima enquanto:
    // 1: não possuir chave ou possuir chave diferente da requisitada
    // 2: não percorreu toda a tabela
    while ((!chaveNoIdx.has_value() || chaveNoIdx.value() != chave) &&
           (colisoes < TAM - 1)) {
      idx = (idx + 1) % TAM;
      chaveNoIdx = this->chaveNoIndex(idx);
      colisoes++;
    }

    // Achou a chave
    if (chaveNoIdx.has_value() && chaveNoIdx.value() == chave) {
      auto valor = this->valorNoIndex(idx);
      // Marca posição como removida
      this->items.at(idx) = std::make_tuple(REMOVIDO, -1);

      this->N--;
      return valor;
    }

    // CHave não estava na tabela
    return std::nullopt;
  }

  int tamanho() { return this->N; }

 private:
  std::array<std::tuple<std::optional<std::string>, int>, TAM> items;
  int N{0};

  int hash(std::string chave) {
    // Valor inicial é um número primo.
    int hash{7};

    // Multiplica o hash atual pelo nº primo 31 e soma com caractére, para cada
    // caractére.
    for (auto c : chave) hash = hash * 31 + c;

    // Garante que o retorno não vai ser maior que a tabela.
    return static_cast<int>((hash) % TAM);
  }

  std::optional<std::string> chaveNoIndex(int idx) {
    return std::get<0>(this->items.at(idx));
  }

  int valorNoIndex(int idx) { return std::get<1>(this->items.at(idx)); }
};
}  // namespace tbh
