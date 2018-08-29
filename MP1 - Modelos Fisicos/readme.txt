//EA872 - LAB1
// Mariane Tiemi Iguti (RA147279) e Gabriela Akemi Shima (RA135819)

Foram adicionados novos atributos de aceleração e força para a classe corpo no model, além de seus respectivos métodos get. O calculo de obtenção da aceleração provém da modelagem de um sistema massa-mola amortecido. 

Considerando a força resultante do sistema logo quando a força externa é zero, obtemos que a resultante atuando no corpo é dada por F = - k*x - b*v = m*a, que é modelado no método update da fĩsica no controller. E a impressão é alterada diretamente no main. Todas alterações e adições de código estão acompanhadas de comentários no padrão "//edit: comentario".