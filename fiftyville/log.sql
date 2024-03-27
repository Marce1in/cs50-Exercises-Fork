-- Keep a log of any SQL queries you execute as you solve the mystery.

--Understanding how the database is stored
SELECT description, street, day, month, year
FROM crime_scene_reports;

--Selecting the exact day and seeing all that happen in that date
SELECT description, street, day, month, year
FROM crime_scene_reports
WHERE day = 28
AND month = 7
AND year = 2021;

--Selecting the exact day and street
SELECT description
FROM crime_scene_reports
WHERE day = 28
AND month = 7
AND year = 2021
AND street = 'Humphrey Street';

--After descovering that the Theft took place ate 10:15am at the Humphrey Street bakerey
--I look at the bakery security logs of that day

SELECT *
FROM bakery_security_logs
WHERE day = 28
AND month = 7
AND year = 2021

--After looking how this table works I select the hour that the description
--said it was the time of the crime
SELECT activity, license_plate, hour, minute
FROM bakery_security_logs
WHERE day = 28
AND month = 7
AND year = 2021
AND hour BETWEEN 9 AND 10;

--After this a look all the license plates that enter in
--Between 9 and exit at 10
SELECT license_plate
FROM bakery_security_logs
WHERE day = 28
AND month = 7
AND year = 2021
AND hour BETWEEN 9 AND 10
AND activity = 'entrance'

INTERSECT

SELECT license_plate
FROM bakery_security_logs
WHERE day = 28
AND month = 7
AND year = 2021
AND hour BETWEEN 9 AND 10
AND minute > 15
AND activity = 'exit';

--After founding the Suspicious license plates I look at each hour and minutes
--of the entrance and exit of them
SELECT activity, license_plate, hour, minute
FROM bakery_security_logs
WHERE license_plate IN (
    '4328GD8',
    '5P2BI95',
    '6P58WS2',
    'G412CB7'
);

--After analysing the entrance and exit hours I decided to look in the
--People table for their data using the license plate as an 'id'
SELECT license_plate, name, phone_number, passport_number
FROM people
WHERE license_plate IN (
    '4328GD8',
    '5P2BI95',
    '6P58WS2',
    'G412CB7'
);

--Now we have your prime suspects:
--+---------------+---------+----------------+-----------------+
--| license_plate |  name   |  phone_number  | passport_number |
--+---------------+---------+----------------+-----------------+
--| 5P2BI95       | Vanessa | (725) 555-4692 | 2963008352      |
--| 6P58WS2       | Barry   | (301) 555-4174 | 7526138472      |
--| G412CB7       | Sofia   | (130) 555-0289 | 1695452385      |
--| 4328GD8       | Luca    | (389) 555-5198 | 8496433585      |
--+---------------+---------+----------------+-----------------+

--And their activity during the crime
SELECT name, activity, hour, minute
FROM people
JOIN bakery_security_logs
    ON bakery_security_logs.license_plate = people.license_plate
WHERE people.license_plate IN (
    '4328GD8',
    '5P2BI95',
    '6P58WS2',
    'G412CB7'
)
ORDER BY hour, minute;
--+---------+----------+------+--------+
--|  name   | activity | hour | minute |
--+---------+----------+------+--------+
--| Luca    | entrance | 9    | 14     |
--| Vanessa | entrance | 9    | 15     |
--| Barry   | entrance | 9    | 20     |
--| Sofia   | entrance | 9    | 28     |
--| Vanessa | exit     | 10   | 16     |
--| Barry   | exit     | 10   | 18     |
--| Luca    | exit     | 10   | 19     |
--| Sofia   | exit     | 10   | 20     |
--+---------+----------+------+--------+

--I dicided to read the interviews looking for some evidences
SELECT name, transcript
FROM interviews
WHERE day = 28
AND month = 7
AND year = 2021

--|Ruth| Sometime within ten minutes of the theft, I saw the thief
--get into a car in the bakery parking lot and drive away. If you have
--security footage from the bakery parking lot, you might want to look
--for cars that left the parking lot in that time frame.

