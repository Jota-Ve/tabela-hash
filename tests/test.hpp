

#include <cassert>
//
#include <fmt/core.h>  // NOLINT

#include <tabela-hash/tabelaHash.hpp>

using fmt::print;  // NOLINT

void testRecuperaChaveComTabelaVaziaIgualZero() {
  tbh::TabelaHash tabela;
  assert(!tabela.recupera("a").has_value());  // NOLINT
  print("Sucesso: testRecuperaChaveComTabelaVaziaIgualZero()\n");
}

void testRecuperaChaveInexistente() {
  tbh::TabelaHash tabela;

  tabela.insere("a", 1);
  assert(tabela.recupera("b") == tbh::VALOR_FALHA);  // NOLINT
  print("Sucesso: testRecuperaChaveInexistente()\n");
}

void testRecupera() {
  tbh::TabelaHash tabela;

  assert(tabela.insere("teste1", 1) == true);  // NOLINT
  assert(tabela.insere("teste2", 2) == true);  // NOLINT
  assert(tabela.insere("teste3", 3) == true);  // NOLINT

  assert(tabela.recupera("teste1") == 1);  // NOLINT
  assert(tabela.recupera("teste2") == 2);  // NOLINT
  assert(tabela.recupera("teste3") == 3);  // NOLINT

  print("Sucesso: testRecupera()\n");
}

void testInsereTabelaCheia() {
  tbh::TabelaHash tabela;

  for (int i = 1; i <= tbh::TAM; i++) {
    assert(tabela.insere(std::to_string(i), i) == true);  // NOLINT
    assert(tabela.tamanho() == i);                        // NOLINT
  }

  assert(tabela.tamanho() == tbh::TAM);          // NOLINT
  assert(tabela.insere("iqhoqb", 10) == false);  // NOLINT
  print("Sucesso: testInsereTabelaCheia()\n");
}

void testRemoveTabelaVazia() {
  tbh::TabelaHash tabela;

  assert(!tabela.remove("a").has_value());  // NOLINT
  print("Sucesso: testRemoveTabelaVazia()\n");
}

void testRemove() {
  tbh::TabelaHash tabela;

  tabela.insere("a", 1);                      // NOLINT
  tabela.remove("a");                         // NOLINT
  assert(!tabela.recupera("a").has_value());  // NOLINT
  assert(tabela.tamanho() == 0);              // NOLINT

  print("Sucesso: testRemoveTabelaVazia()\n");
}

void testTudo() {
  testRecuperaChaveComTabelaVaziaIgualZero();
  testRecuperaChaveInexistente();
  testRecupera();
  testInsereTabelaCheia();
  testRemoveTabelaVazia();
  testRemove();
}
