
#pragma once

#include <cassert>
//
#include <fmt/core.h>  // NOLINT

#include <string>
#include <tabela-hash/tabelaHash.hpp>

using fmt::print;  // NOLINT

void testBuscaChaveComTabelaVaziaIgualZero() {
  tbh::TabelaHash tabela;
  assert(!tabela.busca("a").has_value());  // NOLINT
  print("Sucesso: testBuscaChaveComTabelaVaziaIgualZero()\n");
}

void testBuscaChaveInexistente() {
  tbh::TabelaHash tabela;
  tabela.insere("a", 1);
  assert(tabela.busca("b") == tbh::VALOR_FALHA);  // NOLINT
  print("Sucesso: testBuscaChaveInexistente()\n");
}

void testBusca() {
  tbh::TabelaHash tabela;

  assert(tabela.insere("teste1", 1) == true);  // NOLINT
  assert(tabela.insere("teste2", 2) == true);  // NOLINT
  assert(tabela.insere("teste3", 3) == true);  // NOLINT

  assert(tabela.busca("teste1") == 1);  // NOLINT
  assert(tabela.busca("teste2") == 2);  // NOLINT
  assert(tabela.busca("teste3") == 3);  // NOLINT

  print("Sucesso: testBusca()\n");
}

void testCrescimentoDaTabela() {
  tbh::TabelaHash tabela;

  for (int i = 1; i <= tbh::TAM_INICIAL; i++) {
    assert(tabela.insere(std::to_string(i), i) == true);  // NOLINT
    assert(tabela.tamanho() == i);                        // NOLINT
  }

  assert(tabela.insere("iqhoqb", 10) == true);       // NOLINT
  assert(tabela.tamanho() == tbh::TAM_INICIAL + 1);  // NOLINT
  print("Sucesso: testCrescimentoDaTabela()\n");
}

void testEncontraItemAposRedimensionarTabela() {
  tbh::TabelaHash tabela;

  for (int i = 0; i < tbh::TAM_INICIAL * 2; i++)
    assert(tabela.insere(std::to_string(i), i) == true);  // NOLINT

  for (int i = 0; i < tbh::TAM_INICIAL * 2; i++)
    assert(tabela.busca(std::to_string(i)).value_or(-1) == i);  // NOLINT

  print("Sucesso: testEncontraItemAposRedimensionarTabela()\n");
}

void testRemoveTabelaVazia() {
  tbh::TabelaHash tabela;

  assert(!tabela.remove("a").has_value());  // NOLINT
  print("Sucesso: testRemoveTabelaVazia()\n");
}

void testRemove() {
  tbh::TabelaHash tabela;

  tabela.insere("a", 1);                   // NOLINT
  tabela.remove("a");                      // NOLINT
  assert(!tabela.busca("a").has_value());  // NOLINT
  assert(tabela.tamanho() == 0);           // NOLINT

  print("Sucesso: testRemove()\n");
}

void testRemoveTudo() {
  tbh::TabelaHash tabela;
  for (int i = 0; i < tbh::TAM_INICIAL; i++)
    tabela.insere(std::to_string(i), i);

  for (int i = 0; i < tbh::TAM_INICIAL; i++)
    assert(tabela.remove(std::to_string(i)) == i);  // NOLINT

  assert(tabela.tamanho() == 0);  // NOLINT

  print("Sucesso: testRemoveTudo()\n");
}

void testTudo() {
  testBuscaChaveComTabelaVaziaIgualZero();
  testBuscaChaveInexistente();
  testBusca();
  testCrescimentoDaTabela();
  testEncontraItemAposRedimensionarTabela();
  testRemoveTabelaVazia();
  testRemove();
  testRemoveTudo();
}
