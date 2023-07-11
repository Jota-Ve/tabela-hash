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
  TabelaHash() { items.resize(TAM_INICIAL, VAZIO); }

  bool insere(std::string chave, int valor) {
    if (chave == std::get<0>(REMOVIDO)) return false;

    auto idx = this->hash(chave) % items.capacity();

    // para se encontrar a chave ou um index ainda não utilizado
    while (items.at(idx).has_value() && chaveNoIndex(idx).value() != chave) {
      idx = (idx + 1) % items.capacity();
    }

    chaveValor_t item = items.at(idx);
    // Se já existe, apenas atualiza
    if (item.has_value() && std::get<0>(item.value()) == chave) {
      std::get<1>(items.at(idx).value()) = valor;
    } else {
      items.at(idx) = std::make_tuple(chave, valor);
      N++;
    }

    if (tamanho() > (items.size() / 2)) aumentaTabela();
    // else
    //   print("Tamanho={}, items.size()/2={}\n", tamanho(), items.size() / 2);
    return true;
  }

  optional<int> busca(std::string chave) {
    //
    if (chave == std::get<0>(REMOVIDO)) return std::nullopt;

    auto idx{this->hash(chave) % items.capacity()};
    auto it = items.at(idx);

    std::optional<std::string> chaveNoIdx;
    if (it.has_value())
      chaveNoIdx = std::get<0>(it.value());
    else
      chaveNoIdx = std::nullopt;

    auto colisoes{0};

    // Verifica a próxima enquanto:
    // 1: não possuir chave ou possuir chave diferente da requisitada
    // 2: não percorreu toda a tabela
    // print("procruando {} no idx {}\n", chave, idx);
    while ((chaveNoIdx.has_value() && chaveNoIdx.value() != chave) &&
           (colisoes < items.size() - 1)) {
      // print("{}/{}/{}: chaveNoIdx.has_value()={}, chave={}\n", idx, colisoes,
      //       TAM, chaveNoIdx.has_value(), chave);
      // print("procruando {} no idx {}\n", chave, idx);
      idx = (idx + 1) % items.size();

      auto item = items.at(idx);
      if (item.has_value())
        chaveNoIdx = std::get<0>(item.value());
      else
        chaveNoIdx = std::nullopt;

      colisoes++;
    }

    // Se encontrou a chave no idx, retorna seu valor
    if (chaveNoIdx.has_value() && chaveNoIdx.value() == chave) {
      return std::get<1>(items.at(idx).value());
    }

    // Não encontrou a chave, retorna valor de falha
    return VALOR_FALHA;
  }

  optional<int> remove(std::string chave) {
    auto idx{this->hash(chave) % items.size()};
    auto it = items.at(idx);

    std::optional<std::string> chaveNoIdx;
    if (it.has_value())
      chaveNoIdx = std::get<0>(it.value());
    else
      chaveNoIdx = std::nullopt;
    int colisoes{0};

    // Verifica a próxima enquanto:
    // 1: não possuir chave ou possuir chave diferente da requisitada
    // 2: não percorreu toda a tabela

    // print("procurando {} no idx {}\n", chave, idx);

    while ((chaveNoIdx.has_value() && chaveNoIdx.value() != chave) &&
           (colisoes < items.size() - 1)) {
      idx = (idx + 1) % items.size();
      chaveNoIdx = std::get<0>(items.at(idx).value());
      colisoes++;
    }

    // Achou a chave
    if (chaveNoIdx.has_value() && chaveNoIdx.value() == chave) {
      // print("removendo {} no idx {}\n", chave, idx);

      auto valor = std::get<1>(items.at(idx).value());
      // Marca posição como removida
      this->items.at(idx) = REMOVIDO;

      this->N--;
      return valor;
    }

    // Chave não estava na tabela
    return std::nullopt;
  }

  int tamanho() { return N; }

 private:
  std::vector<chaveValor_t> items;
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
    auto item = this->items.at(idx);
    if (item.has_value()) return std::get<0>(item.value());
    return std::nullopt;
  }

  optional<int> valorNoIndex(int idx) {
    auto item = this->items.at(idx);
    if (item.has_value()) return std::get<1>(item.value());
    return std::nullopt;
  }

  bool indexRemovido(int idx) {
    return (this->items.at(idx).has_value() &&
            this->items.at(idx).value() == REMOVIDO);
  }

  void aumentaTabela() {
    std::vector<chaveValor_t> novaTabela;
    novaTabela.resize(items.size() * 2, VAZIO);
    // print("\nAumentando tamanho {} -> {}\n", items.size(), items.size() * 2);

    for (auto i = 0; i < items.size(); i++) {
      auto it = items.at(i);

      if (it.has_value()) {
        ulong idx = i;
        if (it.value() != REMOVIDO)
          idx = hash(std::get<0>(it.value())) % novaTabela.size();
        novaTabela.at(idx) = it.value();
      }
    }

    items = novaTabela;
  }
};
}  // namespace tbh
