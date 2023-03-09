
--DROP PROCEDURE modifyType
CREATE PROCEDURE modifyType
AS
BEGIN

    ALTER TABLE Session
    ALTER COLUMN duration FLOAT

    PRINT N'Duration from Session is now FLOAT'

END;

GO

--DROP PROCEDURE undoModifyType
CREATE PROCEDURE undoModifyType
AS
BEGIN

    ALTER TABLE Session
    ALTER COLUMN duration INT

    PRINT N'Duration from Session is now INT'

END;

GO

--DROP PROCEDURE addDefaultConstraint
CREATE PROCEDURE addDefaultConstraint
AS
BEGIN

    ALTER TABLE Tool
    ADD CONSTRAINT df_amount DEFAULT 1
    FOR amount;

    PRINT N'ADDED default constraint in Tool on amount'

END

GO

--DROP PROCEDURE undoAddDefaultConstraint
CREATE PROCEDURE undoAddDefaultConstraint
AS
BEGIN

    ALTER TABLE Tool
    DROP CONSTRAINT df_amount

    PRINT N'DROPED default constraint in Tool on amount'

END

GO

--DROP PROCEDURE addTable
CREATE PROCEDURE addTable
AS
BEGIN

    CREATE TABLE Universe
    (
        id_u INT PRIMARY KEY IDENTITY,
        name VARCHAR(50) NOT NULL
    )

    PRINT N'ADDED the table Universe'

END

GO

--DROP PROCEDURE undoAddTable
CREATE PROCEDURE undoAddTable
AS
BEGIN

    DROP TABLE Universe

    PRINT N'DROPED the table Universe'

END

GO

--DROP PROCEDURE addColumn
CREATE PROCEDURE addColumn
AS
BEGIN

    ALTER TABLE Universe
    ADD id_dm INT

    PRINT N'ADDED column id_dm in table Universe'

END

GO

--DROP PROCEDURE undoAddColumn
CREATE PROCEDURE undoAddColumn
AS
BEGIN

    ALTER TABLE Universe
    DROP COLUMN id_dm

    PRINT N'DROPED column id_dm in table Universe'

END

GO

--DROP PROCEDURE addForeignConstraint
CREATE PROCEDURE addForeignConstraint
AS
BEGIN

    ALTER TABLE Universe
    ADD CONSTRAINT fk_Universe FOREIGN KEY(id_dm) REFERENCES DungeonMaster(id_dm)

    PRINT N'ADDED foreign key constraint table Universe'

END

GO

--DROP PROCEDURE undoAddForeignConstraint
CREATE PROCEDURE undoAddForeignConstraint
AS
BEGIN

    ALTER TABLE Universe
    DROP CONSTRAINT fk_Universe

    PRINT N'DROPED foreign key constraint table Universe'

END


GO

--EXEC sp_executesql N'EXEC @nume', N'@nume AS VARCHAR(50)' , @nume = 'modifyType'
--EXEC ('EXEC ' + 'modifyType')
--EXEC modifyType
--EXEC undoModifyType
--EXEC addDefaultConstraint
--EXEC undoAddDefaultConstraint
--EXEC addTable
--EXEC undoAddTable
--EXEC addColumn
--EXEC undoAddColumn
--EXEC addForeignConstraint
--EXEC undoAddForeignConstraint