--|Eugene| I don't know the thief's name, but it was someone I recognized.
--Earlier this morning, before I arrived at Emma's bakery, I was walking
--by the ATM on Leggett Street and saw the thief there withdrawing some
--money.

--|Raymond| As the thief was leaving the bakery, they called someone
--who talked to them for less than a minute. In the call, I heard the
--thief say that they were planning to take the earliest flight out of
--Fiftyville tomorrow. The thief then asked the person on the other
--end of the phone to purchase the flight ticket.

--With that i decided to look for the phone calls of my prime suspects
SELECT people.id, name, caller, receiver
FROM phone_calls
JOIN people
    ON caller = phone_number
WHERE caller IN (
    '(725) 555-4692',
    '(301) 555-4174',
    '(130) 555-0289',
    '(389) 555-5198'
)
AND day = 28
AND month = 7
AND year = 2021
AND duration BETWEEN 0 AND 60;

--What I found sock me, Sofia was the only one that called someone in
--that day and the duration was less than one minute, this match
--with what Raimond said in his interview.
--+--------+-------+----------------+----------------+
--|   id   | name  |     caller     |    receiver    |
--+--------+-------+----------------+----------------+
--| 398010 | Sofia | (130) 555-0289 | (996) 555-8899 |
--+--------+-------+----------------+----------------+

--Also the exit time match with Ruth interview, the culprid lefted after
--10 minutes.
--I still was socked, why Sofia? I needed to be sure so i decided to
--Check what Eugene said in their interview, the ATM on Leggett Street

--First I decided to get her account number, it's gonna be easy
--because I already have her ID

SELECT *
FROM bank_accounts
WHERE person_id = 398010;

--But i didn't find anyone, that's strange, so I decided to
--find her using the atm transactions
SELECT name
FROM atm_transactions
JOIN bank_accounts
    ON atm_transactions.account_number = bank_accounts.account_number
JOIN people
    ON person_id = people.id
WHERE day = 28
AND month = 7
AND atm_transactions.year = 2021
AND atm_location = 'Leggett Street'
AND transaction_type = 'withdraw';

--+---------+
--|  name   |
--+---------+
--| Bruce   |
--| Diana   |
--| Brooke  |
--| Kenny   |
--| Iman    |
--| Luca    |
--| Taylor  |
--| Benista |
--+---------+

--She was not there, maybe i got the wrong suspects? maybe the enter time
--was before 9 am? i decided look at this
SELECT name, activity, hour, minute
FROM people
JOIN bakery_security_logs
    ON bakery_security_logs.license_plate = people.license_plate
WHERE people.license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE day = 28
    AND month = 7
    AND year = 2021
    AND hour BETWEEN 8 AND 10
    AND activity = 'entrance'

    INTERSECT

    SELECT license_plate
    FROM bakery_security_logs
    WHERE day = 28
    AND month = 7
    AND year = 2021
    AND hour = 10
    AND minute BETWEEN 10 AND 20
    AND activity = 'exit'
)
AND day = 28
AND month = 7
AND year = 2021;
--So i got this:
--+---------+----------+------+--------+
--|  name   | activity | hour | minute |
--+---------+----------+------+--------+
--| Bruce   | entrance | 8    | 23     |
--| Luca    | entrance | 9    | 14     |
--| Vanessa | entrance | 9    | 15     |
--| Barry   | entrance | 9    | 20     |
--| Sofia   | entrance | 9    | 28     |
--| Vanessa | exit     | 10   | 16     |
--| Bruce   | exit     | 10   | 18     |
--| Barry   | exit     | 10   | 18     |
--| Luca    | exit     | 10   | 19     |
--| Sofia   | exit     | 10   | 20     |
--+---------+----------+------+--------+

--Sofia don't withdraw any money, so we can exclude her.
--With this, the only people left are Barry, Luca, Vanessa and Bruce
--Ok let's create a HUGE query combining this list with the ATM list
SELECT name
FROM atm_transactions
JOIN bank_accounts
    ON atm_transactions.account_number = bank_accounts.account_number
