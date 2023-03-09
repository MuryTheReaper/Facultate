USE DungeonsAndDragons
GO

INSERT INTO Tables
    (Name)
VALUES
    ('DungeonMaster'),
    ('NPC'),
    ('DmTool')
GO

CREATE VIEW DungeonMasterView
AS
    SELECT name, age
    FROM DungeonMaster
GO

CREATE VIEW NPCView
AS
    SELECT N.name, N.faction, N.relationship
    FROM NPC N INNER JOIN DungeonMaster D ON N.id_dm = D.id_dm
GO

CREATE VIEW DmToolView
AS
    SELECT T.type, COUNT(D.name) as 'uses'
    FROM DungeonMaster D INNER JOIN DmTool DT ON D.id_dm = DT.id_dm INNER JOIN Tool T ON T.id_t = DT.id_t
    GROUP BY T.type
GO

INSERT INTO Views
    (Name)
VALUES
    ('DungeonMasterView'),
    ('NPCView'),
    ('DmToolView')


INSERT INTO Tests
    (Name)
VALUES
    ('InserareStergere10View1'),
    ('InserareStergere100View2'),
    ('InserareStergere1000ViewAll')

INSERT INTO TestTables
    (TestID, TableID, NoOfRows, Position)
VALUES
    (1, 1, 10, 1),
    (2, 1, 100, 1),
    (3, 1, 1000, 1),
    (1, 2, 10, 2),
    (2, 2, 100, 2),
    (3, 2 , 1000, 2),
    (1, 3, 10, 3),
    (2, 3, 100, 3),
    (3, 3, 1000, 3)

INSERT INTO TestViews
    (TestID, ViewID)
VALUES
    (1, 1),
    (2, 2),
    (3, 1),
    (3, 2),
    (3, 3)

GO

CREATE OR ALTER PROCEDURE InsertDungeonMaster
    (@rows int)
AS
BEGIN

    DECLARE @i int
    DECLARE @name VARCHAR(50)
    DECLARE @age int

    SET @i = 1

    WHILE @i <= @rows
    BEGIN

        SET @name = 'NumeGeneric' + CONVERT(VARCHAR(5), @i)
        SET @age = 18 + @i

        INSERT INTO DungeonMaster
            (name, age)
        VALUES
            (@name, @age)

        SET @i = @i + 1

    END

END
GO

CREATE OR ALTER PROCEDURE DeleteDungeonMaster
    (@rows int)
AS
BEGIN

    DECLARE @i int
    DECLARE @id int

    SET @i = 1

    WHILE @i <= @rows
    BEGIN

        SELECT TOP 1
            @id = DungeonMaster.id_dm
        FROM DungeonMaster
        ORDER BY DungeonMaster.id_dm DESC

        IF @id > 4
        DELETE FROM DungeonMaster WHERE DungeonMaster.id_dm = @id

        SET @i = @i + 1

    END

END
GO

CREATE OR ALTER PROCEDURE InsertNPC
    (@rows int)
AS
BEGIN

    DECLARE @i int
    DECLARE @id int
    DECLARE @name VARCHAR(50)
    DECLARE @faction VARCHAR(50)
    DECLARE @relationship VARCHAR(50)
    DECLARE @token int


    SET @i = 1

    WHILE @i <= @rows
    BEGIN

        SET @name = 'NumeGeneric' + CONVERT(VARCHAR(5), @i)
        SET @faction = 'FactionGeneric' + CONVERT(VARCHAR(5), @i)
        SET @token = @i % 3

        IF @token = 0
        BEGIN
            SET @relationship = 'friend'
        END

        IF @token = 1
        BEGIN
            SET @relationship = 'enemy'
        END

        IF @token = 2
        BEGIN
            SET @relationship = 'neutral'
        END

        SELECT TOP 1
            @id = DungeonMaster.id_dm
        FROM DungeonMaster
        ORDER BY id_dm DESC

        INSERT INTO NPC
            (name, faction, relationship, id_dm)
        VALUES
            (@name, @faction, @relationship, @id)

        SET @i = @i + 1

    END

