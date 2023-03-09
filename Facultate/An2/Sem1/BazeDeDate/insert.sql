use DungeonsAndDragons
GO

INSERT INTO Player
    (name, age)
VALUES
    ('Andrei' , 20),
    ('Momo', 25),
    ('Iancu', 23),
    ('Gica', 24),
    ('Cosmin', 20)

INSERT INTO CHARACTER
    (id_c, name, LEVEL, class)
VALUES
    (1, 'Redogast', 3, 'druid'),
    (2, 'Darcy', 10, 'rogue'),
    (3, 'Lynn', 8, 'fighter'),
    (4, 'Jik', 15, 'fighter'),
    (5, 'Zen', 5, 'wizard')

INSERT INTO Equipment
    (name, type, cost, damage, ac)
VALUES
    ('Longsword', 'weapon', 15, '1d10', 0),
    ('Dagger', 'weapon', 2, '1d4', 0),
    ('Greatsword', 'weapon', 50, '2d6', 0),
    ('Rapier', 'weapon', 25, '1d8', 0),
    ('Shortsword', 'weapon', 10, '1d6', 0),
    ('Leather', 'armour', 10, '0', 11),
    ('Hide', 'armour', 10, '0', 12),
    ('Half plate', 'armour', 750, '0', 15),
    ('Plate', 'armour', 1500, '0', 18),
    ('Chain shirt', 'armour', 50, '0', 13),
    ('Studded leather', 'armour', 45, '0', 12),
    ('Ring of protection', 'accessory', 300, '0', 1)

INSERT INTO CharacterEquipment
    (id_c, id_eq)
VALUES
    (1, 11),
    (1, 5),
    (2, 2),
    (2, 11),
    (2, 5),
    (2, 4),
    (3, 3),
    (4, 1),
    (4, 3),
    (4, 9),
    (4, 2),
    (4, 12),
    (5, 2)

INSERT INTO Snack
    (name, type, cost, id_p)
VALUES
    ('Water', 'drink', 2.5, 2),
    ('Cola', 'drink', 6.2, 2),
    ('Tortitzi', 'food', 11.4, 3)


INSERT INTO DungeonMaster
    (name, age)
VALUES
    ('Stefan', 22),
    ('Mazilu', 19),
    ('Matei', 19),
    ('Flipian', 18)


INSERT INTO NPC
    (name, faction, relationship, id_dm)
VALUES
    ('Alexandra', 'Aagon' , 'enemy', 1),
    ('Juvenil', 'New Koli', 'friend', 1),
    ('Yuvar', 'Wild Lands', 'enemy', 1),
    ('Lalien', 'Eclipse', 'neutral', 1),
    ('Xanathar', 'Draconia', 'neutral', 2),
    ('Arkhan', 'Aagon', 'enemy', 2),
    ('Vecna', 'Aagon', 'enemy', 2),
    ('Strahd', 'Alveria', 'neutral', 3),
    ('Tiamat', 'Alveria', 'neutral', 4)


INSERT INTO Tool
    (type, amount)
VALUES
    ('d6', 6),
    ('paper', 30),
    ('pencil', 3),
    ('d10', 2),
    ('eraser', 1),
    ('d6', 2),
    ('d20', 2),
    ('d20', 6)

INSERT INTO DmTool
    (id_t, id_dm)
VALUES
    (1, 1),
    (2, 1),
    (2, 2),
    (2, 3),
    (2, 4),
    (3, 3),
    (4, 1),
    (5, 4),
    (6, 1),
    (6, 2),
    (7, 3)

INSERT INTO Session
    (title, date, duration,id_dm)
VALUES
    ('Session 0', '2020-06-23', 195, 1),
    ('Session 1', '2020-07-03', 275, 1),
    ('Session 0', '2022-06-23', 195, 2),
    ('Session 0', '2018-03-21', 255, 3),
    ('Session 0', '2019-04-17', 370, 4)

INSERT INTO PlayerSession
    (id_p, id_se)
VALUES
    (1, 5),
    (1, 1),
    (2, 1),
    (3, 1),
    (4, 1),
    (5, 1),
    (1, 2),
    (2, 2),
    (3, 2),
    (4, 2),
    (5, 2),
    (1, 3),
    (2, 3),
    (3, 4),
    (1, 4),
    (2, 5),
    (3, 5),
    (4, 5)

INSERT INTO Version
    (curentVersion)
VALUES
    (0)
	
