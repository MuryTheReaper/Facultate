USE DungeonsAndDragons
Go

CREATE OR ALTER FUNCTION testRange (@number FLOAT, @from int, @to int, @function int)
RETURNS INT
AS
BEGIN

    DECLARE @ok INT
    SET @ok = 0

    IF (@number > @from and @number < @to and @function = 0) OR
        (@number > @from and @function = 1) OR
        (@number < @to and @function = 2)
    BEGIN

        SET @ok = 1

    END

    RETURN @ok

END

GO


CREATE OR ALTER FUNCTION testName (@name VARCHAR(50))
RETURNS INT
AS
BEGIN

    DECLARE @ok INT
    SET @ok = 1

    IF @name LIKE '%[0-9]%'
    BEGIN

        SET @ok = 0

    END

    RETURN @ok

END

go

CREATE OR ALTER FUNCTION testType (@type VARCHAR(50), @options VARCHAR(200))
RETURNS INT
AS
BEGIN

    DECLARE @ok INT
    DECLARE @value VARCHAR
    SET @ok = 1

    SELECT @value = [value]
    FROM string_split(@options, ' ')
    WHERE value = @type

    IF @value IS NULL    
    BEGIN
        SET @ok = 0
    END

    RETURN @ok

END

Go
CREATE OR ALTER PROCEDURE addCharacter
    @id_p INT,
    @name VARCHAR(50),
    @level INT,
    @class VARCHAR(50)
AS
BEGIN

    DECLARE @id INT
    DECLARE @idC INT

    SELECT @id = id_p
    FROM [Player]
    WHERE id_p = @id_p

    SELECT @idC = id_c
    FROM [Character]
    WHERE id_c = @id_p

    IF @id IS NULL 
    BEGIN
        RAISERROR('There is no player with that id',16,1)
        RETURN
    END

    IF @idC IS NOT NULL 
    BEGIN
        RAISERROR('Player already has character',16,1)
        RETURN
    END

    IF dbo.testName(@name) = 0
    BEGIN
        RAISERROR('Name cant contain numbers',16,1)
        RETURN
    END

    IF dbo.testRange(@level, 0, 21, 0) = 0
    BEGIN
        RAISERROR('Level must be between 0 and 21',16,1)
        RETURN
    END

    IF dbo.testType(@class, 'fighter wizard rogue druid') = 0
    BEGIN
        RAISERROR('Not a valid class',16,1)
        RETURN
    END

    INSERT INTO [Character]
        (id_c, name, [level], class)
    VALUES
        (@id_p, @name, @level, @class)


    PRINT N'Character added succesfully'

END

go

CREATE OR ALTER PROCEDURE getCharacter
    @id_c INT
AS
BEGIN

    DECLARE @id INT

    SELECT @id = id_c
    FROM [Character]
    WHERE id_c = @id_c

    IF @id IS NULL
    BEGIN
        RAISERROR('There is no character with that id',16,1)
        RETURN
    END

    SELECT *
    FROM [Character]
    WHERE id_c = @id_c

END

GO

CREATE OR ALTER PROCEDURE deleteCharacter
    @id_c INT
AS
BEGIN

    DECLARE @id INT

    SELECT @id = id_c
    FROM [Character]
    WHERE id_c = @id_c

    IF @id IS NULL
    BEGIN
        RAISERROR('There is no character with that id',16,1)
        RETURN
    END

    DELETE FROM CharacterEquipment WHERE id_c = @id_c
    DELETE FROM [Character] WHERE id_c = @id_c

    PRINT N'Character deleted succefully'


END

GO

CREATE OR ALTER PROCEDURE updateCharacter
    @id_c INT,
    @name VARCHAR(50),
    @level INT,
    @class VARCHAR(50)
AS
BEGIN

    DECLARE @id INT

    SELECT @id = id_c
    FROM [Character]
    WHERE id_c = @id_c

    IF @id IS NULL 
    BEGIN
        RAISERROR('There is no character with that id',16,1)
        RETURN
    END

    IF dbo.testName(@name) = 0
    BEGIN
        RAISERROR('Name cant contain numbers',16,1)
        RETURN
    END

    IF dbo.testRange(@level, 0, 21, 0) = 0
    BEGIN
        RAISERROR('Level must be between 0 and 21',16,1)
        RETURN
    END

    IF dbo.testType(@class, 'fighter wizard rogue druid') = 0
    BEGIN
        RAISERROR('Not a valid class',16,1)
        RETURN
    END

    UPDATE [Character] set name = @name, [level] = @level, class = @class 
    WHERE id_c = @id_c

    PRINT N'Character updated succesfully'

END

GO

CREATE OR ALTER PROCEDURE addEquipment
    @name VARCHAR(50),
    @type VARCHAR(50),
    @cost FLOAT,
    @damage VARCHAR(50),
    @ac INT
