-- schema.sql - Cria o banco do DEMO "Tarefas por Projeto" (projetos + tarefas).
--
-- Este arquivo é executado AUTOMATICAMENTE pelo Docker, uma única vez, quando o container do banco é criado
-- pela primeira vez (volume vazio):   docker compose up -d --wait
--
-- Depois de alterar este arquivo, aplique de novo apagando os dados do container e subindo outra vez:
--     docker compose down -v
--     docker compose up -d --wait
-- (Por isso o schema deve ter dados de exemplo e ser a única fonte da verdade da estrutura do banco.)
--
-- Este é o schema do DEMO (Tarefas por Projeto). No projeto da equipe, as tabelas são as do SEU tema.
-- Não troque o nome do banco sem avisar a equipe: o docker-compose.yml e o servidor usam "projeto_iteam"
-- (variável MARIADB_DATABASE no compose e DB_NOME no servidor).

-- Acentos: força o cliente que executa este arquivo a falar UTF-8. Sem isto, dados de exemplo como "Ciências"
-- podem ser gravados com os caracteres trocados (aparece "CiÃªncias" na tela), dependendo do cliente usado.
SET NAMES utf8mb4;

CREATE DATABASE IF NOT EXISTS projeto_iteam
    CHARACTER SET utf8mb4
    COLLATE utf8mb4_unicode_ci;

USE projeto_iteam;

-- ===================== DEMO: Tarefas por Projeto =====================
-- Entidade de apoio: projeto (nome UNICO).  Entidade principal: tarefa (pertence a um projeto).

CREATE TABLE IF NOT EXISTS projetos (
    id          INT UNSIGNED  NOT NULL AUTO_INCREMENT,
    nome        VARCHAR(80)   NOT NULL,
    descricao   VARCHAR(255)  NULL,
    criado_em   TIMESTAMP     NOT NULL DEFAULT CURRENT_TIMESTAMP,
    PRIMARY KEY (id),
    CONSTRAINT uq_projetos_nome UNIQUE (nome)               -- nome repetido -> erro 1062 -> API responde 409
) ENGINE = InnoDB;

CREATE TABLE IF NOT EXISTS tarefas (
    id              INT UNSIGNED  NOT NULL AUTO_INCREMENT,
    projeto_id      INT UNSIGNED  NOT NULL,
    titulo          VARCHAR(100)  NOT NULL,
    descricao       TEXT          NULL,
    status          VARCHAR(12)   NOT NULL DEFAULT 'pendente', -- lista fixa: pendente | andamento | feito
    prioridade      TINYINT       NOT NULL DEFAULT 3,          -- 1 (mais urgente) a 5 (menos urgente)
    prazo           DATE          NULL,                        -- opcional
    horas_estimadas DECIMAL(5,1)  NULL,                        -- opcional
    concluida_em    TIMESTAMP     NULL,                        -- preenchido pela rota "concluir"
    criado_em       TIMESTAMP     NOT NULL DEFAULT CURRENT_TIMESTAMP,
    PRIMARY KEY (id),
    CONSTRAINT fk_tarefas_projeto FOREIGN KEY (projeto_id) REFERENCES projetos (id)
        ON DELETE RESTRICT,                                    -- projeto com tarefas nao pode ser apagado -> 409
    CONSTRAINT ck_tarefas_status CHECK (status IN ('pendente', 'andamento', 'feito')),
    CONSTRAINT ck_tarefas_prioridade CHECK (prioridade BETWEEN 1 AND 5),
    CONSTRAINT ck_tarefas_horas CHECK (horas_estimadas IS NULL OR horas_estimadas >= 0)
) ENGINE = InnoDB;

-- Dados de exemplo. Os prazos sao relativos a HOJE, para sempre haver tarefas atrasadas, de hoje e futuras.
INSERT INTO projetos (nome, descricao)
SELECT * FROM (
    SELECT 'Site da Padaria' AS nome, 'Cardápio online e pedidos por WhatsApp' AS descricao
    UNION ALL SELECT 'App de Estudos', 'Cronograma e lembretes para a turma'
    UNION ALL SELECT 'Feira de Ciências', NULL
) AS exemplo
WHERE NOT EXISTS (SELECT 1 FROM projetos);

INSERT INTO tarefas (projeto_id, titulo, descricao, status, prioridade, prazo, horas_estimadas, concluida_em)
SELECT p.id, t.titulo, t.descricao, t.status, t.prioridade, t.prazo, t.horas, t.concluida_em
FROM (
    SELECT 'Site da Padaria' AS projeto, 'Desenhar a página inicial' AS titulo, 'Rascunho no papel e depois no Figma' AS descricao,
           'feito' AS status, 2 AS prioridade, DATE_SUB(CURRENT_DATE, INTERVAL 6 DAY) AS prazo, 4.0 AS horas,
           DATE_SUB(NOW(), INTERVAL 5 DAY) AS concluida_em
    UNION ALL SELECT 'Site da Padaria', 'Cadastrar os pães no cardápio', NULL, 'andamento', 1, DATE_SUB(CURRENT_DATE, INTERVAL 2 DAY), 3.5, NULL
    UNION ALL SELECT 'Site da Padaria', 'Integrar o botão do WhatsApp', 'Link com mensagem pronta', 'pendente', 2, DATE_ADD(CURRENT_DATE, INTERVAL 3 DAY), 1.5, NULL
    UNION ALL SELECT 'Site da Padaria', 'Publicar o site', NULL, 'pendente', 3, DATE_ADD(CURRENT_DATE, INTERVAL 10 DAY), NULL, NULL
    UNION ALL SELECT 'App de Estudos', 'Levantar as matérias da turma', NULL, 'feito', 3, DATE_SUB(CURRENT_DATE, INTERVAL 4 DAY), 2.0, DATE_SUB(NOW(), INTERVAL 4 DAY)
    UNION ALL SELECT 'App de Estudos', 'Montar o cronograma semanal', 'Uma tabela por dia da semana', 'andamento', 2, CURRENT_DATE, 5.0, NULL
    UNION ALL SELECT 'App de Estudos', 'Enviar lembretes por e-mail', NULL, 'pendente', 4, NULL, 6.0, NULL
    UNION ALL SELECT 'Feira de Ciências', 'Escolher o experimento', 'Votação na sala', 'pendente', 1, DATE_SUB(CURRENT_DATE, INTERVAL 1 DAY), 0.5, NULL
    UNION ALL SELECT 'Feira de Ciências', 'Comprar os materiais', NULL, 'pendente', 3, DATE_ADD(CURRENT_DATE, INTERVAL 7 DAY), 2.0, NULL
) AS t
JOIN projetos p ON p.nome = t.projeto
WHERE NOT EXISTS (SELECT 1 FROM tarefas);

-- O INSERT ... SELECT acima reserva ids a mais que as linhas inseridas (a primeira tarefa nova ganharia o id 16).
-- Isto faz o próximo id ser o seguinte ao último que existe.
ALTER TABLE projetos AUTO_INCREMENT = 1;
ALTER TABLE tarefas AUTO_INCREMENT = 1;