END
GO

CREATE OR ALTER PROCEDURE DeleteNPC
    (@rows int)
AS
BEGIN

    DECLARE @i int
    DECLARE @id int

    SET @i = 1

    WHILE @i <= @rows
    BEGIN

        SELECT TOP 1
            @id = NPC.id_npc
        FROM NPC
        ORDER BY NPC.id_npc DESC

        DELETE FROM NPC WHERE NPC.id_npc = @id

        SET @i = @i + 1

    END

END
GO

CREATE OR ALTER PROCEDURE InsertDmTool
    (@rows int)
AS
BEGIN

    DECLARE @i int
    DECLARE @id int
    DECLARE @id_dm INT
    DECLARE @id_tool int
    DECLARE @idt int

    SET @i = 1

    WHILE @i <= @rows
    BEGIN

        SELECT TOP 1
            @id = DungeonMaster.id_dm
        FROM DungeonMaster
        ORDER BY NEWID()

        SELECT TOP 1
            @idt = Tool.id_t
        FROM Tool
        ORDER BY id_t DESC

        SELECT @id_dm = DmTool.id_dm, @id_tool = DmTool.id_t
        FROM DmTool
        WHERE DmTool.id_dm = @id and DmTool.id_t = @idt

        IF @id_dm IS NOT NULL and @id_tool IS NOT NULL
        BEGIN

            DECLARE @type VARCHAR(50)

            set @type = 'GenericType' + CONVERT(varchar(50), @i)

            INSERT INTO Tool
                (type, amount)
            VALUES
                (@type, @i)

            SELECT TOP 1
                @idt = MAX(Tool.id_t)
            FROM Tool

        END

        INSERT INTO DmTool
            (id_dm, id_t)
        VALUES
            (@id, @idt)

        SET @i = @i + 1

    END

END
GO

CREATE OR ALTER PROCEDURE DeleteDmTool
    (@rows int)
AS
BEGIN

    DECLARE @i int
    DECLARE @id int
    DECLARE @idt int

    SET @i = 1

    WHILE @i <= @rows
    BEGIN

        SELECT TOP 1
            @id = DmTool.id_dm, @idt = DmTool.id_t
        FROM DmTool
        ORDER BY DmTool.id_t DESC

        DELETE FROM DmTool WHERE DmTool.id_dm = @id and DmTool.id_t = @idt

        SET @i = @i + 1

    END

END
GO

CREATE OR ALTER PROCEDURE Testing
    (@idTest INT)
