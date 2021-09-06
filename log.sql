-- Keep a log of any SQL queries you execute as you solve the mystery.

-- This query was ran to get the reports of the crime scene. i had to start from here in order to get information
-- about what was found at the crime scene
SELECT * FROM crime_scene_reports;

-- From the crime scene reports, i found that three witnesses were interviewed so i ran this query to get the transcripts of the interview
-- in order to get more information regarding movements, suspects and the likes
SELECT transcript FROM interviews WHERE year = "2020" AND month = "7" AND day = "28";

-- i found out that the thief drove away from the court house within ten minutes of the theft so i had to get the activity
-- and license plate during that time frame
SELECT activity, license_plate, hour, minute FROM courthouse_security_logs WHERE year = "2020" AND month = "7" AND day = "28";

-- i searched for the names and passport numbers of the license plates i got
SELECT name, passport_number FROM people WHERE license_plate IN
("5P2BI95", "94KL13X", "6P58WS2", "4328GD8", "G412CB7", "L93JTIZ", "322W7JE", "0NTHK55");

-- A witness said they the thief is someone he recognized, earlier this morning as he was walking by the ATM on Fifer Street
-- he saw the thief withdrawing some money so i ran his query to get the account numbers
SELECT account_number FROM atm_transactions WHERE year = "2020" AND month = "7" AND day = "28"
AND transaction_type = "withdraw" AND atm_location = "Fifer Street";

-- I got the account numbers of the people that withdrew money on that day at the atm located at Fifer Street, so i decided to search for
-- their names using their account numbers
SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN
("28500762", "28296815", "76054385", "49610011", "16153065", "25506511", "81061156", "26013199"));

-- The witness also said that as the thief was leaving the courthouse, they called someone who talked to them for less than a minute,
-- so i searched for both the caller and the receiver eventhough it was just the caller i needed at the moment
SELECT caller, receiver FROM phone_calls WHERE year = "2020" AND month = "7" AND day = "28" AND duration < 60;

-- After getting the numbers that called for less than one minute on that day, i decided to search for their names
SELECT name FROM people WHERE phone_number IN
("(130) 555-0289", "(499) 555-9472", "(367) 555-5533", "(499) 555-9472",
"(286) 555-6063", "(770) 555-1861", "(031) 555-6622", "(826) 555-1652", "(338) 555-6650");

-- Now i have three lists of names and so from the three list i wrote down the names that appeared on the three lists,
-- the common names were Russell and Ernest so i lookedup their passport numbers. The witness said he heard the thief say
-- that they were planning to take the earliest flight out of Fiftyville tomorrow and the thief then asked the person on
-- the otherend of the phone to purchase the flight ticket. I decided to get the flight id, passport number and
-- destination_airport_id using Russell and Ernest's passport number so that i can get the thiefs passport number using
--this query and get their name, i also made sure to check flights earlier than 12:00pm
SELECT flights.id, passengers.passport_number, flights.destination_airport_id FROM flights JOIN passengers ON flights.id = passengers.flight_id
WHERE passport_number IN ("3592750733", "5773159633") AND year = "2020" AND month = "7" AND day = "29" AND hour < 12;

-- i found out the thief is Ernest and so using the flight id which i got from the previous query, i was able to get
-- the city that the thief escaped to
SELECT city FROM airports WHERE id = "4";

-- i lookedup the phone number of Ernest in order to get the receiver's phone number
SELECT phone_number FROM people WHERE name = "Ernest";

-- After getting the reciever's phone number, i looked up the accomplice name who is the receiver of Ernest's call
SELECT name FROM people WHERE phone_number = "(375) 555-8161";







