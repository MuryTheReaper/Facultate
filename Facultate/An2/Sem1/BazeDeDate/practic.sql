CREATE DATABASE Practic
GO
USE Practic
GO

--drop database Practic

CREATE TABLE TipuriDeMelodii
(
    id_t INT PRIMARY KEY IDENTITY,
    denumire VARCHAR(50),
    descriere VARCHAR(50)
)

CREATE TABLE Melodii
(
    id_m INT PRIMARY KEY IDENTITY,
    denumire VARCHAR(50),
    an INT,
    duratie TIME,
    id_t INT FOREIGN KEY REFERENCES TipuriDeMelodii(id_t)
)

CREATE TABLE Adrese
(
    id_a INT PRIMARY KEY IDENTITY,
    tara VARCHAR(50),
    loc VARCHAR(50),
    strada VARCHAR(50),
    numar INT,
    codPostal BIGINT
)

CREATE TABLE Interpreti
(
    id_i INT PRIMARY KEY IDENTITY,
    nume VARCHAR(50),
    prenume VARCHAR(50),
    gen VARCHAR(50),
    dataDeNastere DATE,
    id_a INT FOREIGN KEY REFERENCES Adrese(id_a)

)

CREATE TABLE MelodiiInterpreti
(
    id_m INT FOREIGN KEY REFERENCES Melodii(id_m),
    id_i INT FOREIGN KEY REFERENCES Interpreti(id_i),
    studio VARCHAR(50),
    cost FLOAT,
    CONSTRAINT pk_MelodiiInterpreti PRIMARY KEY (id_m, id_i)
)
GO

INSERT INTO TipuriDeMelodii
    (denumire, descriere)
VALUES
    ('rock', 'populara la adolescenti'),
    ('pop', 'populara la radio')

INSERT INTO Melodii
    (denumire, an, duratie, id_t)
VALUES
    ('MelodieRock', 1999, '00:03:27', 1),
    ('MelodiePop', 2022, '00:02:29', 2)

INSERT INTO Adrese
    (tara, loc, strada, numar, codPostal)
VALUES
    ('Romania', 'Pitesti', 'Gheorghe Frantescu', 2, 1234)

INSERT INTO Interpreti
    (nume, prenume, gen, dataDeNastere, id_a)
VALUES
    ('Muresan', 'Andrei', 'masculin', '2002-01-11', 1),
    ('Marmandiu', 'Vlad', 'masculin', '2002-01-12', 1)
GO

CREATE OR ALTER PROCEDURE Inserare
    @id_melodie INT,
    @id_interpret INT,
    @stuido VARCHAR(50),
    @cost INT
AS
BEGIN

    DECLARE @idM INT
    DECLARE @idI INT

    SELECT @idM = id_m, @idI = id_i
    FROM MelodiiInterpreti
    WHERE id_m = @id_melodie and id_i = @id_interpret

    IF @idM is NULL and @idI is NULL
    BEGIN

        INSERT INTO MelodiiInterpreti
            (id_m, id_i, studio, cost)
        VALUES
            (@id_melodie, @id_interpret, @stuido, @cost)

    END
    ELSE
    BEGIN

        UPDATE MelodiiInterpreti set studio = @stuido, cost = @cost
        WHERE id_m = @id_melodie and id_i = @id_interpret

    END

END

GO

CREATE OR ALTER FUNCTION melodiiCuNInterpreti (@n INT)
RETURNS TABLE 
AS
RETURN SELECT M.denumire
FROM MelodiiInterpreti MI INNER JOIN Melodii M ON MI.id_m = M.id_m
GROUP BY M.denumire
HAVING COUNT(MI.id_i) >= @n

GO

EXEC Inserare 1, 1, 'Haha Production', 360
EXEC Inserare 1, 2, 'Haha Production', 350
EXEC Inserare 2, 2, 'Haha Production', 276

SELECT *
FROM dbo.melodiiCuNInterpreti(2)