AS
BEGIN

    SET NOCOUNT ON

    DECLARE @desc NVARCHAR(50)
    SELECT @desc = Name
    FROM Tests
    WHERE TestID = @idTest

    IF @desc IS NULL
    BEGIN
        RAISERROR('Not a known test',16,1)
        RETURN
    END

    INSERT INTO TestRuns
        (Description)
    VALUES
        (@desc)

    DECLARE @TestRunID int
    SELECT TOP 1
        @TestRunID=T.TestRunID
    FROM TestRuns T
    ORDER BY T.TestRunID DESC

    DECLARE @TabelsForTest TABLE(
        tableId int,
        name VARCHAR(50),
        position int
    )

    DECLARE @ViewsForTest TABLE(
        viewId int,
        name VARCHAR(50)
    )

    INSERT INTO @TabelsForTest
    SELECT Tables.TableID, Tables.Name, TestTables.Position
    FROM TestTables INNER JOIN Tables ON TestTables.TableID = Tables.TableID
    WHERE TestTables.TestID = @idTest

    INSERT INTO @ViewsForTest
    SELECT Views.ViewID, Views.Name
    FROM Views INNER JOIN TestViews ON Views.ViewID = TestViews.ViewID
    WHERE TestViews.TestID = @idTest

    DECLARE @rows int

    SELECT @rows = NoOfRows
    From TestTables
    WHERE TestID = @idTest

    DECLARE @max int

    SELECT @max = MAX(position)
    FROM @TabelsForTest

    DECLARE @min int

    SELECT @min = MIN(position)
    FROM @TabelsForTest

    DECLARE @maxV int

    SELECT @maxV = MAX(ViewID)
    FROM @ViewsForTest

    DECLARE @minV int

    SELECT @minV = MIN(ViewID)
    FROM @ViewsForTest


    DECLARE @i int = @max
    DECLARE @table VARCHAR(50)
    DECLARE @viewName VARCHAR(50)
    DECLARE @sql VARCHAR(50)
    DECLARE @id int

    DECLARE @insertDeleteTimes TABLE (
        tableID int,
        StartAt DATETIME,
        EndAt DATETIME
    )

    DECLARE @start datetime, @end DATETIME, @startD DATETIME, @endI DATETIME
    DECLARE @startV DATETIME, @endV DATETIME
    SET @start = GETDATE()

    WHILE @i >= @min
    BEGIN

        SELECT @Table = name, @id = tableId
        FROM @TabelsForTest
        WHERE position = @i

        SET @startD = GETDATE()

        INSERT @insertDeleteTimes
            (tableID, StartAt)
        VALUES
            (@id, @startD)

        SET @sql = 'Delete' + @Table + ' ' + CONVERT(varchar(5), @rows)
        EXEC (@sql)

        SET @i = @i -1

    END

    SET @i = @min

    WHILE @i <= @max
    BEGIN

        SELECT @Table = name, @id = tableId
        FROM @TabelsForTest
        WHERE position = @i

        SET @sql = 'Insert' + @Table + ' ' + CONVERT(varchar(5), @rows)
        EXEC (@sql)

        SET @endI = GETDATE()

        UPDATE @insertDeleteTimes SET EndAt = @endI WHERE tableID = @id

        SET @i = @i + 1

    END

    SET @i = @minV

    WHILE @i <= @maxV
    BEGIN

        SELECT @viewName = name
        FROM @ViewsForTest
        WHERE ViewID = @i

        SET @startV = GETDATE()

        SET @sql = 'Select * FROM ' + @viewName
        EXEC (@sql)

        SET @endV = GETDATE()

        INSERT INTO TestRunViews
            (TestRunID, ViewID, StartAt, EndAt)
        VALUES
            (@TestRunID, @i, @startV, @endV)

        SET @i = @i + 1
    END

    SET @end = GETDATE()

    UPDATE TestRuns SET StartAt = @start, EndAt = @end WHERE TestRunID = @TestRunID

    SET @i = @min
    WHILE @i <= @max
    BEGIN

        SELECT @start = StartAt, @end = EndAt
        FROM @insertDeleteTimes
        WHERE tableID = @i

        INSERT INTO TestRunTables
            (TestRunID, TableID, StartAt, EndAt)
        VALUES
            (@TestRunID, @i, @start, @end)

        SET @i = @i + 1

    END

END
GO

CREATE OR ALTER PROCEDURE ShowLastTest
AS
BEGIN

    DECLARE @id int

    SELECT TOP 1
        @id = TestRunID
    from TestRuns
    ORDER BY TestRunID DESC

    SELECT *
    FROM TestRuns
    WHERE TestRunID = @id

    SELECT *
    FROM TestRunTables
    WHERE TestRunID = @id

    SELECT *
    FROM TestRunViews
    WHERE TestRunID = @id

END


GO

SELECT *
FROM Tests

SELECT *
FROM TestTables

SELECT *
FROM TestViews

SELECT *
FROM Views

SELECT *
FROM Tables

EXEC Testing 3
EXEC ShowLastTest


DELETE FROM DmTool
DELETE FROM Tool WHERE id_t > 9
DELETE FROM NPC WHERE id_dm > 4
DELETE FROM DungeonMaster WHERE id_dm > 4
EXEC InsertDungeonMaster 15
EXEC InsertNPC 15
EXEC InsertDmTool 15



