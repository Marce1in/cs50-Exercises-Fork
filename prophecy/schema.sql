
CREATE TABLE houses(
    id INTEGER,
    house TEXT,
    head TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE students(
    id INTEGER,
    student TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE assignments(
    id_student INTEGER,
    id_house INTEGER,
    FOREIGN KEY(id_student) REFERENCES students(id)
);

SELECT students.student, houses.house, houses.head
FROM assignments
JOIN students
    ON students.id = assignments.id_student
JOIN houses
    ON houses.id = assignments.id_house;



SELECT songs.name, artists.name
FROM songs
JOIN artists
    ON songs.artist_id = artists.id

SELECT songs.name, artists.name FROM songs
JOIN artists
    ON songs.artist_id = artists.id
WHERE artist_id == (
    SELECT id FROM artists
    WHERE name = "Post Malone"
    );