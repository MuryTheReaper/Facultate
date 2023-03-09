CREATE DATABASE DungeonsAndDragons;
go
use DungeonsAndDragons
go

--DROP DATABASE DungeonsAndDragons

CREATE TABLE Player
(
    id_p INT PRIMARY KEY IDENTITY,
    name VARCHAR(50) NOT NULL,
    age INT CHECK(age>12)
)

CREATE TABLE Character
(
    id_c INT PRIMARY KEY,
    name VARCHAR(50) NOT NULL,
    level INT CHECK(level>0 AND level<21),
    class VARCHAR(50) NOT NUll CHECK(class='fighter' or class='wizard' or class='rogue' or class='druid'),
    CONSTRAINT fk_Character FOREIGN KEY(id_c) REFERENCES Player(id_p)
)

CREATE TABLE Equipment
(
    id_eq INT PRIMARY KEY IDENTITY,
    name VARCHAR(50) NOT NULL,
    type VARCHAR(50) NOT NULL CHECK(type='weapon' or type='armour' or type='accessory'),
    cost FLOAT CHECK(cost>0),
    damage VARCHAR(50) NOT NULL CHECK(damage='1d4' or damage='1d6' or damage='1d8' or damage='1d10' or damage='1d12' or damage='2d6' or damage='0'),
    ac INT NOT NULL CHECK(ac<=22)

)

CREATE TABLE CharacterEquipment
(
    id_c INT FOREIGN KEY REFERENCES Character(id_c),
    id_eq INT FOREIGN KEY REFERENCES Equipment(id_eq),
    CONSTRAINT pk_CharacterEquipment PRIMARY KEY (id_c, id_eq)
)


CREATE TABLE DungeonMaster
(
    id_dm INT PRIMARY KEY IDENTITY,
    name VARCHAR(50) NOT NULL,
    age INT CHECK(age>12)
)

CREATE TABLE NPC
(
    id_npc INT PRIMARY KEY IDENTITY,
    name VARCHAR(50) NOT NULL,
    faction VARCHAR(50) NOT NULL,
    relationship VARCHAR(50) NOT NULL CHECK(relationship='friend' or relationship='enemy' or relationship='neutral'),
    id_dm INT FOREIGN KEY REFERENCES DungeonMaster(id_dm)
)

CREATE TABLE Snack
(
    id_s INT PRIMARY KEY IDENTITY,
    name VARCHAR(50) NOT NULL,
    type VARCHAR(50) NOT NULL,
    cost FLOAT,
    id_p INT FOREIGN KEY REFERENCES PLayer(id_p)
)

CREATE TABLE Session
(
    id_se INT PRIMARY KEY IDENTITY,
    title VARCHAR(50) NOT NULL,
    date DATE,
    duration INT,
    id_dm INT FOREIGN KEY REFERENCES DungeonMaster(id_dm)
)

CREATE TABLE PlayerSession
(
    id_p INT FOREIGN KEY REFERENCES PLayer(id_p),
    id_se INT FOREIGN KEY REFERENCES Session(id_se),
    CONSTRAINT pk_PlayerSession PRIMARY KEY(id_p,id_se)
)

CREATE TABLE Tool
(
    id_t INT PRIMARY KEY IDENTITY,
    type VARCHAR(50) NOT NULL,
    amount INT CHECK(amount>0)
)

CREATE TABLE DmTool
(
    id_dm INT FOREIGN KEY REFERENCES DungeonMaster(id_dm),
    id_t INT FOREIGN KEY REFERENCES Tool(id_t),
    CONSTRAINT pk_DmTool PRIMARY KEY(id_dm,id_t)
)

--DROP TABLE Version
CREATE TABLE Version
(
    curentVersion INT
)
