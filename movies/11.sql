SELECT title
FROM movies
JOIN stars
    ON movie_id = movies.id
WHERE person_id = (
    SELECT id
    FROM people
    WHERE name = 'Chadwick Boseman'
)
ORDER BY (
    SELECT rating
    FROM ratings
    WHERE ratings.movie_id = stars.movie_id
) DESC
LIMIT 5;