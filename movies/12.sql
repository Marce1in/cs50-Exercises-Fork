SELECT title
FROM movies
JOIN stars
    ON movie_id = movies.id
WHERE person_id = (
    SELECT id
    FROM people
    WHERE name = 'Johnny Depp'
)
INTERSECT
SELECT title
FROM movies
JOIN stars
    ON movie_id = movies.id
WHERE person_id = (
    SELECT id
    FROM people
    WHERE name = 'Helena Bonham Carter'
);