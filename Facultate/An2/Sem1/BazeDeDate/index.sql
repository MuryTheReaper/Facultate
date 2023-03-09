USE DungeonsAndDragons
GO

CREATE OR ALTER VIEW EquipmentJik
AS
    SELECT C.name as Character, COUNT(E.name) as EquipmentCount
    FROM Character C INNER JOIN CharacterEquipment CE ON C.id_c = CE.id_c INNER JOIN Equipment E ON CE.id_eq = E.id_eq
    GROUP BY C.name
GO

CREATE OR ALTER VIEW EquipmentCost
AS
    SELECT C.name as Name, SUM(E.cost) as EquipmentCount
    FROM Character C INNER JOIN CharacterEquipment CE ON C.id_c = CE.id_c INNER JOIN Equipment E ON CE.id_eq = E.id_eq
    GROUP BY C.name
GO




IF EXISTS (SELECT name
FROM sys.indexes
WHERE name=N'N_idx_name')
    DROP INDEX N_idx_name ON Character;
GO

IF EXISTS (SELECT name
FROM sys.indexes
WHERE name=N'N_idx_cost')
    DROP INDEX N_idx_cost ON Equipment;
GO

--45%
CREATE NONCLUSTERED INDEX N_idx_name ON Character (name);
GO

--not usefull
CREATE NONCLUSTERED INDEX N_idx_cost ON Equipment (cost);
GO

SELECT *
FROM EquipmentJik

SELECT *
FROM EquipmentCost