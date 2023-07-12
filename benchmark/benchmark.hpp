
#pragma once

#include <bits/ranges_algo.h>
#include <fmt/core.h>

#include <algorithm>
#include <cassert>
#include <chrono>  //NOLINT
#include <fstream>
// #include <iomanip>
#include <ios>
// #include <iostream>
#include <array>
#include <tuple>

#include "../include/tabela-hash/tabelaHash.hpp"

using fmt::print;  // NOLINT

namespace bcmk {

constexpr auto TAM{1000000};

void benchmarkInserir() {
  print("benchmark inserir\n");

  tbh::TabelaHash tb;

  std::ofstream arquivo;

  arquivo.open("../benchmark/test-inserir.csv", std::ios::out);
  arquivo << "TamanhoTabela"
          << ";"
          << "NanoSeg"
          << "\n";

  for (auto i = 0; i < TAM; i++) {
    auto chave = std::to_string(i);
    auto valor = i;

    auto tabTamanho = tb.tamanho();

    auto inicio = std::chrono::steady_clock::now();  // NOLINT
    auto retorno = tb.insere(chave, valor);
    auto fim = std::chrono::steady_clock::now();

    assert(retorno);  // NOLINT

    auto duracao = fim - inicio;
    auto NanoSeg =
        std::chrono::duration_cast<std::chrono::nanoseconds>(duracao).count();

    arquivo << tabTamanho << ";" << NanoSeg << "\n";
  }
  arquivo.close();
}

void benchmarkBusca() {
  print("benchmark buscar\n");

  tbh::TabelaHash tb;

  std::ofstream arquivo;

  arquivo.open("../benchmark/test-buscar.csv", std::ios::out);
  arquivo << "TamanhoTabela"
          << ";"
          << "NanoSeg"
          << "\n";

  for (int i = 0; i < TAM; i++) {
    auto chave = std::to_string(i);
    auto valor = i;
    auto retornoInsere = tb.insere(chave, valor);
    assert(retornoInsere);  // NOLINT
    auto tabTamanho = tb.tamanho();

    auto inicio = std::chrono::steady_clock::now();  // NOLINT

    auto retorno = tb.busca(chave);

    auto fim = std::chrono::steady_clock::now();

    // print("{}: {}\n", chave, i);
    assert(retorno.has_value());  // NOLINT

    auto duracao = fim - inicio;
    auto NanoSeg =
        std::chrono::duration_cast<std::chrono::nanoseconds>(duracao).count();

    arquivo << tabTamanho << ";" << NanoSeg << "\n";
  }
  arquivo.close();
}

void benchmarkRemover() {
  print("benchmark remover\n");

  tbh::TabelaHash tb;

  std::ofstream arquivo;

  arquivo.open("../benchmark/test-remover.csv", std::ios::out);
  arquivo << "TamanhoTabela"
          << ";"
          << "NanoSeg"
          << "\n";

  for (int i = 0; i < TAM; i++) {
    auto chave = std::to_string(i);
    auto valor = i;
    tb.insere(chave, valor);
  }

  std::array<std::tuple<int, int>, TAM> tempoRemocao;
  for (int i = 0; i < TAM; i++) {
    auto chave = std::to_string(i);
    auto valor = i;

    auto tabTamanho = tb.tamanho();
    auto inicio = std::chrono::steady_clock::now();  // NOLINT
    auto retorno = tb.remove(chave);
    auto fim = std::chrono::steady_clock::now();

    assert(retorno);  // NOLINT

    auto duracao = fim - inicio;
    auto NanoSeg =
        std::chrono::duration_cast<std::chrono::nanoseconds>(duracao).count();

    tempoRemocao.at(i) = std::make_tuple(tb.tamanho(), NanoSeg);
  }

  for (int i = tempoRemocao.size() - 1; i >= 0; i--)
    arquivo << std::get<0>(tempoRemocao.at(i)) << ";"
            << std::get<1>(tempoRemocao.at(i)) << "\n";

  arquivo.close();
}
};  // namespace bcmk
