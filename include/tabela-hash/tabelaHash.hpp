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
#include <iostream>
#include <string>
#include <tuple>
//

using fmt::print;  // NOLINT
using scn::scan;   // NOLINT

constexpr int TAM{10};

class TabelaHash {
 public:
  bool insere(std::string chave, int valor) {
    if (this->tamanho() == TAM) return false;

    int idx = this->hash(chave);
    while (std::get<0>(this->items.at(idx)) != "" &&
           std::get<0>(this->items.at(idx)) != chave)
      idx++;

    this->items.at(idx) = std::make_tuple(chave, valor);
    this->N++;
    return true;
  }

  int recupera(std::string chave) {
    int idx = this->hash(chave);
    int cont{0};
    while (std::get<0>(this->items.at(idx)) != chave &&
           cont < this->tamanho()) {
      idx++;
      cont++;
    }

    if (std::get<0>(this->items.at(idx)) == chave)
      return std::get<1>(this->items.at(idx));

    return 0;
  }

  int tamanho() { return this->N; }

 private:
  std::array<std::tuple<std::string, int>, TAM> items;
  int N{0};

  int hash(std::string chave) { return static_cast<int>(chave.length()) % TAM; }
};