AS
BEGIN

    IF dbo.testName(@name) = 0 
    BEGIN
        RAISERROR('Name cant contain numbers',16,1)
        RETURN
    END

    IF dbo.testType(@type, 'weapon armour accessory') = 0 
    BEGIN
        RAISERROR('Type is not valid',16,1)
        RETURN
    END

    IF dbo.testRange(@cost, 0, 0, 1) = 0 
    BEGIN
        RAISERROR('Cost must be higher than 0',16,1)
        RETURN
    END

    IF dbo.testType(@damage, '1d4 1d6 1d8 1d10 1d12 2d6 0') = 0 
    BEGIN
        RAISERROR('Not a valid dice type',16,1)
        RETURN
    END

    IF dbo.testRange(@ac, 0, 23, 2)= 0 
    BEGIN
        RAISERROR('Not a valid ac number',16,1)
        RETURN
    END

    INSERT INTO Equipment
        (name, [type], cost, damage, ac)
    VALUES
        (@name, @type, @cost, @damage, @ac)


    PRINT N'Equipment added succesfully'

END

go

CREATE OR ALTER PROCEDURE getEquipment
    @id_e INT
AS
BEGIN

    DECLARE @id INT

    SELECT @id = id_eq
    FROM [Equipment]
    WHERE id_eq = @id_e

    IF @id IS NULL
    BEGIN
        RAISERROR('There is no equipment with that id',16,1)
        RETURN
    END

    SELECT *
    FROM [Equipment]
    WHERE id_eq= @id_e

END

go

CREATE OR ALTER PROCEDURE deleteEquipment
    @id_e INT
AS
BEGIN

    DECLARE @id INT

    SELECT @id = id_eq
    FROM [Equipment]
    WHERE id_eq = @id_e

    IF @id IS NULL
    BEGIN
        RAISERROR('There is no equipment with that id',16,1)
        RETURN
    END

    DELETE FROM CharacterEquipment WHERE id_eq = @id_e
    DELETE FROM [Equipment] WHERE id_eq = @id_e

    PRINT N'Equipment deleted succefully'


END

go

CREATE OR ALTER PROCEDURE updateEquipment
    @id_e INT,
    @name VARCHAR(50),
    @type VARCHAR(50),
    @cost FLOAT,
    @damage VARCHAR(50),
    @ac INT
AS
BEGIN

    DECLARE @id INT

    SELECT @id = id_eq
    FROM [Equipment]
    WHERE id_eq = @id_e

    IF @id IS NULL
    BEGIN
        RAISERROR('There is no equipment with that id',16,1)
        RETURN
    END

    IF dbo.testName(@name) = 0 
    BEGIN
        RAISERROR('Name cant contain numbers',16,1)
        RETURN
    END

    IF dbo.testType(@type, 'weapon armour accessory') = 0 
    BEGIN
        RAISERROR('Type is not valid',16,1)
        RETURN
    END

    IF dbo.testRange(@cost, 0, 0, 1) = 0 
    BEGIN
        RAISERROR('Cost must be higher than 0',16,1)
        RETURN
    END

    IF dbo.testType(@damage, '1d4 1d6 1d8 1d10 1d12 2d6 0') = 0 
    BEGIN
        RAISERROR('Not a valid dice type',16,1)
        RETURN
    END

    IF dbo.testRange(@ac, 0, 23, 2)= 0 
    BEGIN
        RAISERROR('Not a valid ac number',16,1)
        RETURN
    END

    UPDATE Equipment set name = @name, type = @type, cost = @cost, damage = @damage, ac = @ac
    WHERE id_eq = @id_e


    PRINT N'Equipment updated succesfully'

END

GO

CREATE OR ALTER PROCEDURE addCharEquip
    @id_c INT,
    @id_e INT
AS
BEGIN

    DECLARE @idC INT
    DECLARE @idE INT

    SELECT @idC = id_c
    FROM [Character]
    WHERE id_c = @id_c

    SELECT @idE = id_eq
    FROM Equipment
    WHERE id_eq = @id_e


    IF @idC IS NULL
    BEGIN
        RAISERROR('There is no character with that id',16,1)
        RETURN
    END

    IF @idE IS NULL
    BEGIN
        RAISERROR('There is no equipment with that id',16,1)
        RETURN
    END

    SET @idC = NULL
    SET @idE = NULL


    SELECT @idC = id_c, @idE = id_eq
    FROM CharacterEquipment
    WHERE id_c = @id_c and id_eq = @id_e


    IF @idC IS NOT NULL and @idE IS NOT NULL
    BEGIN
        RAISERROR('That combination already exists',16,1)
        RETURN
    END

    INSERT INTO CharacterEquipment
        (id_c, id_eq)
    VALUES
        (@id_c, @id_e)


    PRINT N'CharacterEquipment addes succesfully'

END
GO

CREATE OR ALTER PROCEDURE getCharEquip
    @id_c INT,
    @id_e INT
