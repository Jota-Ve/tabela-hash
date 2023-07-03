
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
  tbh::TabelaHash tb;

  std::ofstream arquivo;

  arquivo.open("../benchmark/inserir.csv", std::ios::out);
  arquivo << "TamanhoTabela"
          << ";"
          << "MicroSeg"
          << ";"
          << "Chave"
          << ";"
          << "Valor"
          << "\n";

  std::array<int, tbh::TAM> arr{};
  arrayEmbaralhado(&arr);

  for (int i = 0; i < tbh::TAM; i++) {
    auto chave = std::to_string(arr.at(i));
    auto valor = i;

    auto inicio = std::chrono::steady_clock::now();  // NOLINT
    tb.insere(chave, valor);
    auto fim = std::chrono::steady_clock::now();

    auto duracao = fim - inicio;
    auto microSeg =
        std::chrono::duration_cast<std::chrono::microseconds>(duracao).count();

    arquivo << tb.tamanho() << ";" << microSeg << ";" << chave << ";" << valor
            << "\n";
  }
}
void benchmarkRemover() {
  tbh::TabelaHash tb;

  std::ofstream arquivo;

  arquivo.open("../benchmark/remover.csv", std::ios::out);
  arquivo << "TamanhoTabela"
          << ";"
          << "MicroSeg"
          << ";"
          << "Chave"
          << ";"
          << "Valor"
          << "\n";

  std::array<int, tbh::TAM> arr{};
  arrayEmbaralhado(&arr);

  for (int i = 0; i < tbh::TAM; i++) {
    auto chave = std::to_string(arr.at(i));
    auto valor = i;

    auto inicio = std::chrono::steady_clock::now();  // NOLINT
    tb.insere(chave, valor);
    auto fim = std::chrono::steady_clock::now();

    auto duracao = fim - inicio;
    auto microSeg =
        std::chrono::duration_cast<std::chrono::microseconds>(duracao).count();

    arquivo << tb.tamanho() << ";" << microSeg << ";" << chave << ";" << valor
            << "\n";
  }
}
};  // namespace bcmk
