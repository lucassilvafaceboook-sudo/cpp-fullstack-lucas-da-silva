SET NAMES utf8mb4;
CREATE DATABASE IF NOT EXISTS clinica_pet
    DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
USE clinica_pet;

CREATE TABLE IF NOT EXISTS tutores (
    id       INT UNSIGNED NOT NULL AUTO_INCREMENT,
    nome     VARCHAR(100) NOT NULL,
    telefone VARCHAR(20)  NOT NULL,
    email    VARCHAR(120) NULL,
    PRIMARY KEY (id),
    UNIQUE KEY uq_tutores_email (email)
) ENGINE = InnoDB;

CREATE TABLE IF NOT EXISTS pets (
    id              INT UNSIGNED  NOT NULL AUTO_INCREMENT,
    nome            VARCHAR(60)   NOT NULL,
    especie         VARCHAR(20)   NOT NULL,
    raca            VARCHAR(60)   NULL,
    mes_nascimento  TINYINT UNSIGNED  NULL,   -- 1 a 12
    ano_nascimento  SMALLINT UNSIGNED NULL,
    peso_kg         DECIMAL(5,2)  NULL,
    tutor_id        INT UNSIGNED  NOT NULL,
    PRIMARY KEY (id),
    CONSTRAINT fk_pets_tutor FOREIGN KEY (tutor_id) REFERENCES tutores (id),
    -- mesma lista de src/especies.hpp
    CONSTRAINT ck_pets_especie CHECK (especie IN (
        'cachorro', 'gato', 'coelho', 'hamster', 'porquinho_india', 'chinchila',
        'furao', 'rato', 'camundongo', 'gerbil', 'ourico', 'petauro',
        'calopsita', 'periquito', 'papagaio', 'arara', 'canario', 'galinha',
        'pato', 'ave', 'cobra', 'lagarto', 'jabuti', 'tartaruga',
        'sapo', 'axolote', 'peixe', 'aranha', 'escorpiao', 'inseto',
        'cavalo', 'burro', 'boi', 'porco', 'cabra', 'ovelha',
        'macaco', 'capivara', 'gamba', 'silvestre', 'outro')),
    CONSTRAINT ck_pets_peso CHECK (peso_kg IS NULL OR peso_kg > 0),
    -- "não pode ser no futuro" é checado na API (o CHECK do MySQL não aceita a data de hoje)
    CONSTRAINT ck_pets_ano CHECK (ano_nascimento IS NULL OR ano_nascimento >= 1900),
    CONSTRAINT ck_pets_mes CHECK (mes_nascimento IS NULL OR (mes_nascimento BETWEEN 1 AND 12 AND ano_nascimento IS NOT NULL))
) ENGINE = InnoDB;

CREATE TABLE IF NOT EXISTS usuarios (
    id         INT UNSIGNED NOT NULL AUTO_INCREMENT,
    nome       VARCHAR(100) NOT NULL,
    email      VARCHAR(120) NOT NULL,
    senha_hash VARCHAR(255) NOT NULL,
    papel      VARCHAR(20)  NOT NULL,
    tutor_id   INT UNSIGNED NULL,          -- só para clientes: o cadastro de tutor dele
    criado_em  DATETIME     NOT NULL DEFAULT CURRENT_TIMESTAMP,
    PRIMARY KEY (id),
    UNIQUE KEY uq_usuarios_email (email),
    UNIQUE KEY uq_usuarios_tutor (tutor_id),
    CONSTRAINT fk_usuarios_tutor FOREIGN KEY (tutor_id) REFERENCES tutores (id),
    CONSTRAINT ck_usuarios_papel CHECK (papel IN ('cliente', 'veterinario'))
) ENGINE = InnoDB;

CREATE TABLE IF NOT EXISTS sessoes (
    token_hash CHAR(64)     NOT NULL,      -- sha256 do token; o token em si só o navegador tem
    usuario_id INT UNSIGNED NOT NULL,
    expira_em  DATETIME     NOT NULL,
    PRIMARY KEY (token_hash),
    CONSTRAINT fk_sessoes_usuario FOREIGN KEY (usuario_id) REFERENCES usuarios (id) ON DELETE CASCADE
) ENGINE = InnoDB;

CREATE TABLE IF NOT EXISTS atendimentos (
    id          INT UNSIGNED NOT NULL AUTO_INCREMENT,
    pet_id      INT UNSIGNED NOT NULL,
    tipo        VARCHAR(20)  NOT NULL,     -- consulta (com sintomas) ou vacina
    sintomas    TEXT         NULL,
    status      VARCHAR(20)  NOT NULL DEFAULT 'aguardando',
    observacoes TEXT         NULL,         -- anotações do veterinário
    criado_em   DATETIME     NOT NULL DEFAULT CURRENT_TIMESTAMP,
    PRIMARY KEY (id),
    CONSTRAINT fk_atendimentos_pet FOREIGN KEY (pet_id) REFERENCES pets (id) ON DELETE CASCADE,
    CONSTRAINT ck_atendimentos_tipo CHECK (tipo IN ('consulta', 'vacina')),
    CONSTRAINT ck_atendimentos_status CHECK (status IN ('aguardando', 'concluido'))
) ENGINE = InnoDB;

-- Dados de exemplo (para a demonstração já começar com algo na tela)
INSERT INTO tutores (nome, telefone, email) VALUES
    ('Ana Souza',      '(11) 98888-1111', 'ana@email.com'),
    ('Bruno Lima',     '(11) 97777-2222', NULL),
    ('Carla Menezes',  '(21) 96666-3333', 'carla@email.com');

INSERT INTO pets (nome, especie, raca, mes_nascimento, ano_nascimento, peso_kg, tutor_id) VALUES
    ('Thor',   'cachorro', 'Labrador',      3, 2021, 28.40, 1),
    ('Mimi',   'gato',     'Siamês',        8, 2019,  4.20, 1),
    ('Piu',    'ave',      'Calopsita',     1, 2023,  0.09, 2),
    ('Bolinha','outro',    'Hamster',    NULL, NULL,  NULL, 3);
