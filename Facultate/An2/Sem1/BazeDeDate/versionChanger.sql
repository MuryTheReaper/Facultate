ALTER PROCEDURE versionChanger
    @newVersion int
AS
BEGIN

    SET NOCOUNT ON

    IF @newVersion > 5 OR @newVersion < 0
    BEGIN
        RAISERROR('Version must be between 0 and 5',16,1)
        RETURN
    END

    DECLARE @oldVersion INT

    SET @oldVersion = 
    (SELECT curentVersion
    FROM Version)

    IF @newVersion = @oldVersion
    BEGIN
        PRINT N'The datebase is already at that version'
        RETURN
    END


    IF @newVersion > @oldVersion
    BEGIN

        DECLARE @functionArrayDo TABLE (id INT,
            functionName varchar(50))
        INSERT INTO @functionArrayDo
        VALUES
            (1, 'modifyType'),
            (2, 'addDefaultConstraint'),
            (3, 'addTable'),
            (4, 'addColumn'),
            (5, 'addForeignConstraint')

        DECLARE @functionDo VARCHAR(50)

        WHILE @newVersion != @oldVersion
        BEGIN

            SET @functionDo = (SELECT functionName
            FROM @functionArrayDo
            WHERE id = @oldVersion + 1)

            EXEC ('EXEC ' + @functionDo)

            SET @oldVersion = @oldVersion + 1

        END

    END
    ELSE 
    BEGIN
        DECLARE @functionArrayUndo TABLE (id INT,
            functionName varchar(50))
        INSERT INTO @functionArrayUndo
        VALUES
            (1, 'undoModifyType'),
            (2, 'undoAddDefaultConstraint'),
            (3, 'undoAddTable'),
            (4, 'undoAddColumn'),
            (5, 'undoAddForeignConstraint')

        DECLARE @functionUndo VARCHAR(50)

        WHILE @newVersion != @oldVersion
        BEGIN

            SET @functionUndo = (SELECT functionName
            FROM @functionArrayUndo
            WHERE id = @oldVersion)

            EXEC ('EXEC ' + @functionUndo)

            SET @oldVersion = @oldVersion - 1

        END
    END

    UPDATE Version
        SET curentVersion = @newVersion

END

GO

EXEC versionChanger 1