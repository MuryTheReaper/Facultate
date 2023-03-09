use DungeonsAndDragons
GO

--inventarul caracterului detinut de jucatorul Gica
SELECT e.name as Inventory
FROM Player p INNER JOIN Character c ON p.id_p=c.id_c INNER JOIN CharacterEquipment ce ON ce.id_c = c.id_c INNER JOIN Equipment e ON e.id_eq = ce.id_eq
WHERE p.name = 'Gica'

--cat gold detine fiecare jucator
SELECT p.name as Player, SUM(e.cost) as Gold
FROM Player p INNER JOIN Character c ON p.id_p=c.id_c INNER JOIN CharacterEquipment ce ON ce.id_c = c.id_c INNER JOIN Equipment e ON e.id_eq = ce.id_eq
GROUP BY p.name

--cele mai populare obiecte folosite de mai mult de o data
SELECT Count(e.name) as Count, e.name as Equipment, AVG(e.cost) as CostPerUnit
FROM Character c INNER JOIN CharacterEquipment ce ON ce.id_c = c.id_c INNER JOIN Equipment e ON e.id_eq = ce.id_eq
GROUP BY e.name
HAVING Count(e.cost) > 1
ORDER BY Count DESC

--care dintre DungeonMasteri folosesc d6-uri (zar cu 6 fete)
SELECT DISTINCT dm.name as DM
FROM DungeonMaster dm INNER JOIN DmTool dmt ON dm.id_dm = dmt.id_dm INNER JOIN Tool t ON dmt.id_t = t.id_t
WHERE t.type = 'd6'

--timpul jucat de fiecare jucator care in medie a jucat mai mult de 250 de minute
SELECT p.name as Player, SUM(s.duration) as Time
FROM Session s INNER JOIN PlayerSession ps ON s.id_se = ps.id_se INNER JOIN Player p ON ps.id_p = p.id_p
GROUP BY p.name
HAVING AVG(s.duration)>250
ORDER BY Time DESC

--ce jucatori au participat la sesiunile DM-ului Stefan
SELECT DISTINCT p.name as Player
FROM Session s INNER JOIN PlayerSession ps ON s.id_se = ps.id_se INNER JOIN Player p ON ps.id_p = p.id_p INNER JOIN DungeonMaster dm ON dm.id_dm=s.id_dm
WHERE dm.name = 'Stefan'

--ce jucatori nu au adus gustari la sesiunile care au durat mai mult de 350 de min
SELECT DISTINCT p.name as Player
FROM Session s INNER JOIN PlayerSession ps ON s.id_se = ps.id_se INNER JOIN Player p ON ps.id_p = p.id_p LEFT OUTER JOIN Snack sk ON sk.id_p = p.id_p
WHERE s.duration>350 and sk.name IS NULL


--ce caractere au fost jucate la sesiunea din 17.4.2019
SELECT c.name as Character
FROM Session s INNER JOIN PlayerSession ps ON s.id_se = ps.id_se INNER JOIN Player p ON ps.id_p = p.id_p INNER JOIN Character c ON c.id_c = p.id_p
WHERE s.date = '2019-04-17'

--inamicii caracterului Redogast
SELECT DISTINCT npc.name as NPC
FROM Session s INNER JOIN PlayerSession ps ON s.id_se = ps.id_se INNER JOIN Player p ON ps.id_p = p.id_p INNER JOIN DungeonMaster dm ON dm.id_dm=s.id_dm
    INNER JOIN NPC npc ON npc.id_dm = dm.id_dm INNER JOIN Character c ON c.id_c = p.id_p
WHERE c.name = 'Redogast' and npc.relationship = 'enemy'

--suma cheltuita pe gustari pentru fiecare sesiune
SELECT s.date as Session, SUM(sk.cost) as Cost
FROM Session s INNER JOIN PlayerSession ps ON s.id_se = ps.id_se INNER JOIN Player p ON ps.id_p = p.id_p INNER JOIN Snack sk ON sk.id_p = p.id_p
GROUP BY s.date
ORDER BY Cost DESC
