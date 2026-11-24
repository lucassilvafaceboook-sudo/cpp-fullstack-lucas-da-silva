# Equipe

> **Preencha este arquivo no dia 5 (o que for possível) e mantenha-o atualizado até o dia 9.** Apague as linhas de instrução (as que começam com `>`) quando terminar.

## Identificação

| Campo | Preencher |
|-------|-----------|
| Nome da equipe | |
| Tema (📚 Biblioteca · 🐾 Clínica Pet · 🛒 Estoque de Loja) | |
| Nome do projeto | |
| Link da cópia da equipe no GitHub | |
| Tag de entrega | `projeto-final` |

## Integrantes

> Use o **mesmo nome de usuário** com o qual cada pessoa faz os *commits*.

| Nome | Usuário no GitHub | Papel principal (pode revezar) |
|------|-------------------|--------------------------------|
| | | |
| | | |
| | | |
| | | |

## Como executar (do zero, em outro computador)

> O professor vai seguir exatamente estes passos. Testem em um computador que não seja o de vocês, ou refaçam tudo numa pasta nova.

1. **Requisitos:** (compilador g++, biblioteca do MariaDB, Docker Desktop… com versões, se souberem)
2. **Banco:** (como subir o banco com `docker compose`, e como zerá-lo quando o `schema.sql` mudar)
3. **Compilar:** (comando exato)
4. **Executar:** (comando exato, e em qual pasta)
5. **Acessar:** (endereço no navegador)

## Rotas da API

> Uma linha por rota. Se houver exemplos de corpo JSON, coloquem no README da equipe.

| Método | Caminho | O que faz | Status possíveis |
|--------|---------|-----------|------------------|
| GET | `/api/...` | | 200 |
| | | | |

## Banco de dados

> Liste as tabelas, as chaves e as regras. Um desenho simples (mesmo à mão, fotografado) ou um diagrama em texto serve.

| Tabela | Colunas principais | Relacionamentos / regras |
|--------|--------------------|--------------------------|
| | | |

## Divisão de tarefas

> Atualizem ao longo dos dias. A ideia é revezar: cada pessoa deve ter mexido em banco, API e front.

| Dia | Quem | O que foi feito |
|-----|------|-----------------|
| 6 | | |
| 7 | | |
| 8 | | |
| 9 | | |

## Decisões e dificuldades

> Duas ou três decisões de projeto que vocês tomaram (e por quê) e um problema que deu trabalho e como foi resolvido. Isso ajuda muito na apresentação.

-
-

## Extras implementados

> Marque o que fizeram (além dos obrigatórios).

- [ ] Busca / filtro
- [ ] Rota de resumo ou relatório
- [ ] Paginação ou ordenação
- [ ] Validações extras no front-end
- [ ] Outro:

## Checklist de entrega (dia 9)

- [ ] O projeto compila sem avisos (`-Wall -Wextra`)
- [ ] `docker compose up -d --wait` cria o banco do zero (o `schema.sql` é executado sozinho) e há dados de exemplo
- [ ] Todo SQL usa parâmetros `?`
- [ ] CRUD completo funciona pela tela
- [ ] O README da equipe foi testado em outro computador
- [ ] Todos os integrantes têm *commits* no próprio usuário
- [ ] A tag `projeto-final` foi criada e enviada (`git push origin projeto-final`) e o link foi entregue ao professor
