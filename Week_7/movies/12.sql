SELECT
    DISTINCT(title)
FROM
    movies
WHERE
    title IN (
        SELECT
            title
        FROM
            movies
        JOIN
            stars
            ON
            movies.id = stars.movie_id
        Join
            people
            ON
            stars.person_id = people.id
        WHERE
            people.name = 'Johnny Depp'
    )
    AND
    title IN (
        SELECT
            title
        FROM
            movies
        JOIN
            stars
            ON
            movies.id = stars.movie_id
        Join
            people
            ON
            stars.person_id = people.id
        WHERE
            name = 'Helena Bonham Carter'
    )