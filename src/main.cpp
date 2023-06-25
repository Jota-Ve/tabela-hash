// SPDX-License-Identifier:  MIT
// Copyright (C) 2023 - Prof. Igor Machado Coelho
// ?(jota-ve): Devo atualizar o copyright acima para os integrantes do grupo

#include <memory>
//
#include <fmt/core.h>  // NOLINT

#include <tabela-hash/tabelaHash.hpp>

using fmt::print;

int main() {
  TabelaHash tabela;

  tabela.insere("teste1", 1);
  tabela.insere("teste2", 2);
  tabela.insere("teste3", 3);
  tabela.insere("este valor deveria ser 47", 47);

  print("teste1: {}\n", tabela.recupera("teste1"));
  print("teste2: {}\n", tabela.recupera("teste2"));
  print("teste3: {}\n", tabela.recupera("teste3"));
  print("este valor deveria ser 47: {}\n",
        tabela.recupera("este valor deveria ser 47"));
  return 0;
}

// Ctrl+Shift+P
// CMake: build
// CMake: configure
// CMake: debug
// [aplicacao]
