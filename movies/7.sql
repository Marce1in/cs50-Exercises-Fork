SELECT title, rating
FROM ratings
JOIN movies
    ON id = movie_id
WHERE year = 2010
AND rating NOT NULL
ORDER BY rating DESC, title;