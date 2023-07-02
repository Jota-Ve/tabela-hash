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
using std::optional;                                               // NOLINT
using chaveValor_t = std::optional<std::tuple<std::string, int>>;  // NOLINT

constexpr int TAM{7007};
constexpr auto VALOR_FALHA{std::nullopt};
constexpr auto VAZIO{std::nullopt};
constexpr auto REMOVIDO{std::make_tuple("", -1)};

class TabelaHash {
  /* Lista do que fazer
  TODO: Testar se os valores removidos compartilham memória
  // TODO: Implementar funçao de remover
  //   TODO: Mudar retorno para optional<T>
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
    // Recusa caso tabela esteja cheia ou chave seja
    // a mesma usada para marcar item removido
    if (this->tamanho() == TAM || chave == std::get<0>(REMOVIDO)) return false;

    int idx = this->hash(chave);
    // para se encontrar a chave ou um index ainda não utilizado
    while (this->indexUtilizado(idx) &&
           this->chaveNoIndex(idx).value() != chave)
      idx = (idx + 1) % TAM;

    // print("{}/{}/{}: chaveNoIdx={}, chave={}\n", idx, colisoes, TAM,
    //       chaveNoIdx->empty(), chave);

    // Guardando novo chave-valor ou atualizando valor de chave existente
    this->items.at(idx) = std::make_tuple(chave, valor);
    this->N++;

    return true;
  }

  optional<int> busca(std::string chave) {
    //
    int idx{this->hash(chave)};
    auto chaveNoIdx{this->chaveNoIndex(idx)};
    int colisoes{0};

    // Verifica a próxima enquanto:
    // 1: não possuir chave ou possuir chave diferente da requisitada
    // 2: não percorreu toda a tabela
    while ((chaveNoIdx.has_value() && chaveNoIdx.value() != chave) &&
           (colisoes < TAM - 1)) {
      // print("{}/{}/{}: chaveNoIdx.has_value()={}, chave={}\n", idx, colisoes,
      //       TAM, chaveNoIdx.has_value(), chave);
      idx = (idx + 1) % TAM;
      chaveNoIdx = this->chaveNoIndex(idx);
      colisoes++;
    }

    // Se encontrou a chave no idx, retorna seu valor
    if (chaveNoIdx.has_value() && chaveNoIdx.value() == chave)
      return this->valorNoIndex(idx);

    // Não encontrou a chave, retorna valor de falha
    return VALOR_FALHA;
  }

  optional<int> remove(std::string chave) {
    int idx{this->hash(chave)};
    auto chaveNoIdx{this->chaveNoIndex(idx)};
    int colisoes{0};

    // Verifica a próxima enquanto:
    // 1: não possuir chave ou possuir chave diferente da requisitada
    // 2: não percorreu toda a tabela
    while ((chaveNoIdx.has_value() && chaveNoIdx.value() != chave) &&
           (colisoes < TAM - 1)) {
      idx = (idx + 1) % TAM;
      chaveNoIdx = this->chaveNoIndex(idx);
      colisoes++;
    }

    // Achou a chave
    if (chaveNoIdx.has_value() && chaveNoIdx.value() == chave) {
      auto valor = this->valorNoIndex(idx);
      // Marca posição como removida
      this->items.at(idx) = REMOVIDO;

      this->N--;
      return valor;
    }

    // Chave não estava na tabela
    return std::nullopt;
  }

  int tamanho() { return this->N; }

 private:
  std::array<chaveValor_t, TAM> items;
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

  optional<std::string> chaveNoIndex(int idx) {
    auto item = this->items.at(idx);
    if (item.has_value()) return std::get<0>(item.value());
    return std::nullopt;
  }

  optional<int> valorNoIndex(int idx) {
    auto item = this->items.at(idx);
    if (item.has_value()) return std::get<1>(item.value());
    return std::nullopt;
  }

  bool indexUtilizado(int idx) { return this->items.at(idx).has_value(); }

  bool indexRemovido(int idx) {
    return (this->items.at(idx).has_value() &&
            this->items.at(idx).value() == REMOVIDO);
  }
};
}  // namespace tbh
