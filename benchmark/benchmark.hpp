
#pragma once

#include <bits/ranges_algo.h>
#include <fmt/core.h>

#include <algorithm>
#include <chrono>  //NOLINT
#include <fstream>
// #include <iomanip>
#include <ios>
// #include <iostream>
#include <array>

#include "../include/tabela-hash/tabelaHash.hpp"

using fmt::print;  // NOLINT

namespace bcmk {

void arrayEmbaralhado(std::array<int, tbh::TAM>* arr) {
  for (auto i = 0; i < arr->size(); i++) arr->at(i) = i;
  std::random_shuffle(arr->begin(), arr->end());
}

void benchmarkInserir() {
  print("benchmark inserir\n");

  tbh::TabelaHash tb;

  std::ofstream arquivo;

  arquivo.open("../benchmark/inserir.csv", std::ios::out);
  arquivo << "TamanhoTabela"
          << ";"
          << "NanoSeg"
          << "\n";

  for (auto i = 0; i < tbh::TAM; i++) {
    auto chave = std::to_string(i);
    auto valor = i;

    auto tabTamanho = tb.tamanho();

    auto inicio = std::chrono::steady_clock::now();  // NOLINT
    tb.insere(chave, valor);
    auto fim = std::chrono::steady_clock::now();

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

  arquivo.open("../benchmark/buscar.csv", std::ios::out);
  arquivo << "TamanhoTabela"
          << ";"
          << "NanoSeg"
          << "\n";

  for (int i = 0; i < tbh::TAM; i++) {
    auto chave = std::to_string(i);
    auto valor = i;
    tb.insere(chave, valor);
    auto tabTamanho = tb.tamanho();

    auto inicio = std::chrono::steady_clock::now();  // NOLINT

    tb.busca(chave);

    auto fim = std::chrono::steady_clock::now();

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

  arquivo.open("../benchmark/remover.csv", std::ios::out);
  arquivo << "TamanhoTabela"
          << ";"
          << "NanoSeg"
          << "\n";

  // for (int i = 0; i < tbh::TAM; i++) {
  //   auto chave = std::to_string(i);
  //   auto valor = i;
  //   tb.insere(chave, valor);
  // }

  for (int i = 0; i < tbh::TAM; i++) {
    auto chave1 = std::to_string(i);
    auto chave2 = std::to_string(i + 1);
    auto valor = i;

    tb.insere(chave1, valor);
    tb.insere(chave2, valor);

    auto tabTamanho = tb.tamanho();
    auto inicio = std::chrono::steady_clock::now();  // NOLINT
    tb.remove(chave2);
    auto fim = std::chrono::steady_clock::now();

    auto duracao = fim - inicio;
    auto NanoSeg =
        std::chrono::duration_cast<std::chrono::nanoseconds>(duracao).count();

    arquivo << tabTamanho << ";" << NanoSeg << "\n";
  }

  arquivo.close();
}
};  // namespace bcmk
