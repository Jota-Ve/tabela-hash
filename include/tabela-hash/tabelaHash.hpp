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
#include <sys/types.h>

#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <string>
#include <tuple>
#include <vector>

//

using fmt::print;  // NOLINT
using scn::scan;   // NOLINT
namespace tbh {
using std::optional;                                               // NOLINT
using chaveValor_t = std::optional<std::tuple<std::string, int>>;  // NOLINT

constexpr int TAM_INICIAL{127};
constexpr auto VALOR_FALHA{std::nullopt};
constexpr auto VAZIO{std::nullopt};
constexpr auto REMOVIDO{std::make_tuple("", -1)};

class TabelaHash {
  /* Lista do que fazer
  // TODO: Implementar funçao de remover
  //   TODO: Mudar retorno para optional<T>
      TODO: Mudar tipo do valor para Template

  TODO: Implementar redimensionamento da tabela

  // TODO: Cronometrar perfomance da tabela

  ?: Função que retorna a quantidade de colisões ?

  TODO: Usar dados de + alunos da UFF

  // TODO: Melhorar função de hash

  ?: Implementar biblioteca de testes ?
  */

 public:
  TabelaHash() { itens.resize(TAM_INICIAL, VAZIO); }

  bool insere(std::string chave, int valor) {
    if (chave == std::get<0>(REMOVIDO)) return false;

    auto idx = this->hash(chave) % itens.capacity();

    // para se encontrar a chave ou um index ainda não utilizado
    while (itens.at(idx).has_value() && chaveNoIndex(idx).value() != chave) {
      idx = (idx + 1) % itens.capacity();
    }

    chaveValor_t item = itens.at(idx);
    // Se já existe, apenas atualiza
    if (item.has_value() && std::get<0>(item.value()) == chave) {
      std::get<1>(itens.at(idx).value()) = valor;
    } else {
      itens.at(idx) = std::make_tuple(chave, valor);
      N++;
    }

    if (tamanho() > (itens.size() / 2)) aumentaTabela();

    return true;
  }

  optional<int> busca(std::string chave) {
    //
    if (chave == std::get<0>(REMOVIDO)) return VALOR_FALHA;

    auto idx{this->hash(chave) % itens.capacity()};
    auto it = itens.at(idx);

    std::optional<std::string> chaveNoIdx;
    if (it.has_value())
      chaveNoIdx = std::get<0>(it.value());
    else
      chaveNoIdx = std::nullopt;

    auto colisoes{0};

    // Verifica a próxima enquanto:
    // 1: não possuir chave ou possuir chave diferente da requisitada
    // 2: não percorreu toda a tabela
    while ((chaveNoIdx.has_value() && chaveNoIdx.value() != chave) &&
           (colisoes < itens.size())) {
      idx = (idx + 1) % itens.size();

      auto item = itens.at(idx);
      if (item.has_value())
        chaveNoIdx = std::get<0>(item.value());
      else
        chaveNoIdx = std::nullopt;

      colisoes++;
    }

    // Se encontrou a chave no idx, retorna seu valor
    if (chaveNoIdx.has_value() && chaveNoIdx.value() == chave) {
      return std::get<1>(itens.at(idx).value());
    }

    // Não encontrou a chave, retorna valor de falha
    return VALOR_FALHA;
  }

  optional<int> remove(std::string chave) {
    auto idx{this->hash(chave) % itens.size()};
    auto it = itens.at(idx);

    std::optional<std::string> chaveNoIdx;
    if (it.has_value())
      chaveNoIdx = std::get<0>(it.value());
    else
      chaveNoIdx = std::nullopt;
    int colisoes{0};

    // Verifica a próxima enquanto:
    // 1: não possuir chave ou possuir chave diferente da requisitada
    // 2: não percorreu toda a tabela

    while ((chaveNoIdx.has_value() && chaveNoIdx.value() != chave) &&
           (colisoes < itens.size())) {
      idx = (idx + 1) % itens.size();
      it = itens.at(idx);

      if (it.has_value())
        chaveNoIdx = std::get<0>(it.value());
      else
        chaveNoIdx = VAZIO;

      colisoes++;
    }

    // Achou a chave
    if (chaveNoIdx.has_value() && chaveNoIdx.value() == chave) {
      auto valor = std::get<1>(it.value());
      // Marca posição como removida
      itens.at(idx) = REMOVIDO;
      N--;
      return valor;
    }

    // Chave não estava na tabela
    return VALOR_FALHA;
  }

  int tamanho() { return N; }

 private:
  std::vector<chaveValor_t> itens;
  int N{0};

  int hash(std::string chave) {
    // Valor inicial é um número primo.
    int hash{7};

    // Multiplica o hash atual pelo nº primo 31 e soma com caractére, para cada
    // caractére.
    for (auto c : chave) hash = hash * 31 + c;

    // Garante que o retorno não vai ser maior que a tabela.
    return static_cast<int>(hash);  // % items.capacity());
  }

  optional<std::string> chaveNoIndex(int idx) {
    auto item = this->itens.at(idx);
    if (item.has_value()) return std::get<0>(item.value());
    return std::nullopt;
  }

  optional<int> valorNoIndex(int idx) {
    auto item = this->itens.at(idx);
    if (item.has_value()) return std::get<1>(item.value());
    return std::nullopt;
  }

  bool indexRemovido(int idx) {
    return (this->itens.at(idx).has_value() &&
            this->itens.at(idx).value() == REMOVIDO);
  }

  void aumentaTabela() {
    std::vector<chaveValor_t> novoItens;
    // Preenche a nova tabela com o dobro do tamanho da tabela atual
    novoItens.resize(itens.size() * 2, VAZIO);

    for (auto antigoIdx = 0; antigoIdx < itens.size(); antigoIdx++) {
      auto it = itens.at(antigoIdx);

      // Ignora valores removidos
      if (it.value_or(REMOVIDO) == REMOVIDO) continue;

      auto chave = std::get<0>(it.value());
      auto valorHash = hash(chave);

      // Limita o hash a nova capacidade da tabela
      auto novoIdx = valorHash % novoItens.capacity();
      // Enquanto o idx já estiver coupado, vai pro próximo
      while (novoItens.at(novoIdx).has_value()) novoIdx++;
      // Guarda o item na nova tabela
      novoItens.at(novoIdx) = it;
    }

    // Atualiza a tabela
    itens = novoItens;
  }
};
}  // namespace tbh
