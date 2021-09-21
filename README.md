# Modelo de Cozinha em computação gráfica

## Trabalho de computação gráfica sobre a modelagem de uma cozinha.

## Trabalho realizado pela dupla [Ana Carolina Nesso Guedes](https://github.com/carolnesso) e [Rayssa Rosseno](https://github.com/RayssaRoseno)

Para compilar, por padrão com o uso de 4 threads, utilize o comando `make build`.
Utilize `make compile` para compilar com um único thread.
Para compilar o arquivos e logo após executar o binário, utilize o comando `make run`.
Para compilar sem mensagens de log, utilize o comand `make silent <comando>`.

O programa funciona tanto no Windows quanto no Linux, mas no linux as bibliotecas devem ser instaladas utilizando o comando `sudo apt install freeglut3 freeglut3-dev`.

Os controles de movimento são com as teclas `wasd`, e o mouse.

Para movimentação vertical, utilize `barra de espaço` para ir para cima e `b` para ir para baixo.

Para abrir e fechar a portas, pressione a tecla `p` para abrir, `o` para fechar, e para abrir e fechar as janelas, pressione `l` para abrir e `m` para fechar.
    No total são 3 objetos que podem ser abertos/fechados, sendo eles duas janelas e uma porta.

Para ligar ou desligar a luminária, utilize a tecla `k`.

## Requisitos da AB1

 - [:heavy_check_mark:] Poder navegar pela cozinha utilizando o mouse e teclado
 - [:heavy_check_mark:] Além de mais 5 objetos à sua escolha
 - [:heavy_check_mark:] Uma porta deverá poder abrir e fechar com o teclado
 - [:heavy_check_mark:] Uma janela deverá abrir e fechar como teclado

## Requisitos da AB2

 - [:heavy_check_mark:] Modelar e apresentar um quadro com mapeamento de textura
 - [:heavy_check_mark:] Ventilador de teto com hélice girando no sentido horário em velocidade baixa
 - [:heavy_check_mark:] Luminária spot em cima da mesa
 - [:heavy_check_mark:] Iluminação especular e difusa na modelagem
 - [:heavy_check_mark:] Aplicar mapeamento de textura em, pelo menos, 5 objetos

## Referências:

* [Referência do monitor da disciplina](https://github.com/valeriojr/COMP269/blob/master/opengl.c)
* [Básicos do opengl](https://github.com/valeriojr/monitoria-cg/blob/master/material/book.pdf)
* [Camera - Getting started](https://learnopengl.com/Getting-started/Camera)
* [Viewing obj file format](https://en.wikipedia.org/wiki/Wavefront_.obj_file)
* [Applying MSAA](https://learnopengl.com/Advanced-OpenGL/Anti-Aliasing)
* [Textures in OpenGL](https://www.youtube.com/watch?v=n4k7ANAFsIQ)