AS
BEGIN

    DECLARE @idC INT
    DECLARE @idE INT

    SELECT @idC = id_c
    FROM [Character]
    WHERE id_c = @id_c

    SELECT @idE = id_eq
    FROM Equipment
    WHERE id_eq = @id_e


    IF @idC IS NULL
    BEGIN
        RAISERROR('There is no character with that id',16,1)
        RETURN
    END

    IF @idE IS NULL
    BEGIN
        RAISERROR('There is no equipment with that id',16,1)
        RETURN
    END

    SET @idC = NULL
    SET @idE = NULL


    SELECT @idC = id_c, @idE = id_eq
    FROM CharacterEquipment
    WHERE id_c = @id_c and id_eq = @id_e


    IF @idC IS NULL and @idE IS NULL
    BEGIN
        RAISERROR('That combination does not exists',16,1)
        RETURN
    END

    SELECT *
    FROM CharacterEquipment
    WHERE id_c = @id_c and id_eq = @id_e

END
GO

CREATE OR ALTER PROCEDURE deleteCharEquip
    @id_c INT,
    @id_e INT
AS
BEGIN

    DECLARE @idC INT
    DECLARE @idE INT

    SELECT @idC = id_c
    FROM [Character]
    WHERE id_c = @id_c

    SELECT @idE = id_eq
    FROM Equipment
    WHERE id_eq = @id_e


    IF @idC IS NULL
    BEGIN
        RAISERROR('There is no character with that id',16,1)
        RETURN
    END

    IF @idE IS NULL
    BEGIN
        RAISERROR('There is no equipment with that id',16,1)
        RETURN
    END

    SET @idC = NULL
    SET @idE = NULL


    SELECT @idC = id_c, @idE = id_eq
    FROM CharacterEquipment
    WHERE id_c = @id_c and id_eq = @id_e


    IF @idC IS NULL and @idE IS NULL
    BEGIN
        RAISERROR('That combination does not exists',16,1)
        RETURN
    END

    DELETE FROM CharacterEquipment WHERE id_eq = @id_e and id_c = @id_c


    PRINT N'CharacterEquipment deleted succesfully'

END
GO

CREATE OR ALTER PROCEDURE updateCharEquip
    @id_c INT,
    @id_e INT,
    @id_nc INT,
    @id_ne INT
AS
BEGIN

    DECLARE @idC INT
    DECLARE @idE INT

    SELECT @idC = id_c
    FROM [Character]
    WHERE id_c = @id_c

    SELECT @idE = id_eq
    FROM Equipment
    WHERE id_eq = @id_e


    IF @idC IS NULL
    BEGIN
        RAISERROR('There is no character with that id',16,1)
        RETURN
    END

    IF @idE IS NULL
    BEGIN
        RAISERROR('There is no equipment with that id',16,1)
        RETURN
    END

    SET @idC = NULL
    SET @idE = NULL


    SELECT @idC = id_c, @idE = id_eq
    FROM CharacterEquipment
    WHERE id_c = @id_c and id_eq = @id_e


    IF @idC IS NULL and @idE IS NULL
    BEGIN
        RAISERROR('That combination does not exists',16,1)
        RETURN
    END

    SET @idC = NULL
    SET @idE = NULL

    SELECT @idC = id_c
    FROM [Character]
    WHERE id_c = @id_nc

    SELECT @idE = id_eq
    FROM Equipment
    WHERE id_eq = @id_ne

    IF @idC IS NULL
    BEGIN
        RAISERROR('There is no character with that id new',16,1)
        RETURN
    END

    IF @idE IS NULL
    BEGIN
        RAISERROR('There is no equipment with that id new',16,1)
        RETURN
    END

    UPDATE CharacterEquipment set id_c = @id_nc, id_eq = @id_ne 
    WHERE id_c = @id_c and id_eq = @id_e

    PRINT N'CharacterEquipment updated succesfully'

END
GO

CREATE OR ALTER PROCEDURE CRUD
    @tableName VARCHAR(50)
AS
BEGIN

    SET NOCOUNT ON
    DECLARE @id INT

    IF @tableName = 'Character'
    BEGIN

        --create
        EXEC addCharacter 6, 'Jack', 5, 'rogue'

        --read
        EXEC getCharacter 6

        --update
        EXEC updateCharacter 6, 'Jacky', 6, 'fighter'

        EXEC getCharacter 6

        --delete
        EXEC deleteCharacter 6

    END
    ELSE
    IF @tableName = 'Equipment'
    BEGIN

        --create
        EXEC addEquipment 'Excalibur', 'weapon', 100, '2d6', 0

        SELECT TOP 1
            @id = id_eq
        FROM Equipment
        ORDER BY id_eq DESC

        --read
        EXEC getEquipment @id

        --update
        EXEC updateEquipment @id, 'Horn of Winter', 'accessory', 50, '0', 3

        EXEC getEquipment @id

        --delete
        EXEC deleteEquipment @id

    END
    ELSE
    IF @tableName = 'CharacterEquipment'
    BEGIN

        --create
        EXEC addCharEquip 1, 4

        --read
        EXEC getCharEquip 1, 4

        --update
        EXEC updateCharEquip 1, 4, 2, 1

        EXEC getCharEquip 2, 1

        --delete
        EXEC deleteCharEquip 2, 1

    END
    ELSE
    BEGIN
        RAISERROR('Not a valid table name',16,1)
    END

END
GO

EXEC CRUD 'Character'