JOIN people
    ON person_id = people.id
WHERE name IN (
    SELECT name
    FROM people
    JOIN bakery_security_logs
        ON bakery_security_logs.license_plate = people.license_plate
    WHERE people.license_plate IN (
        SELECT license_plate
        FROM bakery_security_logs
        WHERE day = 28
        AND month = 7
        AND year = 2021
        AND hour BETWEEN 8 AND 10
        AND activity = 'entrance'

        INTERSECT

        SELECT license_plate
        FROM bakery_security_logs
        WHERE day = 28
        AND month = 7
        AND year = 2021
        AND hour = 10
        AND minute BETWEEN 10 AND 20
        AND activity = 'exit'
    )
    AND day = 28
    AND month = 7
    AND year = 2021
)
AND day = 28
AND month = 7
AND atm_transactions.year = 2021
AND atm_location = 'Leggett Street'
AND transaction_type = 'withdraw';

--So we got this:
--+-------+
--| name  |
--+-------+
--| Bruce |
--| Luca  |
--+-------+
--Ok, so we have Luca and Bruce as the prime suspects
--the only thing left is check what Raimond said in his interview,
--the culprid called for someone for less than 1 minute,
--Lets combine the queries and create the SUPER ULTRA GIANT QUERY
SELECT people.id, name, caller, receiver
FROM phone_calls
JOIN people
    ON caller = phone_number
WHERE caller IN (
    SELECT phone_number
    FROM atm_transactions
    JOIN bank_accounts
        ON atm_transactions.account_number = bank_accounts.account_number
    JOIN people
        ON person_id = people.id
    WHERE name IN (
        SELECT name
        FROM people
        JOIN bakery_security_logs
            ON bakery_security_logs.license_plate = people.license_plate
        WHERE people.license_plate IN (
            SELECT license_plate
            FROM bakery_security_logs
            WHERE day = 28
            AND month = 7
            AND year = 2021
            AND hour BETWEEN 8 AND 10
            AND activity = 'entrance'

            INTERSECT

            SELECT license_plate
            FROM bakery_security_logs
            WHERE day = 28
            AND month = 7
            AND year = 2021
            AND hour = 10
            AND minute BETWEEN 10 AND 20
            AND activity = 'exit'
        )
        AND day = 28
        AND month = 7
        AND year = 2021
    )
    AND day = 28
    AND month = 7
    AND atm_transactions.year = 2021
    AND atm_location = 'Leggett Street'
    AND transaction_type = 'withdraw'
)
AND day = 28
AND month = 7
AND year = 2021
AND duration BETWEEN 0 AND 60;

--So we got this:
--+--------+-------+----------------+----------------+
--|   id   | name  |     caller     |    receiver    |
--+--------+-------+----------------+----------------+
--| 686048 | Bruce | (367) 555-5533 | (375) 555-8161 |
--+--------+-------+----------------+----------------+
--Bruce is the Thief!!
--But now we have to find the accomplice that bought the fly Ticket!!
--He number is (375) 555-8161
--Now, let's discover who it is!

SELECT name
FROM people
WHERE phone_number = '(375) 555-8161';

--+-------+
--| name  |
--+-------+
--| Robin |
--+-------+
--Soo Mr.Robin was the accomplice!
--Now we have to discover where the fly Ticket will lead Bruce
--First we will need his passport number

SELECT name, passport_number
FROM people
WHERE phone_number = '(367) 555-5533';

--+-------+-----------------+
--| name  | passport_number |
--+-------+-----------------+
--| Bruce | 5773159633      |
--+-------+-----------------+

--With his passaport number we have to locate the fly that he will took
--tomorrow

SELECT city as 'Destination City'
FROM airports
WHERE id = (
    SELECT destination_airport_id
    FROM passengers
    JOIN flights
        ON id = flight_id
    WHERE passport_number = 5773159633
    AND day = 29
);
--he's going to New York City!