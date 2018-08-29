//EA872 - LAB2
// Mariane Tiemi Iguti (RA147279) e Gabriela Akemi Shima (RA135819)
#include <vector>

#include "oo_model.hpp"

#include <ncurses.h>

Corpo::Corpo(float massa, float velocidade, float posicao, float aceleracao, float forca, float k, float b) {
  this->massa = massa;
  this->velocidade = velocidade;
  this->posicao = posicao;
  this->aceleracao = aceleracao; //edit: novo atributo aceleracao
  this->forca = forca;//edit: novo atributo forca
  this->k = k; //edit: novo atributo k: constante da mola
  this->b = b; //edit: novo atributo b: constante de amortecimento

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
float Corpo::get_k() { //edit: Add método de get para novo parametro k: constante da mola
  return this->k;
}

float Corpo::get_b() { //edit: Add método de get para novo parametro b: constante de amortecimento
  return this->b;
}

ListaDeCorpos::ListaDeCorpos() {
  this->corpos = new std::vector<Corpo *>(0);
}

void ListaDeCorpos::hard_copy(ListaDeCorpos *ldc) {
  std::vector<Corpo *> *corpos = ldc->get_corpos();

  for (int k=0; k<corpos->size(); k++) {
    Corpo *c = new Corpo( (*corpos)[k]->get_massa(),\
                          (*corpos)[k]->get_posicao(),\
                          (*corpos)[k]->get_velocidade(),\
                          (*corpos)[k]->get_aceleracao(),\
                          (*corpos)[k]->get_forca(),\
                          (*corpos)[k]->get_k(),\
                          (*corpos)[k]->get_b()
                        );
    this->add_corpo(c);
  }

}


void ListaDeCorpos::add_corpo(Corpo *c) {
  (this->corpos)->push_back(c);
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

  for (int i = 0; i < (*c).size(); i++) {

    float k_corpo = (*c)[i]->get_k(); //edit: Add constante da mola N/m
    float b_corpo = (*c)[i]->get_b(); //edit: Add coeficiente de amortecimento

    float new_aceleracao = (- b_corpo*(*c)[i]->get_velocidade() - k_corpo*(*c)[i]->get_posicao() ) / (*c)[i]->get_massa();//edit: Add Calcula aceleracao a partir do modelo a=(-b*v-k*x)/m
    float new_vel = (*c)[i]->get_velocidade() + (float)deltaT * (new_aceleracao)/1000; //edit: Trocamos a gravidade = - 10 por aceleracao calculada
    float new_pos = (*c)[i]->get_posicao() + (float)deltaT * new_vel/1000;
    float new_forca = (*c)[i]->get_aceleracao() * (*c)[i]->get_massa(); //edit: Add Calcula a forca
    (*c)[i]->update(new_vel, new_pos, new_aceleracao, new_forca); //edit: Atualiza os novos parâmetros de aceleracao e forca
  }
}

Tela::Tela(ListaDeCorpos *ldc, int maxI, int maxJ, float maxX, float maxY) {
  this->lista = ldc;
  this->lista_anterior = new ListaDeCorpos();
  this->lista_anterior->hard_copy(this->lista);
  this->maxI = maxI;
  this->maxJ = maxJ;
  this->maxX = maxX;
  this->maxY = maxY;
}

void Tela::init() {
  initscr();			       /* Start curses mode 		*/
	raw();				         /* Line buffering disabled	*/
  curs_set(0);           /* Do not display cursor */
}

void Tela::update() {
  int i;

  std::vector<Corpo *> *corpos_old = this->lista_anterior->get_corpos();

  // Apaga corpos na tela
  for (int k=0; k<corpos_old->size(); k++)
  {
    i = (int) ((*corpos_old)[k]->get_posicao()) * \
        (this->maxI / this->maxX);
    if(move(i,k) != ERR)   /* Move cursor to position */
    echochar(' ');  /* Prints character, advances a position */
  }

  // Desenha corpos na tela
  std::vector<Corpo *> *corpos = this->lista->get_corpos();

  for (int k=0; k<corpos->size(); k++)
  {
    i = (int) ((*corpos)[k]->get_posicao()) * \
        (this->maxI / this->maxX);
    if(move(i,k) != ERR) /* Move cursor to position */
      echochar('*');  /* Prints character, advances a position */

    // Atualiza corpos antigos
    (*corpos_old)[k]->update(  (*corpos)[k]->get_velocidade(),\
                               (*corpos)[k]->get_posicao(),\
                               (*corpos)[k]->get_aceleracao(),\
                               (*corpos)[k]->get_forca()
                             );
  }

  // Atualiza tela
  refresh();
}

void Tela::stop() {
  endwin();
}

Tela::~Tela() {
  this->stop();;
}
