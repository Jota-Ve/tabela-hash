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
#include <string>
#include <tuple>

//

using fmt::print;  // NOLINT
using scn::scan;   // NOLINT
namespace tbh {

constexpr int TAM{6047};
constexpr int VALOR_FALHA{0};

class TabelaHash {
  /* Lista do que fazer
  TODO: Implementar redimensionamento da tabela
  TODO: Melhorar função de hash
  TODO: Cronometrar perfomance da tabela

  ?: Implementar biblioteca de testes ?
  */

 public:
  bool insere(std::string chave, int valor) {
    // Se estiver cheia, recusa inserção
    if (this->tamanho() == TAM) return false;

    int idx = this->hash(chave);
    auto idxChave = this->chaveNoIndex(idx);

    int cont{0};
    // Enquanto idx estiver ocupado com outra chave, atualiza idx
    while ((idxChave != "") && (idxChave != chave)) {
      idx = (idx + 1) % TAM;
      idxChave = this->chaveNoIndex(idx);
      cont++;
    }
    // if (cont) print("\"{}\": {}\n", chave, cont);

    // Guardando novo chave-valor ou atualizando valor de chave existente
    this->items.at(idx) = std::make_tuple(chave, valor);
    this->N++;

    return true;
  }

  int recupera(std::string chave) {
    //
    int idx{this->hash(chave)};
    auto idxChave{this->chaveNoIndex(idx)};
    int cont{0};

    // Verifica a próxima enquanto possuir chave, ela for diferente da
    // solicitada e não percorreu toda a tabela
    while ((idxChave != "") && (idxChave != chave) && (cont < TAM)) {
      idx = (idx + 1) % TAM;
      idxChave = this->chaveNoIndex(idx);
      cont++;
    }

    // Se encontrou a chave no idx, retorna seu valor
    if (idxChave == chave) return this->valorNoIndex(idx);

    // Não encontrou a chave, retorna valor de falha
    return VALOR_FALHA;
  }

  int tamanho() { return this->N; }

 private:
  std::array<std::tuple<std::string, int>, TAM> items;
  int N{0};

  int hash(std::string chave) {
    int soma{1};
    for (auto x : chave) {
      soma *= static_cast<int>(x) + 1;
    }
    return static_cast<int>((soma) % TAM);

    auto idx = static_cast<int>(chave.length()) % TAM;
    return idx;
  }

  std::string chaveNoIndex(int idx) { return std::get<0>(this->items.at(idx)); }

  int valorNoIndex(int idx) { return std::get<1>(this->items.at(idx)); }
};
}  // namespace tbh