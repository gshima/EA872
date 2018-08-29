//EA872 - LAB2
// Mariane Tiemi Iguti (RA147279) e Gabriela Akemi Shima (RA135819)
#ifndef OO_MODEL_HPP
#define OO_MODEL_HPP

class Corpo {
  private:
  float massa;
  float velocidade;
  float posicao;
  float aceleracao;
  float forca;
  float k;
  float b;

  public:
  Corpo(float massa, float velocidade, float aceleracao, float forca,float posicao, float k, float b);
  void update(float nova_velocidade, float nova_posicao, float nova_aceleracao, float nova_forca);
  float get_massa();
  float get_velocidade();
  float get_posicao();
  float get_aceleracao(); //edit: Add metodo get para novo atributo
  float get_forca(); //edit: Add metodo get para novo atributo
  float get_k(); //edit: Add metodo get para novo atributo
  float get_b(); //edit: Add metodo get para novo atributo

};

class ListaDeCorpos {
 private:
    std::vector<Corpo*> *corpos;

  public:
    ListaDeCorpos();
    void hard_copy(ListaDeCorpos *ldc);
    void add_corpo(Corpo *c);
    std::vector<Corpo*> *get_corpos();
};

class Fisica {
  private:
    ListaDeCorpos *lista;

  public:
    Fisica(ListaDeCorpos *ldc);
    void add_corpo(Corpo *c);
    void update(float deltaT);
};

class Tela {
  private:
    ListaDeCorpos *lista, *lista_anterior;
    int maxI, maxJ;
    float maxX, maxY;

  public:
    Tela(ListaDeCorpos *ldc, int maxI, int maxJ, float maxX, float maxY);
    ~Tela();
    void stop();
    void init();
    void update();
};



#endif
