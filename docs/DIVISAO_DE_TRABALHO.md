# Divisão de trabalho — cub3D

Guia para dividir o projeto entre dois devs:

| Papel | Responsável por | Pastas |
|---|---|---|
| **Dev P — Parsing** | Ler e validar o `.cub` e entregar uma `t_scene` pronta | `src/parsing/`, `maps/` |
| **Dev E — Execução** | MiniLibX, raycasting, texturas, input e saída limpa | `src/execution/`, `textures/` |

Os dois trabalham **em paralelo** porque existe um **contrato** entre as partes:
a struct `t_scene` (em `includes/structs.h`). O parsing *preenche*, a execução
*só lê*.

> ⚠️ Na defesa, **os dois** serão questionados sobre o projeto inteiro.
> Dividir a implementação não significa dividir o entendimento. Veja a seção
> [Preparação para a defesa](#7-preparação-para-a-defesa).

---

## 1. O contrato: `t_scene`

```c
typedef struct s_scene
{
	char	*tex_paths[TEX_COUNT];  // [TEX_NO], [TEX_SO], [TEX_WE], [TEX_EA]
	int		floor_color;            // 0xRRGGBB
	int		ceiling_color;          // 0xRRGGBB
	t_map	map;                    // grid, width, height
	t_spawn	spawn;                  // x, y, dir ('N','S','E','W')
	char	**lines;                // uso interno do parsing
}	t_scene;
```

### Garantias que o parsing entrega quando `parse_scene()` retorna

Se `parse_scene()` retornou, a execução pode assumir **sem verificar de novo**:

1. `tex_paths[i]` != `NULL` para os 4 ids, terminam em `.xpm` e o arquivo abre com `open()`.
2. `floor_color` e `ceiling_color` estão no formato `0xRRGGBB` (cada componente em `[0,255]`).
3. `map.grid` é **retangular**: todas as linhas têm exatamente `map.width` caracteres
   (linhas curtas foram completadas com `' '`), e termina com `NULL`.
4. `map.height` = número de linhas do grid.
5. O grid contém apenas `'0'`, `'1'` e `' '`. O caractere de spawn
   **já foi trocado por `'0'`**.
6. `spawn.x` = coluna, `spawn.y` = linha, `spawn.dir` ∈ {`N`,`S`,`E`,`W`}.
7. O mapa é fechado: nenhuma célula `'0'` encosta na borda do grid ou num `' '`.
8. `lines` já foi liberado (`NULL`).

Se **qualquer** coisa estiver errada, o parsing chama `parse_error()`, que
imprime `Error\n<mensagem>\n` e encerra o programa — a execução nunca começa.

### Regras para mexer nos arquivos compartilhados

Arquivos compartilhados: `includes/structs.h`, `includes/defines.h`,
`includes/cub3d.h`, `src/main.c`, `src/utils/`, `Makefile`.

- Qualquer mudança nesses arquivos vai em um PR **revisado pelo outro dev**.
- Mudar o contrato (`t_scene`, `t_map`, `t_spawn`) exige **conversa antes** do código.
- Adicionou um `.c`? Adicione no `Makefile` (a Norma não permite wildcard) no mesmo commit.
- Adicionou uma função? O protótipo vai no header da sua parte
  (`parsing.h` ou `execution.h`).

---

## 2. Mapa de arquivos e donos

### Dev P — Parsing (`src/parsing/`)

| Arquivo | Funções | O que faz |
|---|---|---|
| `parse_scene.c` | `init_scene`, `parse_scene`, `parse_error` | Ponto de entrada; orquestra as etapas; erro de parsing |
| `check_args.c` | `check_args`, `has_extension` | `argc == 2` e extensão `.cub` |
| `read_file.c` | `read_file_lines`, `count_file_lines` | Lê o arquivo todo em `scene->lines` |
| `parse_elements.c` | `parse_elements`, `get_element_type`, `all_elements_set` | Identifica `NO/SO/WE/EA/F/C` até achar o mapa |
| `parse_texture.c` | `parse_texture` | Valida e guarda um caminho de textura |
| `parse_color.c` | `parse_color`, `parse_color_component`, `pack_rgb` | Valida `R,G,B` e empacota em `0xRRGGBB` |
| `parse_map.c` | `parse_map`, `get_map_size`, `pad_map_line` | Monta o grid retangular |
| `validate_map.c` | `validate_map_chars`, `find_spawn`, `validate_map_closed`, `is_open_cell` | Caracteres, spawn único, mapa fechado |
| `parse_utils.c` | `is_empty_line`, `skip_spaces`, `is_map_line` | Helpers |
| `free_scene.c` | `free_scene` | Libera tudo que o parsing alocou |

### Dev E — Execução (`src/execution/`)

| Arquivo | Funções | O que faz |
|---|---|---|
| `init_game.c` | `init_game`, `init_window`, `init_frame` | `mlx_init`, janela, imagem do frame |
| `init_textures.c` | `load_textures`, `load_texture` | Carrega os 4 `.xpm` |
| `init_player.c` | `init_player`, `set_player_direction` | `pos`, `dir`, `plane` a partir do spawn |
| `hooks.c` | `setup_hooks`, `on_key_press`, `on_key_release`, `on_close` | Eventos de teclado e fechar janela |
| `game_loop.c` | `game_loop` | Atualiza jogador → desenha → mostra |
| `movement.c` | `update_player`, `move_player`, `is_walkable` | W/A/S/D |
| `rotation.c` | `rotate_player` | ← / → |
| `render.c` | `render_frame`, `draw_background` | Chão/teto + um raio por coluna |
| `raycast.c` | `init_ray`, `init_step` | Direção do raio e passo do DDA |
| `dda.c` | `perform_dda`, `compute_wall` | Acha a parede e calcula altura/distância |
| `draw_column.c` | `draw_column`, `select_texture`, `get_tex_x` | Desenha a fatia de parede texturizada |
| `draw_utils.c` | `put_pixel`, `get_pixel` | Acesso ao buffer da imagem |
| `cleanup.c` | `exit_game`, `exit_error`, `destroy_images` | Saída limpa (ESC, X, erro) |

### Compartilhado

| Arquivo | Dono sugerido | Observação |
|---|---|---|
| `src/main.c` | ambos | Já está ligado; só muda se o fluxo mudar |
| `src/utils/error.c` (`print_error`) | Dev P | Implementar **primeiro** — os dois usam |
| `src/utils/free_utils.c` (`free_strs`) | Dev P | Implementar **primeiro** — os dois usam |
| `Makefile` | Dev E | Precisa da MiniLibX funcionando |
| `README.md` | ambos | Atualizar no final (logins, uso de IA) |

### Dois tipos de erro

| Momento | Função | Por quê |
|---|---|---|
| Antes da MiniLibX existir (parsing) | `parse_error(scene, msg)` | Só tem a `t_scene` para liberar |
| Depois de `init_game()` começar | `exit_error(game, msg)` | Tem imagens/janela/display para destruir |

Os dois imprimem via `print_error()` → `Error\n<msg>\n` na saída de erro.
As mensagens ficam em `defines.h` (`ERR_*`).

---

## 3. Trabalhando em paralelo sem depender do outro

### Dev E sem o parsing pronto: cena "mock"

Enquanto o parsing não existe, o Dev E pode criar **na sua branch** uma função
temporária (ex.: `mock_scene(t_scene *scene)`) que preenche a `t_scene` à mão
com o mapa de `maps/valid/simple.cub`, as texturas de `textures/`, cores fixas e
um spawn. No `main`, troca temporariamente `parse_scene(...)` por `mock_scene(...)`.

Regras:
- O mock deve respeitar **todas** as garantias da seção 1 (grid retangular,
  spawn trocado por `'0'`, etc.). Assim, quando o parsing real chegar, nada muda.
- O mock **não vai para a `main`** — apague antes do merge.

### Dev P sem a execução pronta: debug print

O Dev P pode criar **na sua branch** uma função temporária `print_scene()` que
imprime os caminhos, as cores em hexadecimal, o spawn e o grid (com `|` nas
bordas para enxergar o padding). No `main`, comenta temporariamente o que vem
depois de `parse_scene()`.

Teste com todos os arquivos de `maps/`:
- `maps/valid/*` → devem imprimir a cena corretamente.
- `maps/invalid/*` → devem imprimir `Error` + mensagem, **sem leaks**.

```bash
for f in maps/invalid/*; do echo "== $f"; ./cub3D "$f"; done
valgrind --leak-check=full ./cub3D maps/invalid/two_spawns.cub
```

Também não vai para a `main`.

---

## 4. Etapas (marcos)

### Fase 0 — Setup (juntos, ~1 dia)

- [ ] Clonar a MiniLibX em `minilibx-linux/` e copiar a libft em `libft/` (ver `README.md`).
- [ ] `make` compilando o esqueleto sem warnings.
- [ ] Ler juntos `structs.h` e este documento; ajustar o contrato se necessário.
- [ ] Ler juntos `docs/LOGICA_DO_CUB3D.md`.
- [ ] Decidir as regras ambíguas do `.cub` (seção 2.3 da LOGICA) e anotar aqui embaixo.
- [ ] Implementar `print_error` e `free_strs` (compartilhados).

**Decisões tomadas sobre o `.cub`:** *(preencher)*

- Espaços em volta das vírgulas em `F`/`C` (`F 220, 100, 0`): …
- Tabs: …
- Zeros à esquerda (`F 010,0,0`): …
- Escolha da textura por direção: …

### Fase 1 — Paralelo

**Dev P**
- [ ] `check_args` + `has_extension`
- [ ] `read_file_lines` (+ trocar `\n` por fim de string)
- [ ] `get_element_type` + `parse_elements`
- [ ] `parse_texture`
- [ ] `parse_color` (+ `parse_color_component`, `pack_rgb`)
- [ ] `parse_map` + `get_map_size` + `pad_map_line`
- [ ] `validate_map_chars`, `find_spawn`, `validate_map_closed`
- [ ] `free_scene` + `parse_error` sem leaks em **todos** os caminhos de erro

**Dev E**
- [ ] `init_window`, `init_frame`, `put_pixel` → janela com uma cor
- [ ] `setup_hooks`, `on_close`, `on_key_press(ESC)`, `exit_game` → fecha limpo
- [ ] `draw_background` → chão e teto com as cores da cena
- [ ] `init_player` + `set_player_direction`
- [ ] Raycasting **sem textura** (`init_ray`, `init_step`, `perform_dda`, `compute_wall`,
      parede com cor sólida, uma cor diferente por face)
- [ ] `update_player`, `move_player`, `rotate_player` (teclas press/release)
- [ ] `load_textures`, `get_pixel`, `select_texture`, `get_tex_x`, `draw_column`
- [ ] `destroy_images` e saída limpa sem leaks

### Fase 2 — Integração (juntos)

- [ ] Merge das duas branches na `main`; remover mock e `print_scene`.
- [ ] Rodar todos os mapas válidos e andar por eles.
- [ ] Rodar todos os mapas inválidos.
- [ ] Spawn em cada direção (`maps/valid/spawn_*.cub`) olhando para o lado certo.

### Fase 3 — Polimento (juntos)

- [ ] `norminette includes/ src/` sem erros (adicionar o header 42 em todos os arquivos).
- [ ] Valgrind: nenhum `definitely lost` em mapa válido (saída por ESC e pelo X) e inválido.
- [ ] `make` duas vezes seguidas não recompila nada (sem relink).
- [ ] Testes de "uso errado": sem argumento, 2 argumentos, arquivo inexistente,
      diretório com nome `.cub`, arquivo sem permissão.
- [ ] Minimizar / trocar de janela e voltar: imagem continua correta.
- [ ] `README.md`: logins na primeira linha, seção de uso de IA atualizada.

### Fase 4 — Bônus (só se o obrigatório estiver perfeito)

Arquivos bônus devem terminar em `_bonus.c/_bonus.h` e a regra `bonus` do
`Makefile` deve compilá-los. Sugestão de divisão:

| Bônus | Dev P | Dev E |
|---|---|---|
| Colisão com paredes | — | margem de colisão em `is_walkable` |
| Minimapa | — | desenhar o grid em escala no canto |
| Portas | símbolo novo no mapa (ex.: `D`) e validação | abrir/fechar, raycasting com portas |
| Sprites animados | símbolo/posições no mapa | z-buffer, projeção e animação |
| Rotação com mouse | — | `mlx_mouse_*` / evento de movimento |

---

## 5. Fluxo com Git

- `main` sempre compila. Ninguém faz push direto nela.
- Branches: `parsing/<assunto>` e `exec/<assunto>` (ex.: `parsing/colors`, `exec/dda`).
- PRs pequenos (uma etapa da fase 1 por PR) e **revisados pelo outro dev**.
  A revisão é a melhor forma de aprender a parte do outro.
- Commits no imperativo e em inglês: `Add color parsing`, `Fix DDA side detection`.
- Antes de abrir PR: `make re`, `norminette`, e os testes de mapa relevantes.

---

## 6. Convenções de código

- Todos os arquivos de código, nomes e comentários em **inglês**.
- Norma 42: máx. 25 linhas por função, 5 funções por arquivo, 4 parâmetros,
  5 variáveis, sem `for`, **sem comentários dentro de funções**, declarações no topo.
- Os comentários `TODO` acima de cada função descrevem o que ela deve fazer;
  substitua pelo comportamento real (ou apague) quando implementar.
- Se uma função crescer demais, divida em funções `static` no mesmo arquivo ou
  crie um novo arquivo (e atualize o `Makefile`).
- Nunca alocar memória dentro do loop de renderização.

---

## 7. Preparação para a defesa

O avaliador pode perguntar qualquer coisa a qualquer um, e pode pedir uma
**pequena modificação** no código durante a avaliação.

- Ao fim de cada fase, cada dev explica a sua parte para o outro (15–30 min).
- O Dev P deve saber explicar: DDA, por que usar distância perpendicular,
  como a textura é escolhida e amostrada, como a rotação funciona.
- O Dev E deve saber explicar: como o mapa é validado como fechado, como os
  elementos são detectados em qualquer ordem, como os leaks são evitados nos erros.
- Treinem modificações rápidas, por exemplo:
  - mudar a velocidade de movimento / FOV;
  - trocar a cor do chão por um gradiente;
  - aceitar um novo caractere no mapa;
  - imprimir uma mensagem de erro diferente para um caso específico.
- Tudo que foi gerado com IA precisa ser entendido e defendido por vocês
  (regra do subject). Registrem no `README.md` como a IA foi usada.
