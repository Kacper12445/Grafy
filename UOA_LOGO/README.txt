Zad 1 Brama
Przy używaniu bramy musimy uruchomić input z silnikiem. Bez niego brama nie działa.
Przy zamykaniu bramy powinniśmy ustalić za pomocą inputa czy na torze bramy będzie znajdować się przeszkoda. Jeśli tak to zostanie uruchomiony alarm, który automatycznie otworzy bramę. Alarm musimy wyłączyć ręcznie za pomocą inputa.
Po 10 otwarciach bramy jesteśmy informowani o tym że powinniśmy wezwać serwis.
********************************************************************************************
Zad 2 Zawory
Program działa w sposób następujący:
Na początku ustawiamy stan naszych zaworów: czy maja być one otwarte czy też zamknięte. Po wyborcze wyskakują tam komunikaty na wyjściu z informacją o ich stanie. Gdy napełniamy nasz zbiornik za pomocą analogowego inputa zawory powinny być w stanie:
- Zawór napełniający otwarty 
- Zawór spustowy zamknięty
Napełniając zbiornik wodą możemy zauważyć, że przy 7 litrach uruchamia się alarm informujący o tym że poziom wody osiagnął poziom maksymalny. Alarm ten wyłącza automatycznie zawór napełniający, zmieniając jego stan na zamknięty. Następnie ręcznie możemy otworzyc zawór spustowy po czym zmniejszych analogowym inputem wartości. Przy 5 litrach wody wyłączany jest alarm, który również swoim zamknięciem otwiera zawór napełniający co powoduje, że przy obu zaworach otwartych stan wody się nie zmienia czym jesteśmy informowani za pomocą outputa.
Wtedy powinniśmy zamknąc zawór napełniający i kontynuować "spuszczanie" wody ze zbiornika.
Gdy stan wody osiągnie 2 litry, jesteśmy ostrzegani alarmem, że stan wody jest minimalny. Alarm ten zamyka zawór spustowy.
********************************************************************************************
Zad 3 Własny pomysł
Program przedstawia działanie dźwigu.
Zadajemy wartość masy jaką ma podnieść dźwig poprzez analogowy komparator po czym uruchamiamy silnik inputem.Jeśli masa za duża(>5kg) to dostajemy komunikat o tym, że masa jest za duża i dźwig nie jest w stanie jej podnieść. Jeśli jednak masa jest wystarczająco mała to dźwig podnosi obiekt. Po minięciu 5 sekund dostajemy komunikat, że nasz obiekt jest podniesiony. Po wyłączeniu silnika nasz obiekt zostaje 5 sekund opuszczany po czym dostajemy komunikat o tym, że obiekt jest opuszczony. Po 10 podniesieniach wyskakuje nam komunikat żeby wysłać dźwig do przeglądu.