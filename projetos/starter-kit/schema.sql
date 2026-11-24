-- schema.sql - Cria o banco e a tabela de exemplo (recados).
--
-- Este arquivo é executado AUTOMATICAMENTE pelo Docker, uma única vez, quando o container do banco é criado
-- pela primeira vez (volume vazio):   docker compose up -d --wait
--
-- Depois de alterar este arquivo, aplique de novo apagando os dados do container e subindo outra vez:
--     docker compose down -v
--     docker compose up -d --wait
-- (Por isso o schema deve ter dados de exemplo e ser a única fonte da verdade da estrutura do banco.)
--
-- Para o seu tema, ADICIONE as suas tabelas abaixo (e pode apagar a de recados quando não precisar mais).
-- Não troque o nome do banco sem avisar a equipe: o docker-compose.yml e o servidor usam "projeto_iteam"
-- (variável MARIADB_DATABASE no compose e DB_NOME no servidor).

-- Acentos: força o cliente que executa este arquivo a falar UTF-8. Sem isto, dados de exemplo como "Ciências"
-- podem ser gravados com os caracteres trocados (aparece "CiÃªncias" na tela), dependendo do cliente usado.
SET NAMES utf8mb4;

CREATE DATABASE IF NOT EXISTS projeto_iteam
    CHARACTER SET utf8mb4
    COLLATE utf8mb4_unicode_ci;

USE projeto_iteam;

CREATE TABLE IF NOT EXISTS recados (
    id          INT UNSIGNED  NOT NULL AUTO_INCREMENT,
    titulo      VARCHAR(100)  NOT NULL,
    mensagem    TEXT          NULL,
    prioridade  TINYINT       NOT NULL DEFAULT 1,
    criado_em   TIMESTAMP     NOT NULL DEFAULT CURRENT_TIMESTAMP,
    PRIMARY KEY (id),
    CONSTRAINT ck_recados_prioridade CHECK (prioridade BETWEEN 1 AND 5)
) ENGINE = InnoDB;

-- Dados de exemplo (só entram se a tabela estiver vazia).
INSERT INTO recados (titulo, mensagem, prioridade)
SELECT 'Bem-vindo', 'Este recado veio do banco de dados.', 1 FROM DUAL
WHERE NOT EXISTS (SELECT 1 FROM recados);
