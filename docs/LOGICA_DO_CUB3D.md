# A lógica do cub3D

Conceitos gerais para usar durante a implementação. Não é código pronto:
é o *porquê* e o *como* de cada parte, com as fórmulas que vocês vão precisar.

Sumário:

1. [Visão geral](#1-visão-geral)
2. [O arquivo `.cub`](#2-o-arquivo-cub)
3. [O mapa como grid](#3-o-mapa-como-grid)
4. [Validando o mapa fechado](#4-validando-o-mapa-fechado)
5. [MiniLibX essencial](#5-minilibx-essencial)
6. [Jogador e câmera: vetores](#6-jogador-e-câmera-vetores)
7. [Raycasting passo a passo](#7-raycasting-passo-a-passo)
8. [Texturas](#8-texturas)
9. [Movimento e rotação](#9-movimento-e-rotação)
10. [Loop do jogo e desempenho](#10-loop-do-jogo-e-desempenho)
11. [Memória e saída limpa](#11-memória-e-saída-limpa)
12. [Armadilhas comuns](#12-armadilhas-comuns)
13. [Glossário](#13-glossário)
14. [Referências](#14-referências)

---

## 1. Visão geral

O cub3D desenha uma cena "3D" a partir de um mapa **2D**. Não existe modelo 3D:
para cada coluna da tela, lançamos um raio a partir do jogador, descobrimos
**a que distância** ele bate numa parede e desenhamos uma linha vertical cuja
altura é inversamente proporcional a essa distância. Parede perto → linha alta;
parede longe → linha baixa. Isso é **raycasting**.

```
 argv[1] (.cub)
      │
      ▼
 ┌───────────────── PARSING ─────────────────┐
 │ ler linhas → elementos (NO SO WE EA F C)  │
 │            → mapa → validar               │
 └──────────────────┬────────────────────────┘
                    │ t_scene (contrato)
                    ▼
 ┌──────────────── EXECUÇÃO ─────────────────┐
 │ mlx_init → janela → imagem → texturas     │
 │ jogador (pos, dir, plane) → hooks         │
 │                                           │
 │ mlx_loop ──► game_loop() a cada frame:    │
 │   1. atualizar jogador (teclas)           │
 │   2. chão/teto                            │
 │   3. para cada coluna x: raio → DDA →     │
 │      distância → fatia texturizada        │
 │   4. imagem → janela                      │
 └───────────────────────────────────────────┘
```

---

## 2. O arquivo `.cub`

### 2.1 Estrutura

```
NO ./textures/north.xpm      ← 4 texturas (qualquer ordem)
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
                             ← linhas vazias permitidas entre elementos
F 220,100,0                  ← cor do chão   (R,G,B em [0,255])
C 225,30,0                   ← cor do teto

        1111111111           ← mapa: SEMPRE por último
        1000000001
111111111000N00001           ← espaços fazem parte do mapa
1000000000000000001
1111111111111111111
```

### 2.2 Regras do subject

- Os 6 elementos (`NO`, `SO`, `WE`, `EA`, `F`, `C`) podem vir **em qualquer ordem**.
- O mapa é **sempre o último** elemento.
- Dentro de um elemento, as informações podem ser separadas por **um ou mais espaços**
  (`NO     ./path` é válido).
- O mapa só pode ter `0`, `1`, `N`, `S`, `E`, `W` e espaço.
- Exatamente **um** jogador (`N`, `S`, `E` ou `W`).
- O mapa deve ser **fechado por paredes**.
- Qualquer erro de configuração → `Error\n` + mensagem explícita, e sair limpo.

> 📝 **Nota sobre a tradução:** a versão pt-BR diz que os elementos "devem ser
> separados por uma ou mais linhas vazias", mas o próprio exemplo do subject tem
> `NO/SO/WE/EA` em linhas consecutivas. O original em inglês diz *"can be
> separated"*. Ou seja: linhas vazias entre elementos são **permitidas, não
> obrigatórias**.

### 2.3 Casos ambíguos (decidam e documentem)

O subject não fala de tudo. O importante é **ser consistente e saber defender**.

| Caso | Sugestão |
|---|---|
| Espaços antes do identificador (`   NO ./a.xpm`) | Aceitar |
| Tabs em qualquer lugar | Rejeitar (erro) |
| Espaços dentro da cor (`F 220, 100, 0`) | Rejeitar *ou* aceitar — decidam |
| Sinal (`+10`) ou mais de 3 dígitos (`0010`) | Rejeitar |
| Vírgula sobrando (`220,100,0,`) ou faltando (`220,100`) | Erro |
| Algo depois do caminho (`NO ./a.xpm lixo`) | Erro |
| Mesma textura em duas direções | Aceitar |
| Linhas vazias **antes** do mapa / **depois** do mapa | Aceitar |
| Linha vazia **no meio** do mapa | Erro |
| Qualquer coisa que não seja mapa **depois** do mapa | Erro |
| Mapa começa antes dos 6 elementos estarem definidos | Erro (elemento faltando) |
| Elemento repetido (`NO` duas vezes) | Erro |

### 2.4 Estratégia de leitura

1. Ler o arquivo inteiro em um array de linhas (`scene->lines`), tirando o `\n`.
2. Percorrer as linhas classificando cada uma (`get_element_type`):
   textura, cor, vazia, linha de mapa ou inválida.
3. A **primeira linha de mapa** encerra a fase de elementos. Nesse ponto, todos os
   6 elementos precisam estar definidos.
4. Da primeira linha de mapa em diante, tudo é mapa (com as regras de linha vazia).

Por que ler tudo antes? Porque o mapa precisa de duas passadas (medir largura e
altura, depois copiar) e fica muito mais simples com as linhas em memória.

**Como detectar "não definido"**: `tex_paths[i] == NULL` e cor `== -1`.
Isso também resolve duplicatas: se já está definido e aparece de novo → erro.

### 2.5 Cores

Cada componente vai em 8 bits. A MiniLibX espera a cor como um `int`
`0x00RRGGBB`:

```
color = (r << 16) | (g << 8) | b
```

Exemplo: `220,100,0` → `0xDC6400`.

---

## 3. O mapa como grid

### 3.1 Padding: deixar o mapa retangular

As linhas do mapa têm tamanhos diferentes. Completar todas com `' '` até a
largura da maior linha elimina acessos fora da string:

```
arquivo:              grid (| marca a borda):
    11111             |    11111   |
    10001             |    10001   |
11111S001111          |11111S001111|
100000000001          |100000000001|
111111111111          |111111111111|
```

### 3.2 Sistema de coordenadas

```
        x (coluna) →
      0   1   2   3   4
  0 [ 1 | 1 | 1 | 1 | 1 ]
y 1 [ 1 | 0 | 0 | 0 | 1 ]
↓ 2 [ 1 | 0 | N | 0 | 1 ]
  3 [ 1 | 1 | 1 | 1 | 1 ]

grid[y][x]   ← sempre linha primeiro!
```

- `x` = coluna, cresce para a **direita** (leste).
- `y` = linha, cresce para **baixo** (sul). Isso inverte algumas intuições de
  matemática (o "norte" é `y` negativo).
- Cada célula tem tamanho 1. A posição do jogador é `double`:
  o centro da célula `(x, y)` é `(x + 0.5, y + 0.5)`.
- Para saber em que célula um ponto está: `(int)pos.x`, `(int)pos.y`.

No exemplo acima, o jogador começa em `pos = (2.5, 2.5)`.

---

## 4. Validando o mapa fechado

"Fechado" quer dizer: o jogador nunca consegue alcançar o "lado de fora".
Na prática: **nenhuma célula andável pode encostar no vazio**.

### Abordagem recomendada: verificar vizinhos

Para cada célula `'0'` (e a do spawn):

- se ela está na **borda** do grid (primeira/última linha ou coluna) → aberto;
- se algum dos 4 vizinhos (cima, baixo, esquerda, direita) é `' '` → aberto.

```
 1 1 1 1          1 1 1 1          1 1 1 1
 1 0 0 1          1 0 0 1          1 0 _ 1      _ = espaço
 1 0 0 1          1 0 0 0  ← borda 1 0 0 1
 1 1 1 1          1 1 1 1          1 1 1 1
  válido           inválido         inválido (0 encosta no espaço)
```

Vantagens: sem recursão, sem cópia do grid, e pega **todas** as regiões
(inclusive áreas `0` que o jogador não alcança).

Por que 4 vizinhos bastam? O DDA (seção 7) anda célula por célula só em `x` ou
em `y`, nunca na diagonal, então um raio não "escapa" por um canto.

### Alternativa: flood fill

A partir do spawn, "pintar" recursivamente as células alcançáveis numa cópia
do grid; se a pintura chegar na borda ou num espaço → aberto. Funciona, mas:
precisa de cópia do grid, recursão profunda em mapas grandes e não valida
regiões inalcançáveis. Se usarem, saibam explicar essa diferença.

---

## 5. MiniLibX essencial

### 5.1 Inicialização

```c
mlx = mlx_init();                                   // conexão com o X11
win = mlx_new_window(mlx, W, H, "cub3D");
img = mlx_new_image(mlx, W, H);                     // buffer off-screen
addr = mlx_get_data_addr(img, &bpp, &line_len, &endian);
tex = mlx_xpm_file_to_image(mlx, path, &tw, &th);   // carrega textura
```

Todas podem retornar `NULL` → tratar como erro.

### 5.2 Desenhando em uma imagem (não use `mlx_pixel_put`)

`mlx_pixel_put` desenha direto na janela, um pixel por chamada — é lento demais
e pisca. O certo é escrever na memória da imagem e enviar a imagem inteira uma
vez por frame:

```
offset do pixel (x, y) = y * line_len + x * (bpp / 8)
```

`line_len` pode ser **maior** que `W * 4` (alinhamento) — sempre use `line_len`.
Ler um pixel de textura usa a mesma fórmula (é assim que `get_pixel` funciona).

Depois de desenhar tudo: `mlx_put_image_to_window(mlx, win, img, 0, 0)`.

### 5.3 Eventos

```c
mlx_hook(win, 2,  1L << 0, on_key_press,   game);   // KeyPress
mlx_hook(win, 3,  1L << 1, on_key_release, game);   // KeyRelease
mlx_hook(win, 17, 0,       on_close,       game);   // DestroyNotify (X vermelho)
mlx_loop_hook(mlx, game_loop, game);                // chamado sem parar
mlx_loop(mlx);                                      // nunca retorna
```

Keycodes no Linux (X11): `ESC 65307`, `W 119`, `A 97`, `S 115`, `D 100`,
`← 65361`, `→ 65363`. Estão em `defines.h`. **No macOS os códigos são outros.**

### 5.4 Encerrando (Linux)

```c
mlx_destroy_image(mlx, img);   // para cada imagem (frame + 4 texturas)
mlx_destroy_window(mlx, win);
mlx_destroy_display(mlx);      // existe só na versão Linux
free(mlx);
```

---

## 6. Jogador e câmera: vetores

O jogador é descrito por três vetores 2D:

| Vetor | Significado |
|---|---|
| `pos` | Onde o jogador está no mapa |
| `dir` | Para onde ele olha (comprimento 1) |
| `plane` | O "plano da câmera": perpendicular a `dir`, aponta para a **direita** da tela |

```
                 plane
   -plane  ◄──────┼──────►  +plane         ← "tela" (plano da câmera)
            \     │     /
             \    │dir /
              \   │   /
               \  │  /
                \ │ /
                 pos
```

Os raios saem de `pos` e atravessam a "tela", da borda esquerda
(`dir - plane`) até a borda direita (`dir + plane`).

### Campo de visão (FOV)

```
FOV = 2 * atan(|plane| / |dir|)
```

Com `|dir| = 1` e `|plane| = 0.66` → FOV ≈ **66°** (constante `FOV_PLANE`).

### Orientação inicial

Lembrando que `y` cresce para baixo, e `plane` aponta para a direita do jogador:

| Spawn | `dir` | `plane` |
|---|---|---|
| `N` | `( 0, -1)` | `( 0.66,  0)` |
| `S` | `( 0,  1)` | `(-0.66,  0)` |
| `E` | `( 1,  0)` | `( 0,  0.66)` |
| `W` | `(-1,  0)` | `( 0, -0.66)` |

Teste mental: olhando para o norte, a direita é o leste (`+x`) → `plane = (+0.66, 0)`. ✔

---

## 7. Raycasting passo a passo

Para **cada coluna** `x` da tela (de `0` a `WIN_WIDTH - 1`):

### 7.1 Direção do raio

```
camera_x = 2 * x / WIN_WIDTH - 1          // -1 (esquerda) … 0 (centro) … +1 (direita)
ray.dir  = dir + plane * camera_x
```

### 7.2 DDA — andando pelo grid

**DDA** (*Digital Differential Analysis*) anda pelo grid **de borda em borda**
de célula, sempre escolhendo a próxima borda mais próxima — seja uma linha
vertical (borda em `x`) ou horizontal (borda em `y`). Ele nunca pula uma célula.

Variáveis:

| Nome | Significado |
|---|---|
| `map_x`, `map_y` | Célula atual do raio (começa na célula do jogador) |
| `delta_dist.x` | Quanto o raio anda para cruzar **uma** célula inteira em `x` = `|1 / ray.dir.x|` |
| `delta_dist.y` | Idem em `y` = `|1 / ray.dir.y|` |
| `side_dist.x` | Distância (ao longo do raio) até a **próxima** borda vertical |
| `side_dist.y` | Distância até a **próxima** borda horizontal |
| `step_x`, `step_y` | `+1` ou `-1`: para que lado o raio anda |
| `side` | `0` se bateu numa borda vertical (lado x), `1` se horizontal (lado y) |

Se `ray.dir.x == 0`, `1 / 0` daria divisão por zero: use um valor enorme
(ex.: `1e30`) para `delta_dist.x` — o raio nunca vai "escolher" andar em `x`.

**Passo inicial:**

```
se ray.dir.x < 0:  step_x = -1;  side_dist.x = (pos.x - map_x)       * delta_dist.x
senão:             step_x = +1;  side_dist.x = (map_x + 1.0 - pos.x) * delta_dist.x
(mesma coisa para y)
```

**Loop:**

```
enquanto não bateu:
    se side_dist.x < side_dist.y:
        side_dist.x += delta_dist.x;  map_x += step_x;  side = 0
    senão:
        side_dist.y += delta_dist.y;  map_y += step_y;  side = 1
    se grid[map_y][map_x] == '1': bateu
```

```
  ┌───┬───┬───┬───┐
  │   │   │   │ 1 │   o raio sai de P e cruza bordas
  ├───┼───┼───┼─▲─┤   alternando x e y, conforme a
  │   │   │  ╱│   │   mais próxima. Para quando a
  ├───┼───┼─╱─┼───┤   célula atual é parede.
  │   │  ╱│   │   │
  ├───┼╱──┼───┼───┤
  │  P│   │   │   │
  └───┴───┴───┴───┘
```

Como o mapa foi validado como fechado, o raio **sempre** acha uma parede antes
de sair do grid.

### 7.3 Distância perpendicular (e o efeito "olho de peixe")

Se usássemos a distância real (euclidiana) do jogador até a parede, uma parede
reta à nossa frente pareceria curva: os raios das bordas da tela são mais longos
que o do centro. Isso é o **fisheye**.

A solução é usar a distância **perpendicular ao plano da câmera**, que o DDA já
nos dá de graça:

```
se side == 0:  perp_dist = side_dist.x - delta_dist.x
senão:         perp_dist = side_dist.y - delta_dist.y
```

(subtraímos um `delta_dist` porque o loop avançou um passo além da borda de
contato.)

### 7.4 Altura da parede na tela

```
line_height = (int)(WIN_HEIGHT / perp_dist)
draw_start  = -line_height / 2 + WIN_HEIGHT / 2     → se < 0, vira 0
draw_end    =  line_height / 2 + WIN_HEIGHT / 2     → se >= H, vira H - 1
```

A parede fica centralizada verticalmente (o horizonte é o meio da tela).
Acima de `draw_start` é teto; abaixo de `draw_end` é chão.

---

## 8. Texturas

### 8.1 Escolha da textura (qual face?)

A face atingida depende de `side` e do sinal da direção do raio. Usamos a
convenção **"a textura da direção para onde você está olhando"**
(olhando para o norte → você vê a textura `NO`):

| `side` | condição | textura |
|---|---|---|
| 0 (borda vertical) | `ray.dir.x > 0` (indo para leste) | `EA` |
| 0 | `ray.dir.x < 0` (indo para oeste) | `WE` |
| 1 (borda horizontal) | `ray.dir.y > 0` (indo para sul) | `SO` |
| 1 | `ray.dir.y < 0` (indo para norte) | `NO` |

A convenção oposta ("a face da parede que aponta para o norte usa `NO`") também
é aceitável. O subject só exige que as 4 direções tenham texturas diferentes.
Escolham uma e saibam explicar.

### 8.2 Coluna da textura (`tex_x`)

Primeiro, onde exatamente o raio bateu **ao longo** da parede (`wall_x`, de 0 a 1):

```
se side == 0:  wall_x = pos.y + perp_dist * ray.dir.y
senão:         wall_x = pos.x + perp_dist * ray.dir.x
wall_x = wall_x - floor(wall_x)

tex_x = (int)(wall_x * tex_width)
```

**Espelhamento:** em duas das quatro faces a textura sai invertida. Com o nosso
sistema (y para baixo), inverta quando:

```
(side == 0 && ray.dir.x < 0) || (side == 1 && ray.dir.y > 0)
    → tex_x = tex_width - tex_x - 1
```

> O tutorial do Lode usa outra orientação de eixos, então as condições dele são
> diferentes. **Confiem no teste visual:** as texturas em `textures/` têm a letra
> da direção e um quadrado ciano no **canto superior esquerdo**. Se a letra
> aparecer espelhada ou o quadrado à direita, a condição está errada para aquela face.

### 8.3 Linha da textura (`tex_y`)

A fatia na tela tem `line_height` pixels; a textura tem `tex_height`. Para cada
pixel da tela, avançamos `step` pixels na textura:

```
step    = tex_height / line_height
tex_pos = (draw_start - WIN_HEIGHT / 2 + line_height / 2) * step

para y de draw_start até draw_end:
    tex_y = (int)tex_pos   (limitar a tex_height - 1)
    tex_pos += step
    cor = get_pixel(tex, tex_x, tex_y)
    put_pixel(frame, x, y, cor)
```

O termo `- WIN_HEIGHT / 2 + line_height / 2` corrige o início quando a parede
é maior que a tela (perto demais): `draw_start` foi cortado para 0, mas a
textura deve começar "no meio".

---

## 9. Movimento e rotação

### 9.1 Teclas: pressionar/soltar

Não mova o jogador dentro de `on_key_press`. O repeat do teclado é irregular e
duas teclas ao mesmo tempo não funcionam. Em vez disso:

- `on_key_press` → `keys.w = 1`
- `on_key_release` → `keys.w = 0`
- `game_loop` → a cada frame, aplica o movimento das teclas que estão em `1`.

Resultado: movimento suave e combinações (andar + girar) funcionam.

### 9.2 Andar

```
W:  pos += dir * MOVE_SPEED
S:  pos -= dir * MOVE_SPEED
A:  pos += ( dir.y, -dir.x) * MOVE_SPEED      // perpendicular à esquerda
D:  pos += (-dir.y,  dir.x) * MOVE_SPEED      // perpendicular à direita
```

Teste mental: `dir = (0, -1)` (norte) → `A` = `(-1, 0)` (oeste). ✔

**Colisão:** "colisão com paredes" está na lista de **bônus**, mas no obrigatório
o programa **não pode quebrar** se o jogador sair do mapa (acesso fora do grid →
segfault → nota 0). O mínimo seguro é não deixar a posição entrar em `'1'` nem
em `' '` (é o que `is_walkable` faz). Testar `x` e `y` separadamente faz o
jogador "deslizar" na parede em vez de travar.

### 9.3 Girar

Rotação de um vetor por um ângulo `a` (matriz de rotação):

```
x' = x * cos(a) - y * sin(a)
y' = x * sin(a) + y * cos(a)
```

Aplicar em **`dir` e em `plane`** (senão o FOV deforma). Guardar o `x` antigo
antes de sobrescrever, porque o cálculo de `y'` usa o `x` original.

Com `y` para baixo, ângulo **positivo** gira para a **direita** (sentido horário
na tela): `→` usa `+ROT_SPEED`, `←` usa `-ROT_SPEED`.

---

## 10. Loop do jogo e desempenho

- Desenhe **o frame inteiro** na imagem e só então faça `mlx_put_image_to_window`.
  Isso evita piscar e garante que minimizar/trocar de janela não "apague" a cena
  (o próximo frame redesenha tudo) — requisito de "gerenciamento suave da janela".
- **Nunca** faça `malloc` dentro do loop. Tudo é alocado na inicialização.
- `MOVE_SPEED` e `ROT_SPEED` são "por frame": num PC mais rápido, anda mais
  rápido. Opcional: usar `gettimeofday` (permitida) para calcular o tempo entre
  frames e multiplicar as velocidades por ele.
- O custo por frame é ~`WIN_WIDTH` raios. Se ficar lento, reduza a resolução
  antes de otimizar código.

---

## 11. Memória e saída limpa

Todo caminho de saída precisa liberar tudo:

| Saída | Quem libera |
|---|---|
| Erro no parsing | `parse_error` → `free_scene` |
| Erro na inicialização da MLX | `exit_error` → `exit_game` (com ponteiros possivelmente `NULL`) |
| ESC / X vermelho | `exit_game` |

Por isso a `t_game` começa zerada (`ft_bzero` no `main`) e as funções de
limpeza checam `NULL` antes de liberar: assim funcionam com inicialização
parcial.

Valgrind:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/valid/simple.cub
```

A X11 pode mostrar blocos `still reachable` que não são de vocês. O que importa:
**`definitely lost: 0`** e nenhum `Invalid read/write`.

---

## 12. Armadilhas comuns

- `grid[x][y]` em vez de `grid[y][x]`.
- Esquecer de trocar o caractere do spawn por `'0'` → DDA trata `N` como "não parede" (ok),
  mas a validação de fechado pode ignorar essa célula.
- Linha do arquivo com `\r` (arquivo salvo no Windows) → caractere inválido no mapa.
  Façam os mapas no Linux / verifiquem com `cat -A`.
- Comparar `"NO"` sem checar o caractere seguinte → `NOO ./a.xpm` passa como `NO`.
- `atoi` aceita lixo (`"12abc"` → 12). Validem os dígitos antes.
- Não usar `line_len` no offset do pixel → imagem torta.
- Dividir inteiros: `2 * x / WIN_WIDTH` com `int` dá sempre 0 ou 1. Use `double`.
- Girar só `dir` e esquecer o `plane`.
- Textura carregada mas `addr` não pego com `mlx_get_data_addr`.
- `mlx_destroy_display` esquecido → leak no Linux.
- Mapa válido no limite: jogador colado na parede, mapa 3x3, mapa com "buracos"
  de espaço fechados por `1`, mapa muito largo.

---

## 13. Glossário

| Termo | Significado |
|---|---|
| **Raycasting** | Técnica de lançar um raio por coluna da tela para descobrir a distância até a parede |
| **DDA** | Algoritmo que percorre um grid célula por célula ao longo de uma reta |
| **FOV** | *Field of view*, o ângulo de visão horizontal |
| **Plano da câmera** | Vetor perpendicular à direção que define a largura do FOV |
| **Fisheye** | Distorção que curva paredes retas se usarmos a distância euclidiana |
| **Distância perpendicular** | Distância da parede até o plano da câmera (corrige o fisheye) |
| **XPM** | Formato de imagem em texto, lido por `mlx_xpm_file_to_image` |
| **bpp** | *Bits per pixel* da imagem (normalmente 32) |
| **line_len** | Quantos bytes ocupa uma linha da imagem na memória |
| **Padding** | Completar as linhas do mapa com espaço para ficarem do mesmo tamanho |
| **Spawn** | Posição e orientação inicial do jogador |

---

## 14. Referências

- Lode Vandevenne — *Raycasting*: <https://lodev.org/cgtutor/raycasting.html>
  (base das fórmulas deste documento; atenção à orientação dos eixos)
- MiniLibX (docs não oficiais): <https://harm-smits.github.io/42docs/libs/minilibx>
- MiniLibX para Linux: <https://github.com/42Paris/minilibx-linux>
- Permadi — *Ray-Casting Tutorial*: <https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/>
- *A first-person engine in 265 lines*: <https://www.playfuljs.com/a-first-person-engine-in-265-lines/>
