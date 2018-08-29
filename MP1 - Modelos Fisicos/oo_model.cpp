//EA872 - LAB1
// Mariane Tiemi Iguti (RA147279) e Gabriela Akemi Shima (RA135819)
#include <vector>
#include "oo_model.hpp"
#include <iostream>

Corpo::Corpo(float massa, float velocidade, float posicao, float aceleracao, float forca) { //edit: Add novos parametros de aceleracao e forca
  this->massa = massa;
  this->velocidade = velocidade;
  this->posicao = posicao; 
  this->aceleracao = aceleracao; //edit: novo atributo aceleracao
  this->forca = forca;//edit: novo atributo forca
}

void Corpo::update(float nova_velocidade, float nova_posicao, float nova_aceleracao, float nova_forca) { //edit: Add novos parametros de aceleracao e forca
  this->velocidade = nova_velocidade;
  this->posicao = nova_posicao;
  this->aceleracao = nova_aceleracao; //edit: novo atributo aceleracao
  this->forca = nova_forca; //edit: novo atributo forca
}

float Corpo::get_massa() {
  return this->massa;
}

float Corpo::get_velocidade() {
  return this->velocidade;
}

float Corpo::get_posicao() {
  return this->posicao;
}

float Corpo::get_aceleracao() { //edit: Add método de get para novo parametro aceleracao
  return this->aceleracao;
}

float Corpo::get_forca() { //edit: Add método de get para novo parametro forca
  return this->forca;
}

ListaDeCorpos::ListaDeCorpos() {
  this->corpos = new std::vector<Corpo *>(0);
}

void ListaDeCorpos::add_corpo(Corpo *c) {
  (this->corpos)->push_back(c);
  std::cout << "Agora tenho: " << this->corpos->size() << " elementos" << std::endl;
}

std::vector<Corpo*> *ListaDeCorpos::get_corpos() {
  return (this->corpos);
}

Fisica::Fisica(ListaDeCorpos *ldc) {
  this->lista = ldc;
}

void Fisica::update(float deltaT) {
  // Atualiza parametros dos corpos!
  std::vector<Corpo *> *c = this->lista->get_corpos();
  
  float k = 100; //edit: Add constante da mola N/m
  float b = 0.5; //edit: Add coeficiente de amortecimento
  
  for (int i = 0; i < (*c).size(); i++) {
    float new_aceleracao = (- b*(*c)[i]->get_velocidade() - k*(*c)[i]->get_posicao() ) / (*c)[i]->get_massa();//edit: Add Calcula aceleracao a partir do modelo a=(-b*v-k*x)/m
    float new_vel = (*c)[i]->get_velocidade() + (float)deltaT * (new_aceleracao)/1000; //edit: Trocamos a gravidade = - 10 por aceleracao calculada
    float new_pos = (*c)[i]->get_posicao() + (float)deltaT * new_vel/1000; 
    float new_forca = (*c)[i]->get_aceleracao() * (*c)[i]->get_massa(); //edit: Add Calcula a forca
    (*c)[i]->update(new_vel, new_pos, new_aceleracao, new_forca); //edit: Atualiza os novos parâmetros de aceleracao e forca
  }
}


