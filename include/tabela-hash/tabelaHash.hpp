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

constexpr int TAM{3};

class TabelaHash {
 public:
  bool insere(std::string chave, int valor) {
    print("Inserindo chave \"{}\"\n", chave);
    if (this->tamanho() == TAM) {
      print("Tabela Cheia!\n");
      return false;
    }

    int idx = this->hash(chave);
    while (std::get<0>(this->items.at(idx)) != "" &&
           std::get<0>(this->items.at(idx)) != chave) {
      print("idx {} já contém chave \"{}\", indo para o próximo idx...\n", idx,
            std::get<0>(this->items.at(idx)));
      idx++;
    }

    print("Guardando \"{}\" no idx {}\n", chave, idx);
    this->items.at(idx) = std::make_tuple(chave, valor);
    this->N++;
    print("\n");
    return true;
  }

  int recupera(std::string chave) {
    print("Recuperando chave \"{}\"\n", chave);
    int idx = this->hash(chave);
    int cont{0};
    while (std::get<0>(this->items.at(idx)) != chave &&
           cont < this->tamanho()) {
      print("idx {} contém chave \"{}\", indo para o próximo idx...\n", idx,
            std::get<0>(this->items.at(idx)));
      idx++;
      cont++;
    }

    if (std::get<0>(this->items.at(idx)) == chave) {
      print("Encontrou chave \"{}\" no idx {}\n\n", chave, idx);
      return std::get<1>(this->items.at(idx));
    }

    print("Chave \"{}\" não está na tabela\n", chave);
    print("\n");

    return 0;
  }

  int tamanho() { return this->N; }

 private:
  std::array<std::tuple<std::string, int>, TAM> items;
  int N{0};

  int hash(std::string chave) {
    auto idx = static_cast<int>(chave.length()) % TAM;
    print("hash(\"{}\") -> {}\n", chave, idx);
    print("\n");
    return idx;
  }
};
