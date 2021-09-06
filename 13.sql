SELECT DISTINCT(people.name) FROM people JOIN stars ON stars.person_id = people.id JOIN movies ON stars.movie_id = movies.id
WHERE movies.id IN (SELECT stars.movie_id FROM stars JOIN movies ON stars.movie_id = movies.id JOIN people ON stars.person_id = people.id
WHERE name = "Kevin Bacon" AND birth = "1958") AND NOT name = "Kevin Bacon";

-- SELECT name FROM people WHERE name = "Kevin Bacon" AND id  IN (SELECT person_id FROM stars WHERE movie_id IN
-- (SELECT id FROM movies WHERE birth = "1958");

-- SELECT people.name FROM people JOIN stars ON people.id = stars.person_id JOIN movies ON stars.movie_id = movies.id WHERE
-- name = "Kevin Bacon" AND birth = "1958" INTERSECT
-- SELECT people.name FROM people JOIN stars ON people.id = stars.person_id JOIN movies ON stars.movie_id = movies.id;

-- WHERE id IN (SELECT movie_id FROM stars WHERE person_id IN
-- (SELECT id FROM people WHERE name = "Chadwick Boseman")) ORDER BY rating DESC LIMIT 5;

-- SELECT title FROM movies WHERE id IN (SELECT movie_id FROM stars WHERE person_id IN
-- (SELECT id FROM people WHERE name = "Johnny Depp")) INTERSECT
-- SELECT title FROM movies WHERE id IN (SELECT movie_id FROM stars WHERE person_id IN
-- (SELECT id FROM people WHERE name = "Helena Bonham Carter"));



-- SELECT movie.id FROM movies JOIN stars ON movie.id = stars.movie_id JOIN people ON stars.person_id = people.id
-- WHERE name = "Kevin Bacon" AND birth = "1958"w2 INTERSECT






