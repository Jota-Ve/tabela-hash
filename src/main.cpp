// SPDX-License-Identifier:  MIT
// Copyright (C) 2023 - Prof. Igor Machado Coelho
// ?(jota-ve): Devo atualizar o copyright acima para os integrantes do grupo

#include <cassert>
#include <memory>
//
#include <fmt/core.h>  // NOLINT

#include <../benchmark/benchmark.hpp>
#include <../tests/test.hpp>
#include <tabela-hash/tabelaHash.hpp>

using fmt::print;

int main() {
  // testTudo();
  bcmk::benchmarkInserir();
  return 0;
}

// Ctrl+Shift+P
// CMake: build
// CMake: configure
// CMake: debug
// [aplicacao]
